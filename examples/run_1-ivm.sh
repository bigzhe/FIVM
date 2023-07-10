#!/bin/bash

path="1-ivm"
queries=("Q10-1-IVM-sum-prod") 
# queries=("Q10-1-IVM-sum-prod" "Q15" "Q20")

mkdir -p "generated/cpp/${path}"

for query in "${queries[@]}"
do
    echo "Compiling ${query}..."
    ../bin/run_backend.sh --batch -o generated/cpp/${path}/path-${query}-BATCH.hpp generated/m3/${path}/path-${query}.m3

    echo g++ -O3 -DNDEBUG -Wall -Wno-unused-variable -std=c++17 -pedantic src/main.cpp -I ../backend/lib -I src -I src/lib -DBATCH_SIZE=1000 -include generated/cpp/${path}/path-${query}_BATCH.hpp -include src/application/path_twitter/application_path-Q10.hpp -o bin/${path}/path-${query}_BATCH_1000
    g++ -O3 -DNDEBUG -Wall -Wno-unused-variable -std=c++17 -pedantic src/main.cpp -I ../backend/lib -I src -I src/lib -DBATCH_SIZE=1000 -include generated/cpp/${path}/path-${query}_BATCH.hpp -include src/application/path_twitter/application_path-Q10.hpp -o bin/${path}/path-${query}_BATCH_1000

done