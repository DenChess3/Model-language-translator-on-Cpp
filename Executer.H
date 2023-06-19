#ifndef Ex_H
#define Ex_H
#include "Lex.H"
#include "Poliz.H"
#include "Stack.H"
#include "ArrID.H"
extern ArrID tid;

class Executer {
    Lex pl;
    public:
    void execute(Poliz& prog);
};

#endif