#ifndef __UTILS_H
#define __UTILS_H

#include <vector>
using std::vector;
#include <string>
using std::string;
#include <dirent.h>
#include <cstdlib>
#include <cassert>
#include <profile.hpp>

namespace profile
{

static const vector<string> default_paths =
{
  "/usr/local/share/profiles/",
  "/usr/share/profiles/",
  "/share/profiles/",
  "~/.local/share/profiles/",
  "~/.local/profiles/",
  "~/.profiles/",
  ".",
};

void usage();
vector<Profile*> init_profiles();

}

#endif
