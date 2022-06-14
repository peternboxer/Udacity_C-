#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"
#include "process.h"

// Helper constructor to assign pid
Process::Process(int pid) {
  _pid = pid;
  _user = LinuxParser::User(pid);
  _ram = LinuxParser::Ram(pid);
  _cmd = LinuxParser::Command(pid);
  _uptime = LinuxParser::UpTime(pid);
  _cpu = CpuUtilization();
}

int Process::Pid() { return _pid; }

float Process::CpuUtilization() const {
  std::vector<float> data = LinuxParser::CpuUtilization(_pid);
  float uptime = LinuxParser::UpTime();
  float utime = data[0];
  float stime = data[1];
  float cutime = data[2];
  float cstime = data[3];
  float starttime = data[4];

  float total_time = utime + stime + cutime + cstime;
  float seconds = uptime - (starttime / sysconf(_SC_CLK_TCK));

  return (total_time / sysconf(_SC_CLK_TCK)) / seconds;
}

std::string Process::Command() { return _cmd; }

std::string Process::Ram() { return _ram; }

std::string Process::User() { return _user; }

long int Process::UpTime() { return _uptime; }

bool Process::operator<(Process const& a) const {
  return this->CpuUtilization() > a.CpuUtilization();
}