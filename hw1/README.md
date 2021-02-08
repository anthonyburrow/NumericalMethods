# myquadtratic

## Compiling the code

This program may be compiled at the root directory using the Makefile with
just a `make` command. This generates "./bin/*.o" files for the implementations
as well as the final executable, "./bin/myquadratic.exe".

## Running the code

To change the equation for which a solution may be found, alter the
"./config/params" file. On the third line of this file, the coefficients are to
be entered (separated by spaces, from highest to lowest order). This file is
read during runtime, so you don't have to recompile when changing equations.

From the *root* directory, run the executable with `./bin/myquadratic`.

Unfortunately the executable can't be run from anywhere, because of reading
the "./configs/params" file. This is because the compilers don't seem to like
`<filesystem>`, so I can't get an absolute path, and C++ doesn't use relative
paths from the executable, but rather where the executable is run.

## Elements

* `./config/` : Contains parameter information.

* `./bin/` : Created upon `make`. Contains binaries/executables (the program).

* `./doc/` : Contains results and the description of the assignment.

* `./src/` : The source code.
