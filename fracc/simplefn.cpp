#include "simplefn.h"
#include "exp.h"
#include "util.h"
#include <sstream>
#include <iostream>

SimpleFn::SimpleFn(const std::string& str): m_needsSignal(false)
{
  std::stringstream stream(str);
  std::string line;
  while(std::getline(stream, line)) {
    std::stringstream tmp(line);
    EatWS(tmp);
    if(!tmp)
      continue;
    m_exps.push_back(new Exp(tmp));
  }

  for(unsigned i=0;i<m_exps.size();i++)
    if(m_exps[i]->UsesSignals())
      RequireSignal();
}

SimpleFn::SimpleFn(const SimpleFn& rhs): m_needsSignal(rhs.m_needsSignal) {
  for(unsigned i=0;i<rhs.m_exps.size();i++) {
    m_exps.push_back(new Exp(*rhs.m_exps[i]));
  }
}

SimpleFn::~SimpleFn()
{
  for(unsigned i=0;i<m_exps.size();i++)
    delete m_exps[i];
}

SimpleFn *SimpleFn::Compile(Program& program) const
{
  return new SimpleFn(*this);
}

std::ostream& SimpleFn::Write(std::ostream& out) const
{
  unsigned params = 0, temps = 0, signals = 0;
  for(unsigned i=0;i<m_exps.size();i++)
    m_exps[i]->GetMaxSizes(params, temps, signals);
  for(unsigned i=0;i<m_exps.size();i++)
    m_exps[i]->Write(out, params, temps, signals);
  return out;
}
