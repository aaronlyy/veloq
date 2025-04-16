#include "result.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>

namespace veloq {

void print_result(Result &result, bool show_output) {
    std::cout << "\n== Result: " << result.command << " ==\n";

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Runtime:    " << result.runtime << " ms\n";
    std::cout << "Exit code:  " << result.exit_code << "\n";
    if (result.timeout) {
        std::cout << "Timeout:    ✅\n";
    }

    if (show_output) {
      std::cout << "--- OUTPUT ---\n";
      for (const auto& line : result.stdout_lines) {
          std::cout << line.output << "\n";
      }
    }
}

void print_result(ResultCollection& result_collection, bool show_output) {
    std::cout << "\n== Benchmark: " << result_collection.command << " ==\n";

    std::cout << "Runs:            " << result_collection.times << "\n";
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Average runtime: " << result_collection.average_runtime << " ms\n";
    std::cout << "Median runtime:  " << result_collection.median_runtime << " ms\n";

    std::cout << "--- Individual runs ---\n";
    int i = 0;
    for (const auto& r : result_collection.results) {
        std::cout << "[" << ++i << "] " << r.runtime << " ms";
        if (r.timeout) std::cout << " (timeout)";
        if (r.exit_code != 0) std::cout << " (exit " << r.exit_code << ")";
        std::cout << "\n";
    }
}

}
