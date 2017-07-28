#!/usr/bin/env bash
set -o errexit
set -o nounset

HOSTBITS=`uname -m | grep -e 32 -e 64 -o`
HOSTOS=`uname -s | tr '[:upper:]' '[:lower:]'`
HOSTDESC=$HOSTOS$HOSTBITS

# Find GNU Make
if type gmake > /dev/null 2>&1 ; then
        gmake=gmake
else
        gmake=make
fi
if ! type vamos > /dev/null 2>&1 ; then
        echo "ERROR: 'vamos' not in PATH"
        exit 1
fi

SCRIPTDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
ASDFTOP="$( readlink -f "${SCRIPTDIR}/..")"

pushd $ASDFTOP/build-gcc/gcc
DEJAGNU=$ASDFTOP/dejagnu/dejagnurc $gmake -j4 check-gcc//vamos/{-m68000,-m68020/-msoft-float}

d=$(./xgcc --version|grep -o "(asdf-.\+)" | tr -d "()")
dd="$SCRIPTDIR/$d-$HOSTDESC"

echo "----"
echo "Copying log files to $dd"

mkdir -p $dd
cp -v testsuite.vamos.-m68000/gcc/gcc.sum $dd/gcc-000.sum
cp -v testsuite.vamos.-m68000/gcc/gcc.log $dd/gcc-000.log
cp -v testsuite.vamos.-m68020.-msoft-float/gcc/gcc.sum $dd/gcc-020soft.sum
cp -v testsuite.vamos.-m68020.-msoft-float/gcc/gcc.log $dd/gcc-020soft.log

popd

