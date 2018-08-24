#!/usr/bin/env bash
set -o errexit
set -o nounset

SCRIPTDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
ASDFTOP="$( readlink -f "${SCRIPTDIR}/..")"

PREFIX=$ASDFTOP/opt/asdf
TARGET=m68k-asdf-elf
pushd $ASDFTOP > /dev/null
GITDESC=`git describe --tags --dirty | cut -c 2-`
popd > /dev/null
HOSTBITS=`uname -m | grep -e 32 -e 64 -o`
HOSTOS=`uname -s | tr '[:upper:]' '[:lower:]'`
HOSTDESC=$HOSTOS$HOSTBITS
PKGVERSION="asdf-$GITDESC"
ARCHBASE=${PKGVERSION}-${HOSTDESC}
PROGPREFIX=asdf-

CFGDEF=
CFGDEF="$CFGDEF --target=$TARGET"
CFGDEF="$CFGDEF --with-arch=m68k"
CFGDEF="$CFGDEF --with-cpu=68000"
CFGDEF="$CFGDEF --prefix=$PREFIX"
CFGDEF="$CFGDEF --with-sysroot"
CFGDEF="$CFGDEF --with-pkgversion=$PKGVERSION"
CFGDEF="$CFGDEF --docdir=$PREFIX/doc"
CFGDEF="$CFGDEF --disable-plugin"

CFGHOST=
CFGHOST="$CFGHOST --disable-nls"
CFGHOST="$CFGHOST --disable-shared"
if [ $HOSTOS = freebsd ]; then
        CFGHOST="$CFGHOST --with-gmp=/usr/local"
fi

CFLAGS_FOR_TARGET="-O2"; export CFLAGS_FOR_TARGET
CFLAGS_FOR_TARGET="$CFLAGS_FOR_TARGET -DMALLOC_PROVIDED"
CFLAGS_FOR_TARGET="$CFLAGS_FOR_TARGET -DCLOCK_PROVIDED"
CFLAGS_FOR_TARGET="$CFLAGS_FOR_TARGET -DHAVE_RENAME"
# Newlib fixup for rename() -> _rename() (!)
CFLAGS_FOR_TARGET="$CFLAGS_FOR_TARGET -D_COMPILING_NEWLIB"
export CFLAGS_FOR_TARGET

PATH="${PREFIX}/bin/:${PATH}"; export PATH
if type gmake > /dev/null 2>&1 ; then
        gmake=gmake
else
        gmake=make
fi

if type md5 > /dev/null 2>&1 ; then
        md5=md5
else
        md5=md5sum
fi

if type gcc > /dev/null 2>&1 ; then
        buildcc=gcc
        buildld=gcc
elif type clang > /dev/null 2>&1 ; then
        buildcc=clang
        buildld=clang
fi

verb() {
        echo VERB "$@"
        eval "$@"
}

genlinks() {
        verb pushd $PREFIX/bin
        for file in $TARGET-*; do
                verb ln -s -f $file `echo $file | sed s/${TARGET}-/${PROGPREFIX}/g`
        done
        verb popd
}

# Bootstrap prefix directory
pre() {
        verb mkdir -p $PREFIX/bin $PREFIX/doc
        verb $gmake -C $ASDFTOP/ext clean extdep
        verb $ASDFTOP/ext/install-ndk.sh
        verb "git archive --format=tar HEAD:extradist/ | tar xvf - -C $PREFIX"
        verb ln -s -f $ASDFTOP/ext/ndk-3.9 $PREFIX/$TARGET/sys-root/
        verb mkdir -p $PREFIX/$TARGET/sys-root/usr/include/asdf
        verb "(cd $ASDFTOP/scripts ; ./bits.tcl > $PREFIX/$TARGET/sys-root/usr/include/asdf/custombits.h)"
}

build_vlink() {
        verb mkdir -p $ASDFTOP/build-vlink/obj

        verb pushd $ASDFTOP/build-vlink
        verb $gmake \
                -C $ASDFTOP/ext/vlink \
                CC=$buildcc \
                LD=$buildld \
                TARGET=$ASDFTOP/build-vlink/vlink \
                DIR=$ASDFTOP/build-vlink/obj
        verb install -c $ASDFTOP/build-vlink/vlink $PREFIX/bin/${PROGPREFIX}vlink
        # Link in the fresh vlink in a directory searched early by GCC,
        # possibly via GCC_EXEC_PREFIX environment used for example when
        # running test suite in GCC build directory before installation.
        # Otherwise (an outdated) vlink in PATH could be selected, which is not
        # what we want.
        verb mkdir -p $PREFIX/$TARGET/bin
        verb ln -f $PREFIX/bin/${PROGPREFIX}vlink $PREFIX/$TARGET/bin/${PROGPREFIX}vlink
        if [ $op_pdf -ne 0 ]; then
                verb texi2dvi -p -o $ASDFTOP/build-vlink/vlink.pdf $ASDFTOP/ext/vlink/vlink.texi
                verb install -c -m 644 $ASDFTOP/build-vlink/vlink.pdf $PREFIX/doc/vlink.pdf
        fi
        verb popd
}

