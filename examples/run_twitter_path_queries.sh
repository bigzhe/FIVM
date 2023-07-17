#!/bin/bash

# queries=("Q10" "Q15" "Q20")
queries=("Q10-sum-prod")
dataset="twitter"

rm -rf "generated/m3/path_${dataset}"
rm -rf "generated/cpp/path_${dataset}"
rm -rf "bin/path_${dataset}"

mkdir -p "generated/m3/path_${dataset}"
mkdir -p "generated/cpp/path_${dataset}"
mkdir -p "bin/path_${dataset}"

for query in "${queries[@]}"
do
    echo "Compiling ${query}..."
    q_base=$(echo "$query" | cut -d '-' -f 1)

    m3_file="generated/m3/path_${dataset}/path-${query}.m3"
    backend_hpp="generated/cpp/path_${dataset}/path-${query}_BATCH.hpp"
    application_hpp="src/application/path_${dataset}/application_path-${q_base}.hpp"
    binary_name="bin/path_${dataset}/path-${query}_BATCH_1000"

    echo ../bin/run_frontend.sh --batch -o "$m3_file" "queries/path_${dataset}/path-${query}.sql"
    ../bin/run_frontend.sh --batch -o "$m3_file" "queries/path_${dataset}/path-${query}.sql"

    echo ../bin/run_backend.sh --batch -o "$backend_hpp" "$m3_file"
    ../bin/run_backend.sh --batch -o "$backend_hpp" "$m3_file"

    echo g++ -O3 -DNDEBUG -Wall -Wno-unused-variable -std=c++17 -pedantic src/main.cpp -I ../backend/lib -I src -I src/lib -DBATCH_SIZE=1000 -include "$backend_hpp" -include "$application_hpp" -o "$binary_name"
    g++ -O3 -DNDEBUG -Wall -Wno-unused-variable -std=c++17 -pedantic src/main.cpp -I ../backend/lib -I src -I src/lib -DBATCH_SIZE=1000 -include "$backend_hpp" -include "$application_hpp" -o "$binary_name"

    ./bin/path_${dataset}/path-${query}_BATCH_1000 > "output/path_${dataset}/path-${query}_BATCH_1000.txt"
done


