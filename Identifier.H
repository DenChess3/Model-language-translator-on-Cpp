#ifndef Iden_H
#define Iden_H
#include "Lex.H"
#include <string.H>

class Identifier {
    char* name;
    bool declare;
    bool assign;
    int value;
    type_of_lex type;

    public:
    Identifier() {declare = false; assign = false;}
    char* get_name() {return name;}
    bool get_declare() {return declare;}
    bool get_assign() {return assign;}
    int get_value() {return value;}
    type_of_lex get_type() {return type;}

    void put_name(const char* n) {
        name = new char [strlen(n) + 1];
        strcpy(name, n);
    }
    void put_declare() {declare = true;}
    void put_assign() {assign = true;}
    void put_value(int v) {value = v;}
    void put_type(type_of_lex t) {type = t;}
};
#endif