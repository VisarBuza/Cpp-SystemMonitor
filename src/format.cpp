#include <string>

#include "format.h"

using std::string;


// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
string Format::ElapsedTime(long seconds) { 
    int hours = seconds / 3600;
    int remainingSeconds = seconds % 3600;
    int minutes = remainingSeconds / 60;
    remainingSeconds = remainingSeconds % 60;
    return std::to_string(hours) + ":" + std::to_string(minutes) + ":" + std::to_string(remainingSeconds);  
}

string Format::ConvertToMb(string ram) {
    long kb = std::stol(ram);
    long mb = kb / 1000;
    return std::to_string(mb);
}