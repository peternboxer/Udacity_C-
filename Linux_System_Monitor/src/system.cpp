#include "system.h"

#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "linux_parser.h"
#include "process.h"
#include "processor.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

Processor& System::Cpu() {
  Processor processor;
  cpu_ = processor;
  return cpu_;
}

vector<Process>& System::Processes() {
  std::vector<int> PIDs = LinuxParser::Pids();
  // clear existing pids, system refresh at 1 Hz per ncurses_display.cpp
  processes_.clear();
  /* Improve Performance */
  processes_.reserve(PIDs.size());
  for (int pid : PIDs) {
    Process p(pid);
    // filter out 0 ram process
    if (std::stoi(p.Ram()) > 0) {
      processes_.emplace_back(p);
    }
  }
  
  std::sort(processes_.begin(), processes_.end(), [](Process& p1, Process& p2) {
    return p1.CpuUtilization() > p2.CpuUtilization();
  });
  return processes_;
}

std::string System::Kernel() { return LinuxParser::Kernel(); }

float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

long int System::UpTime() { return LinuxParser::UpTime(); }
