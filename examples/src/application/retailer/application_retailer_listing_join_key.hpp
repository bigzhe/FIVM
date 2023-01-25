#ifndef APPLICATION_RETAILER_LISTING_JOIN_HPP
#define APPLICATION_RETAILER_LISTING_JOIN_HPP

#include "application_retailer_base.hpp"

void Application::on_snapshot(dbtoaster::data_t& data) {
    on_end_processing(data, false);
}

void Application::on_begin_processing(dbtoaster::data_t& data) {

}

void Application::on_end_processing(dbtoaster::data_t& data, bool print_result) {

    cout << endl << "Enumerating listing join result... " << endl;

    // enumerate in the key space
    const auto& viewIIWLC = data.get_V_locn_IIWLC1();

    // size_t output_size = viewIIWLC.store.size();
    size_t total_multiplicity = 0;

    // for (auto &t : viewIIWLC.store) {

    V_locn_IIWLC1_entry *tmp = viewIIWLC.head;

    while (tmp) {
        int locn = tmp->locn;
        tmp = tmp->nxt;
        // if (print_result) cout << t.first << " -> " << t.second << endl;
        if (print_result) cout << locn << endl;
        total_multiplicity += 1;
    }

    cout << "Number of output tuples: " << total_multiplicity << endl;
    cout << "Total multiplicity: " << total_multiplicity << endl;
}

#endif /* APPLICATION_RETAILER_LISTING_JOIN_HPP */
