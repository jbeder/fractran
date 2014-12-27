#include "iffn.h"
#include "exp.h"
#include <sstream>
#include <iostream>

const int ifSlots = 4;

IfFn::IfFn(const SimpleFn& bodyFn)
{
  RequireSignal();

  AddIfExp(bodyFn.NeedsSignal());

  for(unsigned i=0;i<bodyFn.Size();i++) {
    Exp *pExp = bodyFn.Get(i);
    Exp *pShifted = pExp->ShiftBy(1, ifSlots);
    UpdateShifted(pShifted, bodyFn.NeedsSignal());
    Add(pShifted);
  }

  Add(CreateDoneSignal());
}

namespace {
  Exp *CreateExp(int p0, const std::string& signals)
  {
    Exp *pExp = new Exp;
    pExp->SetSlot(ToSlot("p0"), p0);
    std::stringstream stream(signals);
    int value;
    unsigned index = 0;
    while(stream >> value) {
      pExp->SetSignalSlot(index, value);
      index++;
    }
    return pExp;
  }
}

void IfFn::AddIfExp(bool needsSignal)
{
  if(needsSignal)
    Add(CreateExp(-1, "-1   1   1   0  1"));
  else
    Add(CreateExp(-1, "-1   1   1   0"));
  Add(CreateExp( 0, "-1   0   0   0"));
  Add(CreateExp( 1, " 0  -1   0   0"));
  Add(CreateExp( 0, " 0   0   1  -1"));
}

void IfFn::UpdateShifted(Exp *pShifted, bool needsSignal)
{
  pShifted->SetSignalSlot(ifSlots - 2, -1);
  pShifted->SetSignalSlot(ifSlots - 1, 1);
}

Exp *IfFn::CreateDoneSignal()
{
  Exp *pExp = new Exp;
  pExp->SetSignalSlot(ifSlots - 2, -1);
  return pExp;
}
