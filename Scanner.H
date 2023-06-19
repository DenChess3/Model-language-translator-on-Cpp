#ifndef Scanner_H
#define Scanner_H

#include "Lex.H"
#include "ArrID.H"
extern ArrID tid;
#include <iostream>


class Scanner {
    enum State{ H, ID, NUM, COM, ALE, DELIM, NEQ };
    static char* tw[];
    static type_of_lex words[];
    static char* tm[];
    static type_of_lex marks[];
    State state;
    FILE* fp;
    char c;
    char buf[100];
    int buftop;
    void clear();
    void add();
    int look(const char* buf, char** list);
    void gc() { c = fgetc(fp);}
    public:
    Scanner(const char* file);
    Lex get_lex();
};

#endif