#!/bin/bash
# Wooyoung Jang
# Kyungpook National University
# Date : 2015-12-28
# Last update : 2016-01-13
# Purpose : 
#       This script helps to submit large amount of jobs to Portable Batch System.

#:docstring strstr:
# usage: strstr s1 s2
#
#   strstr echo the substring s2 in s1 and if s2 can not be found in s1 then just do nothing.
# if s2 is a null string then return s1.

###;;;autoload
function strstr ()
{
  # if s2 is a null string then echo s1.
  [ ${#2} -eq 0 ] && { echo "$1", ; return 0; }

  # if s2 can not be found in s1, return 1 without echo
  case "$1" in
    *$2*) ;;
    *) return 1;;
  esac

  # 일치하는 부분부터 끝까지를 떼어 내기 위해 패턴 매칭 사용
  first=${1/$2*/}
  # 그 다음에는 first 에서 일치하지 않는 뒷 부분을 제거
  echo "${1##$first}"
}

# Print out current time
date -u

USRNAME=`whoami`
WORKDIR=`pwd`
RUNSCRIPT="$WORKDIR/run.sh"
OUTDIR="$WORKDIR/output/${1%.list}"
LOGDIR=$OUTDIR/log
ERRDIR=$OUTDIR/err
strstr $1 "MC"
if [ $? -eq 0 ]; then
  TARGETDIR="/u/user/wyjang/ExpDataAnalysis-PHYS794001/SSB_NTuple/13TeV_25ns/MC/${1%.list}"
else
  TARGETDIR="/u/user/wyjang/ExpDataAnalysis-PHYS794001/SSB_NTuple/13TeV_25ns/DATA/${1%.list}"
fi


# Check existence of the RUNSCRIPT.
if [ -e $RUNSCRIPT ]; then
  echo "Pre-run script file is found ... $RUNSCRIPT"
else
  echo "Can not find $RUNSCRIPT"
  exit 1
fi

# Check existence of the list file
if [ -e $1 ]; then
  echo "List file is found ... $1"
else
  echo "Can not find the list file $1"
  exit 2
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
    -F "$irun $OUTFILE $2" \
    $RUNSCRIPT
done < "$1"

echo "End of submission"
