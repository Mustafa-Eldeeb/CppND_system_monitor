#ifndef PROCESSOR_H
#define PROCESSOR_H


#include <array>
#include <vector>

class Processor {
 public:
  Processor(); //contructor
  float Utilization();  // TODO: See src/processor.cpp
  
  long getTotalJiffies();
  // TODO: Declare any necessary private members
 private:
 void CalculateDeltaTime(std::array<long,3>&,std::array<long,3>&);
 virtual void GetLinuxParserForJiffies(std::array<long,3>&);
 float CalculateUtilization();
 void UpdatePrevJiffies();
 std::array<long,3> current_cpu_jiffies_;
 std::array<long,3> prev_cpu_jiffies_;
 std::array<float,3> delta_jiffies_;
};

#endif