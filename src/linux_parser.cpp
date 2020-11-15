#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"

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
  string os, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> kernel;
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
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization()
 { 
   string key,unit,line;
   float val;
   vector<float> mem_data{};
   std::ifstream stream(kProcDirectory+kMeminfoFilename);
   if(stream.is_open())
   {
     for(int i=0; i<5;i++)
     {
       std::getline(stream,line);
       std::istringstream line_stream(line);
       line_stream>>key>>val>>unit;
       mem_data.push_back(val);
     }
   }
   //memory utilization eqn
   float mem_util=(mem_data.at(MemTypes::kMemTotal_)-
                  mem_data.at(MemTypes::KMemBuffer_)-
                  mem_data.at(MemTypes::kMemFree_)-
                  mem_data.at(MemTypes::KMemCached_))/
                  (mem_data.at(MemTypes::kMemTotal_)); 

    return mem_util;
 }

// TODO: Read and return the system uptime
long int LinuxParser::UpTime() 
{ 
  string line; long val{0};
  std::ifstream stream(kProcDirectory+kUptimeFilename);
  if(stream.is_open())
  {
    std::getline(stream,line);
    std::istringstream line_stream(line);
    line_stream >> val;
  }
  return val;
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies()
{
  string line, cpu_str;
  long val, jiffies_total{0};
  std::ifstream stream(kProcDirectory+kStatFilename);
  if(stream.is_open())
  {
    std::getline(stream,line);
    std::istringstream line_stream(line);
    line_stream >> cpu_str;
    while(line_stream >> val)
    {
      jiffies_total +=val;
    }
  }
  return jiffies_total;
}

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid)
{
  long int val{0},jiffies_active{0};
  std::string key,line;

  std::ifstream stream(kProcDirectory+to_string(pid)+kStatFilename);
  if(stream.is_open())
  {
    std::getline(stream,line);
    std::istringstream line_stream(line);
    for(int i=0; i<13;++i)
    {
      line_stream >> key;
    }

    for(int i=0; i<4;++i)
    {
      line_stream >> val;
      jiffies_active+=val;
    }
    return jiffies_active;
  }
  return jiffies_active; //return initialized active jiffies
}

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() 
{ 
  std::string line, cpu_str;
  long int val,jiffies_active{0};
  std::vector<int> cpu_data{};
  std::ifstream stream(kProcDirectory+kStatFilename);
  if(stream.is_open())
  {
    std::getline(stream,line);
    std::istringstream line_stream(line);
    line_stream >> cpu_str; //to pop the first string
    while ((line_stream >> val))
    {
      cpu_data.push_back(val);
    }
    
  }
  //eqn to compute active jiffies
  jiffies_active = 
          cpu_data.at(CPUStates::kNice_)+cpu_data.at(CPUStates::kUser_)+
          cpu_data.at(CPUStates::kIRQ_)+cpu_data.at(CPUStates::kSoftIRQ_)+
          cpu_data.at(CPUStates::kSystem_)+cpu_data.at(CPUStates::kSteal_);
  return jiffies_active;
}

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() 
{
  std::string line ,cpu_str;
  long int val,Jiffies_idle{0};
  std::vector<int> cpu_data{};
  std::ifstream stream(kProcDirectory+kStatFilename);
  if(stream.is_open())
  {
    std::getline(stream,line);
    std::istringstream line_stream(line);
    line_stream>> cpu_str; //pop first
    while(line_stream >> val)
    {
      cpu_data.push_back(val);
    }
  }

  Jiffies_idle = cpu_data.at(CPUStates::kIdle_)+cpu_data.at(CPUStates::kIOwait_);
  return Jiffies_idle;
}

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { return {}; }

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { return 0; }

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { return 0; }

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid[[maybe_unused]]) { return 0; }