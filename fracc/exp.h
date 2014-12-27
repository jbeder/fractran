#pragma once

#include "slot.h"
#include <iosfwd>
#include <vector>

class Exp {
 public:
  Exp() {}
  Exp(std::istream& in);

  void GetMaxSizes(unsigned& params, unsigned& temps, unsigned& signals) const;
  std::ostream& Write(std::ostream& out, unsigned params, unsigned temps,
                      unsigned signals) const;
  Exp* Translate(const std::vector<Slot>& params, unsigned tempStart,
                 unsigned sigStart) const;
  Exp* ShiftBy(unsigned paramShift, unsigned sigShift) const;

  bool UsesSignals() const { return !m_signal.empty(); }

  void SetSlot(const Slot& slot, int value);
  void SetSignalSlot(unsigned index, int value);

 private:
  typedef std::vector<int> Op;

  Op& GetSlotType(Slot::TYPE type);
  const Op ReadOp(std::istream& in);
  void Write(std::ostream& out, const Op& op, unsigned count) const;

  Op m_params, m_temp, m_signal;
};
