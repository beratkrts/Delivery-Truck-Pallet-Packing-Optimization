#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <string>

class Timer {
public:
    Timer() : startTime(std::chrono::high_resolution_clock::now()) {}
    
    double getElapsedTime() const {
        auto endTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = endTime - startTime;
        return elapsed.count();
    }
    
    void reset() {
        startTime = std::chrono::high_resolution_clock::now();
    }
    
    std::string getFormattedTime() const {
        double seconds = getElapsedTime();
        int hours = static_cast<int>(seconds) / 3600;
        int minutes = (static_cast<int>(seconds) % 3600) / 60;
        seconds = seconds - hours * 3600 - minutes * 60;
        
        char buffer[32];
        snprintf(buffer, sizeof(buffer), "%02d:%02d:%.3f", hours, minutes, seconds);
        return std::string(buffer);
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
};

#endif // TIMER_H 