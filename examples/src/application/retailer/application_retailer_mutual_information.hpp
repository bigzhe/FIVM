#ifndef APPLICATION_RETAILER_REGRESSION_HPP
#define APPLICATION_RETAILER_REGRESSION_HPP

#include <cmath>
#include <iomanip>
#include "application_retailer_mi_base.hpp"
#include "csvreader.hpp"
#include "clt.hpp"

// BGDSolver<39, 3> bgd_solver;
// ModelEvaluator model_evaluator;
ChowLiuTreeBuilder<39> clt_builder;

void Application::on_snapshot(dbtoaster::data_t& data) {
    // on_end_processing(data, false);
    std::cout << "snapshot" << std::endl;
}

void Application::on_begin_processing(dbtoaster::data_t& data) {
    // double rmse = model_evaluator.compute_rmse(bgd_solver.params);
    // std::cout << "RMSE: " << rmse << std::endl;
}

void Application::on_end_processing(dbtoaster::data_t& data, bool print_result) {
    

    const auto& cofactor_matrix = data.get_V_locn_IIWLC1();
    
    data.serialize(std::cout, 0);

    // bgd_solver.build_sigma_matrix(cofactor_matrix);
    clt_builder.build_mi_matrix(cofactor_matrix);

    // print out the MI matrix
    for (size_t i = 0; i < 39; i++) {
        for (size_t j = 0; j < 39; j++) {
            std::cout << clt_builder.mi_matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

    // std::cout << "initial params: [ ";
    // for (size_t i = 0; i < bgd_solver.NUM_PARAMS; i++) {
    //     std::cout << std::setprecision(10) <<  bgd_solver.params[i] << " ";
    // }
    // std::cout << " ]" << std::endl;

    // size_t num_iterations = 0.0;
    // double error = 0.0;
    // bgd_solver.run(num_iterations, error);

    // std::cout << "number of iterations: " << num_iterations ;

    // std::cout << "params: [ ";
    // for (size_t i = 0; i < bgd_solver.NUM_PARAMS; i++) {
    //     std::cout << bgd_solver.params[i] << " ";
    // }
    // std::cout << " ]" << std::endl;

    // double rmse = model_evaluator.compute_rmse(bgd_solver.params);
    // std::cout << "RMSE: " << rmse << std::endl;
}

#endif /* APPLICATION_RETAILER_REGRESSION_HPP */