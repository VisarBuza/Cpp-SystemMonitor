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

int Process::Pid() { return this->id; }

float Process::CpuUtilization() {
  float totalTime = 0;
  for (string token : LinuxParser::ProcessCpuUtilization(this->id)) {
    totalTime += std::stoi(token);
  }
  int seconds = LinuxParser::UpTime() - UpTime();

  return ((totalTime / sysconf(_SC_CLK_TCK)) / seconds);
}

string Process::Command() {
  if (command.empty()) {
    command = LinuxParser::Command(this->id);
  }
  return command;
}

string Process::Ram() {
  return Format::ConvertToMb(LinuxParser::Ram(this->id));
}

string Process::User() {
  if (user.empty()) {
    user = LinuxParser::User(this->id);
  }
  return user;
}

long int Process::UpTime() { return LinuxParser::UpTime(this->id); }

bool Process::operator<(Process& a) {
  return CpuUtilization() < a.CpuUtilization();
}