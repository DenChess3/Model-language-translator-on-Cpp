#include "Parser.H"

void Parser:: P() { // P → program D1; B @

    if (c_type == lex_program) // program
        gl();
    else
        throw c_lex;
    D1();
    if (c_type == lex_semicolon) // ;
        gl();
    else
        throw c_lex;
    B();
    if (c_type != lex_fin) // @
        throw c_lex; 
}

void Parser:: D1() { // D1 → var D {,D}
    if (c_type == lex_var) { // var
        gl();
        D();
        while (c_type == lex_comma) { // ,
            gl();
            D();
        }
    } else
        throw c_lex;
}

void Parser:: D() { // D → I {, I}: [ int | bool ]
    si.reset(); // reset int stack
    if (c_type != lex_id)
        throw c_lex;
    else { // I {, I }
        si.push (c_val);
        gl();
        while (c_type == lex_comma) {
            gl();
            if (c_type != lex_id)
                throw c_lex;
            else {
                si.push (c_val);
                gl();
            }
        }
        if (c_type != lex_colon) // :
            throw c_lex;
        else {
            gl();
            if (c_type == lex_int) {
                dec(lex_int);
                gl();

            } else if (c_type == lex_bool) { // bool
                dec(lex_bool);
                gl();
            } else 
                throw c_lex;
        }
    }
}

void Parser:: B() {
    if (c_type == lex_begin) { // B → begin S {;S} end
        gl();
        S();
        while (c_type == lex_semicolon) {
            gl();
            S();
        }
        if (c_type == lex_end)
            gl();
        else
            throw c_lex;
    } else
        throw c_lex;
}

void Parser:: S() { //S → I := E | if E then S else S | while E do S | B | read (I) | write (E)
    int pl0, pl1, pl2, pl3;
    if (c_type == lex_if) { // if
        gl();
        E();
        eq_bool();
        pl2 = prog.get_top();
        prog.blank();
        prog.put_lex(Lex(poliz_fgo));
        if (c_type == lex_then) {
            gl();
            S();
            pl3 = prog.get_top();
            prog.blank();
            prog.put_lex(Lex(poliz_go));
            prog.put_lex(Lex(poliz_label, prog.get_top()), pl2);
            if (c_type == lex_else) {
                gl();
                S();
                prog.put_lex(Lex(poliz_label, prog.get_top()), pl3);
            } else
                throw c_lex;
        } else
            throw c_lex;
    }//end if
    else if (c_type == lex_while) { // while
        pl0 = prog.get_top();
        gl();
        E();
        eq_bool();
        pl1 = prog.get_top(); 
        prog.blank();
        prog.put_lex(Lex(poliz_fgo));
        if (c_type == lex_do) {
            gl();
            S();
            prog.put_lex(Lex(poliz_label, pl0));
            prog.put_lex(Lex(poliz_go));
            prog.put_lex(Lex(poliz_label, prog.get_top()), pl1);
        } else
            throw c_lex;
    }//end while
    else if (c_type == lex_read) { // read
        gl();
        if (c_type == lex_lparen) { // (
            gl();
            if (c_type == lex_id) {
                check_id_in_read();
                prog.put_lex(Lex(poliz_addres, c_val));
                gl();
            } else
                throw c_lex;
        if (c_type == lex_rparen) { // )
            gl();
            prog.put_lex(Lex(lex_read));
        } else
            throw c_lex;
        } else
            throw c_lex;
    }//end read
    else if (c_type == lex_write) { // write
        gl();
        if (c_type == lex_lparen) {
            gl();
            E();
            if (c_type == lex_rparen) {
                gl();
                prog.put_lex(Lex(lex_write));
            } else
                throw c_lex;
        } else
            throw c_lex;
    }//end write
    else if (c_type == lex_id) { // I := E
        check_id ();
        prog.put_lex (Lex(poliz_addres, c_val));
        gl();
        if (c_type == lex_assign) {
            gl();
            E();
            eq_type();
            prog.put_lex(Lex(lex_assign));
        } else
            throw c_lex;
    }//end assign
    else
        B();
    }
 

