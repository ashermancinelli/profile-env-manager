
#include <string>
#include <vector>
using std::vector;
using std::string;

#include <fstream>
#include <algorithm>
using std::begin;
using std::end;

#include <profile.hpp>
#include <utils.hpp>

using namespace profile;

int main(int argc, char** argv)
{
  if(argc==1) { usage(); return 1; }

  vector<string> args(argv+1, argv+argc);
  auto profiles = init_profiles();

  for (int i=0; i<args.size(); i++)
  {
    const string& s = args[i];
    if (s.compare("load") == 0)
    {
      if (i==args.size()-1) { usage(); return 1; }
      auto p = std::find_if_not(begin(profiles), end(profiles),
          [=] (Profile* p) -> bool
          {
            return args[i+1].compare(p->name);
          });

      if (p == end(profiles)) { puts("Profile not found."); return 1; }

      (*p)->run();
      return 0;
    }
    else if (s.compare("show") == 0)
    {
      if (i==args.size()-1) { usage(); return 1; }
      auto p = std::find_if_not(begin(profiles), end(profiles),
          [=] (Profile* p) -> bool
          {
            return args[i+1].compare(p->name);
          });
      if (p == end(profiles)) { puts("Profile not found."); return 1; }

      (*p)->show(verbosity::loud);
      return 0;
    }
    else if (s.compare("avail") == 0)
    {
      puts("Available profiles:");
      for(const auto p : profiles) p->show();
      return 0;
    }
    else
    {
      usage();
      return 1;
    }
  }
  return 0;
}
