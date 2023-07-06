#ifndef TPCH_2_HPP
#define TPCH_2_HPP
#include "../src/basefiles/application_throughputs.hpp"
#include <any>
#include <random>
#include <type_traits>
std::random_device rd;
std::mt19937 rng(rd());
const std::string dataPath = "data/tpch_unordered10";
void Application::init_relations() {
    clear_relations();

		#if defined(RELATION_LINEITEM_STATIC)
        relations.push_back(std::unique_ptr<IRelation>(
            new EventDispatchableRelation<lineitem_entry>(
                "lineitem", dataPath + "/lineitem.tbl", '|', true,
                [](dbtoaster::data_t& data) {
                    return [&](lineitem_entry& t) {
                        data.on_insert_lineitem(t);
                    };
                }
        )));
    #elif defined(RELATION_LINEITEM_DYNAMIC) && defined(BATCH_SIZE)
        typedef const std::vector<DELTA_lineitem_entry>::iterator CIteratorlineitem;
        relations.push_back(std::unique_ptr<IRelation>(
            new BatchDispatchableRelation<DELTA_lineitem_entry>(
                "lineitem", dataPath + "/lineitem.tbl", '|', false,
                [](dbtoaster::data_t& data) {
                    return [&](CIteratorlineitem& begin, CIteratorlineitem& end) {
                        data.on_batch_update_lineitem(begin, end);
                    };
                }
        )));
    #elif defined(RELATION_LINEITEM_DYNAMIC)
        relations.push_back(std::unique_ptr<IRelation>(
            new EventDispatchableRelation<lineitem_entry>(
                "lineitem", dataPath + "/lineitem.tbl", '|', false,
                [](dbtoaster::data_t& data) {
                    return [&](lineitem_entry& t) {
                        data.on_insert_lineitem(t);
                    };
                }
        )));
    #endif

		#if defined(RELATION_PARTSUPP_STATIC)
        relations.push_back(std::unique_ptr<IRelation>(
            new EventDispatchableRelation<partsupp_entry>(
                "partsupp", dataPath + "/partsupp.tbl", '|', true,
                [](dbtoaster::data_t& data) {
                    return [&](partsupp_entry& t) {
                        data.on_insert_partsupp(t);
                    };
                }
        )));
    #elif defined(RELATION_PARTSUPP_DYNAMIC) && defined(BATCH_SIZE)
        typedef const std::vector<DELTA_partsupp_entry>::iterator CIteratorpartsupp;
        relations.push_back(std::unique_ptr<IRelation>(
            new BatchDispatchableRelation<DELTA_partsupp_entry>(
                "partsupp", dataPath + "/partsupp.tbl", '|', false,
                [](dbtoaster::data_t& data) {
                    return [&](CIteratorpartsupp& begin, CIteratorpartsupp& end) {
                        data.on_batch_update_partsupp(begin, end);
                    };
                }
        )));
    #elif defined(RELATION_PARTSUPP_DYNAMIC)
        relations.push_back(std::unique_ptr<IRelation>(
            new EventDispatchableRelation<partsupp_entry>(
                "partsupp", dataPath + "/partsupp.tbl", '|', false,
                [](dbtoaster::data_t& data) {
                    return [&](partsupp_entry& t) {
                        data.on_insert_partsupp(t);
                    };
                }
        )));
    #endif

		#if defined(RELATION_PART_STATIC)
        relations.push_back(std::unique_ptr<IRelation>(
            new EventDispatchableRelation<part_entry>(
                "part", dataPath + "/part.tbl", '|', true,
                [](dbtoaster::data_t& data) {
                    return [&](part_entry& t) {
                        data.on_insert_part(t);
                    };
                }
        )));
    #elif defined(RELATION_PART_DYNAMIC) && defined(BATCH_SIZE)
        typedef const std::vector<DELTA_part_entry>::iterator CIteratorpart;
        relations.push_back(std::unique_ptr<IRelation>(
            new BatchDispatchableRelation<DELTA_part_entry>(
                "part", dataPath + "/part.tbl", '|', false,
                [](dbtoaster::data_t& data) {
                    return [&](CIteratorpart& begin, CIteratorpart& end) {
                        data.on_batch_update_part(begin, end);
                    };
                }
        )));
    #elif defined(RELATION_PART_DYNAMIC)
        relations.push_back(std::unique_ptr<IRelation>(
            new EventDispatchableRelation<part_entry>(
                "part", dataPath + "/part.tbl", '|', false,
                [](dbtoaster::data_t& data) {
                    return [&](part_entry& t) {
                        data.on_insert_part(t);
                    };
                }
        )));
    #endif

}

struct Measurement {
 std::string query_name;
 long update_time;
std::string relations;
std::string free_variables;
 long enumeration_time;
 long size_output; Measurement(std::string query_name, long update_time, std::string relations) : query_name(query_name), update_time(update_time), relations(relations), free_variables(""), enumeration_time(0L), size_output(0L) {}
};

