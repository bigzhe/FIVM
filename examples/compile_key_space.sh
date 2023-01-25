#!/bin/bash

# compile the m3 code to hpp code
# this is not used for the experiments
# cp ./keyspace/retailer_factorized_join_key_BATCH.m3 generated/m3/retailer/retailer_factorized_join_key_BATCH.m3
# ../bin/run_backend.sh -o generated/cpp/retailer/retailer_factorized_join_key_BATCH.hpp generated/m3/retailer/retailer_factorized_join_key_BATCH.m3


# compile the hpp code to binary
cp ./keyspace/retailer_factorized_join_key_BATCH.hpp generated/cpp/retailer/retailer_factorized_join_key_BATCH.hpp
g++ -O3 -DNDEBUG -Wall -Wno-unused-variable -std=c++17 -pedantic src/main.cpp -I ../backend/lib -I src -I src/lib -DBATCH_SIZE=1000 -include generated/cpp/retailer/retailer_factorized_join_key_BATCH.hpp -include src/application/retailer/application_retailer_factorized_join_key.hpp -o bin/retailer/retailer_factorized_join_key_BATCH_1000
