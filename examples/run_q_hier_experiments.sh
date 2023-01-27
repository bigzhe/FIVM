#!/bin/bash

for i in 10000000 1000000 100000 10000
do
    # retailer
    echo "Running retailer experiments for $i"
    ./bin/retailer/retailer_listing_join_q_hier_BATCH_1000 --no-output -s $i > outputs/retailer_listing_join_q_hier_$i.txt
    ./bin/retailer/retailer_factorized_join_q_hier_BATCH_1000 --no-output -s $i > outputs/retailer_factorized_join_q_hier_BATCH_$i.txt

    # favorita
    echo "Running favorita experiments for $i"
    ./bin/favorita/favorita_listing_join_q_hier_BATCH_1000 --no-output -s $i > outputs/favorita_listing_join_q_hier_BATCH_$i.txt
    ./bin/favorita/favorita_factorized_join_q_hier_BATCH_1000 --no-output -s $i > outputs/favorita_factorized_join_q_hier_BATCH_$i.txt

    # housing
    echo "Running housing experiments for $i"
    ./bin/housing/housing_factorized_join_BATCH_1000 --no-output -s $i > outputs/housing_factorized_join_BATCH_$i.txt 
    ./bin/housing/housing_listing_join_BATCH_1000 --no-output -s $i > outputs/housing_listing_join_BATCH_$i.txt


done