//
// Created by Abdullah Selek on 10/06/2017.
//

#ifndef VISIONARY_UTILS_H
#define VISIONARY_UTILS_H

#include <stdio.h>  /* defines FILENAME_MAX */
#ifdef WINDOWS
    #include <direct.h>
    #define GetCurrentDir _getcwd
#else
    #include <unistd.h>
    #define GetCurrentDir getcwd
#endif

const char * currentDirectory() {
    char currentPath[FILENAME_MAX];
    if (!GetCurrentDir(currentPath, sizeof(currentPath))) {
        return nullptr;
    }
    currentPath[sizeof(currentPath) - 1] = '\0';
    std::string path(currentPath);
    return path.c_str();
}

#endif //VISIONARY_UTILS_H
