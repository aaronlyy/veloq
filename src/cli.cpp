#define BUILD_TIMESTAMP __DATE__ " " __TIME__
#define VERSION "veloq 0.0.1"
#define VERSION_INFO VERSION " (Build: " BUILD_TIMESTAMP ")"

#include <iostream>
#include <filesystem>

#include <CLI/CLI.hpp>

#include "cli.hpp"
#include "config.hpp"
#include "controller.hpp"
#include "format/color.hpp"

namespace veloq {
  int handle_cli(int argc, char** argv) {

    CLI::App app{"veloq"};

    // add version flag with build time
    app.set_version_flag("--version", VERSION_INFO, "Shows version info");

    std::vector<std::string> commands; // commands to be run

    // flags
    bool record{false}; // record command output and add to savefile
    bool diff{false}; // show diffs of output
    bool live{false}; // print live output of commands
    bool no_benchmark{false}; // hide benchmark ouput after command run
    bool verbose{false}; // print debug info
  
    // options
    int runs{1}; // how often should the command be run
    std::string name; // name of benchmark for save file
    std::string filter; // regex string that is used on every line to 
    std::string highlight; // regex string to add color to special lines
    std::filesystem::path output; // output path for savefile
    std::filesystem::path config_path; // run veloq using pre defined config

    // cli flags
    app.add_flag("-d,--diff", diff, "Show diff of outputs");
    app.add_flag("-l,--live", live, "Show live output of commands");
    app.add_flag("--no-benchmark", no_benchmark, "Hide benchmark result ouput in terminal after commands are finished running");
    app.add_flag("-v,--verbose", verbose, "Print debug information");

    // cli options
    app.add_option("commands", commands, "Commands to run")->expected(-1);

    app.add_option("-r,--runs", runs, "How often the commands should be executed. Default is 1.");
    app.add_option("-f,--filter", filter, "Filter output, prints and saves line if regex expression is true"); // TODO
    app.add_option("-m,--mark,--highlight", highlight, "Regex string to highlight command output");
    app.add_option("-o,--out", output, "Output path"); // TODO: Path to save benchmark file
    app.add_option("-c,--config", config_path, "Run benchmark using pre-defined config"); // >TODO: Path to benchmark config
    app.add_option("-n, --name", name, "Name of benchmark. Default is 'veloq benchmark'");
    
    CLI11_PARSE(app, argc, argv);

    // create config object for controller
    Config config;

    // load config from file
    // check if -c/--config is given, if yes, try to load from path
    if (!config_path.empty() && std::filesystem::exists(config_path)) {
      config = load_from_yaml(config_path);
      if (config.verbose) std::cout << "[veloq] Config loaded from given path\n";
    }
    // check if veloq.yaml exists in current directory, if yes load config
    else if (std::filesystem::exists("./veloq.yaml")) {
      std::filesystem::path cwd_config_path = "./veloq.yaml";
      config = load_from_yaml(cwd_config_path);
      if (config.verbose) std::cout << "[veloq] Config loaded from default path (./veloq.yaml)\n";
    }

    // override loaded config with given flags and options
    if (app.get_option("--diff")->count()) {
      config.diff = diff;
    }
    if (app.get_option("--live")->count()) {
      config.live = live;
    }
    if (app.get_option("--no-benchmark")->count()) {
      config.no_benchmark = no_benchmark;
    }
    if (app.get_option("--verbose")->count()) {
      config.verbose = verbose;
    }

    if (app.get_option("commands")->count()) {
      config.commands = commands;
    }

    if (app.get_option("--runs")->count()) {
      config.runs = runs;
    }
    
    if (app.get_option("--name")->count()) {
      config.name = name;
    }

    if (app.get_option("--filter")->count()) {
      config.filter = filter;
    }

    if (app.get_option("--highlight")->count()) {
      config.highlight = highlight;
    }

    if (app.get_option("--out")->count()) {
      config.output = output.string();
    }

    // create controller object for handling the actual running of the awesome stuff
    Controller controller{config};
    controller.run();

    return 0;
  }
}