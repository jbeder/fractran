#pragma once

#include <iosfwd>

namespace YAML {
class Node;
}
class SimpleFn;
class Program;

class Fn {
 public:
  virtual ~Fn() {}

  virtual SimpleFn* Compile(Program& program) const = 0;
};

Fn* CreateFn(const YAML::Node& fn);
