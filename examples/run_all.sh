#!/bin/zsh

# Function to find the next available file name
get_next_filename() {
  local suffix=1

  while [[ -e "output/output_${suffix}.txt" ]]; do
    ((suffix++))
  done

  echo "output/output_${suffix}.txt"
}

# Check if config.txt exists
if [[ -e "output/output.txt" ]]; then
  # Find the next available file name
  new_filename=$(get_next_filename)
  echo $new_filename
  # Rename config.txt to the new file name
  mv "output/output.txt" "$new_filename"
fi

# Read the comma-separated lists from the file run_params.txt
IFS=',' read -rA list1 <<< $(sed -n 1p run_params.txt)
IFS=',' read -rA list2 <<< $(sed -n 2p run_params.txt)

make clean
for item in $list1; do
  echo make DATASET="$item"
  make -j8 DATASET="$item"
done
num_iter=${1:-1}

# Execute the shell script cavier/run.sh" for each element in the first list
for item in $list1; do
  #CAVIER
  echo cavier/run.sh "$item" "-r$num_iter"
  zsh cavier/run.sh "$item" "-r$num_iter" &

  #FIVM
  count=1
  for file in ./bin/"$item/$item"*_BATCH_1000; do
    echo "$file" -r "$num_iter"
    "$file" -r "$num_iter" &

    ((count++))
    if (( count % 2 == 0 )); then
      # Wait for the two background processes to complete
      wait
    fi
  done

  # Wait for any remaining background processes
  wait

done
