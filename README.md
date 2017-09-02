# ASDF - Amiga Software Development Framework

## Introduction
*ASDF* is a cross-compiler toolchain for *AmigaOS 1.2*, based on *GCC*, *vlink*
and the *Newlib* C standard library. Supported languages are *C* and
*assembly*.


### Overview
The idea is to use recent *GCC* and *Binutils* version to generate object code
in ELF format and then link with *vlink* to generate Amiga Hunk executable
files for *AmigaOS* (680x0).

Included components:

*   [GNU Compiler Collection 7.1](https://gcc.gnu.org)
    For compiling C source code. GCC is licensed under GPL.

*   [GNU Binutils 2.28](https://www.gnu.org/software/binutils/)
    Includes assembler and various ELF file utilities. Binutils is licensed
    under GPL.

*   [vlink portable multi-format linker](http://sun.hasenbraten.de/vlink/)

    *vlink* is a key component of this toolchain with its excellent
    multi-format support which allows for linking ELF object files to Amiga
    Hunk executables.

    *vlink* is copyright Frank Wille. See the *vlink* web page or the document
    `vlink.pdf` for more information on license conditions.

*   [vasm portable and retargetable assembler](http://sun.hasenbraten.de/vasm/)

    *vasm* is copyright Frank Wille. See the *vasm* web page or the document
    `vasm.pdf` for more information on license conditions.

*   [Newlib C library](https://sourceware.org/newlib/)

    *newlib* is an implementation of the C standard library intended for use on
    embedded systems.

    The *newlib* source code is licensed under many different (open) licenses.
    See `newlib/COPYING.NEWLIB` in the Newlib source distribution for details.

*   [ASDF glue layer](glue) Implements the Newlib portability layer for *AmigaOS*
    and run-time startup code. Licensed under FreeBSD license.

*   *Scripts and patches*


Additional components, not distributed with the toolchain:

*   [Native Developer Kit for AmigaOS 3.9](http://www.haage-partner.de/download/AmigaOS/NDK39.lha)
    contains support files for developing *AmigaOS* applications. Available for
    download from the copyright holders web-site, but with unknown distribution
    conditions. *Copyright 1985-2001 Amiga, Inc.*


### Goals
This toolchain will probably not generate the fastest or smallest Amiga
binaries. The goals are rather:

* *Developer friendliness*
  * *GCC 7* lint/warnings
  * *Binutils* object file tools
* *Standard compliance*
  * *Newlib* is serious about the standard
* *Correctness*
  * *GCC* test suite.


## Install
ASDF is currently distributed in source code format.


### Building from source
*ASDF* is known to build successfully in the following environments:

* *Debian GNU/Linux 8.8 (jessie)*
* *FreeBSD 11.1*


The following software has to be preinstalled in the system:

* curl
* lha
* Bash
* Tcl
* Texinfo
* Tex Live (`pdflatex`)
* GNU make
* Compiler for build system (GCC or Clang)
* GCC build dependencies (see the document titled *Installing GCC*)

To Install prerequisites in *FreeBSD 11.1*:
`$ pkg install curl lha bash tcl86 texinfo texlive-full gmake mpc`

Use the following command to build *ASDF* from source:

        $ ./scripts/build.sh all dist

Optionally, `--nopdf`, can be given on the command line to prevent building
documentation in PDF format, and thus eliminating the `pdflatex` dependency.

The toolchain is installed in the `opt/asdf/` directory of the repository
top-level directory. This installation directory can be moved to any suitable
location or soft-linked. `opt/asdf/bin/` should be added to the search path
with something like this:

        $ PATH="$PWD/opt/asdf/bin:$PATH"

A `tar.gz` archive is created for the installation and build log files are
located in the `log/` directory.


#### GCC test suite
For information on how to run the GCC test suite with
[vamos](https://github.com/cnvogelg/amitools), see the file
[dejagnu/README](dejagnu/README).


## Usage
The GCC front-end `m68k-asdf-elf-gcc` can be used for most operations,
including compiling, assembling and linking.

To compile the source file `main.c` into an (ELF) object file named `main.o`:

        $ m68k-asdf-elf-gcc -O2 -c main.c -o main.o

Link to an Amiga Hunk executable file with:

        $ m68k-asdf-elf-gcc hello.o -o hello.hunk

To inspect how the compiler translates C code into assembly:

        $ m68k-asdf-elf-gcc -O2 -S -fverbose-asm myfunc.c -o myfunc.s

Assembly source code can be assembled with the GNU assembler *gas*:

        $ m68k-asdf-elf-as myfunc.s -o myfunc.o

or *vasm*:

        $ asdf-vasm -phxass -Felf  myfunc.s -o myfunc_elf.o
        $ asdf-vasm -phxass -Fhunk myfunc.s -o myfunc_hunk.o


### GCC Options
Standard GCC (m68k) options can be used:

*   `-O0`, `-O1`, `-O2`, `-O3`, `-Os`, `-Og`, etc.

    Control optimization.

*   `-Wall`, `-Wextra`, `-pedantic`, etc.

    Request compiler warnings.

*   `-mcpu=68020`, `-mcpu=68040`, `-mcpu=68060`, etc.

    Generate code for a specific processor. `-mcpu=68000` is used by default.

*   `-msoft-float`

    Do not use hardware floating-point instructions.

*   `-std=89`, `-std=c99`, etc.

    Specify language standard.

*   `-fno-omit-frame-pointer`

    Put frame pointer in register `a6` in function prologues.
    `-fomit-frame-pointer` is used by default.

*   `-Wl,option`

    Pass an `option` to the linker (`vlink`).

*   `-S`

    Stop compiler before assembling. Can be used together with the
    `-fverbose-asm` option to annotate the assembly code with C source.

*   `-mshort`

    Use 16-bit integers (instead of 32-bit which is the default). Objects
    compiled for 16-bit integers should not be mixed with code compiled for
    32-bit.


Options specific to *ASDF*:

* `-qnstart`

    Link application with *nano startup* code for small applications which do
    no require system realated C standard library services. This options is
    applicable to linking only.


### Multilibs
Multilib version of *Newlib* and *libgcc* are provided for
68000/68020/68040/68060, with and without soft-float. To list all available
multilibs, use:

    $ m68k-asdf-elf-gcc -print-multi-lib

Adding the `-v` option when compiling or linking gives more information on
search locations for headers and libraries.


### Optional tool prefix
Tools prefixed with `m68k-asdf-elf-` in the `asdf/bin` directory have short
names, prefixed with `asdf-`. These are just soft links to the default names.

    $ ls -l asdf-objdump | cut -d ' ' -f 9-
    asdf-objdump -> m68k-asdf-elf-objdump


### Documentation
Documentation for the tools and C library is available in PDF format in the
`opt/asdf/doc/` directory. Manual pages are also available, and should be
available when `PATH` has been setup as described above. For example:

    $ man m68k-asdf-elf-size


## Run-time environment
### Standard startup
By default, applications are linked with a startup object named `ustart.o` (`u`
for *micro*). It prepares a C run-time environment for use with *Newlib*, with
support for:

*   Dynamic memory allocation

    `malloc()`, `realloc()`, `free()`, etc. Memory is automatically deallocated
    at return from `main()` and when `exit()` or `abort()` is called.

*   File I/O

    `<stdio.h>` functions such as `fopen()`, `fwrite()`, `fgetc()`, `fseek()`,
    etc. Files opened with `<stdio.h>` are closed on return from `main()` and
    when calling `exit()` or `abort()`.

*   Time related functions

    `<time.h>` functions such as `time()` and a limited `clock()`.
    `dos.library/DateStamp()` is used internally.

*   `atexit()`

By default, the C run-time is highly compatible with the C standard library.

The GCC front-end has been configured with knowledge of paths to NDK 3.9
includes and linker libraries (`amiga.lib` and `debug.lib`).

Standard startup is implemented in [ustart.s](glue/ustart.s) and
[ustart_main.c](glue/ustart_main.c).

### Nano startup
An option to the full C run-time environment startup code is to link with the
`nstart.o` startup object, which is selected with the GCC link option
`-qnstart`.

The purpose of the nano startup is to support small applications.

`nstart.o` does the following:

* Initializes `SysBase`
* Calls `main()`
* Returns to the shell when `main()` returns

*AmigaOS* library functions can be called as usual with `amiga.lib` stubs and
Amiga library prototypes in `<clib/[lib]_protos.h>`.

Some notable limitations when using the `nstart.o` startup code:

* `argc` is `0` and `argv[argc]` is `NULL`.
* File I/O using `<stdio.h>` is not supported. `dos.library` can be used.
* C library dynamic memory allocation is not supported when using the nano
  startup. `exec.library` functions such as `AllocMem()` and `FreeMem()`, can
  be used instead. Note also that many *Newlib* functions call dynamic memory
  functions internally, which means that functions such as `snprintf()` can not
  be used with the nano startup and will likely end up in linker errors.
* `exit()`, `abort()` and `atexit()` will not work.

Nano startup is implemented in [nstart.s](glue/nstart.s).

### Custom startup
To create a custom startup module, link the application with `-nostdlib` and
provide your own startup object file as the first object to the linker.
[Startup code from *Commodore-Amiga, Inc.*](http://aminet.net/dev/src/RKRM_Libs_prgs.lha)
can be used.


### Default compiler options
The following compiler options are implied (GCC specs):

* `-fno-omit-frame-pointer` which prevents the compiler from reserving an
  address register for use as frame pointer. This can be reverted with
  `-fno-omit-frame-pointer`.
* `-fleading-underscore` which prefixes all symbol names with an underscore
  character, as per the *Amiga* symbol name convention. Assembly code is free
  to use non-prefixed symbol names, but these can not be referenced from C
  code.
* `-isystem [toolchain]/m68k-asdf-elf/sys-root/include_h` for direct access to
  NDK includes.

For more details, see

    $ m68k-asdf-elf-gcc -dumpspecs


## Examples
The [examples](examples) directory contains examples on how the toolchain can
be used.  See the `README` files in each subdirectory for more information.


## Toolchain limitations
* Starting applications from *Workbench* is not supported.
* Soft-float seems to be broken for the `long double` type.
* GCC option `-fpic`, to generate position-independent code, does not work.
* Inline prototypes for AmigaOS `proto/` are not yet available. However, see
  [examples/takesys/xproto.h](examples/takesys/xproto.h) how it can be
  implemented. `<clib/[lib]_protos.h>` and `amiga.lib` stubs are supported.
* `getenv()` and `setenv()` is available but the namespace is isolated from
  *AmigaOS*.
* `signal()` and `raise()` does nothing.
* `clock()` does not tell the truth. The function returns the amount of time
  that has elapsed since some point in the past. Thus it can be used to measure
  wall-clock time. The value can be divided by `CLOCKS_PER_SEC` to obtain the
  number of seconds.


## Development information
For information on how to rebuild selected parts of the toolchain, see
[scripts/build.sh](scripts/build.sh).

A TODO list is available in [TODO.md](TODO.md).

