#include "exp.h"
#include "util.h"
#include <iostream>
#include <iomanip>
#include <cassert>

const char Divider = '|';

Exp::Exp(std::istream& in)
{
  m_params = ReadOp(in);
  m_temp = ReadOp(in);
  m_signal = ReadOp(in);
}

const Exp::Op Exp::ReadOp(std::istream& in)
{
  Op op;
  while(1) {
    EatWS(in);
    if(!in)
      break;
    if(in.peek() == Divider) {
      in.get();
      break;
    }

    int value;
    in >> value;
    op.push_back(value);
  }
  return op;
}

void Exp::GetMaxSizes(unsigned& params, unsigned& temps, unsigned& signals) const
{
  if(m_params.size() > params)
    params = m_params.size();
  if(m_temp.size() > temps)
    temps = m_temp.size();
  if(m_signal.size() > signals)
    signals = m_signal.size();
}

std::ostream& Exp::Write(std::ostream& out, unsigned params, unsigned temps, unsigned signals) const
{
  Write(out, m_params, params);
  Write(out, m_signal, signals);
  Write(out, m_temp, temps);
  out << "\n";
  return out;
}

void Exp::Write(std::ostream& out, const Op& op, unsigned count) const
{
  for(unsigned i=0;i<op.size();i++)
    out << std::setw(3) << op[i];
  for(unsigned i=op.size();i<count;i++)
    out << std::setw(3) << 0;
}

Exp *Exp::Translate(const std::vector<Slot>& params, unsigned tempStart, unsigned sigStart) const
{
  assert(params.size() >= m_params.size());

  std::auto_ptr<Exp> pExp(new Exp);

  for(unsigned i=0;i<m_params.size();i++)
    pExp->SetSlot(params[i], m_params[i]);

  for(unsigned i=0;i<m_temp.size();i++) {
    Slot slot;
    slot.type = Slot::TEMP;
    slot.index = i + tempStart;
    pExp->SetSlot(slot, m_temp[i]);
  }

  for(unsigned i=0;i<m_signal.size();i++)
    pExp->SetSignalSlot(i + sigStart, m_signal[i]);

  return pExp.release();
}

Exp *Exp::ShiftBy(unsigned paramShift, unsigned sigShift) const
{
  std::auto_ptr<Exp> pExp(new Exp);

  for(unsigned i=0;i<m_params.size();i++) {
    Slot slot;
    slot.type = Slot::PARAM;
    slot.index = i + paramShift;
    pExp->SetSlot(slot, m_params[i]);
  }

  for(unsigned i=0;i<m_temp.size();i++) {
    Slot slot;
    slot.type = Slot::TEMP;
    slot.index = i;
    pExp->SetSlot(slot, m_temp[i]);
  }

  for(unsigned i=0;i<m_signal.size();i++)
    pExp->SetSignalSlot(i + sigShift, m_signal[i]);

  return pExp.release();
}

Exp::Op& Exp::GetSlotType(Slot::TYPE type)
{
  switch(type) {
  case Slot::PARAM: 
    return m_params;
  case Slot::TEMP:
    return m_temp;
  }
  assert(false);
}

void Exp::SetSlot(const Slot& slot, int value)
{
  Op& op = GetSlotType(slot.type);
  if(slot.index >= op.size())
    op.resize(slot.index+1);
  op[slot.index] = value;
}

void Exp::SetSignalSlot(unsigned index, int value)
{
  if(index >= m_signal.size())
    m_signal.resize(index+1);
  m_signal[index] = value;
}
