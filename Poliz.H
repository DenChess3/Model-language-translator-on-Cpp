#ifndef Poliz_H
#define Poliz_H

#include "Lex.H"

class Poliz {
    Lex* arr;
    int size;
    int top;
    public:
    Poliz(int max_size);
    void put_lex(Lex l);
    void put_lex(Lex l, int place);
    int get_top() {return top;}
    void blank() {top++;}
    Lex& operator[](int i);
    //void print();
    ~Poliz();
};

#endif