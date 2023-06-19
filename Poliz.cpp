#include "Poliz.H"

Poliz:: Poliz(int max_size) {
    size = max_size;
    arr = new Lex[size];
    top = 0;
}

void Poliz:: put_lex(Lex l) {
    arr[top] = l;
    top++;
}

void Poliz:: put_lex(Lex l, int place) {
    arr[place] = l;
}

Lex& Poliz:: operator[](int i) {
    if ( i > size) 
        throw "Poliz error: index > max_size";
    else if ( i > top) 
            throw "Poliz error: index > pointer";
        else
            return arr[i];
}

/*void Poliz:: print() {
    for( int i = 0; i < top; i++)
        std::cout << arr[i];
}*/

Poliz:: ~Poliz() {
    delete [] arr;
}