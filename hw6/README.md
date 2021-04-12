# vtop1

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

This program may be compiled from the root directory with `make vtop1`. This
generates the ".o" file as well as the final executable "./bin/vtop1".

## Running the code

There is a basic Slurm script within "jobs/" called "run_vtop1.slurm". It's
best to `cd` into "jobs/" first so that the output doesn't fall into the root
directory. The script may then be run with `sbatch run_vtop1.slurm`.

## Elements

* `./bin/` : Created upon compiling manually or with `make`. Contains
             binaries/executables (the programs).

* `./doc/` : Contains the description of the assignment.

* `./jobs/` : Contains the script that schedules the program to run using
              Slurm, as well as the resulting output.

* `./src/` : The source code.
