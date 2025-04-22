#define BUILD_TIMESTAMP __DATE__ " " __TIME__
#define VERSION "veloq 0.0.1"
#define VERSION_INFO VERSION " (Build: " BUILD_TIMESTAMP ")"

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
    int runs_per_command{1}; // how often should the command be run
    std::filesystem::path output_path; // output path of replay file
    std::filesystem::path replay_path; // path to replay file that is going to be simulated
    std::vector<std::string> config_path; // run benchmark using pre defined command
    std::string filter_regex; // regex string that is used on every line to 
    std::vector<std::string> commands; // commands to be run
    std::string name; // name of benchmark for save file
  
    app.add_flag("-d,--diff", show_diff, "Show diff of outputs"); // todo
    app.add_flag("-l,--live", live_output, "Show live output of commands");

    app.set_version_flag("--version", VERSION_INFO, "Shows version info");

    app.add_option("-r,--runs", runs_per_command, "How often the commands should be executed. Default is 1.");
    app.add_option("-f,--filter", filter_regex, "Filter output, prints and saves line if regex expression is true"); // TODO
    app.add_option("-o,--out", output_path, "Output path"); // TODO: Path to save benchmark file
    app.add_option("-c,--config", config_path, "Run benchmark using pre-defined config"); // >TODO: Path to benchmark config
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
        std::cout << "Command: " << run_collection.command << std::endl;
        std::cout << "Full Runtime: " << run_collection.runtime() << "s" << std::endl;
        std::cout << "Average runtime: " << run_collection.average_runtime() << "s" << std::endl;
        std::cout << "Median runtime: " << run_collection.median_runtime() << "s" << std::endl;
      }
    }

    return 0;
  }
}