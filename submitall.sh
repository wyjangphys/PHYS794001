#!/bin/bash

  ./job_submit_mc.sh TTBar_Sample.list
  ./job_submit_mc.sh DYJetsToLL_M_10To50.list
  ./job_submit_mc.sh DYJetsToLL_M_50.list
  ./job_submit_mc.sh WJetsToLNu.list
  ./job_submit_mc.sh WW.list
  ./job_submit_mc.sh WZ.list
  ./job_submit_mc.sh ZZ.list
  ./job_submit_mc.sh ST_tW_antitop.list
  ./job_submit_mc.sh ST_tW_top.list
  ./job_submit_data.sh MuMu.list
  ./job_submit_data.sh ElEl.list
  ./job_submit_data.sh MuEl.list

# Deprecated
#  ./job_submit_mc.sh TTJets.list
