
// macro for unix/win support of popen
#ifdef _WIN32
  #define popen _popen
  #define pclose _pclose
#endif

#include "runner.hpp"
#include "utils.hpp"
#include <chrono>
#include <iostream>
#include <cstdio> 

namespace veloq {

  // class that executes commands & captures outputs and timings
  Runner::Runner(unsigned int runs_per_command, bool live_output) : runs_per_command_(runs_per_command), live_output_(live_output){}

  RunCollection Runner::run(const std::string& command) {

    // create new run collection to save runs
    RunCollection run_collection;
    run_collection.command = command;

    for (unsigned int i = 0; i < runs_per_command_; i++) {

      // create object to capture run
      RunResult run;

      // set start stuff
      run.command = command;
      run.start_time = std::chrono::system_clock::now();

      // open process and get stream
      FILE* pipe = popen(command.c_str(), "r");

      // catch error of process cant be started
      if (!pipe) {
      throw std::runtime_error("Error running command: " + command);
      }

      // start time of process
      std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

      // buffer for every new line of output the command generates
      char buffer[512];

      // counter for line numbers
      int line = 0;

      // iterate through lines of command output
      while (fgets(buffer, sizeof(buffer), pipe)) {

        // convert buffer to string
        std::string line_content = buffer;

        // remove line breaks
        if (!line_content.empty() && line_content.back() == '\n') {
          line_content.pop_back();
        }

        // calculate offset between the start of the process and the current time for later replay
        std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
        std::chrono::milliseconds offset = std::chrono::duration_cast<std::chrono::milliseconds>(now - start);

        // create ouput struct for every new line
        run.stdout_lines.push_back(Output{
          StreamType::Stdout,
          line_content,
          offset,
          line++
        });

        // if live_output_ is true, print captured output before moving on, could change timings
        if (live_output_) {
          std::cout << line_content << std::endl;
        }
      }

      // close stream
      pclose(pipe);

      // get finish time and set it in the struct

      run.end_time = std::chrono::system_clock::now();
      run.exit_code = 0; // change to actual exit code

      // push results of current run to run collection
      run_collection.run_results.push_back(run);
    }

    return run_collection;
  }
}