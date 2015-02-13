#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class Compiler
{
    public:
        static stringstream stream;

        static void startBoilerplate();
        static void endBoilerplate();
        static void add();
        static void sub();
        static void mult();
        static void div();
        static void mod();
        static void exp();
        static void negate();
        static void output();
        static void push(long);
};

stringstream Compiler::stream (stringstream::in | stringstream::out);

void Compiler::push(long x) {
    stream << "\tPUSH QWORD " << x << endl;   
}

void Compiler::add() {
    stream << "\tpop rax" << endl
           << "\tadd [rsp], rax" << endl;
}

void Compiler::sub() {
    stream << "\tpop rax" << endl
           << "\tsub [rsp], rax" << endl;
}

void Compiler::mult() {
    stream << "\tpop rax" << endl
           << "\timul rax, [rsp]" << endl
           << "\tmov [rsp], rax" << endl;
}

void Compiler::div() {
    stream << "\tpop rcx" << endl
           << "\tpop rax" << endl
           << "\tcqo" << endl
           << "\tcall safe_div" << endl
           << "\tpush QWORD rax" << endl;
}

void Compiler::mod() {
    stream << "\tpop rcx" << endl
           << "\tpop rax" << endl
           << "\tcqo" << endl
           << "\tcall safe_div" << endl
           << "\tpush QWORD rdx" << endl;
}

void Compiler::exp() {
    stream << "\tpop rsi" << endl
           << "\tpop rdi" << endl
           << "\tcall intpow" << endl
           << "\tpush QWORD rax" << endl;
}

void Compiler::negate() {
    stream << "\tneg QWORD [rsp]" << endl;
}

void Compiler::output() {
    endBoilerplate();
    cout << stream.str() << endl;
    stream.str("");
}

void Compiler::startBoilerplate() {
    stream << "\textern printf" << endl
           << "\tSECTION .data" << endl
           << "\tfmt_decimal_nl:\tdb \"%ld\", 10, 0" << endl
           << "\tfmt_div_zero:\tdb \"ERROR: divide by zero!\", 10, 0" << endl << endl

           << "\tSECTION .text" << endl
           << "\tglobal main" << endl

    /* Exponentiation function */
           << "intpow:" << endl
           << "\tpush rbp" << endl
           << "\tmov rbp, rsp" << endl
           << "\tmov rax, rdi" << endl
           << "loop:" << endl
           << "\tcmp rsi, 1" << endl
           << "\tjle finish" << endl
           << "\tdec rsi" << endl
           << "\timul rax, rdi" << endl
           << "\tjmp loop" << endl
           << "finish:" << endl
           << "\tmov rsp, rbp" << endl
           << "\tpop rbp" << endl
           << "\tret" << endl << endl

           << "safe_div:" << endl
    /* Check the divisor */
           << "\tcmp rcx, 0" << endl
           << "\tje error_div_zero" << endl
           << "\tidiv QWORD rcx" << endl
           << "\tret" << endl

    /* Divide by zero exception handler. */
           << "error_div_zero:" << endl
           << "\tmov rdi, fmt_div_zero" << endl
           << "\tpop rsi" << endl
           << "\tmov al, 0" << endl
           << "\tcall printf" << endl
           << "\tmov rsp, rbp" << endl
           << "\tpop rbp" << endl
           << "\tret" << endl << endl

           << "main:" << endl
    /* Set up stack frame. */
           << "\tpush rbp" << endl
           << "\tmov rbp, rsp" << endl;
}

void Compiler::endBoilerplate() {
    stream << "\tmov rdi, fmt_decimal_nl" << endl
           << "\tpop rsi" << endl
           << "\tmov al, 0" << endl
           << "\tcall printf" << endl
           << "\tmov rsp, rbp" << endl
           << "\tpop rbp" << endl
           << "\tret" << endl;
}
