#define BUILD_TIMESTAMP __DATE__ " " __TIME__
#define VERSION "veloq 0.0.1"
#define VERSION_INFO VERSION " (Build: " BUILD_TIMESTAMP ")"

#include <iostream>
#include <filesystem>

#include <CLI/CLI.hpp>

#include "cli.hpp"
#include "config.hpp"
namespace veloq {
  int handle_cli(int argc, char** argv) {

    CLI::App app{"veloq"};

    // add version flag with build time
    app.set_version_flag("--version", VERSION_INFO, "Shows version info");

    std::vector<std::string> commands; // commands to be run

    // flags
    bool record{false}; // record command output and add to savefile
    bool show_diff{false}; // show diffs of output
    bool live_output{false}; // print live output of commands
    bool no_benchmark{false}; // hide benchmark ouput after command run
    bool verbose{false}; // print debug info
  
    // options
    int runs_per_command{1}; // how often should the command be run
    std::string name; // name of benchmark for save file
    std::string filter_regex; // regex string that is used on every line to 
    std::string highlight_regex; // regex string to add color to special lines
    std::filesystem::path output_path; // output path for savefile
    std::vector<std::string> config_path; // run veloq using pre defined config

    // cli flags
    app.add_flag("-d,--diff", show_diff, "Show diff of outputs");
    app.add_flag("-l,--live", live_output, "Show live output of commands");
    app.add_flag("--no-benchmark", no_benchmark, "Hide benchmark result ouput in terminal after commands are finished running");
    app.add_flag("-v,--verbose", verbose, "Print debug information");

    // cli options
    app.add_option("commands", commands, "Commands to run")->expected(-1);

    app.add_option("-r,--runs", runs_per_command, "How often the commands should be executed. Default is 1.");
    app.add_option("-f,--filter", filter_regex, "Filter output, prints and saves line if regex expression is true"); // TODO
    app.add_option("-m,--mark,--highlight", highlight_regex, "Regex string to highlight command output");
    app.add_option("-o,--out", output_path, "Output path"); // TODO: Path to save benchmark file
    app.add_option("-c,--config", config_path, "Run benchmark using pre-defined config"); // >TODO: Path to benchmark config
    app.add_option("-n, --name", name, "Name of benchmark. Default is 'veloq benchmark'");
    
    CLI11_PARSE(app, argc, argv);

    // create config object for controller
    Config config;

    // set given flags in config
    config.show_diff = show_diff;
    config.live_output = live_output;
    config.no_benchmark = no_benchmark;
    config.verbose = verbose;

    // only set options if given
    if (app.get_option("commands")->count()) {
      config.commands = commands;
    }

    if (app.get_option("--runs")->count()) {
      config.runs_per_command = runs_per_command;
    }
    
    if (app.get_option("--name")->count()) {
      config.name = name;
    }

    if (app.get_option("--filter")->count()) {
      config.filter_regex = filter_regex;
    }

    if (app.get_option("--highlight")->count()) {
      config.highlight_regex = highlight_regex;
    }

    if (app.get_option("--out")->count()) {
      config.output_path = output_path.string(); // optional<string>
    }

    // create controller object for handling the actual running of the awesome stuff

    return 0;
  }
}