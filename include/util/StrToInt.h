#ifndef __STRTOINT_H__
#define __STRTOINT_H__

#include <iostream>
#include <sstream>

using std::string;

inline string int2str(int number) {
    std::ostringstream oss;
    oss << number;
    return oss.str();
}
inline int str2int(const string &str) {
    int number;
    std::istringstream iss(str);
    iss >> number;
    return number;
}
inline unsigned short str2unshort(const string &str) {
    unsigned short port;
    std::istringstream iss(str);
    iss >> port;
    return port;
}

#endif