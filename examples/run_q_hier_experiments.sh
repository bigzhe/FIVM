#!/bin/bash

for i in 10000000 1000000 100000 10000
do

    # retailer
    ./bin/retailer/retailer_listing_join_q_hier_BATCH_1000 --no-output -s 1000 > outputs/retailer_listing_join_q_hier_BATCH_1000.txt
    ./bin/retailer/retailer_factorized_join_q_hier_BATCH_1000 --no-output -s 1000 > outputs/retailer_factorized_join_q_hier_BATCH_1000.txt

    # favorita
    ./bin/favorita/favorita_listing_join_q_hier_BATCH_1000 --no-output -s 1000 > outputs/favorita_listing_join_q_hier_BATCH_1000.txt
    ./bin/favorita/favorita_factorized_join_q_hier_BATCH_1000 --no-output -s 1000 > outputs/favorita_factorized_join_q_hier_BATCH_1000.txt

    # housing
    ./bin/housing/housing_factorized_join_BATCH_1000 --no-output -s 1000 > outputs/housing_factorized_join_BATCH_1000.txt 
    ./bin/housing/housing_listing_join_BATCH_1000 --no-output -s 1000 > outputs/housing_listing_join_BATCH_1000.txt


done