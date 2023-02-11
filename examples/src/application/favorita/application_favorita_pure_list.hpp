#ifndef APPLICATION_FAVORITA_STATIC_HPP
#define APPLICATION_FAVORITA_STATIC_HPP

#include "application_favorita_base.hpp"

void Application::on_snapshot(dbtoaster::data_t& data) {
    on_end_processing(data, false);
}

void Application::on_begin_processing(dbtoaster::data_t& data) {

}

void Application::on_end_processing(dbtoaster::data_t& data, bool print_result) {

    cout << endl << "Enumerating listing join result... " << endl;
    data.on_system_ready_event();

    const auto& root_view = data.get_V_date_SITSOH1();

    size_t output_size = root_view.store.size();
    size_t total_multiplicity = 0;

    for (auto &t : root_view.store) {
        if (print_result) cout << t.first << " -> " << t.second << endl;
        total_multiplicity += t.second;
    }

    cout << "Number of output tuples: " << output_size << endl;
    cout << "Total multiplicity: " << total_multiplicity << endl;
}

#endif /* APPLICATION_FAVORITA_STATIC_HPP */