#include <string>
#include <vector>
#include <chrono>
#include "runner.hpp"

namespace veloq {

  struct BenchmarkConfig {
    std::string name;
    unsigned int runs_per_command;
    bool live_output;
    std::vector<std::string> commands;
  };

  // this struct only holds the raw benchmark results
  // for analyses etc we going to use veloq::analysis::BenchmarkAnalyser
  struct BenchmarkResult {

    std::string name = "veloq benchmark";

    // all commands run in this benchmark
    std::vector<std::string> commands;

    // all run collections of commands
    std::vector<RunCollection> run_collections;

    // timestamps of benchmark
    std::chrono::system_clock::time_point start_time;
    std::chrono::system_clock::time_point end_time;
  };

  class Benchmark {
    public:
      Benchmark(BenchmarkConfig config);

      // start benchmark with given config
      BenchmarkResult start();

    private:
      BenchmarkConfig benchmark_config_;
  };
}