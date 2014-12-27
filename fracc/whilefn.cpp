#include "whilefn.h"
#include "exp.h"
#include <sstream>
#include <iostream>

const int whileSlots = 10;

WhileFn::WhileFn(const SimpleFn &bodyFn) {
  RequireSignal();

  if (bodyFn.NeedsSignal())
    Add(CreateGrabSignal());

  Add(CreateStaySignal(bodyFn.NeedsSignal()));

  for (unsigned i = 0; i < bodyFn.Size(); i++) {
    Exp *pExp = bodyFn.Get(i);
    Exp *pShifted =
        pExp->ShiftBy(1, whileSlots + (bodyFn.NeedsSignal() ? 2 : 0));
    UpdateShifted(pShifted, bodyFn.NeedsSignal());
    Add(pShifted);
  }

  Add(CreateGotoSignal(bodyFn.NeedsSignal()));
  AddWhileExp(bodyFn.NeedsSignal());
}

Exp *WhileFn::CreateGrabSignal() {
  Exp *pMoveSignal = new Exp;
  pMoveSignal->SetSignalSlot(whileSlots - 2, -1);
  pMoveSignal->SetSignalSlot(whileSlots, 1);
  pMoveSignal->SetSignalSlot(whileSlots + 2, 1);
  return pMoveSignal;
}

Exp *WhileFn::CreateStaySignal(bool needsSignal) {
  Exp *pStaySignal = new Exp;
  if (needsSignal) {
    pStaySignal->SetSignalSlot(whileSlots, 1);
    pStaySignal->SetSignalSlot(whileSlots + 1, -1);
  } else {
    pStaySignal->SetSignalSlot(whileSlots - 2, 1);
    pStaySignal->SetSignalSlot(whileSlots - 1, -1);
  }
  return pStaySignal;
}

void WhileFn::UpdateShifted(Exp *pShifted, bool needsSignal) {
  if (needsSignal) {
    pShifted->SetSignalSlot(whileSlots, -1);
    pShifted->SetSignalSlot(whileSlots + 1, 1);
  } else {
    pShifted->SetSignalSlot(whileSlots - 2, -1);
    pShifted->SetSignalSlot(whileSlots - 1, 1);
  }
}

Exp *WhileFn::CreateGotoSignal(bool needsSignal) {
  Exp *pGotoSignal = new Exp;
  if (needsSignal)
    pGotoSignal->SetSignalSlot(whileSlots, -1);
  else
    pGotoSignal->SetSignalSlot(whileSlots - 2, -1);

  pGotoSignal->SetSignalSlot(0, 1);
  return pGotoSignal;
}

namespace {
Exp *CreateExp(int p0, const std::string &signals, bool needsSignal) {
  Exp *pExp = new Exp;
  pExp->SetSlot(ToSlot("p0"), p0);
  std::stringstream stream(signals);
  int value;
  unsigned index = 0;
  while (stream >> value) {
    pExp->SetSignalSlot(index, value);
    index++;
  }
  return pExp;
}
}

void WhileFn::AddWhileExp(bool needsSignal) {
  Add(CreateExp(0, " 0   0   0   0   0   1   0  -2   0", needsSignal));
  Add(CreateExp(0, " 0   0   0   0   0  -1   1   1   0", needsSignal));
  Add(CreateExp(0, " 0   0   0   0   0   0  -1   0   0", needsSignal));
  Add(CreateExp(0, " 1  -1   0   0   0   0   0   0   0", needsSignal));
  Add(CreateExp(-1, "-1   1   0   0   1   1   0   1   0", needsSignal));
  Add(CreateExp(0, " 0   0   1  -1   0   0   0   0   0", needsSignal));
  Add(CreateExp(0, "-1   0   1   0   0   0   0   0   0", needsSignal));
  Add(CreateExp(1, " 0   0  -1   1  -1   0   0   0   0", needsSignal));
  Add(CreateExp(0, " 0   0  -1   0   0   0   0  -1   1", needsSignal));
  Add(CreateExp(0, " 0   0  -1   0   0   0   0   0   0", needsSignal));
}