build_vasm() {
        verb mkdir -p $ASDFTOP/build-vasm/obj

        verb pushd $ASDFTOP/build-vasm
        verb $gmake \
                -C $ASDFTOP/ext/vasm \
                CC=$buildcc \
                LD=$buildld \
                CPU=m68k SYNTAX=mot \
                PRE=$ASDFTOP/build-vasm/obj/ \
                VASMEXE=$ASDFTOP/build-vasm/vasm \
                VOBJDMPEXE=$ASDFTOP/build-vasm/vobjdump
        verb install -c $ASDFTOP/build-vasm/vasm $PREFIX/bin/${PROGPREFIX}vasm
        verb install -c $ASDFTOP/build-vasm/vobjdump $PREFIX/bin/${PROGPREFIX}vobjdump
        if [ $op_pdf -ne 0 ]; then
                verb texi2dvi -p -o $ASDFTOP/build-vasm/vasm.pdf $ASDFTOP/ext/vasm/doc/vasm.texi
                verb install -c -m 644 $ASDFTOP/build-vasm/vasm.pdf $PREFIX/doc/vasm.pdf
        fi
        verb popd
}

build_binutils() {
        verb mkdir -p $ASDFTOP/build-binutils

        verb pushd $ASDFTOP/build-binutils
        verb $ASDFTOP/ext/binutils/configure \
                $CFGDEF \
                $CFGHOST \
                --disable-gdb
        verb $gmake -j 3 all
        verb $gmake install
        if [ $op_pdf -ne 0 ]; then
                verb $gmake -j 4 pdf
                verb $gmake install-pdf
        fi
        verb popd
        verb genlinks
}

build_gcc1() {
        verb mkdir -p $ASDFTOP/build-gcc

        verb pushd $ASDFTOP/build-gcc
        gcc_cv_ld_sysroot=no; export gcc_cv_ld_sysroot
        verb $ASDFTOP/ext/gcc/configure \
                $CFGDEF \
                $CFGHOST \
                --enable-languages=c \
                --disable-libssp \
                --disable-tls \
                --disable-libgomp \
                --disable-threads \
                --disable-zlib \
                --enable-decimal-float=no \
                --disable-lto \
                --disable-lto-plugin \
                --disable-libquadmath \
                --disable-intl \
                --without-headers \
                --with-newlib
        verb $gmake -j 4 all-host
        verb $gmake install-host
        if [ $op_pdf -ne 0 ]; then
                verb $gmake -j 4 pdf-host
                verb $gmake install-pdf-host
        fi
        verb popd
        verb genlinks
}

build_newlib() {
        verb mkdir -p $ASDFTOP/build-newlib

        verb pushd $ASDFTOP/build-newlib
        # For more newlib configuration options, see newlib/newlib/README
        verb $ASDFTOP/ext/newlib/configure \
                $CFGDEF \
                --disable-newlib-multithread \
                --disable-newlib-supplied-syscalls \
                --enable-newlib-io-c99-formats \
                --enable-newlib-io-long-long \
                --disable-newlib-atexit-dynamic-alloc \
                --enable-newlib-global-atexit \
                --disable-newlib-fseek-optimization \
                --disable-shared \
                --enable-static \
                --disable-libgloss
        verb $gmake -j 4 all
        verb $gmake install
        if [ $op_pdf -ne 0 ]; then
                verb $gmake -j 4 pdf
                verb $gmake install-pdf
        fi
        verb popd
}

build_gcc2() {
        verb pushd $ASDFTOP/build-gcc
        verb $gmake -j 4 all-target
        verb $gmake install-target
        verb popd
}

build_glue() {
        verb mkdir -p $ASDFTOP/build-glue
        verb pushd $ASDFTOP/build-glue
        verb $gmake \
                -C $ASDFTOP/glue/ \
                OUTDIR=$PWD \
                INSTALLDIR=$PREFIX/$TARGET/lib \
                all install
        verb popd
}

