#ifndef APPLICATION_RETAILER_CHOWLIUTREE_HPP
#define APPLICATION_RETAILER_CHOWLIUTREE_HPP

#include <cmath>
#include <iomanip>
#include "application_retailer_mi_base.hpp"
#include "csvreader.hpp"
#include "clt.hpp"

ChowLiuTreeBuilder<39> clt_builder;

void Application::on_snapshot(dbtoaster::data_t& data) {
    on_end_processing(data, false);
}

void Application::on_begin_processing(dbtoaster::data_t& data) {

}

void Application::on_end_processing(dbtoaster::data_t& data, bool print_result) {
    

    const auto& cofactor_matrix = data.get_V_locn_IIWLC1();
    
    clt_builder.build_mi_matrix(cofactor_matrix);

    // // print out the MI matrix
    for (size_t i = 0; i < 39; i++) {
        for (size_t j = 0; j < 39; j++) {
            std::cout << clt_builder.mi_matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
    
    // build the chow liu tree
    clt_builder.build_chow_liu_tree();
    if (print_result)
        clt_builder.print_chow_liu_tree();

}

#endif /* APPLICATION_RETAILER_CHOWLIUTREE_HPP */