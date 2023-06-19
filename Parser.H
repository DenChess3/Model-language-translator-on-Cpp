#ifndef Parser_H
#define Parser_H

#include "Lex.H"
#include "Scanner.H"
#include "Stack.H"
#include "ArrID.H"
extern ArrID tid;
#include "Poliz.H"
class Parser {
    Lex c_lex;
    type_of_lex c_type;
    int c_val;
    Scanner scan;
    Stack<int, 100> si;
    Stack<type_of_lex, 100> sl;
    void P();
    void D1();
    void D();
    void B();
    void S();
    void E();
    void E1();
    void T();
    void F();
    void dec(type_of_lex type);
    void check_id();
    void check_op();
    void check_not();
    void eq_type();
    void eq_bool();
    void check_id_in_read();
    void gl();
    public:

    Poliz prog;
    Parser (const char* file): scan(file), prog(1000) {}
    void analyze();
};

#endif