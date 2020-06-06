#include <utils.hpp>

#include <sys/utsname.h>
#include <sys/stat.h>

namespace profile
{

void usage()
{
  puts("Usage:");
  puts("\tshow");
  puts("\tavail");
  puts("\tload");
  puts("\thelp");
}

bool is_directory(const std::string& pth)
{
  DIR *dp;
  dp = opendir(pth.c_str());
  if (dp == NULL) return false;
  return true;
}

bool is_file(const std::string& f)
{
  struct stat path_stat;
  stat(f.c_str(), &path_stat);
  return S_ISREG(path_stat.st_mode);
}

string expand_path(string pth)
{
  if (pth.c_str()[0] != '~') return pth;
  auto home = string(getenv("HOME"));
  return home + '/' + pth.substr(1);
}

struct directory_iterator
{
private:
  string base_path;
  vector<string> leaves;
  vector<string>::iterator lidx;

public:
  directory_iterator(const string& path) : base_path(path)
  {
    assert(is_directory(path) && "Directory path not found");
    DIR* dp = opendir(path.c_str());
    struct dirent *entry;

    while((entry = readdir(dp)))
    {
      if (is_directory(path + "/" + entry->d_name)) continue;
      leaves.push_back(path + "/" + entry->d_name);
    }
    lidx = leaves.begin();
  }
  bool good() { return lidx != leaves.end(); }
  string next() { return *lidx++; }
};

bool has_ext(const std::string& pth, const std::string& ext)
{
  std::size_t found = pth.find(ext);

  // not found
  if (found == std::string::npos) return false;

  // found, but not the last extension
  if (found+ext.length() != pth.length()) return false;

  return true;
}

vector<Profile*> init_profiles()
{
  struct utsname buffer;
  if (uname(&buffer) != 0)
  {
    assert(false && "Uname failed for some reason.");
  }
  auto nodename = string(buffer.nodename);

  vector<Profile*> ps;
  bool found_any = false;
  for (const string& path_str : default_paths)
  {
    // Add the nodename to the path so that in shared directory
    // environments, the profiles may differ from node to node
    string path = expand_path(path_str) + nodename;
    if(!is_directory(path)) continue;
    directory_iterator di(path);

    while (di.good())
    {
      const std::string& leaf = di.next();
      if (!has_ext(leaf, ".json")) continue;
      ps.push_back(
        Profile::from(
          std::ifstream(
            strdup(leaf.c_str()))));
    }
  }
  return ps;
}

optional<string> resolve_path(const string fn)
{
  auto home = getenv("PROFILEHOME");
  if (home != nullptr)
  {
    if (is_file(home + fn))
    {
      return string(home + fn);
    }
  }
  else
  {
    for (const string& path_str : default_paths)
    {
      if (is_file(path_str + fn))
      {
        return path_str + fn;
      }
    }
  }
  return {};
}

}
