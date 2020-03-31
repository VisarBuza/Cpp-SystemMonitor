#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "format.h"
#include "linux_parser.h"
#include "process.h"

using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
int Process::Pid() { return this->id; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() {
  float totalTime = 0;
  for (string token : LinuxParser::ProcessCpuUtilization(this->id)) {
    totalTime += std::stoi(token);
  }
  int seconds = LinuxParser::UpTime() - UpTime();

  return ((totalTime / sysconf(_SC_CLK_TCK)) / seconds);
}

// TODO: Return the command that generated this process
string Process::Command() {
  if (command.empty()) {
    command = LinuxParser::Command(this->id);
  }
  return command;
}

// TODO: Return this process's memory utilization
string Process::Ram() {
  return Format::ConvertToMb(LinuxParser::Ram(this->id));
}

// TODO: Return the user (name) that generated this process
string Process::User() {
  if (user.empty()) {
    user = LinuxParser::User(this->id);
  }
  return user;
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(this->id); }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process& a) {
  return CpuUtilization() < a.CpuUtilization();
}