#include "processor.h"
#include "linux_parser.h"

float Processor::Utilization() { 
    float active_cpu = LinuxParser::ActiveJiffies();
    float idle_cpu = LinuxParser::IdleJiffies();

    return (active_cpu - idle_cpu)/active_cpu;
}