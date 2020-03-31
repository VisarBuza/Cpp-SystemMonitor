#include "processor.h"
#include "linux_parser.h"

#include <iostream>
#include <string>

// Return the aggregate CPU utilization
float Processor::Utilization() {
  if (currentValues.size() == 0) {
    ParseCurrentState();
    return 0.0;
  }

  previousValues = currentValues;
  currentValues.clear();
  ParseCurrentState();

  float prevTotal = Idle(previousValues) + NonIdle(previousValues);
  float total = Idle(currentValues) + NonIdle(currentValues);

  float totalDifference = total - prevTotal;
  float idleDifference = Idle(currentValues) - Idle(previousValues);

  return (totalDifference - idleDifference) / totalDifference;
}

// Calculate the amount of time spent on idle
int Processor::Idle(const std::vector<int>& state) {
  return state[3] + state[4];
}

// Calculate the amount of time spent utilized
int Processor::NonIdle(const std::vector<int>& state) {
  int sum = 0;
  for (int mode : state) {
    sum += mode;
  }
  sum -= (state[3] + state[4]);
  return sum;
}

// Parse the current state from the LinuxParser
void Processor::ParseCurrentState(){
  for (std::string token : LinuxParser::CpuUtilization()) 
    currentValues.push_back(std::stoi(token));
}