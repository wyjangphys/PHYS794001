#!/bin/bash

export PATH=/u/user/wyjang/ExpDataAnalysis-PHYS794001/SSB_Code:$PATH

echo "Executing commmand ... ./TTBarXSec $1 $2"
cd /u/user/wyjang/ExpDataAnalysis-PHYS794001/SSB_Code
./TTBarXSec $1 $2
