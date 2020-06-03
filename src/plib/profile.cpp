#include "profile.hpp"

namespace profile
{

char ** c_str_ar(const vector<string> v)
{
  if (v.size() == 0) return nullptr;
  char ** ar = new char*[v.size()];
  for (int i=0; i<v.size(); i++)
  {
    ar[i] = strdup(v[i].c_str());
  }
  return ar;
}

Profile* Profile::from(json js)
{
  char* name = strdup(js["name"].get<std::string>().c_str());
  char* bin = strdup(js["bin"].get<std::string>().c_str());
  auto p = new Profile(name, bin);

  if (js.find("syscalls") != js.end())
  {
    p->syscalls = js["syscalls"].get<vector<string>>();
  }

  if (js.find("args") != js.end())
  {
    p->args = js["args"].get<vector<string>>();
  }
  return p;
}

Profile* Profile::from(std::ifstream f)
{
  json js;
  if (f)
  {
    f >> js;
  }
  return from(js);
}

Profile::Profile(const char* name, const char* bin)
{
  this->name = strdup(name);
  this->bin = strdup(bin);
}

void Profile::run() const
{
  printf("Loading profile %s\n", name);

  auto args = c_str_ar(this->args);

  if (syscalls.size() == 0)
  {
    auto sys = c_str_ar(this->syscalls);
    for(int i=0; i < syscalls.size(); i++)
    {
      system(sys[i]);
    }
  }

  execvp(bin, args);
}

void Profile::show(verbosity v) const
{
  printf("name:\t%s\nbin:\t%s\n", this->name, this->bin);

  if (v > verbosity::quiet)
  {
    printf("\nbinary arguments:");
    for(auto c : args) printf("\n\t%s", c.c_str());

    printf("\nsystem calls:");
    for(auto c : syscalls) printf("\n\t%s", c.c_str());
  }
}

}
