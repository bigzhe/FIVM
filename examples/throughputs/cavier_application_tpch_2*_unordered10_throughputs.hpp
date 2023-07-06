#ifndef TPCH_2_HPP
#define TPCH_2_HPP
#include "../src/basefiles/application_throughputs.hpp"
#include <any>
#include <random>
#include <type_traits>
std::random_device rd;
std::mt19937 rng(rd());
const std::string dataPath = "data/tpch_unordered10";
void Application::init_relations()
{
    clear_relations();

#if defined(RELATION_LINEITEM_STATIC)
    relations.push_back(std::unique_ptr<IRelation>(
        new EventDispatchableRelation<lineitem_entry>(
            "lineitem", dataPath + "/lineitem.tbl", '|', true,
            [](dbtoaster::data_t &data)
            {
                return [&](lineitem_entry &t)
                {
                    data.on_insert_lineitem(t);
                };
            })));
#elif defined(RELATION_LINEITEM_DYNAMIC) && defined(BATCH_SIZE)
    typedef const std::vector<DELTA_lineitem_entry>::iterator CIteratorlineitem;
    relations.push_back(std::unique_ptr<IRelation>(
        new BatchDispatchableRelation<DELTA_lineitem_entry>(
            "lineitem", dataPath + "/lineitem.tbl", '|', false,
            [](dbtoaster::data_t &data)
            {
                return [&](CIteratorlineitem &begin, CIteratorlineitem &end)
                {
                    data.on_batch_update_lineitem(begin, end);
                };
            })));
#elif defined(RELATION_LINEITEM_DYNAMIC)
    relations.push_back(std::unique_ptr<IRelation>(
        new EventDispatchableRelation<lineitem_entry>(
            "lineitem", dataPath + "/lineitem.tbl", '|', false,
            [](dbtoaster::data_t &data)
            {
                return [&](lineitem_entry &t)
                {
                    data.on_insert_lineitem(t);
                };
            })));
#endif

#if defined(RELATION_PARTSUPP_STATIC)
    relations.push_back(std::unique_ptr<IRelation>(
        new EventDispatchableRelation<partsupp_entry>(
            "partsupp", dataPath + "/partsupp.tbl", '|', true,
            [](dbtoaster::data_t &data)
            {
                return [&](partsupp_entry &t)
                {
                    data.on_insert_partsupp(t);
                };
            })));
#elif defined(RELATION_PARTSUPP_DYNAMIC) && defined(BATCH_SIZE)
    typedef const std::vector<DELTA_partsupp_entry>::iterator CIteratorpartsupp;
    relations.push_back(std::unique_ptr<IRelation>(
        new BatchDispatchableRelation<DELTA_partsupp_entry>(
            "partsupp", dataPath + "/partsupp.tbl", '|', false,
            [](dbtoaster::data_t &data)
            {
                return [&](CIteratorpartsupp &begin, CIteratorpartsupp &end)
                {
                    data.on_batch_update_partsupp(begin, end);
                };
            })));
#elif defined(RELATION_PARTSUPP_DYNAMIC)
    relations.push_back(std::unique_ptr<IRelation>(
        new EventDispatchableRelation<partsupp_entry>(
            "partsupp", dataPath + "/partsupp.tbl", '|', false,
            [](dbtoaster::data_t &data)
            {
                return [&](partsupp_entry &t)
                {
                    data.on_insert_partsupp(t);
                };
            })));
#endif

#if defined(RELATION_ORDERS_STATIC)
    relations.push_back(std::unique_ptr<IRelation>(
        new EventDispatchableRelation<orders_entry>(
            "orders", dataPath + "/orders.tbl", '|', true,
            [](dbtoaster::data_t &data)
            {
                return [&](orders_entry &t)
                {
                    data.on_insert_orders(t);
                };
            })));
#elif defined(RELATION_ORDERS_DYNAMIC) && defined(BATCH_SIZE)
    typedef const std::vector<DELTA_orders_entry>::iterator CIteratororders;
    relations.push_back(std::unique_ptr<IRelation>(
        new BatchDispatchableRelation<DELTA_orders_entry>(
            "orders", dataPath + "/orders.tbl", '|', false,
            [](dbtoaster::data_t &data)
            {
                return [&](CIteratororders &begin, CIteratororders &end)
                {
                    data.on_batch_update_orders(begin, end);
                };
            })));
#elif defined(RELATION_ORDERS_DYNAMIC)
    relations.push_back(std::unique_ptr<IRelation>(
        new EventDispatchableRelation<orders_entry>(
            "orders", dataPath + "/orders.tbl", '|', false,
            [](dbtoaster::data_t &data)
            {
                return [&](orders_entry &t)
                {
                    data.on_insert_orders(t);
                };
            })));
#endif

#if defined(RELATION_PART_STATIC)
    relations.push_back(std::unique_ptr<IRelation>(
        new EventDispatchableRelation<part_entry>(
            "part", dataPath + "/part.tbl", '|', true,
            [](dbtoaster::data_t &data)
            {
                return [&](part_entry &t)
                {
                    data.on_insert_part(t);
                };
            })));
#elif defined(RELATION_PART_DYNAMIC) && defined(BATCH_SIZE)
    typedef const std::vector<DELTA_part_entry>::iterator CIteratorpart;
    relations.push_back(std::unique_ptr<IRelation>(
        new BatchDispatchableRelation<DELTA_part_entry>(
            "part", dataPath + "/part.tbl", '|', false,
            [](dbtoaster::data_t &data)
            {
                return [&](CIteratorpart &begin, CIteratorpart &end)
                {
                    data.on_batch_update_part(begin, end);
                };
            })));
#elif defined(RELATION_PART_DYNAMIC)
    relations.push_back(std::unique_ptr<IRelation>(
        new EventDispatchableRelation<part_entry>(
            "part", dataPath + "/part.tbl", '|', false,
            [](dbtoaster::data_t &data)
            {
                return [&](part_entry &t)
                {
                    data.on_insert_part(t);
                };
            })));
#endif
}

