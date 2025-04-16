#include "runner.hpp"
#include "result.hpp"
#include "utils.hpp"
#include <chrono>
#include <iostream>
#include <cstdio> 

namespace veloq {

  Runner::Runner(
    std::chrono::milliseconds timeout,
    bool verbose,
    bool live
  ) : timeout_(timeout), verbose_(verbose), live_(live){
    if (verbose_) {
      std::cout << "Runner erstellt (fix verbose log)\n"; 
    }
  }

  Result Runner::run_once(const std::string& command) {
    Result result;
    result.command = command;
    result.start_time = std::chrono::system_clock::now();

    // open process and get stream
    FILE* pipe = _popen(command.c_str(), "r");

    // catch error of process cant be started
    if (!pipe) {
      throw std::runtime_error("Error running command: " + command);
    }

    // start time of process
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    
    // buffer for every line
    char buffer[512];

    // count line numbers
    int line = 0;

    // iterate through lines of command output
    while (fgets(buffer, sizeof(buffer), pipe)) {
      // convert buffer to string
      std::string line_content = buffer;
      // remove line breaks
      if (!line_content.empty() && line_content.back() == '\n') {
        line_content.pop_back();
      }

      std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
      std::chrono::milliseconds offset = std::chrono::duration_cast<std::chrono::milliseconds>(now - start);

      // create ouput struct for every line
      result.stdout_lines.push_back(Output{
        StreamType::Stdout,
        line_content,
        offset,
        line++
      });

      // print live output
      if (live_) {
        std::cout << line_content << std::endl;
      }
    }

    // close stream
    _pclose(pipe);

    result.end_time = std::chrono::system_clock::now();
    result.runtime = std::chrono::duration<float, std::milli>(result.end_time - result.start_time).count();
    result.exit_code = 0;

    return result;
}

  ResultCollection Runner::run_multi(const std::string &command, const int &times) {
    ResultCollection result_collection;
    result_collection.command = command;
    result_collection.times = times;

    std::vector<Result> results;

    for (unsigned int i = 0; i < times; i++) {
      const Result result = run_once(command);
      results.push_back(result);
    }

    result_collection.results = results;

    return result_collection;
  }
  
}