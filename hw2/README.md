# myroot

## Loaded Schooner modules

* GCCcore/9.3.0
* zlib/1.2.11-GCCcore-9.3.0
* binutils/2.34-GCCcore-9.3.0
* iccifort/2020.1.217
* impi/2019.7.217-iccifort-2020.1.217
* iimpi/2020a
* imkl/2020.1.217-iimpi-2020a
* ncurses/6.2-GCCcore-9.3.0
* bzip2/1.0.8-GCCcore-9.3.0
* cURL/7.69.1-GCCcore-9.3.0
* CMake/3.16.4-GCCcore-9.3.0
* python/anaconda3

## Compiling the code

This program may be compiled at the *root* directory using the Makefile with
just a `make` command. This generates "./bin/*.o" files for the implementations
as well as the final executable, "./bin/myroot".

## Running the code

To change the initial "guess" of the root, alter the "./config/params" file.
On the second line of this file, the two components for X0 are to be entered
(separated by spaces). This file is read during runtime, so you don't have to
recompile when changing initial conditions.

From the *root* directory of the files given, run the executable with
`./bin/myroot`.

Unfortunately the executable can't be run from anywhere, because of reading
the "./configs/params" file. This is because the compilers don't seem to like
`<filesystem>`, so I can't get an absolute path, and C++ doesn't use relative
paths from the executable, but rather where the executable is run.

## Elements

* `./config/` : Contains parameter information.

* `./bin/` : Created upon compiling manually or with `make`. Contains
             binaries/executables (the programs).

* `./doc/` : Contains results and the description of the assignment.

* `./src/` : The source code.
