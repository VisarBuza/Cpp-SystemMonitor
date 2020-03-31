#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <vector>

class Processor {
 public:
  float Utilization();

 private:
  std::vector<int> previousValues{};
  std::vector<int> currentValues{};
  int Idle(const std::vector<int>& state);
  int NonIdle(const std::vector<int>& state);
  void ParseCurrentState();
};

#endif