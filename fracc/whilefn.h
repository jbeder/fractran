#pragma once

#include "simplefn.h"

class Exp;

class WhileFn: public SimpleFn
{
 public:
  WhileFn(const SimpleFn& bodyFn);

 private:
  Exp *CreateGrabSignal();
  Exp *CreateStaySignal(bool needsSignal);
  void UpdateShifted(Exp *pShifted, bool needsSignal);
  Exp *CreateGotoSignal(bool needsSignal);
  void AddWhileExp(bool needsSignal);
};
