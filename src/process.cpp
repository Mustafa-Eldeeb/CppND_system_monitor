#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid, long total_jiffies):pid_(pid) 
{
    calculateCpuUtil(total_jiffies);
}

//setter for cpu_utilization_ private variable
void Process::calculateCpuUtil( long total_jiffies)
{
    long active_jiffies = LinuxParser::ActiveJiffies(pid_);
    cpu_utiliaztion_ = (active_jiffies*1.0)/total_jiffies ;
}

// TODO: Return this process's ID
int Process::Pid() { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { return cpu_utiliaztion_; }
 
// TODO: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(pid_); }

// TODO: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(pid_); }

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(pid_); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(pid_); }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const { 
    return (this->cpu_utiliaztion_ < a.cpu_utiliaztion_)?true:false; 
    }