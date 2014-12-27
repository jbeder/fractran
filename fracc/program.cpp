#include "program.h"
#include "fn.h"
#include "simplefn.h"
#include "whilefn.h"
#include "iffn.h"
#include "util.h"
#include "yaml-cpp/yaml.h"

Program::Program(const YAML::Node& fns)
{
  for(YAML::Iterator it=fns.begin();it!=fns.end();++it) {
    std::string name;
    it.first() >> name;
    ReadFn(name, it.second());
  }
}

Program::~Program()
{
  for(Fns::iterator it=m_fns.begin();it!=m_fns.end();++it)
    delete it->second;
  for(SimpleFns::iterator it=m_compiledFns.begin();it!=m_compiledFns.end();++it)
    delete it->second;
}

void Program::ReadFn(const std::string& name, const YAML::Node& fn)
{
  m_fns[name] = CreateFn(fn);
}

SimpleFn *Program::GetFn(const std::string& name)
{
  if(m_compiledFns[name])
    return m_compiledFns[name];

  const Fn *pFn = m_fns[name];
  if(!pFn)
    return 0;

  return m_compiledFns[name] = pFn->Compile(*this);
}

SimpleFn *Program::GetWhileFn(const std::string& name)
{
  if(m_whileFns[name])
    return m_whileFns[name];

  SimpleFn *pBodyFn = GetFn(name);
  if(!pBodyFn)
    return 0;

  return m_whileFns[name] = new WhileFn(*pBodyFn);
}

SimpleFn *Program::GetIfFn(const std::string& name)
{
  if(m_ifFns[name])
    return m_ifFns[name];

  SimpleFn *pBodyFn = GetFn(name);
  if(!pBodyFn)
    return 0;

  return m_ifFns[name] = new IfFn(*pBodyFn);
}
