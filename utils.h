#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <sys/stat.h>

inline bool fileExists(const std::string &name) {
  struct stat buffer;
  return (stat(name.c_str(), &buffer) == 0);
}

#endif
