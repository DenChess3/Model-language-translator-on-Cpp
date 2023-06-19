#ifndef I_H
#define I_H

#include "Parser.H"
#include "Executer.H"

class Interpretator {
    Parser parser;
    Executer exe;
    public:
    Interpretator(char* file): parser(file) {}
    void interpretation () {
        parser.analyze();
        exe.execute(parser.prog);
    }
};

#endif