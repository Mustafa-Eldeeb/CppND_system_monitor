#include "processor.h"
#include "linux_parser.h"

using std::vector;
using std::array;


// to prevent divide by zero , initialize prev_cpu_jiffies for the first time.
Processor::Processor()
{
    GetLinuxParserForJiffies(prev_cpu_jiffies_);
}
// TODO: Return the aggregate CPU utilization
float Processor::Utilization()
{
    GetLinuxParserForJiffies(prev_cpu_jiffies_);
    CalculateDeltaTime(current_cpu_jiffies_,prev_cpu_jiffies_);
    const float utilization = CalculateUtilization();
    current_cpu_jiffies_.swap(prev_cpu_jiffies_);
    return utilization;
}

 void Processor::CalculateDeltaTime(std::array<long,3>&first_cpu_jiffies,std::array<long,3>&second_cpu_jiffies)
 {
     for(int i=0;i<3;i++)
     {
        delta_jiffies_[i]=first_cpu_jiffies[i]-second_cpu_jiffies[i];
     }
 }

void Processor::GetLinuxParserForJiffies(std::array<long,3>& cpu_jiffies)
{
    cpu_jiffies[LinuxParser::CPUTime::kIdleTime_]=LinuxParser::IdleJiffies();
    cpu_jiffies[LinuxParser::CPUTime::kActiveTime_]=LinuxParser::ActiveJiffies();
    cpu_jiffies[LinuxParser::CPUTime::kTotalTime_]=LinuxParser::Jiffies();   
}


long Processor::getTotalJiffies()
{
    return current_cpu_jiffies_[LinuxParser::CPUTime::kTotalTime_];
}

void Processor::UpdatePrevJiffies()
{
    for(size_t i =0; i<prev_cpu_jiffies_.size(); ++i)
    {
        prev_cpu_jiffies_[i]=current_cpu_jiffies_[i];
    }
}
