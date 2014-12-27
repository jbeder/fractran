#pragma once

#include <string>
#include <iosfwd>

struct Slot {
  enum TYPE { PARAM, TEMP, NONE };
  TYPE type;
  std::string name;
  unsigned index;
};

std::ostream& operator<<(std::ostream& out, const Slot& slot);

const Slot ToSlot(const std::string& name);
