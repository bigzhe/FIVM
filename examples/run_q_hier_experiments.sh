#!/bin/bash


# retailer
./bin/retailer/retailer_listing_join_q_hier_BATCH_1000 --no-output -s 1000 > outputs/retailer_listing_join_q_hier_BATCH_1000.txt
./bin/retailer/retailer_factorized_join_q_hier_BATCH_1000 --no-output -s 1000 > outputs/retailer_factorized_join_q_hier_BATCH_1000.txt

# TODO: housing

# TODO: favorita

