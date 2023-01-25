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
        int dateid = tmp->dateid;
        int ksn = tmp->ksn;
        int subcategory = tmp->subcategory;
        int category = tmp->category;
        int categoryCluster = tmp->categoryCluster;
        double prize = tmp->prize;
        int rain = tmp->rain;
        int snow = tmp->snow;
        int maxtemp = tmp->maxtemp;
        int mintemp = tmp->mintemp;
        double meanwind = tmp->meanwind;
        int thunder = tmp->thunder;
        int population = tmp->population;
        int white = tmp->white;
        int asian = tmp->asian;
        int pacific = tmp->pacific;
        int blackafrican = tmp->blackafrican;
        double medianage = tmp->medianage;
        int occupiedhouseunits = tmp->occupiedhouseunits;
        int houseunits = tmp->houseunits;
        int families = tmp->families;
        int households = tmp->households;
        int husbwife = tmp->husbwife;
        int males = tmp->males;
        int females = tmp->females;
        int householdschildren = tmp->householdschildren;
        int hispanic = tmp->hispanic;
        int rgn_cd = tmp->rgn_cd;
        int clim_zn_nbr = tmp->clim_zn_nbr;
        int tot_area_sq_ft = tmp->tot_area_sq_ft;
        int sell_area_sq_ft = tmp->sell_area_sq_ft;
        int avghhi = tmp->avghhi;
        double supertargetdistance = tmp->supertargetdistance;
        double supertargetdrivetime = tmp->supertargetdrivetime;
        double targetdistance = tmp->targetdistance;
        double targetdrivetime = tmp->targetdrivetime;
        double walmartdistance = tmp->walmartdistance;
        double walmartdrivetime = tmp->walmartdrivetime;
        double walmartsupercenterdistance = tmp->walmartsupercenterdistance;
        double walmartsupercenterdrivetime = tmp->walmartsupercenterdrivetime;


        tmp = tmp->nxt;
        // if (print_result) cout << t.first << " -> " << t.second << endl;
        if (print_result) cout << locn << endl;
        total_multiplicity += 1;
    }

    cout << "Number of output tuples: " << total_multiplicity << endl;
    cout << "Total multiplicity: " << total_multiplicity << endl;
}

#endif /* APPLICATION_RETAILER_LISTING_JOIN_HPP */
