#include "program.h"
#include "simplefn.h"
#include "yaml-cpp/yaml.h"
#include <iostream>
#include <fstream>

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cerr << "Usage: fracc inputfile\n";
    return 0;
  }

  std::ifstream fin(argv[1]);
  YAML::Parser parser(fin);
  YAML::Node doc;
  parser.GetNextDocument(doc);
  Program program(doc);

  std::string name;
  std::cin >> name;
  SimpleFn *pFn = program.GetFn(name);
  if (pFn)
    pFn->Write(std::cout);

  return 0;
}
