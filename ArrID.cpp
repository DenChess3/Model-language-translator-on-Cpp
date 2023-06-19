#include "ArrID.H"

ArrID tid(100);

ArrID:: ArrID(int max_size) {
    size = max_size;
    arr = new Identifier [size];
    top = 1;
}

Identifier& ArrID::operator[](int k) { return arr[k];}

int ArrID:: put(const char* buf) {
    for (int i = 1; i < top; i++)
        if( !strcmp(buf, arr[i].get_name()) )
            return i; // if element in array
    arr[top].put_name(buf);
    top++;
    return (top - 1);
}

ArrID:: ~ArrID() {
    delete [] arr;
}
