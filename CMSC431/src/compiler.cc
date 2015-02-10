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
    stream << "\tpop rax" << endl;
    stream << "\tadd [rsp], rax" << endl;
}

void Compiler::sub() {
    stream << "\tpop rax" << endl;
    stream << "\tsub [rsp], rax" << endl;
}

void Compiler::mult() {
    stream << "\tpop rax" << endl;
    stream << "\timul rax, [rsp]" << endl;
    stream << "\tmov [rsp], rax" << endl;
}

void Compiler::div() {
    stream << "\tpop rcx" << endl;
    stream << "\tpop rax" << endl;
    stream << "\tcqo" << endl;
    stream << "\tcall safe_div" << endl;
    stream << "\tpush QWORD rax" << endl;
}

void Compiler::mod() {
    stream << "\tpop rcx" << endl;
    stream << "\tpop rax" << endl;
    stream << "\tcqo" << endl;
    stream << "\tcall safe_div" << endl;
    stream << "\tpush QWORD rdx" << endl;
}

void Compiler::exp() {
    stream << "\tpop rsi" << endl;
    stream << "\tpop rdi" << endl;
    stream << "\tcall intpow" << endl;
    stream << "\tpush QWORD rax" << endl;
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
    stream << "\textern printf" << endl;
    stream << "\tSECTION .data" << endl;
    stream << "\tfmt_decimal_nl:\tdb \"%ld\", 10, 0" << endl;
    stream << "\tfmt_div_zero:\tdb \"ERROR: divide by zero!\", 10, 0" << endl << endl;

    stream << "\tSECTION .text" << endl;
    stream << "\tglobal main" << endl;

    /* Exponentiation function */
    stream << "intpow:" << endl;
    stream << "\tpush rbp" << endl;
    stream << "\tmov rbp, rsp" << endl;
    stream << "\tmov rax, rdi" << endl;
    stream << "loop:" << endl;
    stream << "\tcmp rsi, 1" << endl;
    stream << "\tjle finish" << endl;
    stream << "\tdec rsi" << endl;
    stream << "\timul rax, rdi" << endl;
    stream << "\tjmp loop" << endl;
    stream << "finish:" << endl;
    stream << "\tmov rsp, rbp" << endl;
    stream << "\tpop rbp" << endl;
    stream << "\tret" << endl << endl;

    stream << "safe_div:" << endl;
    /* Check the divisor */
    stream << "\tcmp rcx, 0" << endl;
    stream << "\tje error_div_zero" << endl;
    stream << "\tidiv QWORD rcx" << endl;
    stream << "\tret" << endl;

    /* Divide by zero exception handler. */
    stream << "error_div_zero:" << endl;
    stream << "\tmov rdi, fmt_div_zero" << endl;
    stream << "\tpop rsi" << endl;
    stream << "\tmov al, 0" << endl;
    stream << "\tcall printf" << endl;
    stream << "\tmov rsp, rbp" << endl;
    stream << "\tpop rbp" << endl;
    stream << "\tret" << endl << endl;

    stream << "main:" << endl;
    /* Set up stack frame. */
    stream << "\tpush rbp" << endl;
    stream << "\tmov rbp, rsp" << endl;
}

void Compiler::endBoilerplate() {
    stream << "\tmov rdi, fmt_decimal_nl" << endl;
    stream << "\tpop rsi" << endl;
    stream << "\tmov al, 0" << endl;
    stream << "\tcall printf" << endl;
    stream << "\tmov rsp, rbp" << endl;
    stream << "\tpop rbp" << endl;
    stream << "\tret" << endl;
}
