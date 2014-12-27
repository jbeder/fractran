#include "call.h"
#include "exp.h"
#include "util.h"
#include "simplefn.h"
#include "program.h"
#include <iostream>
#include <sstream>
#include <cassert>

Call::Call(std::istream &input) : m_maxTemp(0) {
  ReadFnName(input);
  ReadParamSlots(input);
}

void Call::ReadFnName(std::istream &input) { m_name = ReadWord(input); }

void Call::ReadParamSlots(std::istream &input) {
  EatWS(input);
  assert(input.get() == '(');
  while (input) {
    std::string name = ReadWord(input);
    if (name == "")
      break;
    Slot slot = ToSlot(name);
    if (slot.type == Slot::TEMP && slot.index > m_maxTemp)
      m_maxTemp = slot.index;
    m_params.push_back(slot);
    EatWS(input);
    if (input.peek() == ',')
      input.get();
    else
      break;
  }

  EatWS(input);
  assert(input.get() == ')');
}

SimpleFn *Call::GetFn(Program &program) const {
  if (m_name == "while") {
    assert(m_params.size() >= 1);
    assert(m_params.back().type == Slot::NONE);
    return program.GetWhileFn(m_params.back().name);
  } else if (m_name == "if") {
    assert(m_params.size() >= 1);
    assert(m_params.back().type == Slot::NONE);
    return program.GetIfFn(m_params.back().name);
  }

  return program.GetFn(m_name);
}

Exp *Call::CreateGrabSignal(const Pos &pos) const {
  Exp *pMoveSignal = new Exp;
  pMoveSignal->SetSignalSlot(2 * pos.index, -1);
  pMoveSignal->SetSignalSlot(2 * pos.count + 2 * pos.needsSignalIndex, 1);
  pMoveSignal->SetSignalSlot(2 * pos.count + 2 * pos.needsSignalCount, 1);
  return pMoveSignal;
}

Exp *Call::CreateStaySignal(const Pos &pos) const {
  Exp *pStaySignal = new Exp;
  if (pos.needsSignal) {
    pStaySignal->SetSignalSlot(2 * pos.count + 2 * pos.needsSignalIndex, 1);
    pStaySignal->SetSignalSlot(2 * pos.count + 2 * pos.needsSignalIndex + 1,
                               -1);
  } else {
    pStaySignal->SetSignalSlot(2 * pos.index, 1);
    pStaySignal->SetSignalSlot(2 * pos.index + 1, -1);
  }
  return pStaySignal;
}

void Call::UpdateTranslatedExp(Exp *pTranslated, const Pos &pos) const {
  if (pos.needsSignal) {
    pTranslated->SetSignalSlot(2 * pos.count + 2 * pos.needsSignalIndex, -1);
    pTranslated->SetSignalSlot(2 * pos.count + 2 * pos.needsSignalIndex + 1, 1);
  } else {
    pTranslated->SetSignalSlot(2 * pos.index, -1);
    pTranslated->SetSignalSlot(2 * pos.index + 1, 1);
  }
}

Exp *Call::CreateDoneSignal(const Pos &pos) const {
  Exp *pDoneSignal = new Exp;
  if (pos.needsSignal)
    pDoneSignal->SetSignalSlot(2 * pos.count + 2 * pos.needsSignalIndex, -1);
  else
    pDoneSignal->SetSignalSlot(2 * pos.index, -1);
  return pDoneSignal;
}

Exp *Call::CreateAdvanceSignal(const Pos &pos) const {
  Exp *pAdvanceSignal = new Exp;
  if (pos.needsSignal)
    pAdvanceSignal->SetSignalSlot(2 * pos.count + 2 * pos.needsSignalIndex, -1);
  else
    pAdvanceSignal->SetSignalSlot(2 * pos.index, -1);
  pAdvanceSignal->SetSignalSlot(2 * pos.index + 2, 1);
  return pAdvanceSignal;
}

void Call::AppendTo(SimpleFn &fn, unsigned index, unsigned count,
                    unsigned needsSignalIndex, unsigned needsSignalCount,
                    Program &program, unsigned tempStart) const {
  SimpleFn *pCall = GetFn(program);
  if (!pCall)
    return;

  Pos pos(pCall->NeedsSignal(), index, count, needsSignalIndex,
          needsSignalCount);

  if (pCall->NeedsSignal())
    fn.Add(CreateGrabSignal(pos));

  fn.Add(CreateStaySignal(pos));

  for (unsigned i = 0; i < pCall->Size(); i++) {
    const Exp *pExp = pCall->Get(i);
    Exp *pTranslated =
        pExp->Translate(m_params, tempStart, 2 * count + 2 * needsSignalCount);
    UpdateTranslatedExp(pTranslated, pos);
    fn.Add(pTranslated);
  }
  if (index + 1 == count)
    fn.Add(CreateDoneSignal(pos));
  else
    fn.Add(CreateAdvanceSignal(pos));
}
