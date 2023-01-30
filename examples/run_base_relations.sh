#!/bin/bash

cp pure_base_relations/favorita_base_relations_BATCH.hpp generated/cpp/favorita/favorita_base_relations_BATCH.hpp
cp pure_base_relations/retailer_base_relations_BATCH.hpp generated/cpp/retailer/retailer_base_relations_BATCH.hpp
cp pure_base_relations/housing_base_relations_BATCH.hpp generated/cpp/housing/housing_base_relations_BATCH.hpp


g++ -O3 -DNDEBUG -Wall -Wno-unused-variable -std=c++17 -pedantic src/main.cpp -I ../backend/lib -I src -I src/lib -DBATCH_SIZE=1000 -include generated/cpp/favorita/favorita_base_relations_BATCH.hpp -include src/application/favorita/application_favorita.hpp -o bin/favorita/favorita_base_relations_BATCH_1000

g++ -O3 -DNDEBUG -Wall -Wno-unused-variable -std=c++17 -pedantic src/main.cpp -I ../backend/lib -I src -I src/lib -DBATCH_SIZE=1000 -include generated/cpp/retailer/retailer_base_relations_BATCH.hpp -include src/application/retailer/application_retailer.hpp -o bin/retailer/retailer_base_relations_BATCH_1000

g++ -O3 -DNDEBUG -Wall -Wno-unused-variable -std=c++17 -pedantic src/main.cpp -I ../backend/lib -I src -I src/lib -DBATCH_SIZE=1000 -include generated/cpp/housing/housing_base_relations_BATCH.hpp -include src/application/housing/application_housing.hpp -o bin/housing/housing_base_relations_BATCH_1000


rm -f base_relations.txt
touch base_relations.txt 

./bin/favorita/favorita_base_relations_BATCH_1000 --no-output >> base_relations.txt
./bin/retailer/retailer_base_relations_BATCH_1000 --no-output >> base_relations.txt
./bin/housing/housing_base_relations_BATCH_1000  --no-output >> base_relations.txt




