#!/bin/bash

export PATH=/u/user/wyjang/ExpDataAnalysis-PHYS794001/SSB_Code:$PATH

echo "Executing commmand ... ./TopMass_analysis $1 $2"
cd /u/user/wyjang/ExpDataAnalysis-PHYS794001/SSB_Code
./TopMass_analysis $1 $2
