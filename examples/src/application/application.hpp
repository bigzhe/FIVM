#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <iostream>
#include <vector>
#include "stopwatch.hpp"
#include "dispatcher.hpp"
#include "relation.hpp"

using namespace dbtoaster;

class Application {
  protected:
    std::vector<std::unique_ptr<IRelation>> relations;
    Multiplexer static_multiplexer;
    Multiplexer dynamic_multiplexer;
    
    long total_enum_time = 0;
    long total_update_time = 0;
    
    Stopwatch enumerate_timer;
    Stopwatch update_timer;


    void init_relations();

    void load_relations();

    void clear_relations();

    void init_dispatchers(dbtoaster::data_t& data);

    void clear_dispatchers();

    void process_tables(dbtoaster::data_t& data);

    void process_on_system_ready(dbtoaster::data_t& data);

    void process_streams(dbtoaster::data_t& data);

    void process_streams_snapshot(dbtoaster::data_t& data, long snapshot_interval, long batch_interval);

    void process_streams_no_snapshot(dbtoaster::data_t& data);

    void on_snapshot(dbtoaster::data_t& data);

    void on_begin_processing(dbtoaster::data_t& data);

    void on_end_processing(dbtoaster::data_t& data, bool print_result);

    void print_result(dbtoaster::data_t& data);

  public:
    Application() { }

    ~Application() {
        clear_relations();
        clear_dispatchers();
    }

    void run(size_t num_of_runs, bool output_result, size_t snapshot_interval);
};

void Application::load_relations() {
    for (auto &r : relations) {
        r->clear();
        r->load();
    }
}

void Application::clear_relations() {
    for (auto &r : relations) {
        r->clear();
    }
    relations.clear();
}

void Application::init_dispatchers(dbtoaster::data_t& data) {
    clear_dispatchers();

    for (auto &r : relations) {
        if (r->is_static()) {
            static_multiplexer.add_dispatcher(r->create_dispatcher(data));
        }
        else {
            dynamic_multiplexer.add_dispatcher(r->create_dispatcher(data));
        }
    }
}

void Application::clear_dispatchers() {
    static_multiplexer.clear();
    dynamic_multiplexer.clear();   
}

void Application::process_tables(dbtoaster::data_t& data) {
    while (static_multiplexer.has_next()) {
        static_multiplexer.next();
    }
}

void Application::process_on_system_ready(dbtoaster::data_t& data) {
    data.on_system_ready_event();
}

void Application::process_streams(dbtoaster::data_t& data) {
    #ifdef SNAPSHOT_INTERVAL
        process_streams_snapshot(data, SNAPSHOT_INTERVAL);
    #else
        process_streams_no_snapshot(data);
    #endif
}

void Application::process_streams_snapshot(dbtoaster::data_t& data, long snapshot_interval, long batch_interval) {
    long next_snapshot = 0;
    long next_batch = 0;
    long batch_time = 0;

    while (dynamic_multiplexer.has_next()) {
        update_timer.restart();
        dynamic_multiplexer.next();
        update_timer.stop();
        total_update_time += update_timer.elapsedTimeInMilliSeconds();
        batch_time += update_timer.elapsedTimeInMilliSeconds();

        if (data.tN >= next_snapshot) {
            enumerate_timer.restart();
            on_snapshot(data);
            enumerate_timer.stop();
            total_enum_time += enumerate_timer.elapsedTimeInMilliSeconds();
            batch_time += enumerate_timer.elapsedTimeInMilliSeconds();

            next_snapshot = data.tN + snapshot_interval;
        }

        if (data.tN >= next_batch) {
            std::cout << "Batch time:  " << batch_time << std::endl;
            batch_time = 0;
            next_batch = data.tN + batch_interval;
        }
    }

    if (next_snapshot != data.tN + snapshot_interval) {
        on_snapshot(data);
    }
}

void Application::process_streams_no_snapshot(dbtoaster::data_t& data) {
    while (dynamic_multiplexer.has_next()) {
        dynamic_multiplexer.next();
    }
}

void Application::run(size_t num_of_runs, bool print_result, size_t snapshot_interval) {
    std::cout << "-------------" << std::endl;

    init_relations();

    Stopwatch local_time, total_time;
    
    long total_num_of_tuples = 0;
    

    std::cout << "Loading input relations... " << std::flush;
    local_time.restart();    
    load_relations();
    local_time.stop();
    std::cout << local_time.elapsedTimeInMilliSeconds() << " ms" << std::endl;
    for (auto &r : relations) {
        std::cout << "  " << r->get_name() << " (" << r->size() << ") " << std::endl;
        total_num_of_tuples += r->size();
    }
    
    // compute the batch interval for 100 batches
    // for each interval, we will print the batch time
    long batch_interval = total_num_of_tuples / 100;
    std::cout << "Total number of tuples: " << total_num_of_tuples << std::endl;
    std::cout << "Batch interval: " << batch_interval << std::endl;


    for (size_t run = 0; run < num_of_runs; run++) {

        dbtoaster::data_t data;

        std::cout << "-------------" << std::endl;

        init_dispatchers(data);

        std::cout << "1. On begin of processing... " << std::flush;
        local_time.restart();
        on_begin_processing(data);
        local_time.stop();
        std::cout << local_time.elapsedTimeInMilliSeconds() << " ms" << std::endl;

        std::cout << "2. Processing tables... " << std::flush;
        local_time.restart();
        process_tables(data);
        local_time.stop();
        std::cout << local_time.elapsedTimeInMilliSeconds() << " ms" << std::endl;
        
        total_time.restart();

        std::cout << "3. On system ready... " << std::flush;
        local_time.restart();
        process_on_system_ready(data);
        local_time.stop();
        std::cout << local_time.elapsedTimeInMilliSeconds() << " ms" << std::endl;

        std::cout << "4. Processing streams... " << std::flush;;
        local_time.restart();
        std::cout << std::endl;
        if (snapshot_interval == 0) {
            process_streams_no_snapshot(data);
        }
        else {
            process_streams_snapshot(data, snapshot_interval, batch_interval);
        }
        local_time.stop();
        std::cout << local_time.elapsedTimeInMilliSeconds() << " ms" << std::endl;

        std::cout << "5. On end of processing... " << std::flush;
        local_time.restart();
        on_end_processing(data, print_result);
        local_time.stop();
        std::cout << local_time.elapsedTimeInMilliSeconds() << " ms" << std::endl;

        total_time.stop();
        

        std::cout << "-------------" << std::endl;
        std::cout << "    Total update time: " << total_update_time << std::endl;
        std::cout << "    Total enumerate time: " << total_enum_time  << std::endl;

        std::cout << "    Run: " << run
                  << "    Processed: " << data.tN
                  << "    Skipped: " << data.tS
                  << "    Execution time: " << total_time.elapsedTimeInMilliSeconds() << " ms"
#ifdef BATCH_SIZE
                  << "    Batch size: " << BATCH_SIZE
#endif
                  << std::endl
                  << "-------------"
                  << std::endl;

        clear_dispatchers();
    }

    clear_relations();
}

#endif /* APPLICATION_HPP */