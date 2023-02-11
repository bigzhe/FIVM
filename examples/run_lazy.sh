#!/bin/bash

make DATASET=favorita
make DATASET=retailer
make DATASET=housing

mkdir outputs

echo "Compiling ..."
# list compilation
cp ./pure_generated/favorita_lazy_list_BATCH.m3 ./generated/m3/favorita/favorita_lazy_list_BATCH.m3
cp ./pure_generated/favorita_lazy_fact_BATCH.m3 ./generated/m3/favorita/favorita_lazy_fact_BATCH.m3
cp ./pure_generated/retailer_lazy_list_BATCH.m3 ./generated/m3/retailer/retailer_lazy_list_BATCH.m3
cp ./pure_generated/retailer_lazy_fact_BATCH.m3 ./generated/m3/retailer/retailer_lazy_fact_BATCH.m3
cp ./pure_generated/housing_lazy_list_BATCH.m3 ./generated/m3/housing/housing_lazy_list_BATCH.m3
cp ./pure_generated/housing_lazy_fact_BATCH.m3 ./generated/m3/housing/housing_lazy_fact_BATCH.m3

../bin/run_backend.sh --batch -o generated/cpp/favorita/favorita_lazy_list_BATCH.hpp generated/m3/favorita/favorita_lazy_list_BATCH.m3
g++ -O3 -DNDEBUG -Wall -Wno-unused-variable -std=c++17 -pedantic src/main.cpp -I ../backend/lib -I src -I src/lib -DBATCH_SIZE=1000 -include generated/cpp/favorita/favorita_lazy_list_BATCH.hpp -include src/application/favorita/application_favorita_pure_list.hpp -o bin/favorita/favorita_pure_list_BATCH_1000

../bin/run_backend.sh --batch -o generated/cpp/favorita/favorita_lazy_fact_BATCH.hpp generated/m3/favorita/favorita_lazy_fact_BATCH.m3
g++ -O3 -DNDEBUG -Wall -Wno-unused-variable -std=c++17 -pedantic src/main.cpp -I ../backend/lib -I src -I src/lib -DBATCH_SIZE=1000 -include generated/cpp/favorita/favorita_lazy_fact_BATCH.hpp -include src/application/favorita/application_favorita_pure_fact.hpp -o bin/favorita/favorita_pure_fact_BATCH_1000

../bin/run_backend.sh --batch -o generated/cpp/retailer/retailer_lazy_list_BATCH.hpp generated/m3/retailer/retailer_lazy_list_BATCH.m3
g++ -O3 -DNDEBUG -Wall -Wno-unused-variable -std=c++17 -pedantic src/main.cpp -I ../backend/lib -I src -I src/lib -DBATCH_SIZE=1000 -include generated/cpp/retailer/retailer_lazy_list_BATCH.hpp -include src/application/retailer/application_retailer_pure_list.hpp -o bin/retailer/retailer_pure_list_BATCH_1000

../bin/run_backend.sh --batch -o generated/cpp/retailer/retailer_lazy_fact_BATCH.hpp generated/m3/retailer/retailer_lazy_fact_BATCH.m3
g++ -O3 -DNDEBUG -Wall -Wno-unused-variable -std=c++17 -pedantic src/main.cpp -I ../backend/lib -I src -I src/lib -DBATCH_SIZE=1000 -include generated/cpp/retailer/retailer_lazy_fact_BATCH.hpp -include src/application/retailer/application_retailer_pure_fact.hpp -o bin/retailer/retailer_pure_fact_BATCH_1000

../bin/run_backend.sh --batch -o generated/cpp/housing/housing_lazy_list_BATCH.hpp generated/m3/housing/housing_lazy_list_BATCH.m3
g++ -O3 -DNDEBUG -Wall -Wno-unused-variable -std=c++17 -pedantic src/main.cpp -I ../backend/lib -I src -I src/lib -DBATCH_SIZE=1000 -include generated/cpp/housing/housing_lazy_list_BATCH.hpp -include src/application/housing/application_housing_pure_list.hpp -o bin/housing/housing_pure_list_BATCH_1000

../bin/run_backend.sh --batch -o generated/cpp/housing/housing_lazy_fact_BATCH.hpp generated/m3/housing/housing_lazy_fact_BATCH.m3
g++ -O3 -DNDEBUG -Wall -Wno-unused-variable -std=c++17 -pedantic src/main.cpp -I ../backend/lib -I src -I src/lib -DBATCH_SIZE=1000 -include generated/cpp/housing/housing_lazy_fact_BATCH.hpp -include src/application/housing/application_housing_pure_fact.hpp -o bin/housing/housing_pure_fact_BATCH_1000

for i in 10000000 1000000 100000 10000
do
    # # retailer
    echo "Running retailer experiments for $i"
    ./bin/retailer/retailer_pure_list_BATCH_1000 --no-output -s $i > outputs/retailer_pure_list_BATCH_$i.txt
    ./bin/retailer/retailer_pure_fact_BATCH_1000 --no-output -s $i > outputs/retailer_pure_fact_BATCH_$i.txt

    # favorita
    echo "Running favorita experiments for $i"
    ./bin/favorita/favorita_pure_list_BATCH_1000 --no-output -s $i > outputs/favorita_pure_list_BATCH_$i.txt
    ./bin/favorita/favorita_pure_fact_BATCH_1000 --no-output -s $i > outputs/favorita_pure_fact_BATCH_$i.txt

    # # housing
    echo "Running housing experiments for $i"
    ./bin/housing/housing_pure_list_BATCH_1000 --no-output -s $i > outputs/housing_pure_list_BATCH_$i.txt
    ./bin/housing/housing_pure_fact_BATCH_1000 --no-output -s $i > outputs/housing_pure_fact_BATCH_$i.txt

done
