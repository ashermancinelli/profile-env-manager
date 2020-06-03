#include <utils.hpp>

#include <sys/utsname.h>

namespace profile
{

void usage()
{
  puts("Usage:");
  puts("");
}

vector<Profile*> init_profiles()
{
  struct utsname buffer;
  if (uname(&buffer) != 0)
  {
    assert(false && "Uname failed for some reason.");
  }
  char* nodename = buffer.nodename;

  vector<Profile> ps;
  bool found_any = false;
  for (const string& path_str : default_paths)
  {
    path p(path_str);
    p /= nodename;
    if(!is_directory(p)) continue;
    for (directory_iterator itr(p); itr!=directory_iterator(); ++itr)
    {
      path profile_path = itr->path().leaf();
      if (!profile_path.has_extension()) continue;
      if (!profile_path.extension().compare(".json")==0) continue;
      ps.push_back(Profile::from(std::ifstream(profile_path)));
      found_any = true;
    }
  }
  return ps;
}

}
