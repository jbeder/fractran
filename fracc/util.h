#include <iostream>
#include <string>

inline void EatWS(std::istream& in) {
  while(in.peek() == ' ' || in.peek() == '\n')
    in.get();
}

inline void EatComment(std::istream& in) {
  if(in.peek() != '#')
    return;

  while(in && in.peek() != '\n')
    in.get();
  if(in.peek() == '\n')
    in.get();
}

inline bool IsWord(char ch) {
  return ('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z') || ('0' <= ch && ch <= '9') || ch == '_';
}

inline const std::string ReadWord(std::istream& in) {
  EatWS(in);
  std::string ret;
  while(in) {
    char ch = in.peek();
    if(IsWord(ch))
      ret += in.get();
    else
      break;
  }
  return ret;
}
