#!/bin/bash
# Author: Alexandra Joseph

solution_outputs_dir="verify/outputs"
verify_part="$1"

if [ "$verify_part" == "part_1" ]; then
    touch your_soln
    
    make clean && make
    ./mem-sim inputs/sim_1 > your_soln
    diff -swy -W 200 "$solution_outputs_dir"/deliverable_01/sim_1_output your_soln
    read -p "How's it look? They should be identical."

    rm your_soln

elif [ "$verify_part" == "part_2" ]; then
    touch your_soln

    make clean && make

    printf "Checking no flag output\n"
    ./mem-sim inputs/sim_1 > your_soln
    diff -swy -W 200 "$solution_outputs_dir"/deliverable_02/sim_1_output_no_flag your_soln
    read -p "How's it look? They should be identical."
    printf "\n"

    printf "Checking verbose flag output\n"
    ./mem-sim -v inputs/sim_1 > your_soln
    diff -swy -W 200 "$solution_outputs_dir"/deliverable_02/sim_1_output_v_flag your_soln
    read -p "How's it look? They should be identical."
    printf "\n"

    printf "Checking csv flag output\n"
    ./mem-sim -c inputs/sim_1 > your_soln
    diff -sy -W 200 "$solution_outputs_dir"/deliverable_02/sim_1_output_c_flag your_soln
    read -p "How's it look? They should be identical."
    printf "\n"

    rm your_soln

else
    printf "Input part_1 or part_2 after ./verify_output_format.sh.\n"

    printf "Like this: ./verify_output_format.sh part_1 or ./verify_output_format.sh part_2"
fi