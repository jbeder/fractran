#pragma once

#include "simplefn.h"

class Exp;

class IfFn: public SimpleFn
{
 public:
  IfFn(const SimpleFn& bodyFn);

 private:
  void AddIfExp(bool needsSignal);
  void UpdateShifted(Exp *pShifted, bool needsSignal);
  Exp *CreateDoneSignal();
};
