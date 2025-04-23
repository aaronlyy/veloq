#include <string>
#include <vector>
#include <filesystem>
#include <optional>

namespace veloq {
  struct Config {
    // flags
    bool record; // -r/--record (add command output to save file with time offsets)
    bool show_diff; // -d/--diff (show diff of outputs)
    bool live_output; // -l/--live (print command output while running)
    bool no_benchmark; // --no-benchmark (hide benchmark output after command run)
    bool verbose; //-v/--verbose (print debug info while running)

    // options
    std::optional<std::vector<std::string>> commands; // maybe later own command struct

    std::optional<unsigned int> runs_per_command; // how often the given commands should be run, default is 1, only makes sense while benchmarking
    std::optional<std::string> name; // -n/--name (name of current run, used in savefile)
    std::optional<std::string> filter_regex; // -f/--filter (filter lines using regex)
    std::optional<std::string> highlight_regex; // -h/--highlight (highlight lines using regex)
    std::optional<std::filesystem::path> output_path; // -o/--output path to savefile
  };

  Config load_from_yaml(std::filesystem::path &path);
  Config load_from_json(std::filesystem::path &path);
}