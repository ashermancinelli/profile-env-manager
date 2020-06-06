#ifndef __UTILS_H
#define __UTILS_H

#include <vector>
using std::vector;

#include <string>
using std::string;

#include <optional>
using std::optional;

#include <dirent.h>
#include <cstdlib>
#include <cassert>
#include <profile.hpp>

namespace profile
{

class Profile;

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
optional<string> resolve_path(const string);
bool has_ext(const std::string& pth, const std::string& ext);
struct directory_iterator;
bool is_directory(const std::string& pth);
bool is_file(const std::string& f);
string expand_path(string pth);

}

#endif
