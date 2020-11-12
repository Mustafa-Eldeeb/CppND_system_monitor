#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(int pid, long total_jiffies);                                 //done
  int Pid();                               // TODO: See src/process.cpp //done
  std::string User();                      // TODO: See src/process.cpp //done
  std::string Command();                   // TODO: See src/process.cpp //done
  float CpuUtilization();                  // TODO: See src/process.cpp //done
  std::string Ram();                       // TODO: See src/process.cpp //done
  long int UpTime();                       // TODO: See src/process.cpp //done
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp //done
  void calculateCpuUtil(long total_jiffies);                            //done
  // TODO: Declare any necessary private members
 private:
    int pid_;
    float cpu_utiliaztion_;
};

#endif