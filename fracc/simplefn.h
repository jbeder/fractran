#pragma once

#include "fn.h"
#include <vector>

class Exp;

class SimpleFn : public Fn {
 public:
  SimpleFn() {}
  SimpleFn(const std::string& str);
  SimpleFn(const SimpleFn& rhs);
  virtual ~SimpleFn();

  virtual SimpleFn* Compile(Program& program) const;
  void Add(Exp* pExp) { m_exps.push_back(pExp); }

  std::ostream& Write(std::ostream& out) const;

  void RequireSignal() { m_needsSignal = true; }
  bool NeedsSignal() const { return m_needsSignal; }

  unsigned Size() const { return m_exps.size(); }
  Exp* Get(unsigned i) const { return m_exps[i]; }

 private:
  bool m_needsSignal;
  std::vector<Exp*> m_exps;
};
