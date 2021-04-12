#!/bin/bash
######################################################################
## Filename:      simple_slurm.slurm
## Author:        Eddie Baron <baron@nhn.ou.edu>
## Created at:    Wed Aug 17 15:37:09 2005
## Modified at:   Mon Mar 15 17:09:24 2021
## Modified by:   Eddie Baron <baron@ou.edu>
## Version:       
## Description:   
######################################################################
# begin batch header
#SBATCH --job-name=vtop1_job
#SBATCH --ntasks=20
#SBATCH --ntasks-per-node=20
#SBATCH --exclusive
#SBATCH --time=0:09:59
#SBATCH --mail-type=FAIL,END
#SBATCH --mail-user=anthony.r.burrow-1@ou.edu
#SBATCH -p debug
#SBATCH --output=vtop1_job_%J.out
#SBATCH --error=vtop1_job_%J.err
# end batch header

if [ "$SLURM_TASK_PID" != "" ] ; then
  cd $SLURM_SUBMIT_DIR
  JOB_NAME=$SLURM_JOB_NAME.$SLURM_JOB_ID.$$
  JOB_ID=$SLURM_JOB_ID
  ARC=`uname`
else
  echo "Need to run this in slurm queue"
  exit 1
fi

setenv() { export $1="$2";}
se() { var=$1; shift; setenv $var "$*";}

# Run on the Lustre file system
se TMPDIR $SCRATCH/tmp
[ ! -d $TMPDIR ] && mkdir -p $TMPDIR
WORKDIR=$TMPDIR/$$
[ ! -d $WORKDIR ] && mkdir -p $WORKDIR
se SAVEDIR $SLURM_SUBMIT_DIR

cd $WORKDIR
PROGRAM=vtop1
TARGET=$SLURM_SUBMIT_DIR/../bin/$PROGRAM

# Run the program
echo "Calc begins at: " $(date)  >> output.$JOB_ID
cp $TARGET ./$PROGRAM
mpirun -np 4 ./$PROGRAM >> output.$JOB_ID
echo "Calc ends at: " $(date)  >> output.$JOB_ID

# Copy data back to SAVEDIR
cp output.$JOB_ID $SAVEDIR

# Clean up
cd $SAVEDIR
[ -d $WORKDIR ] && rm -r $WORKDIR
