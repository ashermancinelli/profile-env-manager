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

  if (js.find("envvars") != js.end())
  {
    p->envvars = js["envvars"].get<vector<pair<string, string>>>();
  }

  if (js.find("commands") != js.end())
  {
    p->commands = js["commands"].get<vector<string>>();
  }

  if(js.find("dependencies") != js.end())
  {
    p->dependencies = js["dependencies"].get<vector<string>>();
  }
  return p;
}

Profile* Profile::from(std::ifstream f)
{
  json js;
  if (f) f >> js;
  return from(js);
}

Profile* Profile::from(const string& s)
{ 
  if (is_file(s))
    return from(std::ifstream(s));

  auto path = resolve_path(s);
  if (path)
    return from(std::ifstream(*path));

  throw std::runtime_error("Could not find dependency");
}

Profile::Profile(const char* name, const char* bin)
{
  this->name = strdup(name);
  this->bin = strdup(bin);
}

void Profile::set_sys(Profile* p)
{
  for (const auto [var, val] : p->envvars)
  {
    setenv(var.c_str(), val.c_str(), 1);
  }
}

void Profile::set_sys(const string& profile)
{
  Profile* p = Profile::from(profile);
  set_sys(p);
}

void Profile::run()
{
  set_sys(this);
  for(const auto& dep : dependencies)
    set_sys(dep);

  execvp(bin, NULL);
}

void Profile::show(verbosity v) const
{
  if (v == verbosity::quiet)
  {
    printf("\t%s\n", this->name);
  }
  else
  {
    printf("name:\t%s\nbin:\t%s\n", this->name, this->bin);

    printf("\nenvironment variables:");
    for(const auto [var, val] : envvars)
      printf("\n\t%s = %s", var.c_str(), val.c_str());

    printf("\ncommands:");
    for(const auto cmd : commands)
      printf("\n\t%s", cmd.c_str());

    printf("\ndependencies:");
    for(const auto dep : dependencies)
      printf("\n\t%s", dep.c_str());
  }
}

}
