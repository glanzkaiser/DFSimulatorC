#include <iostream>
#include <ctime>

int main() {
    // Get the current time as a time_t object
    time_t now = time(0); 

    // Convert time_t to a human-readable string
    char* dt = ctime(&now);
    std::cout << "The current date and time is: " << dt << std::endl;

    // Convert time_t to a tm struct for individual components
    tm* ltm = localtime(&now);
    std::cout << "Year: " << 1900 + ltm->tm_year << std::endl;
    std::cout << "Month: " << 1 + ltm->tm_mon << std::endl;
    std::cout << "Day: " << ltm->tm_mday << std::endl;
    std::cout << "Hour: " << ltm->tm_hour << std::endl;
    std::cout << "Minute: " << ltm->tm_min << std::endl;
    std::cout << "Second: " << ltm->tm_sec << std::endl;

    return 0;
}