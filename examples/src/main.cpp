#include <iostream>

#include "application/application.hpp"

int main(int argc, char** argv) {
    
    int opt_num_runs = 1;
    bool opt_print_result = true;
    int snapshot_interval = 0;

    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "--num-runs") == 0 || strcmp(argv[i], "-r") == 0) {
            opt_num_runs = atoi(argv[i + 1]);
        }
        opt_print_result = opt_print_result && (strcmp(argv[i], "--no-output") != 0);
        
        // get snapshot interval
        if (strcmp(argv[i], "--snapshot-inverval") == 0 || strcmp(argv[i], "-s") == 0) {
            snapshot_interval = atoi(argv[i + 1]);
        }
    }

#ifndef __APPLE__
    cpu_set_t  mask;
    CPU_ZERO(&mask);
    CPU_SET(0, &mask);
    sched_setaffinity(0, sizeof(mask), &mask);
#endif

    Application app;
    app.run(opt_num_runs, opt_print_result, snapshot_interval);
    
    return 0;
}