#!/bin/bash

  ./job_submit.sh TTBar_Sample.list
  ./job_submit.sh DYJetsToLL_M_10To50.list
  ./job_submit.sh DYJetsToLL_M_50.list
  ./job_submit.sh WJetsToLNu.list
  ./job_submit.sh WW.list
  ./job_submit.sh WZ.list
  ./job_submit.sh ZZ.list
  ./job_submit.sh ST_tW_antitop.list
  ./job_submit.sh ST_tW_top.list
  ./job_submit_data.sh MuMu.list
  ./job_submit_data.sh ElEl.list
  ./job_submit_data.sh MuEl.list
