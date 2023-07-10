#!/bin/bash

# queries=("Q1" "Q2" "Q3" "Q4" "Q5" "Q6", "Q7")

queries=("Q1" "Q2" "Q3" "Q4" "Q5" "Q6" "Q7")

file_prefix="path"
file_path="/local/scratch/zhang/FIVM/examples/queries/path_twitter/"

redirect="$1"  # Get the value of the first input parameter

for query in "${queries[@]}"
do
    command_sql="python3 generate_vo_files.py ${file_prefix} ${query} ego-twitter sql ${redirect}"
    command_txt="python3 generate_vo_files.py ${file_prefix} ${query} ego-twitter vo ${redirect}"
    file_name="${file_prefix}-${query}"

    if [[ "$redirect" == "true" ]]; then
        mkdir -p ${file_path}
        ${command_sql} > "${file_path}${file_name}.sql"    # Use tee for output, redirecting to file and displaying on the command line
        ${command_txt} > "${file_path}${file_name}.txt"    # Use tee for output, redirecting to file and displaying on the command line
    else
        ${command_sql} 
        ${command_txt}
    fi

done

if [[ "$redirect" == "true" ]]; then
    cd /local/scratch/zhang/FIVM/examples
    make DATASET=path_twitter
fi
