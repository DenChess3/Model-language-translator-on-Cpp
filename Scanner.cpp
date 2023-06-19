#include "Scanner.H"
char* Scanner:: tw[] = {"", "program", "begin", "end", "int", "bool", "true", "false", "if", "else", "do", "and", "not",
                            "or", "read", "then", "var", "write", "while", NULL};

type_of_lex Scanner:: words[] = {lex_null, lex_program, lex_begin, lex_end, lex_int, lex_bool, lex_true, lex_false, lex_if, lex_else,
    lex_do, lex_and, lex_not, lex_or, lex_read, lex_then, lex_var, lex_write, lex_while, lex_null};

char* Scanner:: tm[] = {"", "@", ";", ",", ":", ":=", "(", ")", "=", "<", ">", "+", "-", "*", "/", "<=", "!=", ">=", NULL};
 
type_of_lex Scanner:: marks[] = {lex_null, lex_fin, lex_semicolon, lex_comma, lex_colon, lex_assign, lex_lparen, lex_rparen, lex_eq, lex_lss,
    lex_gtr, lex_plus, lex_minus, lex_times, lex_slash, lex_leq, lex_neq, lex_geq, lex_null};


void Scanner:: clear() {
    buftop = 0;
    for (int i = 0; i < 100; i++)
        buf[i] = '\0';
}

void Scanner:: add() {
    buf[buftop] = c;
    buftop++;
}

int Scanner:: look(const char* buf, char** list) {
    int i = 0;
    while (list[i]) {
        if ( !strcmp(buf, list[i]))
            return i;
        i++;
    }
    return 0;
}

Scanner:: Scanner (const char* file) {
    fp = fopen(file, "r");
    state = H;
    clear();
    gc();
}

Lex Scanner:: get_lex() {
    int d, i;
    state = H;
    do {
        switch(state) {
            case H:
                if ( c == ' ' || c == '\n' || c == '\r' || c == '\t' )
                    gc();
                else if(isalpha(c)) {
                    clear();
                    add();
                    gc();
                    state = ID;
                } else if(isdigit(c)) {
                    d = c - '0';
                    gc();
                    state = NUM;
                } else if( c == '{') {
                    gc();
                    state = COM;
                } else if( c == ':' || c == '<' || c == '>' ){
                    clear();
                    add();
                    gc();
                    state = ALE;
                } else if( c == '@')
                    return Lex(lex_fin);
                else if(c == '!') {
                    clear();
                    add();
                    gc();
                    state = NEQ;
                } else
                    state = DELIM;
                break;
            case ID:
                if (isalpha(c) || isdigit(c)) {
                    add(); 
                    gc();
                } else if (i = look(buf, tw))
                            return Lex(words[i], i);
                        else {
                            i = tid.put(buf);
                            return Lex(lex_id, i);
                        }
                break;
            case NUM:
                if (isdigit(c)) {
                    d = d * 10 + c - '0'; 
                    gc();
                } else
                    return Lex(lex_num, d);
                break;
            case COM: // comments
                if (c == '}') {
                    gc();
                    state = H;
                }
                else if (c == '@' || c == '{')
                    throw c; // error
                else
                    gc();
                break;
            case ALE:
                if (c == '=') { // := or >= or <=
                    add();
                    gc();
                    i = look(buf, tm); 
                    return Lex(marks[i], i);
                } else {                    // : or < or >
                    i = look(buf, tm);
                    return Lex(marks[i], i);
                }
                break;
            case NEQ:
                if (c == '=') { // !=
                    add();
                    gc();
                    i = look(buf, tm);
                    return Lex(lex_neq, i);
                } else                      // !
                    throw '!';
                break;
            case DELIM:
                clear();
                add();
                if (i = look(buf, tm)) { // other normal marks
                    gc();
                    return Lex(marks[i], i);
                } else
                    throw c; // other not normal marks
            break;
        } // switch
    } while(1);
}


