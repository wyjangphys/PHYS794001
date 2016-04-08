#!/bin/tcsh

set inputlists = ("TTJets_Signal_1")


foreach i ( $inputlists )
   
   mkdir -p output

   ./TopMass_analysis ${i}.list ssb.root 

end

