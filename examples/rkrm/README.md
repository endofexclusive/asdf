# ABOUT
This directory contains build scripts and patches for the following example
code from *Commodore-Amiga, Inc.*

- Example code from RKRM: Devices, 3rd ed.
- Example code from RKRM: Libraries, 3rd ed.

The patches fix typos and non-standard language constructs in the original
example source code.


# PREPARATION
*GNU Make* is required for the RKRM build scripts.

To download, extract and patch the examples:

        $ make bootstrap
        $ make clean

The above step has to be done only once, but can be re-run to restore the
`src/` directory.


# BUILD
Build all examples:

        $ make all

Clean the build directories:

        $ make clean

Examples can also be built with `$ make` from each of the `src/`
subdirectories.

To enter the *AmigaOS* matrix, issue the following in the rkrm example directory:

        $ make matrix


# RUN
Copy output files to some directory shared with your Amiga, for example:

        $ find . -name "*.hunk" -exec cp {} /mnt/amiga \;

Most of the `.hunk` files are Amiga executables. There is also one font
(`graphics_libraries/text`) and the sample device (`sampledevice`) being built.
See their corresponding directories for usage information.


# NOTES
Some of the examples programs have not been patched and are instead reported as
*FIXME* by the Make scripts. This includes code which alloctes static chip
objects. They could be fixed by allocating the data in public memory and then
copied to a dynamic allocated chip area, or allocated in an assembly file with
chip hunk sections.

Some examples are also marked *UNSUPPORTED*, typically meaning that the example
is not complete.

