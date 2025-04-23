#include <filesystem>
#include <iostream>
#include "config.hpp"

#include <yaml-cpp/yaml.h>

namespace veloq {
  Config load_from_yaml(std::filesystem::path &path) {

    // check if file exists
    if (!std::filesystem::exists(path)) {
      throw std::runtime_error("Config file does not exist: " + path.string());
    }

    // load file as yaml object
    YAML::Node node = YAML::LoadFile(path.string());

    Config config;

    // create config object and set given flags and options

    // flags
    if (node["diff"]) {
      config.diff = node["diff"].as<bool>();
    }

    if (node["live"]) {
      config.live = node["live"].as<bool>();
    }

    if (node["no_benchmark"]) {
      config.no_benchmark = node["no_benchmark"].as<bool>();
    }

    if (node["verbose"]) {
      config.verbose = node["verbose"].as<bool>();
    }

    // options (std::optional<T>)
    if (node["commands"]) {
      config.commands = node["commands"].as<std::vector<std::string>>();
    }

    if (node["runs"]) {
      config.runs = node["runs"].as<unsigned int>();
    }

    if (node["name"]) {
      config.name = node["name"].as<std::string>();
    }

    if (node["filter"]) {
      config.filter = node["filter"].as<std::string>();
    }

    if (node["highlight"]) {
      config.highlight = node["highlight"].as<std::string>();
    }

    if (node["output"]) {
      config.output = node["output"].as<std::string>(); // std::filesystem::path aus string
    }

    return config;
  }

  Config load_from_json() {
    // check if file exists

    // load file as yaml object

    // create config object and set given properties
    Config config;


    return config;
  }
}