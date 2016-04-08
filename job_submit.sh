#!/bin/bash
# Wooyoung Jang
# Kyungpook National University
# Date : 2015-12-28
# Last update : 2016-01-13
# Purpose : 
#       This script helps to submit large amount of jobs to Portable Batch System.

# Print out current time
date -u

USRNAME=`whoami`
WORKDIR=`pwd`
RUNSCRIPT="$WORKDIR/run.sh"
OUTDIR="$WORKDIR/output/${1%.list}"
LOGDIR=$OUTDIR/log
ERRDIR=$OUTDIR/err
TARGETDIR="/u/user/wyjang/ExpDataAnalysis-PHYS794001/SSB_NTuple/13TeV_25ns/MC/${1%.list}"

# Check existence of the RUNSCRIPT.
if [ -e $RUNSCRIPT ]; then
  echo "Pre-run script file is found ... $RUNSCRIPT"
else
  echo "Can not find $RUNSCRIPT"
fi

# Check the existence of the output directory.
if [ -d $OUTDIR ]; then
  echo "Output files will be located in $OUTDIR."
else
  mkdir $OUTDIR
  echo "Warning: $OUTDIR is made to store output files."
fi

# Check the existence of the output sub-directory.
if [ -d $OUTDIR/${1%.list} ]; then
  echo "Submit for ${1%.list} in $OUTDIR/${1%.list}"
else
  mkdir $OUTDIR/${1%.list}
  echo "Warning: $OUTDIR/${1%.list} is made to store output files."
fi

# Check the existence of the log-file directory.
if [ -d $LOGDIR ]; then
    echo "Log files will be stored at $LOGDIR"
else
  mkdir $LOGDIR
  echo "Warning: $LOGDIR is made to store log files."
fi

# Check the existence of the error-file directory.
if [ -d $ERRDIR ]; then
  echo "Error logs will be stored at $ERRDIR"
else
  mkdir $ERRDIR
  echo "Warning: $ERRDIR is made to store error logs."
fi

# Loop over the whole target files to submit job
while read irun
do
  # Define the name of log, error and output file names.
  LOGFILE=$LOGDIR${irun#$TARGETDIR}.log
  ERRFILE=$ERRDIR${irun#$TARGETDIR}.err
  OUTFILE=$OUTDIR${irun#$TARGETDIR}

  # Execute job submission command.
  echo /usr/bin/qsub -q knu -o $LOGFILE -e $ERRFILE -l walltime=24:00:00,cput=24:00:00 -N $irun -F \"$irun $OUTFILE\" $RUNSCRIPT
  /usr/bin/qsub -q knu \
  -o $LOGFILE -e $ERRFILE \
  -l walltime=24:00:00,cput=24:00:00 \
    -N $irun \
    -F "$irun $OUTFILE" \
    $RUNSCRIPT
done < "$1"

echo "End of submission"
