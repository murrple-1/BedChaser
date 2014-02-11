#ifndef HASHER_H
#define HASHER_H

#include "../core/config.h"
#include <string>

NS_START

unsigned int hash(const std::string & s) {

    const char * cString = s.c_str();
    unsigned int hash = 2345;
    int c;
    while((c = *cString++) != EOF)
    {
        hash = ((hash << 5) + hash) + c;
        c = *cString++;
    }
    return hash;
}

NS_END

#endif // HASHER_H

