#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include "linux_parser.h"

#include "process.h"

using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
int Process::Pid() { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() const { 
    long uptime = LinuxParser::UpTime();
    long utime = LinuxParser::Stat(pid_, 13);
    long stime = LinuxParser::Stat(pid_, 14);
    long cutime = LinuxParser::Stat(pid_, 15);
    long cstime = LinuxParser::Stat(pid_, 16);
    long starttime = LinuxParser::Stat(pid_, 21);
    long Hertz = sysconf(_SC_CLK_TCK);


    long total_time = utime + stime;
    total_time = total_time + cutime + cstime;
    float seconds = uptime - (starttime / Hertz);
    return (total_time / Hertz) / seconds;
}

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
    if (a.pid_ != 0) {
        return a.CpuUtilization() < CpuUtilization();
    } else {
        return false;
    }
}