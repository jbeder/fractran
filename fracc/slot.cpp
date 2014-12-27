#include "slot.h"
#include <string>
#include <sstream>
#include <iostream>

std::ostream& operator<<(std::ostream& out, const Slot& slot) {
  switch (slot.type) {
    case Slot::PARAM:
      out << "p";
      break;
    case Slot::TEMP:
      out << "temp";
      break;
  }
  out << slot.index;
}

const Slot ToSlot(const std::string& name) {
  Slot slot;
  std::string prefix = name, suffix;
  for (unsigned i = 0; i < name.size(); i++) {
    if ('0' <= name[i] && name[i] <= '9') {
      prefix = name.substr(0, i);
      suffix = name.substr(i);
      break;
    }
  }

  if (prefix == "p")
    slot.type = Slot::PARAM;
  else if (prefix == "temp")
    slot.type = Slot::TEMP;
  else {
    slot.type = Slot::NONE;
    slot.name = prefix;
  }

  std::stringstream stream(suffix);
  stream >> slot.index;
  return slot;
}
