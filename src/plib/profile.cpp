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

  if (js.find("syscalls") != js.end())
  {
    puts("Found system calls");
  }

  if (js.find("env") != js.end())
  {
    puts("Found env vars");
  }

  if (js.find("args") != js.end())
  {
    puts("Found args");
  }
  return new Profile(name, bin);
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
  auto envvars = c_str_ar(this->envvars);

  if (syscalls.size() == 0)
  {
    auto sys = c_str_ar(this->syscalls);
    for(int i=0; i < syscalls.size(); i+=2)
    {
      setenv(sys[i], sys[i+1], true);
    }
  }

  execve(bin, args, envvars);
}

void Profile::show() const
{
  printf("name:\t%s\nbin:\t%s\n", this->name, this->bin);
}

}