std::ofstream& operator<<(std::ofstream& os, const Measurement *measurement) {
#if MAP_TYPE == 1 
 auto map_info = "Hybrid";
 #elif MAP_TYPE == 2 
 auto map_info = "Hash";
 #elif MAP_TYPE == 3 
 auto map_info = "BTree";
 #elif MAP_TYPE == 4 
 auto map_info = "CustomHash" + std::to_string(MAXSIZE) + ", " + std::to_string(MAXREGULAR) + ", " + std::to_string(GROWTH_RATE)  ;
 #endif
    os << measurement->query_name << " | "
       << map_info << " | "
       << measurement->update_time << " | "
       << measurement->enumeration_time << " | "
       << measurement->size_output << " | "
       << measurement->free_variables << " | "
       << measurement->relations << "| " << BATCH_SIZE;
    return os;
}

void write_to_config(std::vector<Measurement*>* measurements, std::ofstream& measurements_file, std::string relations){
    measurements_file << "tpch_2|FIVM|"<<"tpch_unordered10|" << "|" << relations << ":";for (size_t i = 0; i < measurements->size(); i++) {
            measurements_file << measurements->at(i);
            if (i != measurements->size() - 1) {
                measurements_file << " : ";
            }
        }    measurements_file << "\n";
}struct DELTA_Q2_entry {
    std::any partkey;
    std::any suppkey;
    std::any orderkey;
    std::any l_quantity;
    std::any ps_availqty;
    std::any p_name;
    long combined_value;
};

