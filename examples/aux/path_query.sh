#!/bin/bash

queries=("Q10" "Q15" "Q20")

file_prefix="path"
file_path="/local/scratch/zhang/FIVM/examples/queries/path_twitter/"
app_path="/local/scratch/zhang/FIVM/examples/src/application/path_twitter/"

redirect="$1"  # Get the value of the first input parameter

for query in "${queries[@]}"
do
    command_sql="python3 generate_vo_files.py ${file_prefix} ${query} ego-twitter sql ${redirect}"
    command_txt="python3 generate_vo_files.py ${file_prefix} ${query} ego-twitter vo ${redirect}"
    command_app="python3 generate_vo_files.py ${file_prefix} ${query} ego-twitter app ${redirect}"
    file_name="${file_prefix}-${query}"

    if [[ "$redirect" == "true" ]]; then
        mkdir -p ${file_path}
        ${command_sql} > "${file_path}${file_name}-factorized-join.sql" 
        ${command_txt} > "${file_path}${file_name}.txt"
        ${command_app} > "${app_path}application_${file_name}.hpp" 
    else
        ${command_sql} 
        ${command_txt}
        ${command_app}
    fi

done

# if [[ "$redirect" == "true" ]]; then
#     cd /local/scratch/zhang/FIVM/examples
#     make DATASET=path_twitter
# fi
