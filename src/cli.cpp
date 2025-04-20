#include <iostream>
#include <filesystem>

#include "CLI11.hpp"

#include "cli.hpp"
#include "runner.hpp"
#include "utils.hpp"
#include "benchmark.hpp"

namespace veloq {
  int handle_cli(int argc, char** argv) {

    CLI::App app{"veloq"};

    // flags
    bool show_diff{false}; // show diffs of output
    bool live_output{false}; // print live output of commands
  
    // options
    int runs_per_command{5}; // how often should the command be run
    std::filesystem::path output_path; // output path of replay file
    std::filesystem::path replay_path; // path to replay file that is going to be simulated
    std::vector<std::string> commands; // commands to be run
    std::string name;
  
    app.add_flag("-d,--diff", show_diff, "Show diff of outputs"); // todo
    app.add_flag("-l,--live", live_output, "Show live output of commands");
    app.add_option("-r,--runs", runs_per_command, "How often the commands should be executed. Default is 5.");
    app.add_option("-s,--simulate", replay_path, "Path to replay file"); // todo
    app.add_option("-o,--out", output_path, "Output path"); // todo
    app.add_option("-n, --name", name, "Name of benchmark. Default is 'veloq benchmark'");
    app.add_option("commands", commands, "Commands to run")->expected(-1);
  
    CLI11_PARSE(app, argc, argv);

    if (commands.size() == 0) {
      std::cout << "huh? maybe try 'veloq --help'\n";
      return 0;
    }
    else {
      BenchmarkConfig benchmark_config;
      benchmark_config.name = name;
      benchmark_config.runs_per_command = runs_per_command;
      benchmark_config.commands = commands;
      benchmark_config.live_output = live_output;
  
      Benchmark benchmark(benchmark_config);
      BenchmarkResult benchmark_result = benchmark.start();

      for (RunCollection &run_collection :  benchmark_result.run_collections) {
        std::cout << "Command: " << run_collection.command << "s" << std::endl;
        std::cout << "Full Runtime: " << run_collection.runtime() << "s" << std::endl;
        std::cout << "Average runtime: " << run_collection.average_runtime() << "s" << std::endl;
        std::cout << "Median runtime: " << run_collection.median_runtime() << "s" << std::endl;
      }
    }

    return 0;
  }
}