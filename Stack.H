#ifndef Stack_H
#define Stack_H

template<class T, int max_size>
class Stack {
    T s[max_size];
    int top;
    public:
    Stack() {top = 0;}
    bool isempty() {return (top == 0);}
    bool isfull() {return (top == max_size);}
    void reset() {top = 0;}
    void push(T t) {
        if(!isfull()) {
            s[top] = t;
            top++;
        } else 
            throw "stack is full";
    }
    T pop() {
        if (!isempty()) {
            top--;
            return s[top];
        } else 
            throw "stack is empty";
    }
};

#endif