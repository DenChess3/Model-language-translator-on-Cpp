#include "Interpretator.H"
#include "Lex.H"
#include <iostream>
using namespace std;

int main (int argc, char* argv[]) {
    try {
        Interpretator interpretator (argv[1]);
        interpretator.interpretation ();
        return 0;
    } catch (char c) {
        cout << "unexpected symbol " << c << endl;
        return 1;
    } catch (Lex l) {
        cout << "unexpected lexeme";
        cout << l;
        return 1;
    } catch (const char* error) {
        cout << error << endl;
        return 1;
    }
}