#ifndef Lex_H
#define Lex_H

#include <iostream>
enum type_of_lex {
    lex_null, // 0
    lex_program, lex_begin, lex_end, lex_int, lex_bool, lex_true, lex_false, lex_if, lex_else, // 9
    lex_do, lex_and, lex_not, lex_or, lex_read, lex_then, lex_var, lex_write, lex_while, // 18
    lex_fin, lex_semicolon, lex_comma, lex_colon, lex_assign, lex_lparen, lex_rparen, lex_eq, lex_lss, // 27
    lex_gtr, lex_plus, lex_minus, lex_times, lex_slash, lex_leq, lex_neq, lex_geq, /* lex_lbrac, lex_rbrac,*/ // 35
    lex_num, lex_id, // 37
    poliz_label, // 38
    poliz_addres, // 39
    poliz_go, // 40
    poliz_fgo // 41
};

class Lex {
    type_of_lex type;
    int value;
    public:
    Lex(type_of_lex t = lex_null, int v = 0): type(t), value(v) {}
    type_of_lex get_type() {return type;}
    int get_value() {return value;}
    friend std::ostream& operator<< (std::ostream& c, Lex lex) {
        c << '(' << lex.type << ',' << lex.value << ')' << std:: endl;
        return(c);
    }
};

#endif