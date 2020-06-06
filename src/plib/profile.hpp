#ifndef __PROFILE_H
#define __PROFILE_H

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <utility>
using std::pair;
using std::make_pair;

#include <fstream>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>

#include <nlohmann/json.hpp>
using nlohmann::json;

#include <utils.hpp>

namespace profile
{

enum verbosity
{
  quiet,
  medium,
  loud,
};

struct Profile
{
  // Name of profile
  char* name;

  // Binary that will replace this process
  char* bin;

  // System calls to be made before starting new process
  vector<string> commands;

  // Environment variables to be set upon start of new process
  vector<pair<string, string>> envvars;

  // Other system environments to be loaded before this
  vector<string> dependencies;

  Profile(const char* name, const char* bin);
  Profile() : Profile("DEFAULT_PROFILE_NAME", "/bin/bash") {}
  void run();
  void show(verbosity v=quiet) const;
  void set_sys(Profile*);
  void set_sys(const string&);
  static Profile* from(std::ifstream);
  static Profile* from(json);
  static Profile* from(const string& s);
};

}

#endif
