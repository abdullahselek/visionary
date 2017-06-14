//
// Created by Abdullah Selek on 10/06/2017.
//

#ifndef VISIONARY_UTILS_H
#define VISIONARY_UTILS_H

#include <thread>
#include <stdio.h>  /* defines FILENAME_MAX */
#ifdef WINDOWS
    #include <direct.h>
    #define GetCurrentDir _getcwd
#else
    #include <unistd.h>
    #define GetCurrentDir getcwd
#endif

class Utils {

public:
    inline static const char * currentDirectory();
    inline static void replaceStringInPlace(std::string& subject,
                              const std::string& search,
                              const std::string& replace);
    inline static void sleep(int seconds);

};

inline const char * Utils::currentDirectory() {
    char currentPath[FILENAME_MAX];
    if (!GetCurrentDir(currentPath, sizeof(currentPath))) {
        return nullptr;
    }
    currentPath[sizeof(currentPath) - 1] = '\0';
    std::string path(currentPath);
    return path.c_str();
}

inline void Utils::replaceStringInPlace(std::string& subject,
                          const std::string& search,
                          const std::string& replace) {
    size_t pos = 0;
    while((pos = subject.find(search, pos)) != std::string::npos) {
        subject.replace(pos, search.length(), replace);
        pos += replace.length();
    }
}

inline void Utils::sleep(int seconds) {
    std::chrono::milliseconds timespan(seconds); // or whatever
    std::this_thread::sleep_for(timespan);
}

#endif //VISIONARY_UTILS_H
