#pragma once

#include "slot.h"
#include <iosfwd>
#include <string>
#include <vector>

class SimpleFn;
class Program;
class Exp;

class Call
{
 public:
  Call(std::istream& input);

  SimpleFn *GetFn(Program& program) const;

  void AppendTo(SimpleFn& fn, unsigned index, unsigned count, unsigned needsSignalIndex, unsigned needsSignalCount, Program& program, unsigned tempStart) const;
  unsigned GetMaxTemp() const { return m_maxTemp; }

 private:
  struct Pos {
  Pos(): needsSignal(false), index(0), count(0), needsSignalIndex(0), needsSignalCount(0) {}
  Pos(bool needsSignal_, unsigned index_, unsigned count_, unsigned needsSignalIndex_, unsigned needsSignalCount_)
  : needsSignal(needsSignal_), index(index_), count(count_), needsSignalIndex(needsSignalIndex_), needsSignalCount(needsSignalCount_) {}

    bool needsSignal;
    unsigned index, count;
    unsigned needsSignalIndex, needsSignalCount;
  };

  Exp *CreateGrabSignal(const Pos& pos) const;
  Exp *CreateStaySignal(const Pos& pos) const;
  void UpdateTranslatedExp(Exp *pTranslated, const Pos& pos) const;
  Exp *CreateDoneSignal(const Pos& pos) const;
  Exp *CreateAdvanceSignal(const Pos& pos) const;

 private:
  void ReadFnName(std::istream& input);
  void ReadParamSlots(std::istream& input);

 private:
  std::string m_name;
  std::vector<Slot> m_params;
  unsigned m_maxTemp;
};
