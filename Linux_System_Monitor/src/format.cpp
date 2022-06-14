#include "format.h"
#include <string>

std::string Format::ElapsedTime(long seconds) {
  int HH, MM;
  long SS;
  std::string ret;

  HH = seconds / 3600;
  MM = (seconds % 3600) / 60;
  SS = (seconds % 3600) % 60;

  std::string H = std::to_string(HH);
  if (HH < 10) {
    H = '0' + H;
  }
  std::string M = std::to_string(MM);
  if (MM < 10) {
    M = '0' + M;
  }
  std::string S = std::to_string(SS);
  if (SS < 10) {
    S = '0' + S;
  }

  return H + ":" + M + ":" + S;
}