#include "linux_parser.h"

#include <dirent.h>
#include <unistd.h>

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.emplace_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// /proc/meminfo
float LinuxParser::MemoryUtilization() {
  string key, size, unit;
  string line;
  float TotalMem, FreeMem, Buffers, Cached;
  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> size >> unit;
      if (key == "MemTotal:") {
        TotalMem = std::stoi(size);
      } else if (key == "MemFree:") {
        FreeMem = std::stoi(size);
      } else if (key == "Cached:") {
        Cached = std::stoi(size);
      } else if (key == "Buffers:") {
        Buffers = std::stoi(size);
      }
    }
    float UtiMem = (TotalMem - FreeMem - Cached - Buffers) / TotalMem;
    return UtiMem;
  }
  return 0;
}

// /proc/uptime
long LinuxParser::UpTime() {
  std::string value("0");
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    stream >> value;
    return std::stol(value);
  }
  return 0.0;
}

// Instructions from Udacity mentor's notes:
// https://knowledge.udacity.com/questions/129844
long LinuxParser::Jiffies() { return UpTime() * sysconf(_SC_CLK_TCK); }

// Instructions from Udacity mentor's notes:
// https://knowledge.udacity.com/questions/129844
long LinuxParser::ActiveJiffies(int pid) {
  std::string line;
  long value;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatFilename);
  long sum = 0;
  if (stream.is_open()) {
    int counter = 1;
    while (stream >> value) {
      if (counter > 13 && counter < 18) {
        sum += value;
      }
      counter++;
    }
    return sum;
  }
  return sum;
}

// Instructions from Udacity mentor's notes:
// https://knowledge.udacity.com/questions/129844
long LinuxParser::ActiveJiffies() {
  std::string line, key, value;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    // dump "cpu"
    linestream >> key;
    long sum = 0;
    while (linestream >> value) {
      sum += std::stol(value);
    }
    return sum;
  }
  return 0;
}

// Instructions from Udacity mentor's notes:
// https://knowledge.udacity.com/questions/129844
long LinuxParser::IdleJiffies() {
  std::string line, value;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    // dump "cpu"
    linestream >> value;
    long sum = 0;
    int counter = 0;

    while (linestream >> value && counter < 5) {
      if (counter == 3 || counter == 4) sum += std::stol(value);
      counter++;
    }
    return sum;
  }
  return 0;
}

// /proc/stat
// obtain aggregate CPU info only
vector<string> LinuxParser::CpuUtilization() {
  std::vector<string> ret;
  std::string line, value;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    // dump "cpu"
    linestream >> value;
    while (linestream >> value) {
      ret.push_back(value);
    }
    return ret;
  }
  return {};
}

// helper function to calculate cpu utilization of individual process
std::vector<float> LinuxParser::CpuUtilization(int pid) {
  std::vector<float> cpuData;
  std::string line, value;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatFilename);
  if (stream.is_open()) {
    int counter = 1;
    while (stream >> value) {
      // utime
      if (counter == 14) {
        cpuData.emplace_back(std::stof(value));
      }
      // stime
      else if (counter == 15) {
        cpuData.emplace_back(std::stof(value));
      }
      // cutime
      else if (counter == 16) {
        cpuData.emplace_back(std::stof(value));
      }
      // cstime
      else if (counter == 17) {
        cpuData.emplace_back(std::stof(value));
      }
      // starttime
      else if (counter == 22) {
        cpuData.emplace_back(std::stof(value));
      }
      counter++;
    }
  }
  return cpuData;
}

// /proc/stat
int LinuxParser::TotalProcesses() {
  std::string line, value;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while (getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> value;
      if (value != "processes") {
        continue;
      } else {
        linestream >> value;
        return std::stoi(value);
      }
    }
  }
  return 0;
}

// /proc/stat
int LinuxParser::RunningProcesses() {
  std::string line, value;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while (getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> value;
      if (value != "procs_running") {
        continue;
      } else {
        linestream >> value;
        return std::stoi(value);
      }
    }
  }
  return 0;
}

/*  /proc/[pid]/cmdline */
string LinuxParser::Command(int pid) {
  std::string line;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kCmdlineFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
  }
  return line;
}

/*  /proc/ [pid] / status */
string LinuxParser::Ram(int pid) {
  std::string line, key, value("0");
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;
      if (key == "VmRSS:") {
        int ram_int = std::stoi(value) / 1024;
        value = std::to_string(ram_int);
        return value;
      }
    }
  }
  return value;
}

/*  /proc/ [pid] / status */
string LinuxParser::Uid(int pid) {
  std::string line, key, value;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> key;
      if (key == "Uid:") {
        linestream >> value;
        return value;
      }
    }
  }
  return value;
}

// /etc/passwd
string LinuxParser::User(int pid) {
  std::string uid = LinuxParser::Uid(pid);
  std::string line;
  std::string usrname, x, id;
  std::ifstream stream(kPasswordPath);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      // replace : with space
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      linestream >> usrname >> x >> id;
      if (id == uid) {
        return usrname;
      }
    }
  }
  return string();
}

// /proc/ [pid] / stat
long LinuxParser::UpTime(int pid) {
  std::string line, value;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatFilename);
  if (stream.is_open()) {
    int counter = 0;
    while (counter < 22) {
      stream >> value;
      counter++;
    }
    long ret = std::stol(value) / sysconf(_SC_CLK_TCK);
    return LinuxParser::UpTime() - ret;
  }
  return 0;
}