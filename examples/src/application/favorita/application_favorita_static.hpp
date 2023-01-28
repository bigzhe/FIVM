#ifndef APPLICATION_FAVORITA_STATIC_HPP
#define APPLICATION_FAVORITA_STATIC_HPP

#include "application_favorita_base.hpp"

void Application::on_snapshot(dbtoaster::data_t& data) {
    on_end_processing(data, false);
}

void Application::on_begin_processing(dbtoaster::data_t& data) {

}

void Application::on_end_processing(dbtoaster::data_t& data, bool print_result) {

    cout << endl << "Enumerating factorized join result... " << endl;

    size_t output_size = 0; 
    size_t total_multiplicity = 0;
    

    const auto& viewSITSH1 = data.get_V_date_SITSOH1();
    
    for (auto &t1 : viewSITSH1.store) {

        auto &key1 = t1.first;
        auto date = std::get<0>(key1);
        
        { // for each V_date_SITSOH1(date)
            V_store_SITS1_entry e2;
            const auto& rel2 = data.get_V_store_SITS1().getValueOrDefault(e2.modify(date));
            for (auto &t2 : rel2.store) {
                auto &key2 = t2.first;
                auto store = std::get<0>(key2);
                
                
                // for each V_item_SI1(date, store) -> (item, unit_sales, onpromotion)
                V_item_SI1_entry e3;
                const auto& rel3 = data.get_V_item_SI1().getValueOrDefault(e3.modify(date, store));
                for (auto &t3 : rel3.store) {
                    auto &key3 = t3.first;
                    
                    auto item = std::get<0>(key3);
                    long value3 = t3.second;
                    
                    
                    // for each V_family_I1(item) -> (family, class, perishable)
                    V_family_I1_entry e4;
                    const auto& rel4 = data.get_V_family_I1().getValueOrDefault(e4.modify(item));
                    for (auto &t4 : rel4.store) {
                        auto &key4 = t4.first;
                        long value4 = t4.second;
                        long value34 = value3 * value4;
                        

                        // for each V_transact_T1(date, store) -> (transactunits)
                        V_transactions_T1_entry e5;
                        const auto& rel5 = data.get_V_transactions_T1().getValueOrDefault(e5.modify(date, store));
                        for (auto &t5 : rel5.store) {
                            auto &key5 = t5.first;
                            long value5 = t5.second;
                            long value345 = value34 * value5;
                            
                            // for each V_city_ST1(store) -> (city, state, type, cluster)
                            V_city_S1_entry e6;
                            const auto& rel6 = data.get_V_city_S1().getValueOrDefault(e6.modify(store));
                            for (auto &t6 : rel6.store) {
                                auto &key6 = t6.first;
                                long value6 = t6.second;
                                long value3456 = value345 * value6;
                                
                                // for each V_oilprize_O1(date) -> (oilprize) 
                                V_oilprize_O1_entry e7;
                                const auto& rel7 = data.get_V_oilprize_O1().getValueOrDefault(e7.modify(date));
                                for (auto &t7 : rel7.store) {
                                    auto &key7 = t7.first;
                                    long value7 = t7.second;
                                    long value34567 = value3456 * value7;
                                    
                                    // for each V_holiday_H1(date) -> (holiday)
                                    V_holiday_type_H1_entry e8;
                                    const auto& rel8 = data.get_V_holiday_type_H1().getValueOrDefault(e8.modify(date));
                                    for (auto &t8 : rel8.store) {
                                        auto &key8 = t8.first;
                                        long value8 = t8.second;
                                        long value = value34567 * value8;
                                        auto key = std::tuple_cat(key1, key2, key3, key4, key5, key6, key7, key8);

                                        output_size++;
                                        total_multiplicity += value;
    
                                        if (print_result) cout << key << " -> " << value << endl;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    cout << "Number of output tuples: " << output_size << endl;
    cout << "Total multiplicity: " << total_multiplicity << endl;
}

#endif /* APPLICATION_FAVORITA_STATIC_HPP */