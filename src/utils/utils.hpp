#ifndef __UTILS_H
#define __UTILS_H

#include <vector>
using std::vector;

#include <boost/filesystem>
using boost::filesystem;

#include <profile.hpp>

namespace profile
{

static constexpr vector<string> default_paths =
{
  "~/.profiles/",
}

void usage();
vector<Profile*> init_profiles();

}

#endif
