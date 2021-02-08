#include <string>
#include <time.h>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
    std::string hour = std::to_string(seconds / 3600);
    std::string min = std::to_string((seconds - (stoi(hour) * 3600)) / 60);
    std::string second = std::to_string(seconds % 60);

    if (hour.length() <= 2) {
        hour.insert(0, 2 - hour.length(), '0');
    }
    
    return hour + ":" + min.insert(0, 2 - min.length(), '0') + ":" + second.insert(0, 2 - second.length(), '0');
}
