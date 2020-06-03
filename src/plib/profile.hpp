#ifndef __PROFILE_H
#define __PROFILE_H

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <fstream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>

#include <nlohmann/json.hpp>
using nlohmann::json;

namespace profile
{

struct Profile
{
  // Name of profile
  char* name;

  // Binary that will replace this process
  char* bin;

  // Arguments to binary to replace this process
  vector<string> args;

  // Environment variables to be set upon start of new process
  vector<string> envvars;

  // System calls to be made before starting new process
  vector<string> syscalls;

  Profile(const char* name, const char* bin);
  Profile() : Profile("DEFAULT_PROFILE_NAME", "/bin/bash") {}
  void run() const;
  void show() const;
  static Profile* from(std::ifstream);
  static Profile* from(json);
};

}

#endif
