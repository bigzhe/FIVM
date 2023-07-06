###### tpch 2 ####

# Cavier 

g++ -O3 -DNDEBUG -Wall -Wno-unused-variable -std=c++17 -pedantic -Wno-unused-local-typedefs src/main.cpp -I ../backend/lib -I src -I src/lib -I src/TLXInstall/include -L src/TLXInstall/lib -ltlx -DBATCH_SIZE=1000 -include throughputs/cavier_tpch_2*_unordered10_throughputs.hpp -include throughputs/application_cavier_tpch_2*_unordered10_throughputs.hpp -o bin/tpch_2/CAVIER_tpch_2*_unordered10_BATCH_1000 -DMAXREGULAR=10000 -DMAXSIZE=15000000
./bin/tpch_2/CAVIER_tpch_2*_unordered10_BATCH_1000 -r 1 > output/CAVIER_tpch_2.txt

# FIVM Q2
g++ -O3 -DNDEBUG -Wall -Wno-unused-variable -std=c++17 -pedantic -Wno-unused-local-typedefs src/main.cpp -I ../backend/lib -I src -I src/lib -I src/TLXInstall/include -L src/TLXInstall/lib -ltlx -DBATCH_SIZE=1000 -include throughputs/fivm_tpch_2*10-Q2_BATCH.hpp -include throughputs/application_fivm_tpch_2*10-Q2_BATCH.hpp -o bin/tpch_2/FIVM_tpch_2*1-Q2_BATCH_1000; -DMAXREGULAR=10000 -DMAXSIZE=15000000
./bin/tpch_2/FIVM_tpch_2*1-Q2_BATCH_1000 -r 1 > output/FIVM_tpch_2_Q2.txt

# FIVM Q1
g++ -O3 -DNDEBUG -Wall -Wno-unused-variable -std=c++17 -pedantic -Wno-unused-local-typedefs src/main.cpp -I ../backend/lib -I src -I src/lib -I src/TLXInstall/include -L src/TLXInstall/lib -ltlx -DBATCH_SIZE=1000 -include throughputs/fivm_tpch_2*10-Q1_BATCH.hpp -include throughputs/application_fivm_tpch_2*10-Q1_BATCH.hpp -o bin/tpch_2/FIVM_tpch_2*1-Q1_BATCH_1000; -DMAXREGULAR=10000 -DMAXSIZE=15000000
./bin/tpch_2/FIVM_tpch_2*1-Q1_BATCH_1000 -r 1 > output/FIVM_tpch_2_Q1.txt


###### retailer 1 ####

