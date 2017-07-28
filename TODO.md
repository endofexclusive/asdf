# TODO

* Get rid of `amiga.lib` dependency.
* Enable multilibs for `-mshort`, which probably requires fixes in Newlib.
* Generate GCC `proto/` inline includes.
* Implement GCC register function parameters.
* Investigate if we can get rid of ELF `.common` sections and generate `.bss`
  instead?
* Get rid of ELF .comment section at link time.
* Newlib gives compiler warnings for long double functions missing prototypes.
  Seems related to some `MC68881` define in Newlib. What is this?
* Investigate how to get GCC `-coverage` option to work.
* Implement `remove()` instead of `unlink()` in glue layer, if `unlink()` is
  only used by Newlib `remove()` and nowhere else.
* Soft-float seems to be broken. Investigate GCC test suite failures.
* Add support for -fpic
* Support macOS build.
* Support MinGW build.

