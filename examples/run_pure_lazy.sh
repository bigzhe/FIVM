#!/bin/bash

# experiments for the pure lazy approach

# for i in ()
retailer_max=$(wc -l ./data/retailer/Inventory.tbl | tr -s " " | cut -d" " -f2)
housing_max=$(wc -l ./data/housing-1-normalised/House.tbl | tr -s " " | cut -d" " -f2) 
favorita_max=$(wc -l ./data/favorita/Sales.csv | tr -s " " | cut -d" " -f2)

rm -rf outputs
mkdir outputs

for i in 10000000 1000000 100000 
do
    # retailer
    echo "Running retailer experiments for $i"
    rm -f ./outputs/retailer_static_$i.txt 
    touch ./outputs/retailer_static_$i.txt
    for ((j=i; j<=retailer_max; j+=i))
    do
        echo "Batch j = $j/$retailer_max"
        rm -rf ./data/retailer-static
        mkdir ./data/retailer-static
        # cp head -$j to retailer-static
        head -$j ./data/retailer/Census.tbl > ./data/retailer-static/Census.tbl
        head -$j ./data/retailer/Inventory.tbl > ./data/retailer-static/Inventory.tbl
        head -$j ./data/retailer/Item.tbl > ./data/retailer-static/Item.tbl
        head -$j ./data/retailer/Location.tbl > ./data/retailer-static/Location.tbl
        head -$j ./data/retailer/Weather.tbl > ./data/retailer-static/Weather.tbl

        # run retailer
        ./bin/retailer/retailer_static_BATCH_1000 --no-output >> ./outputs/retailer_static_$i.txt

        # clean up
        rm -rf ./data/retailer-static
    done



    # housing
    echo "Running housing experiments for $i"
    rm -f ./outputs/housing_static_$i.txt
    touch ./outputs/housing_static_$i.txt
    for ((j=i; j<=housing_max; j+=i))
    do
        echo "Batch j = $j/$retailer_max"
        rm -rf ./data/housing-1-normalised-static
        mkdir ./data/housing-1-normalised-static
        # cp head -$i to data/housing-1-normalised-static
        head -$j ./data/housing-1-normalised/Demographics.tbl > ./data/housing-1-normalised-static/Demographics.tbl
        head -$j ./data/housing-1-normalised/House.tbl > ./data/housing-1-normalised-static/House.tbl
        head -$j ./data/housing-1-normalised/Institution.tbl > ./data/housing-1-normalised-static/Institution.tbl
        head -$j ./data/housing-1-normalised/Restaurant.tbl > ./data/housing-1-normalised-static/Restaurant.tbl
        head -$j ./data/housing-1-normalised/Shop.tbl > ./data/housing-1-normalised-static/Shop.tbl
        head -$j ./data/housing-1-normalised/Transport.tbl > ./data/housing-1-normalised-static/Transport.tbl

        # run housing
        ./bin/housing/housing_static_BATCH_1000 --no-output >> ./outputs/housing_static_$i.txt

        # clean up
        rm -rf ./data/housing-1-normalised-static
    done


    # favorita
    echo "Running favorita experiments for $i"
    rm -f ./outputs/favorita_static_$i.txt
    touch ./outputs/favorita_static_$i.txt
    for ((j=i; j<=favorita_max; j+=i))
    do
        echo "Batch j = $j/$retailer_max"
        rm -rf ./data/favorita-static
        mkdir ./data/favorita-static
        # cp head -$i to data/favorita-static
        head -$j ./data/favorita/Transactions.csv > ./data/favorita-static/Transactions.csv
        head -$j ./data/favorita/Holidays.csv > ./data/favorita-static/Holidays.csv
        head -$j ./data/favorita/Items.csv > ./data/favorita-static/Items.csv
        head -$j ./data/favorita/Oil.csv > ./data/favorita-static/Oil.csv
        head -$j ./data/favorita/Sales.csv > ./data/favorita-static/Sales.csv
        head -$j ./data/favorita/Stores.csv > ./data/favorita-static/Stores.csv

        # run favorita
        ./bin/favorita/favorita_static_BATCH_1000 --no-output >> ./outputs/favorita_static_$i.txt

        # clean up
        rm -rf ./data/favorita-static
    done

done



