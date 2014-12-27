#pragma once

#include "fn.h"
#include <vector>

class Call;
class SimpleFn;

class SeqFn: public Fn
{
 public:
  SeqFn(const std::string& input);
  virtual ~SeqFn();

  virtual SimpleFn *Compile(Program& program) const;

 private:
  std::vector<Call *> m_calls;
  unsigned m_tempStart;
};
