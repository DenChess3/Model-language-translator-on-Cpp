#include "Executer.H"

void Executer:: execute(Poliz& prog) {
    Stack<int, 100> stack;
    int i, j, index = 0, size = prog.get_top();
    while (index < size) {
        pl = prog [ index ];
        switch (pl.get_type()) {
            case lex_true: 
            case lex_false: 
            case lex_num:
            case poliz_addres:
            case poliz_label:
                stack.push(pl.get_value());
                break;
            case lex_id:
                i = pl.get_value();
                if (tid[i].get_assign()) {
                    stack.push(tid[i].get_value());
                    break;
                } else
                    throw "POLIZ: indefinite identifier";
            case lex_not:
                stack.push(stack.pop());
                break;
            case lex_or:
                i = stack.pop();
                stack.push(stack.pop() || i);
                break;
            case lex_and:
                i = stack.pop();
            stack.push(stack.pop() && i);
                break;
            case poliz_go:
                index = stack.pop() - 1;
                break;
            case poliz_fgo:
                i = stack.pop();
                if (stack.pop()) 
                    index = i - 1;
                break;
            case lex_write:
                std::cout << stack.pop() << std::endl;
                break;
            case lex_read: {
                int k = -1;
                i = stack.pop();
                if (tid[i].get_type() == lex_int) {
                    std::cout << "Please input int value for " << tid[i].get_name() << std::endl;
                    std::cin >> k;
                } else {
                    char j[50];
                    do {
                        std::cout << "Please input boolean value (true or false) for " << tid[i].get_name() << std::endl;
                        std::cin >> j;
                        if (!strcmp(j, "true"))
                            k = 1;
                        else if (!strcmp(j, "false"))
                            k = 0;
                        if (k == -1) 
                            std::cout << "Error in input, please try again" << std::endl;
                    } while(k == -1);
                }
                tid[i].put_value(k);
                tid[i].put_assign();
                break;
            }
            case lex_plus:
                stack.push(stack.pop() + stack.pop());
                break;
            case lex_times:
                stack.push (stack.pop() * stack.pop());
                break;
            case lex_minus:
                i = stack.pop();
                stack.push(stack.pop() - i);
                break;
            case lex_slash:
                i = stack.pop();
                if (i) {
                    stack.push(stack.pop() / i);
                    break;
                } else
                    throw "POLIZ:divide by zero";
            case lex_eq:
                stack.push(stack.pop() == stack.pop());
                break;
            case lex_lss:
                i = stack.pop();
                stack.push(stack.pop() < i);
                break;
            case lex_gtr:
                i = stack.pop();
                stack.push(stack.pop() > i);
                break;
            case lex_leq:
                i = stack.pop();
                stack.push(stack.pop() <= i);
                break;
            case lex_geq:
                i = stack.pop();
                stack.push(stack.pop() >= i);
                break;
            case lex_neq:
                i = stack.pop();
                stack.push(stack.pop() != i);
                break;
            case lex_assign:
                i = stack.pop();
                j = stack.pop();
                tid[j].put_value(i);
                tid[j].put_assign(); 
                break;
            default:
                throw "POLIZ: unexpected elem";
            } //end of switch
        index++;
    };//end of while
    std::cout << "Finish of executing" << std::endl;
}