void Parser:: E() { // E → E1 [ = | < | > | <= | >= | != ] E1 | E1
    E1();
    if (c_type == lex_eq || c_type == lex_lss || c_type == lex_gtr ||
        c_type == lex_leq || c_type == lex_geq || c_type == lex_neq) { // "=", "<", ">", "<=", ">=", "!="
        sl.push(c_type);
        gl(); 
        E1(); 
        check_op();
    }
}
 
void Parser:: E1() { // E1 → T {[ + | - | or ] T}
    T();
    while (c_type == lex_plus || c_type == lex_minus || c_type == lex_or) { // +, -, or
        sl.push (c_type);
        gl();
        T();
        check_op();
    }
}
 
void Parser:: T() { // T → F {[ * | / | and ] F}
    F();
    while (c_type == lex_times || c_type == lex_slash || c_type == lex_and) { // *, /, and
        sl.push (c_type);
        gl();
        F();
        check_op();
    }
}
 
void Parser:: F() { // F → I | N | L | not F | (E)
    if (c_type == lex_id) { // ID
        check_id();
        prog.put_lex(Lex(lex_id, c_val));
        gl();
    } else if (c_type == lex_num) { // N
        sl.push (lex_int);
        prog.put_lex (c_lex);
        gl();
    } else if (c_type == lex_true) { // L
        sl.push(lex_bool);
        prog.put_lex(Lex(lex_true, 1));
        gl();
    } else if (c_type == lex_false) { // L
        sl.push(lex_bool);
        prog.put_lex(Lex(lex_false, 0) );
        gl();
    } else if (c_type == lex_not) { // not
        gl(); 
        F(); 
        check_not();
    }
    else if (c_type == lex_lparen) { // (E)
        gl(); 
        E();
        if (c_type == lex_rparen)
            gl();
        else 
            throw c_lex;
    } else 
        throw c_lex;
}



////////////////////////

void Parser:: gl() {
    c_lex = scan.get_lex();
    c_type = c_lex.get_type();
    c_val = c_lex.get_value();
}

void Parser:: analyze() {
    gl();
    P();
    //prog.print();
    std::cout << std::endl << "analysis was successful" << std::endl;
}

void Parser:: dec(type_of_lex type) {
    int i;
    while (!si.isempty()) {
        i = si.pop();
        if (tid[i].get_declare()) 
            throw "Parser: declare twice";
        else {
            tid[i].put_declare();
            tid[i].put_type(type);
        }
    }
}
 
void Parser:: check_id() {
    if (tid[c_val].get_declare())
        sl.push(tid[c_val].get_type());
    else 
        throw "Parser: id not declared";
}
 
void Parser:: check_op() { // check types of operators
    type_of_lex t1, t2, op, t = lex_int, r = lex_bool;
    t2 = sl.pop();
    op = sl.pop();
    t1 = sl.pop();
    if (op == lex_plus || op == lex_minus || op == lex_times || op == lex_slash)
        r = lex_int;
    if (op == lex_or || op == lex_and)
        t = lex_bool;
    if (t1 == t2  &&  t1 == t) 
        sl.push(r);
    else
        throw "Parser: wrong types are in operation";
    prog.put_lex (Lex(op));
}
 
void Parser:: check_not() {
    if (sl.pop() !=lex_bool)
        throw "Parser: wrong type is in not";
    else {
        sl.push(lex_bool);
        prog.put_lex(Lex(lex_not));
    }
}
 
void Parser:: eq_type() {
    if (sl.pop() != sl.pop())
        throw "Parser: wrong types are in :=";
}
 
void Parser:: eq_bool() {
    if (sl.pop() != lex_bool)
        throw "Parser: expression is not boolean";
}
 
void Parser:: check_id_in_read() {
    if (!tid[c_val].get_declare())
        throw "Parser: id not declared";
}