dist() {
        verb "git archive --format=tar HEAD examples | tar xvf - -C $PREFIX"
        verb pushd $PREFIX
        verb echo "Stripping binaries..."
        verb "find $TARGET/bin bin libexec -type f -print -exec strip {} \;"
        verb popd

        verb rm -rf $PREFIX/$TARGET/sys-root/ndk*
        verb cp $ASDFTOP/ext/install-ndk.sh $PREFIX/$TARGET/sys-root/
        verb cp $ASDFTOP/README.md $PREFIX/

        archname=${ARCHBASE}.tar.gz

        verb tar czf $ASDFTOP/$archname -C $ASDFTOP/opt asdf
        verb pushd $ASDFTOP
        verb "$md5 $archname > $ASDFTOP/$archname.md5"
        verb popd

        # Put back NDK link so we can use toolchain in build tree.
        verb ln -s -f $ASDFTOP/ext/ndk-3.9 $PREFIX/$TARGET/sys-root/
}

usage() {
        echo "Usage: $0 [OPTION]... WHAT..."
        echo ""
        echo "OPTION:"
        echo "  --nopdf         - Do not generate PDF files"
        echo "WHAT:"
        echo "  pre             - Bootstrap and fetch external archives"
        echo "  vtools          - vlink, vasm"
        echo "  binutils        - Assembler and tools"
        echo "  gcc1            - Cross compiler"
        echo "  newlib          - C library"
        echo "  gcc2            - GCC target (libgcc)"
        echo "  glue            - AmigaOS<->Newlib layer and startup code"
        echo "  all             - all above"
        echo "  dist            - Create binary distribution archive"
}

echo "HOSTDESC: $HOSTDESC"
echo "GITDESC:  $GITDESC"
if [ "$#" -lt 1 ]; then
        usage
        exit 0
fi

do_pre=0
do_vtools=0
do_binutils=0
do_gcc1=0
do_newlib=0
do_gcc2=0
do_glue=0
do_dist=0
do_usage=0
op_pdf=1
op_extra=0

while [ "$#" -gt 0 ]; do
        key=$1
        case $key in
                --nopdf)    op_pdf=0;;
                --extra)    op_extra="$2"; shift;;
                pre)        do_pre=1;;
                vtools)     do_vtools=1;;
                binutils)   do_binutils=1;;
                gcc1)       do_gcc1=1;;
                newlib)     do_newlib=1;;
                gcc2)       do_gcc2=1;;
                glue)       do_glue=1;;
                dist)       do_dist=1;;
                all)
                        do_pre=1
                        do_vtools=1
                        do_binutils=1
                        do_gcc1=1
                        do_newlib=1
                        do_gcc2=1
                        do_glue=1
                        ;;
                *)
                        echo "unknown argument $1"
                        exit 1
                        break
                        ;;
        esac
        shift
done

mkdir -p log

if [ $do_pre -ne 0 ]; then
        pre > >(tee log/pre.stdout) 2> >(tee log/pre.stderr >&2)
fi

if [ $do_vtools -ne 0 ]; then
        build_vlink > >(tee log/vlink.stdout) 2> >(tee log/vlink.stderr >&2)
        build_vasm > >(tee log/vasm.stdout) 2> >(tee log/vasm.stderr >&2)
fi
if [ $do_binutils -ne 0 ]; then
        build_binutils > >(tee log/binutils.stdout) 2> >(tee log/binutils.stderr >&2)
fi
if [ $do_gcc1 -ne 0 ]; then
        build_gcc1 > >(tee log/gcc1.stdout) 2> >(tee log/gcc1.stderr >&2)
fi
if [ $do_newlib -ne 0 ]; then
        build_newlib > >(tee log/newlib.stdout) 2> >(tee log/newlib.stderr >&2)
fi
if [ $do_gcc2 -ne 0 ]; then
        build_gcc2 > >(tee log/gcc2.stdout) 2> >(tee log/gcc2.stderr >&2)
fi
if [ $do_glue -ne 0 ]; then
        build_glue > >(tee log/glue.stdout) 2> >(tee log/glue.stderr >&2)
fi
if [ $do_dist -ne 0 ]; then
        dist > >(tee log/dist.stdout) 2> >(tee log/dist.stderr >&2)
fi

tar czf $ASDFTOP/$ARCHBASE.log.tar.gz -C $ASDFTOP log

sleep 1
echo DONE "($0)"