long enumerate_Q2(dbtoaster::data_t &data, bool print_result, bool count_view_size, Measurement *measure) {
    size_t output_size = 0; 
std::ofstream view_sizes_file;
if(count_view_size) {
view_sizes_file = std::ofstream("sizes/tpch_2-Q2_Q2_view_sizes.csv");
view_sizes_file << "partkey_lpp1, " << 0<< std::endl;
view_sizes_file << "suppkey_lp1, " << data.get_V_suppkey_lp1().primary_index->count()<< std::endl;
view_sizes_file << "orderkey_l1, " << data.get_V_orderkey_l1().primary_index->count()<< std::endl;
view_sizes_file << "ps_availqty_p1, " << data.get_V_ps_availqty_p1().primary_index->count()<< std::endl;
view_sizes_file << "p_name_p1, " << data.get_V_p_name_p1().primary_index->count()<< std::endl;
view_sizes_file.close();
}
Stopwatch enumeration_timer;
enumeration_timer.restart();
long propagation_time = 0;
long enumeration_time = 0;
std::ofstream output_file;
 if (print_result) output_file.open ("output/Q2.csv");
using partkey_type = std::remove_reference_t<decltype(std::get<0>(std::declval<decltype(data.get_V_partkey_lpp1().store)::value_type>().first))>;
using suppkey_type = std::remove_reference_t<decltype(std::get<0>(std::declval<decltype(data.get_V_suppkey_lp1().head->__av.store)::value_type>().first))>;
using orderkey_type = std::remove_reference_t<decltype(std::get<0>(std::declval<decltype(data.get_V_orderkey_l1().head->__av.store)::value_type>().first))>;
using l_quantity_type = std::remove_reference_t<decltype(std::get<1>(std::declval<decltype(data.get_V_orderkey_l1().head->__av.store)::value_type>().first))>;
using ps_availqty_type = std::remove_reference_t<decltype(std::get<0>(std::declval<decltype(data.get_V_ps_availqty_p1().head->__av.store)::value_type>().first))>;
using p_name_type = std::remove_reference_t<decltype(std::get<0>(std::declval<decltype(data.get_V_p_name_p1().head->__av.store)::value_type>().first))>;
std::vector<DELTA_Q2_entry> update;
update.reserve(1000);const auto& rel0 = data.get_V_partkey_lpp1();
for (const auto &t0 : rel0.store) {
auto partkey = std::get<0>(t0.first);
auto payload_0 = t0.second;
std::vector<std::tuple<suppkey_type, long, std::vector<std::tuple<orderkey_type, l_quantity_type, long>>*, std::vector<std::tuple<ps_availqty_type, long>>*>>* part_1= new std::vector<std::tuple<suppkey_type, long, std::vector<std::tuple<orderkey_type, l_quantity_type, long>>*, std::vector<std::tuple<ps_availqty_type, long>>*>>();
V_suppkey_lp1_entry e1;
const auto& rel1 = data.get_V_suppkey_lp1().getValueOrDefault(e1.modify(partkey));
for (const auto &t1 : rel1.store) {
auto suppkey = std::get<0>(t1.first);
auto payload_1 = t1.second;
std::vector<std::tuple<orderkey_type, l_quantity_type, long>>* part_2= new std::vector<std::tuple<orderkey_type, l_quantity_type, long>>();
V_orderkey_l1_entry e2;
const auto& rel2 = data.get_V_orderkey_l1().getValueOrDefault(e2.modify(partkey,suppkey));
for (const auto &t2 : rel2.store) {
auto orderkey = std::get<0>(t2.first);
auto l_quantity = std::get<1>(t2.first);
auto payload_2 = t2.second;
part_2->emplace_back(std::make_tuple(orderkey, l_quantity, payload_2));}
std::vector<std::tuple<ps_availqty_type, long>>* part_3= new std::vector<std::tuple<ps_availqty_type, long>>();
V_ps_availqty_p1_entry e3;
const auto& rel3 = data.get_V_ps_availqty_p1().getValueOrDefault(e3.modify(partkey,suppkey));
for (const auto &t3 : rel3.store) {
auto ps_availqty = std::get<0>(t3.first);
auto payload_3 = t3.second;
part_3->emplace_back(std::make_tuple(ps_availqty, payload_3));}
part_1->emplace_back(std::make_tuple(suppkey, payload_1, part_2, part_3));}
std::vector<std::tuple<p_name_type, long>>* part_4= new std::vector<std::tuple<p_name_type, long>>();
V_p_name_p1_entry e4;
const auto& rel4 = data.get_V_p_name_p1().getValueOrDefault(e4.modify(partkey));
for (const auto &t4 : rel4.store) {
auto p_name = std::get<0>(t4.first);
auto payload_4 = t4.second;
part_4->emplace_back(std::make_tuple(p_name, payload_4));}
for(const auto &t1 : *part_1){
auto &suppkey = std::get<0>(t1);
auto payload_1 = std::get<1>(t1);
auto &part_2 = std::get<2>(t1);
auto &part_3 = std::get<3>(t1);
for(const auto &t2 : *part_2){
auto &orderkey = std::get<0>(t2);
auto &l_quantity = std::get<1>(t2);
auto payload_2 = std::get<2>(t2);
for(const auto &t3 : *part_3){
auto &ps_availqty = std::get<0>(t3);
auto payload_3 = std::get<1>(t3);
for(const auto &t4 : *part_4){
auto &p_name = std::get<0>(t4);
auto payload_4 = std::get<1>(t4);
update.emplace_back(DELTA_Q2_entry{partkey, suppkey, orderkey, l_quantity, ps_availqty, p_name, 1 * 1 * payload_2 * payload_3 * payload_4});
if (output_size % BATCH_SIZE == BATCH_SIZE -1){ update.clear();}
if (print_result) { output_file << partkey <<"|"<<suppkey <<"|"<<orderkey <<"|"<<l_quantity <<"|"<<ps_availqty <<"|"<<p_name << std::endl;}
output_size++;
}}}}for(auto t1 : *part_1){
auto part_2 = std::get<2>(t1);
delete part_2;
auto part_3 = std::get<3>(t1);
delete part_3;
}
delete part_1;
delete part_4;
}
enumeration_timer.stop();
enumeration_time += enumeration_timer.elapsedTimeInMilliSeconds();
std::cout << "enumeration time Q2: " << enumeration_time << "ms"<< std::endl;
measure->enumeration_time = enumeration_time;
if (update.size() > 0) {
std::uniform_int_distribution<int> uni(0,update.size()-1);
volatile auto dummy = update.at(uni(rng));
std::cout << "dummy: " << dummy.combined_value << std::endl;}
output_file.close();
measure->size_output = output_size;
measure->free_variables = "partkey,suppkey,orderkey,l_quantity,ps_availqty,p_name";
std::cout << "Q2: " << output_size << std::endl;
return propagation_time;
}

void Application::on_snapshot(dbtoaster::data_t& data) {
    on_end_processing(data, false, false);
}

void Application::on_begin_processing(dbtoaster::data_t& data) {
}

void Application::on_end_processing(dbtoaster::data_t& data, bool print_result, bool count_view_size) {

    cout << endl << "Enumerating factorized join result... " << endl;

std::string relation_list = "";
  for(auto& rel: relations){
    relation_list += rel->get_name() + ",";
  }
  relation_list = relation_list.substr(0, relation_list.size() - 1);    std::vector<Measurement*> measurements;
    size_t output_size = 0; 
    long updating_Q2 = 0 + dynamic_multiplexer.updating_times.find("lineitem")->second + dynamic_multiplexer.updating_times.find("partsupp")->second + dynamic_multiplexer.updating_times.find("part")->second ;
    Measurement measure_Q2 = Measurement("Q2", updating_Q2, "lineitem,partsupp,part");
    cout << "Enumerating Q2... " << endl;
  long Q2_propagation = enumerate_Q2(data, print_result, count_view_size, &measure_Q2);
    measurements.push_back(&measure_Q2);
int query_Q2_count = 0;
std::ofstream measurements_file("output/output.txt", std::ios::app | std::ios::out);
write_to_config(&measurements, measurements_file, relation_list);
measurements_file.close();
dynamic_multiplexer.updating_times.clear();}
 #endif