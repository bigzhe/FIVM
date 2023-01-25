#ifndef APPLICATION_RETAILER_FACTORIZED_JOIN_KEY_HPP
#define APPLICATION_RETAILER_FACTORIZED_JOIN_KEY_HPP

#include "application_retailer_base.hpp"

void Application::on_snapshot(dbtoaster::data_t &data)
{
    on_end_processing(data, false);
}

void Application::on_begin_processing(dbtoaster::data_t &data)
{
}

void Application::on_end_processing(dbtoaster::data_t &data, bool print_result)
{

    cout << endl
         << "Enumerating factorized join result... " << endl;

    size_t output_size = 0;
    size_t total_multiplicity = 0;

    V_dateid_IIW1_entry tuple_V_dateid_IIW1;
    V_ksn_II1_entry tuple_V_ksn_II1;
    V_zip_LC1_entry tuple_V_zip_LC1;
    V_ITEM_entry tuple_V_ITEM;
    V_INVENTORY_entry tuple_V_INVENTORY;
    V_CENSUS_entry tuple_V_CENSUS;
    V_WEATHER_entry tuple_V_WEATHER;
    V_LOCATION_entry tuple_V_LOCATION;


    // get locn from V_locn_IIWLC1(locn)
    const auto &viewIIWLC = data.get_V_locn_IIWLC1();
    V_locn_IIWLC1_entry *tuple_V_locn_IIWLC1 = viewIIWLC.head;
    while (tuple_V_locn_IIWLC1)
    {
        int locn = tuple_V_locn_IIWLC1->locn;
        tuple_V_locn_IIWLC1 = tuple_V_locn_IIWLC1->nxt;

        // For each V_dateid_IIW2(locn, dateid) -> dateid
        V_dateid_IIW1_map &viewIIW1 = data.V_dateid_IIW1;

        // slice: n1 is the first tuple that matches locn
        const LinkedNode<V_dateid_IIW1_entry> *n1 = static_cast<const LinkedNode<V_dateid_IIW1_entry> *>(viewIIW1.slice(tuple_V_dateid_IIW1.modify0(locn), 0));
        V_dateid_IIW1_entry *e1;
        while (n1)
        {
            e1 = n1->obj;
            int dateid = e1->dateid; // dateid paired with locn

            // enumerate ksn from V_ksn_II1(locn, dateid, ksn) for fixed (locn and dateid)
            V_ksn_II1_map &viewII1 = data.V_ksn_II1;

            // slice II1: n2 is the first tuple that matches (locn, dateid)
            const LinkedNode<V_ksn_II1_entry> *n2 = static_cast<const LinkedNode<V_ksn_II1_entry> *>(viewII1.slice(tuple_V_ksn_II1.modify01(locn, dateid), 0));
            V_ksn_II1_entry *e2;
            while (n2)
            {
                e2 = n2->obj;
                int ksn = e2->ksn;

                // enumerate subcategory, ... from V_ITEM(ksn, subcategory, ...) for fixed (ksn)
                V_ITEM_map &viewITEM = data.V_ITEM;

                // slice ITEM: n3 is the first tuple that matches ksn
                const LinkedNode<V_ITEM_entry> *n3 = static_cast<const LinkedNode<V_ITEM_entry> *>(viewITEM.slice(tuple_V_ITEM.modify0(ksn), 0));

                V_ITEM_entry *e3;
                while (n3)
                {
                    e3 = n3->obj;
                    // other attributes of ITEM
                    int subcategory = e3->subcategory;
                    int category = e3->category;
                    int categoryCluster = e3->categoryCluster;
                    double prize = e3->prize;

                    // get the multiplicity here
                    long multiplicity = e3->__av;


                    // enumerate inventoryunits from V_INVENTORY(locn, dateid, ksn, inventoryunits) for fixed (locn, dateid, ksn)
                    V_INVENTORY_map &viewINVENTORY = data.V_INVENTORY;

                    // slice INVENTORY: n4 is the first tuple that matches (locn, dateid, ksn)
                    const LinkedNode<V_INVENTORY_entry> *n4 = static_cast<const LinkedNode<V_INVENTORY_entry> *>(viewINVENTORY.slice(tuple_V_INVENTORY.modify012(locn, dateid, ksn), 0));

                    V_INVENTORY_entry *e4;
                    while (n4)
                    {
                        e4 = n4->obj;
                        int inventoryunits = e4->inventoryunits;

                        // get the multiplicity here
                        multiplicity *= e4->__av;

                        // enumerate rain from V_WEATHER(locn, dateid, rain) for fixed (locn, dateid)
                        V_WEATHER_map &viewWEATHER = data.V_WEATHER;
                        // slice WEATHER: n5 is the first tuple that matches (locn, dateid)
                        const LinkedNode<V_WEATHER_entry> *n5 = static_cast<const LinkedNode<V_WEATHER_entry> *>(viewWEATHER.slice(tuple_V_WEATHER.modify01(locn, dateid), 0));

                        V_WEATHER_entry *e5;
                        while (n5)
                        {
                            e5 = n5->obj;
                            int rain = e5->rain;
                            int snow = e5->snow;
                            int maxtemp = e5->maxtemp;
                            int mintemp = e5->mintemp;
                            double meanwind = e5->meanwind;
                            int thunder = e5->thunder;

                            // get the multiplicity here
                            multiplicity *= e5->__av;

                            // enumerate zip from V_zip_LC1(locn, zip) for fixed locn
                            V_zip_LC1_map &viewLC1 = data.V_zip_LC1;

                            // slice LC1: n6 is the first tuple that matches locn
                            const LinkedNode<V_zip_LC1_entry> *n6 = static_cast<const LinkedNode<V_zip_LC1_entry> *>(viewLC1.slice(tuple_V_zip_LC1.modify0(locn), 0));

                            V_zip_LC1_entry *e6;
                            while (n6)
                            {
                                e6 = n6->obj;
                                int zip = e6->zip;

                                // enumerate population, white ... from V_CENSUS(zip, ...) for fixed zip
                                V_CENSUS_map &viewCENSUS = data.V_CENSUS;

                                // slice CENSUS: n7 is the first tuple that matches zip
                                const LinkedNode<V_CENSUS_entry> *n7 = static_cast<const LinkedNode<V_CENSUS_entry> *>(viewCENSUS.slice(tuple_V_CENSUS.modify0(zip), 0));

                                V_CENSUS_entry *e7;
                                while (n7)
                                {
                                    e7 = n7->obj;
                                    // other attributes of CENSUS
                                    int population = e7->population;
                                    int white = e7->white;
                                    int asian = e7->asian;
                                    int pacific = e7->pacific;
                                    int blackafrican = e7->blackafrican;
                                    double medianage = e7->medianage;
                                    int occupiedhouseunits = e7->occupiedhouseunits;
                                    int houseunits = e7->houseunits;
                                    int families = e7->families;
                                    int households = e7->households;
                                    int husbwife = e7->husbwife;
                                    int males = e7->males;
                                    int females = e7->females;
                                    int householdschildren = e7->householdschildren;
                                    int hispanic = e7->hispanic;

                                    // get the multiplicity here
                                    multiplicity *= e7->__av;

                                    // enumerate rgn_cd, ... from V_LOCATION(locn, zip, rgn_cd, ...) for fixed (locn zip)
                                    V_LOCATION_map &viewLOCATION = data.V_LOCATION;

                                    // slice LOCATION: n8 is the first tuple that matches (locn, zip)
                                    const LinkedNode<V_LOCATION_entry> *n8 = static_cast<const LinkedNode<V_LOCATION_entry> *>(viewLOCATION.slice(tuple_V_LOCATION.modify01(locn, zip), 0));

                                    V_LOCATION_entry *e8;
                                    while (n8)
                                    {
                                        e8 = n8->obj;
                                        // other attributes of LOCATION
                                        int rgn_cd = e8->rgn_cd;
                                        int clim_zn_nbr = e8->clim_zn_nbr;
                                        int tot_area_sq_ft = e8->tot_area_sq_ft;
                                        int sell_area_sq_ft = e8->sell_area_sq_ft;
                                        int avghhi = e8->avghhi;
                                        double supertargetdistance = e8->supertargetdistance;
                                        double supertargetdrivetime = e8->supertargetdrivetime;
                                        double targetdistance = e8->targetdistance;
                                        double targetdrivetime = e8->targetdrivetime;
                                        double walmartdistance = e8->walmartdistance;
                                        double walmartdrivetime = e8->walmartdrivetime;
                                        double walmartsupercenterdistance = e8->walmartsupercenterdistance;
                                        double walmartsupercenterdrivetime = e8->walmartsupercenterdrivetime;

                                        // get the multiplicity here
                                        multiplicity *= e8->__av;

                                        output_size += 1;
                                        total_multiplicity += multiplicity;

                                        if (print_result)
                                        {
                                            std::cout << locn << "," << dateid << "," << ksn << "," << inventoryunits << "," << rgn_cd << "," << clim_zn_nbr << "," << tot_area_sq_ft << "," << sell_area_sq_ft << "," << avghhi << "," << supertargetdistance << "," << supertargetdrivetime << "," << targetdistance << "," << targetdrivetime << "," << walmartdistance << "," << walmartdrivetime << "," << walmartsupercenterdistance << "," << walmartsupercenterdrivetime << "," << population << "," << white << "," << asian << "," << pacific << "," << blackafrican << "," << medianage << "," << occupiedhouseunits << "," << houseunits << "," << families << "," << households << "," << husbwife << "," << males << "," << females << "," << householdschildren << "," << hispanic << "," << subcategory << "," << category << "," << categoryCluster << "," << prize << "," << rain << "," << snow << "," << maxtemp << "," << mintemp << "," << meanwind << "," << thunder << std::endl;
                                        }
                                        n8 = n8->next;
                                    }
                                    n7 = n7->next;
                                }
                                n6 = n6->next;
                            }
                            n5 = n5->next;
                        }
                        n4 = n4->next;
                    }
                    n3 = n3->next;
                }
                n2 = n2->next;
            }
            n1 = n1->next;
        }

    }

    cout << "Number of output tuples: " << output_size << endl;
    cout << "Total multiplicity: " << total_multiplicity << endl;
}

#endif /* APPLICATION_RETAILER_FACTORIZED_JOIN_KEY_HPP */