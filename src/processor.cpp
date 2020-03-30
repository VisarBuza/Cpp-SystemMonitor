#include "processor.h"
#include "linux_parser.h"

#include <iostream>
#include <string>

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
  if (currentValues.size() == 0) {
    for (std::string token : LinuxParser::CpuUtilization()) {
      currentValues.push_back(std::stoi(token));
    }
    return 0.0;
  }

  previousValues = currentValues;
  currentValues.clear();

  for (std::string token : LinuxParser::CpuUtilization()) {
    currentValues.push_back(std::stoi(token));
  }

  float prevIdle = previousValues[3] + previousValues[4];
  float prevNonIdle = previousValues[0] + previousValues[1] +
                      previousValues[2] + previousValues[5] +
                      previousValues[6] + previousValues[7];
  float prevTotal = prevIdle + prevNonIdle;

  float idle = currentValues[3] + currentValues[4];
  float nonIdle = currentValues[0] + currentValues[1] + currentValues[2] +
                  currentValues[5] + currentValues[6] + currentValues[7];
  float total = idle + nonIdle;

  float totalDifference = total - prevTotal;
  float idleDifference = idle - prevIdle;
  
  return (totalDifference - idleDifference) / totalDifference;
}