struct Measurement
{
    std::string query_name;
    long update_time;
    std::string relations;
    std::string free_variables;
    long enumeration_time;
    long size_output;
    Measurement(std::string query_name, long update_time, std::string relations) : query_name(query_name), update_time(update_time), relations(relations), free_variables(""), enumeration_time(0L), size_output(0L) {}
};

std::ofstream &operator<<(std::ofstream &os, const Measurement *measurement)
{
#if MAP_TYPE == 1
    auto map_info = "Hybrid";
#elif MAP_TYPE == 2
    auto map_info = "Hash";
#elif MAP_TYPE == 3
    auto map_info = "BTree";
#elif MAP_TYPE == 4
    auto map_info = "CustomHash" + std::to_string(MAXSIZE) + ", " + std::to_string(MAXREGULAR) + ", " + std::to_string(GROWTH_RATE);
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

void write_to_config(std::vector<Measurement *> *measurements, std::ofstream &measurements_file, std::string relations)
{
    measurements_file << "tpch_2|CAVIER|"
                      << "tpch_unordered10|"
                      << "|" << relations << ":";
    for (size_t i = 0; i < measurements->size(); i++)
    {
        measurements_file << measurements->at(i);
        if (i != measurements->size() - 1)
        {
            measurements_file << " : ";
        }
    }
    measurements_file << "\n";
}
long enumerate_Q2(dbtoaster::data_t &data, bool print_result, bool count_view_size, Measurement *measure)
{
    size_t output_size = 0;
    std::ofstream view_sizes_file;
    if (count_view_size)
    {
        view_sizes_file = std::ofstream("sizes/tpch_2_Q2_view_sizes.csv");
        view_sizes_file << "lineitempartpartsupp_Q2, " << 0 << std::endl;
        view_sizes_file << "lineitempartsupp_Q2, " << data.get_V_lineitempartsupp_Q2().primary_index->count() << std::endl;
        view_sizes_file << "partsupp_Q2, " << data.get_V_partsupp_Q2().primary_index->count() << std::endl;
        view_sizes_file << "lineitem_Q2, " << data.get_V_lineitem_Q2().primary_index->count() << std::endl;
        view_sizes_file << "part_Q2, " << data.get_V_part_Q2().primary_index->count() << std::endl;
        view_sizes_file.close();
    }
    Stopwatch enumeration_timer;
    enumeration_timer.restart();
    Stopwatch propagation_timer;
    long propagation_time = 0;
    long enumeration_time = 0;
    std::ofstream output_file;
    if (print_result)
        output_file.open("output/Q2.csv");
    using PARTKEY_type = std::remove_reference_t<decltype(std::get<0>(std::declval<decltype(data.get_V_lineitempartpartsupp_Q2().store)::value_type>().first))>;
    using SUPPKEY_type = std::remove_reference_t<decltype(std::get<0>(std::declval<decltype(data.get_V_lineitempartsupp_Q2().head->__av.store)::value_type>().first))>;
    using PS_AVAILQTY_type = std::remove_reference_t<decltype(std::get<0>(std::declval<decltype(data.get_V_partsupp_Q2().head->__av.store)::value_type>().first))>;
    using ORDERKEY_type = std::remove_reference_t<decltype(std::get<0>(std::declval<decltype(data.get_V_lineitem_Q2().head->__av.store)::value_type>().first))>;
    using L_QUANTITY_type = std::remove_reference_t<decltype(std::get<1>(std::declval<decltype(data.get_V_lineitem_Q2().head->__av.store)::value_type>().first))>;
    using P_NAME_type = std::remove_reference_t<decltype(std::get<0>(std::declval<decltype(data.get_V_part_Q2().head->__av.store)::value_type>().first))>;
    std::vector<DELTA_Q2_entry> update;
    update.reserve(1000);
    const auto &rel0 = data.get_V_lineitempartpartsupp_Q2();
    for (const auto &t0 : rel0.store)
    {
        auto PARTKEY = std::get<0>(t0.first);
        auto payload_0 = t0.second;
        std::vector<std::tuple<SUPPKEY_type, long, std::vector<std::tuple<PS_AVAILQTY_type, long>> *, std::vector<std::tuple<ORDERKEY_type, L_QUANTITY_type, long>> *>> *part_1 = new std::vector<std::tuple<SUPPKEY_type, long, std::vector<std::tuple<PS_AVAILQTY_type, long>> *, std::vector<std::tuple<ORDERKEY_type, L_QUANTITY_type, long>> *>>();
        V_lineitempartsupp_Q2_entry e1;
        const auto &rel1 = data.get_V_lineitempartsupp_Q2().getValueOrDefault(e1.modify(PARTKEY));
        for (const auto &t1 : rel1.store)
        {
            auto SUPPKEY = std::get<0>(t1.first);
            auto payload_1 = t1.second;
            std::vector<std::tuple<PS_AVAILQTY_type, long>> *part_2 = new std::vector<std::tuple<PS_AVAILQTY_type, long>>();
            V_partsupp_Q2_entry e2;
            const auto &rel2 = data.get_V_partsupp_Q2().getValueOrDefault(e2.modify(PARTKEY, SUPPKEY));
            for (const auto &t2 : rel2.store)
            {
                auto PS_AVAILQTY = std::get<0>(t2.first);
                auto payload_2 = t2.second;
                part_2->emplace_back(std::make_tuple(PS_AVAILQTY, payload_2));
            }
            std::vector<std::tuple<ORDERKEY_type, L_QUANTITY_type, long>> *part_3 = new std::vector<std::tuple<ORDERKEY_type, L_QUANTITY_type, long>>();
            V_lineitem_Q2_entry e3;
            const auto &rel3 = data.get_V_lineitem_Q2().getValueOrDefault(e3.modify(PARTKEY, SUPPKEY));
            for (const auto &t3 : rel3.store)
            {
                auto ORDERKEY = std::get<0>(t3.first);
                auto L_QUANTITY = std::get<1>(t3.first);
                auto payload_3 = t3.second;
                part_3->emplace_back(std::make_tuple(ORDERKEY, L_QUANTITY, payload_3));
            }
            part_1->emplace_back(std::make_tuple(SUPPKEY, payload_1, part_2, part_3));
        }
        std::vector<std::tuple<P_NAME_type, long>> *part_4 = new std::vector<std::tuple<P_NAME_type, long>>();
        V_part_Q2_entry e4;
        const auto &rel4 = data.get_V_part_Q2().getValueOrDefault(e4.modify(PARTKEY));
        for (const auto &t4 : rel4.store)
        {
            auto P_NAME = std::get<0>(t4.first);
            auto payload_4 = t4.second;
            part_4->emplace_back(std::make_tuple(P_NAME, payload_4));
        }
        for (const auto &t1 : *part_1)
        {
            auto &SUPPKEY = std::get<0>(t1);
            auto payload_1 = std::get<1>(t1);
            auto &part_2 = std::get<2>(t1);
            auto &part_3 = std::get<3>(t1);
            for (const auto &t2 : *part_2)
            {
                auto &PS_AVAILQTY = std::get<0>(t2);
                auto payload_2 = std::get<1>(t2);
                for (const auto &t3 : *part_3)
                {
                    auto &ORDERKEY = std::get<0>(t3);
                    auto &L_QUANTITY = std::get<1>(t3);
                    auto payload_3 = std::get<2>(t3);
                    for (const auto &t4 : *part_4)
                    {
                        auto &P_NAME = std::get<0>(t4);
                        auto payload_4 = std::get<1>(t4);
                        update.emplace_back(DELTA_Q2_entry{P_NAME, PS_AVAILQTY, L_QUANTITY, PARTKEY, SUPPKEY, ORDERKEY, 1 * 1 * payload_2 * payload_3 * payload_4});
                        if (output_size % BATCH_SIZE == BATCH_SIZE - 1)
                        {
                            enumeration_timer.stop();
                            enumeration_time += enumeration_timer.elapsedTimeInMilliSeconds();
                            propagation_timer.restart();
                            data.on_batch_update_Q2(update.begin(), update.end());
                            propagation_timer.stop();
                            propagation_time += propagation_timer.elapsedTimeInMilliSeconds();
                            enumeration_timer.restart();
                            update.clear();
                        }
                        if (print_result)
                        {
                            output_file << P_NAME << "|" << PS_AVAILQTY << "|" << L_QUANTITY << "|" << PARTKEY << "|" << SUPPKEY << "|" << ORDERKEY << std::endl;
                        }
                        output_size++;
                    }
                }
            }
        }
        for (auto t1 : *part_1)
        {
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
    std::cout << "enumeration time Q2: " << enumeration_time << "ms" << std::endl;
    measure->enumeration_time = enumeration_time;
    propagation_timer.restart();
    data.on_batch_update_Q2(update.begin(), update.end());
    propagation_timer.stop();
    propagation_time += propagation_timer.elapsedTimeInMilliSeconds();
    std::cout << "propagation time Q2: " << propagation_time << "ms" << std::endl;
    output_file.close();
    measure->size_output = output_size;
    measure->free_variables = "P_NAME,PS_AVAILQTY,L_QUANTITY,PARTKEY,SUPPKEY,ORDERKEY";
    std::cout << "Q2: " << output_size << std::endl;
    return propagation_time;
}

struct DELTA_Q1_entry
{
    std::any ORDERKEY;
    std::any O_TOTALPRICE;
    std::any P_NAME;
    std::any L_QUANTITY;
    std::any PS_AVAILQTY;
    std::any PARTKEY;
    std::any SUPPKEY;
    long combined_value;
};

long enumerate_Q1(dbtoaster::data_t &data, bool print_result, bool count_view_size, Measurement *measure)
{
    size_t output_size = 0;
    std::ofstream view_sizes_file;
    if (count_view_size)
    {
        view_sizes_file = std::ofstream("sizes/tpch_2_Q1_view_sizes.csv");
        view_sizes_file << "Q2orders_Q1, " << 0 << std::endl;
        view_sizes_file << "orders_Q1, " << data.get_V_orders_Q1().primary_index->count() << std::endl;
        view_sizes_file << "Q2_Q1, " << data.get_V_Q2_Q1().primary_index->count() << std::endl;
        view_sizes_file.close();
    }
    Stopwatch enumeration_timer;
    enumeration_timer.restart();
    long propagation_time = 0;
    long enumeration_time = 0;
    std::ofstream output_file;
    if (print_result)
        output_file.open("output/Q1.csv");
    using ORDERKEY_type = std::remove_reference_t<decltype(std::get<0>(std::declval<decltype(data.get_V_Q2orders_Q1().store)::value_type>().first))>;
    using O_TOTALPRICE_type = std::remove_reference_t<decltype(std::get<0>(std::declval<decltype(data.get_V_orders_Q1().head->__av.store)::value_type>().first))>;
    using P_NAME_type = std::remove_reference_t<decltype(std::get<0>(std::declval<decltype(data.get_V_Q2_Q1().head->__av.store)::value_type>().first))>;
    using L_QUANTITY_type = std::remove_reference_t<decltype(std::get<1>(std::declval<decltype(data.get_V_Q2_Q1().head->__av.store)::value_type>().first))>;
    using PS_AVAILQTY_type = std::remove_reference_t<decltype(std::get<2>(std::declval<decltype(data.get_V_Q2_Q1().head->__av.store)::value_type>().first))>;
    using PARTKEY_type = std::remove_reference_t<decltype(std::get<3>(std::declval<decltype(data.get_V_Q2_Q1().head->__av.store)::value_type>().first))>;
    using SUPPKEY_type = std::remove_reference_t<decltype(std::get<4>(std::declval<decltype(data.get_V_Q2_Q1().head->__av.store)::value_type>().first))>;
    std::vector<DELTA_Q1_entry> update;
    update.reserve(1000);
    const auto &rel0 = data.get_V_Q2orders_Q1();
    for (const auto &t0 : rel0.store)
    {
        auto ORDERKEY = std::get<0>(t0.first);
        auto payload_0 = t0.second;
        std::vector<std::tuple<O_TOTALPRICE_type, long>> *part_1 = new std::vector<std::tuple<O_TOTALPRICE_type, long>>();
        V_orders_Q1_entry e1;
        const auto &rel1 = data.get_V_orders_Q1().getValueOrDefault(e1.modify(ORDERKEY));
        for (const auto &t1 : rel1.store)
        {
            auto O_TOTALPRICE = std::get<0>(t1.first);
            auto payload_1 = t1.second;
            part_1->emplace_back(std::make_tuple(O_TOTALPRICE, payload_1));
        }
        std::vector<std::tuple<P_NAME_type, L_QUANTITY_type, PS_AVAILQTY_type, PARTKEY_type, SUPPKEY_type, long>> *part_2 = new std::vector<std::tuple<P_NAME_type, L_QUANTITY_type, PS_AVAILQTY_type, PARTKEY_type, SUPPKEY_type, long>>();
        V_Q2_Q1_entry e2;
        const auto &rel2 = data.get_V_Q2_Q1().getValueOrDefault(e2.modify(ORDERKEY));
        for (const auto &t2 : rel2.store)
        {
            auto P_NAME = std::get<0>(t2.first);
            auto L_QUANTITY = std::get<1>(t2.first);
            auto PS_AVAILQTY = std::get<2>(t2.first);
            auto PARTKEY = std::get<3>(t2.first);
            auto SUPPKEY = std::get<4>(t2.first);
            auto payload_2 = t2.second;
            part_2->emplace_back(std::make_tuple(P_NAME, L_QUANTITY, PS_AVAILQTY, PARTKEY, SUPPKEY, payload_2));
        }
        for (const auto &t1 : *part_1)
        {
            auto &O_TOTALPRICE = std::get<0>(t1);
            auto payload_1 = std::get<1>(t1);
            for (const auto &t2 : *part_2)
            {
                auto &P_NAME = std::get<0>(t2);
                auto &L_QUANTITY = std::get<1>(t2);
                auto &PS_AVAILQTY = std::get<2>(t2);
                auto &PARTKEY = std::get<3>(t2);
                auto &SUPPKEY = std::get<4>(t2);
                auto payload_2 = std::get<5>(t2);
                update.emplace_back(DELTA_Q1_entry{ORDERKEY, O_TOTALPRICE, P_NAME, L_QUANTITY, PS_AVAILQTY, PARTKEY, SUPPKEY, 1 * payload_1 * payload_2});
                if (output_size % BATCH_SIZE == BATCH_SIZE - 1)
                {
                    update.clear();
                }
                if (print_result)
                {
                    output_file << ORDERKEY << "|" << O_TOTALPRICE << "|" << P_NAME << "|" << L_QUANTITY << "|" << PS_AVAILQTY << "|" << PARTKEY << "|" << SUPPKEY << std::endl;
                }
                output_size++;
            }
        }
        delete part_1;
        delete part_2;
    }
    enumeration_timer.stop();
    enumeration_time += enumeration_timer.elapsedTimeInMilliSeconds();
    std::cout << "enumeration time Q1: " << enumeration_time << "ms" << std::endl;
    measure->enumeration_time = enumeration_time;
    if (update.size() > 0)
    {
        std::uniform_int_distribution<int> uni(0, update.size() - 1);
        volatile auto dummy = update.at(uni(rng));
        std::cout << "dummy: " << dummy.combined_value << std::endl;
    }
    output_file.close();
    measure->size_output = output_size;
    measure->free_variables = "ORDERKEY,O_TOTALPRICE,P_NAME,L_QUANTITY,PS_AVAILQTY,PARTKEY,SUPPKEY";
    std::cout << "Q1: " << output_size << std::endl;
    return propagation_time;
}

void Application::on_snapshot(dbtoaster::data_t &data)
{
    on_end_processing(data, false, false);
}

void Application::on_begin_processing(dbtoaster::data_t &data)
{
}

void Application::on_end_processing(dbtoaster::data_t &data, bool print_result, bool count_view_size)
{

    cout << endl
         << "Enumerating factorized join result... " << endl;

    std::string relation_list = "";
    for (auto &rel : relations)
    {
        relation_list += rel->get_name() + ",";
    }
    relation_list = relation_list.substr(0, relation_list.size() - 1);
    std::vector<Measurement *> measurements;
    size_t output_size = 0;
    long updating_Q1 = 0 + dynamic_multiplexer.updating_times.find("orders")->second;
    long updating_Q2 = 0 + dynamic_multiplexer.updating_times.find("part")->second + dynamic_multiplexer.updating_times.find("partsupp")->second + dynamic_multiplexer.updating_times.find("lineitem")->second;
    Measurement measure_Q2 = Measurement("Q2", updating_Q2, "part,partsupp,lineitem");
    cout << "Enumerating Q2... " << endl;
    long Q2_propagation = enumerate_Q2(data, print_result, count_view_size, &measure_Q2);
    measurements.push_back(&measure_Q2);
    Measurement measure_Q1 = Measurement("Q1", updating_Q1, "orders,Q2");
    cout << "Enumerating Q1... " << endl;
    long Q1_propagation = enumerate_Q1(data, print_result, count_view_size, &measure_Q1);
    measurements.push_back(&measure_Q1);
    int query_Q2_count = 1;
    int query_Q1_count = 0;
    measure_Q1.update_time += Q2_propagation / query_Q2_count;
    std::ofstream measurements_file("output/output.txt", std::ios::app | std::ios::out);
    write_to_config(&measurements, measurements_file, relation_list);
    measurements_file.close();
    dynamic_multiplexer.updating_times.clear();
}
#endif