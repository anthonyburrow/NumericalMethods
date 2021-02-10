# myquadtratic

## Compiling the code

### Problem 1: "./bin/myquadratic_single"

The executable for this single-implementation executable can be compiled in the
*root* directory with just
`mkdir ./bin ; g++ ./src/myquadratic_single.cpp -o ./bin/myquadratic_single`.

### Problems 2-4: "./bin/myquadratic"

This program may be compiled at the *root* directory using the Makefile with
just a `make` command. This generates "./bin/*.o" files for the implementations
as well as the final executable, "./bin/myquadratic".

## Running the code

To change the equation for which a solution may be found, alter the
"./config/params" file. This same file is used for both executables. On the
third line of this file, the coefficients are to be entered (separated by spaces,
from highest to lowest order). This file is read during runtime, so you don't
have to recompile when changing equations.

From the *root* directory, run the executable with either `./bin/myquadratic_single`
or `./bin/myquadratic`.

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
