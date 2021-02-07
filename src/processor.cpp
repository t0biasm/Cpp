#include <string>
#include <sstream>
#include "processor.h"
#include "linux_parser.h"

using std::stof;
using std::string;

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
  string line;
  string cpu, user, nice, system, s_idle, iowait, irq, softirq, steal, guest, guest_nice;
  std::ifstream filestream(LinuxParser::kProcDirectory.substr(0, LinuxParser::kProcDirectory.size()-1) + LinuxParser::kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream >> cpu >> user >> nice >> system >> s_idle >> iowait >> irq >> softirq >> steal >> guest >> guest_nice;
      if (cpu == "cpu") {
        break;
      }
    }
  }

  float idle = stof(s_idle) + stof(iowait);
  float non_idle = stof(user) + stof(nice) + stof(system) + stof(irq) + stof(softirq) + stof(steal);
  
  float total = idle + non_idle;

  float totald = total - prev_total_;
  float idled = idle - prev_idle_;
  
  prev_idle_ = idle;
  prev_total_ = total;

  return (totald - idled) / totald;
}