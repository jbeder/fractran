#include "fn.h"
#include "simplefn.h"
#include "seqfn.h"
#include "yaml-cpp/yaml.h"

Fn* CreateFn(const YAML::Node& fn) {
  std::string type = fn.GetTag();
  std::string str;
  fn >> str;
  if (type == "!simple")
    return new SimpleFn(str);
  else if (type == "!seq")
    return new SeqFn(str);
  return 0;
}
