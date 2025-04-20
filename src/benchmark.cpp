#include "benchmark.hpp"
#include "runner.hpp"

namespace veloq {

  Benchmark::Benchmark(BenchmarkConfig benchmark_config) : benchmark_config_(benchmark_config) {}

  BenchmarkResult Benchmark::start() {
    BenchmarkResult benchmark_result;

    // create runner object
    Runner runner(benchmark_config_.runs_per_command, benchmark_config_.live_output);

    for (std::string command : benchmark_config_.commands) {
      benchmark_result.commands.push_back(command);

      RunCollection run_collection = runner.run(command);

      benchmark_result.run_collections.push_back(run_collection);
    }

    return benchmark_result;
  }
}