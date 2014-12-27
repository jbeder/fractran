#pragma once

#include <map>
#include <string>

class Fn;
class SimpleFn;
namespace YAML {
class Node;
}

class Program {
 public:
  Program(const YAML::Node& fns);
  ~Program();

  SimpleFn* GetFn(const std::string& name);
  SimpleFn* GetWhileFn(const std::string& name);
  SimpleFn* GetIfFn(const std::string& name);

 private:
  void ReadFn(const std::string& name, const YAML::Node& fn);

 private:
  typedef std::map<std::string, Fn*> Fns;
  Fns m_fns;

  typedef std::map<std::string, SimpleFn*> SimpleFns;
  SimpleFns m_compiledFns;
  SimpleFns m_whileFns;
  SimpleFns m_ifFns;
};
