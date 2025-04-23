#pragma once
#include <string>
#include <vector>
#include <filesystem>
#include <optional>

namespace veloq {
  struct Config {
    // flags
    // bool record; // -r/--record (add command output to save file with time offsets)
    bool diff; // -d/--diff (show diff of outputs)
    bool live; // -l/--live (print command output while running)
    bool no_benchmark; // --no-benchmark (hide benchmark output after command run)
    bool verbose; //-v/--verbose (print debug info while running)

    // options
    std::optional<std::vector<std::string>> commands; // maybe later own command struct

    std::optional<unsigned int> runs; // how often the given commands should be run, default is 1, only makes sense while benchmarking
    std::optional<std::string> name; // -n/--name (name of current run, used in savefile)
    std::optional<std::string> filter; // -f/--filter (filter lines using regex)
    std::optional<std::string> highlight; // -h/--highlight (highlight lines using regex)
    std::optional<std::filesystem::path> output; // -o/--output path to savefile
  };

  Config load_from_yaml(std::filesystem::path &path);
  // Config load_from_json(std::filesystem::path &path);
}