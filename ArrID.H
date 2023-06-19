#ifndef ArrID_H
#define ArrID_H

#include <string.H>
#include "Identifier.H"
class ArrID {
    Identifier  *arr;
    int size;
    int top;
    public:

    ArrID(int max_size);
    Identifier& operator[](int k);
    int put(const char* buf);
    ~ArrID();
};
#endif