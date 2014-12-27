#include "seqfn.h"
#include "call.h"
#include "exp.h"
#include "program.h"
#include "simplefn.h"
#include <sstream>
#include <iostream>
#include <memory>

SeqFn::SeqFn(const std::string& input)
{
  std::stringstream stream(input);
  std::string line;

  m_tempStart = 0;
  while(std::getline(stream, line)) {
    std::stringstream tmp(line);
    m_calls.push_back(new Call(tmp));
    unsigned maxTemp = m_calls.back()->GetMaxTemp();
    if(maxTemp >= m_tempStart)
      m_tempStart = maxTemp + 1;
  }
}

SeqFn::~SeqFn()
{
  for(unsigned i=0;i<m_calls.size();i++)
    delete m_calls[i];
}

SimpleFn *SeqFn::Compile(Program& program) const
{
  std::auto_ptr<SimpleFn> pCompiled(new SimpleFn);
  pCompiled->RequireSignal();
  unsigned needsSignalCount = 0;
  for(unsigned i=0;i<m_calls.size();i++) {
    SimpleFn *pFn = m_calls[i]->GetFn(program);
    if(pFn && pFn->NeedsSignal())
      needsSignalCount++;
  }

  unsigned needsSignalIndex = 0;
  for(unsigned i=0;i<m_calls.size();i++) {
    m_calls[i]->AppendTo(*pCompiled, i, m_calls.size(), needsSignalIndex, needsSignalCount, program, m_tempStart);
    SimpleFn *pFn = m_calls[i]->GetFn(program);
    if(pFn && pFn->NeedsSignal())
      needsSignalIndex++;
  }

  return pCompiled.release();
}
