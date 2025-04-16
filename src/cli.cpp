#include <iostream>
#include <filesystem>

#include "CLI11.hpp"

#include "cli.hpp"
#include "runner.hpp"
#include "result.hpp"
#include "utils.hpp"

namespace veloq {
  int handle_cli(int argc, char** argv) {

    CLI::App app{"veloq"};

    // flags
    bool verbose{false}; // show debug and other stuff
    bool graph{false}; // show graphs (work in progress)
    bool diff{false}; // show diffs of output
    bool live{false}; // print live output of commands
    
  
    // options
    int times{1}; // how often should the command be run
    int timeout{10000}; // timeout till stop
    std::filesystem::path out; // output path of replay file
    std::filesystem::path replay;
    std::vector<std::string> commands; // commands to be run
  
    app.add_flag("-v,--verbose", verbose, "Show outputs of command");
    app.add_flag("-g,--graph", graph, "Display ASCII graph"); // todo
    app.add_flag("-d,--diff", diff, "Show diff of outputs"); // todo
    app.add_flag("-l,--live", live, "Show live output of commands");
    app.add_option("-n,--times", times, "How often the commands should be executed");
    app.add_option("-r,--replay", replay, "Path to replay file"); // todo
    app.add_option("-o,--out", out, "Output path"); // todo
    app.add_option("-t, --timeout", timeout, "Timeout after milliseconds"); // todo
    app.add_option("commands", commands, "Commands to run")->expected(-1);
  
    CLI11_PARSE(app, argc, argv);
  
    Runner runner(std::chrono::milliseconds(timeout), verbose, live); // create runner object, is used for every command given

    // only one command to run once
    if (commands.size() == 1 && times == 1) {
      const Result result = runner.run_once(commands[0]);
    }
    // one command to run but multiple times
    else if (commands.size() > 1) {
      const ResultCollection result_collection = runner.run_multi(commands[0], times);
    }
    // many commands but only one run per command
    else if (commands.size() > 1 && times == 1) {
      // create vector of single results
      std::vector<Result> results;
      for (std::string &command : commands) {
        const Result result = runner.run_once(command);
        results.push_back(result);
      }
      // print each time of commnand
      // work in progress
    }
    // many commands that need to be run multiple times
    else if (commands.size() > 1 && times > 1) {
      // vector of result collections
      std::vector<ResultCollection> result_collections;
      for (std::string &command : commands) {
        const ResultCollection result_collection = runner.run_multi(command, times);
        result_collections.push_back(result_collection);
      }
      // print average time and median of each command execution
      // work in progress
    }
    // no commands given, can only be for replay reasons
    else if (commands.empty() && !replay.empty()) {
      std::cout << "--- REPLAY ---\n";
      std::cout << replay << std::endl;
      std::cout << "--- REPLAY END ---\n";
    }
    else {
      std::cout << "huh? maybe try 'veloq --help'\n";
    }

    return 0;
  }
}