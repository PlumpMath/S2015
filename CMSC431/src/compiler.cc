#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <unordered_map>
#include "compiler.hh"

using namespace std;

Compiler::Compiler() {
    stringstream data (stringstream::in | stringstream::out);
    stringstream text_section (stringstream::in | stringstream::out);
    stringstream end_stream (stringstream::in | stringstream::out);
    stringstream output_stream (stringstream::in | stringstream::out);
    floatCount = 0;

    // Generate stubs.
    startData();
}

void Compiler::push(char* value, int type, bool isVar) {
    char _value[80];
    _value[0] = '\0';
    if (isVar) {
         strcat(_value, "[");
         strcat(_value, value);
         strcat(_value, "]");
    } else {
        strcat(_value, value);
    }

    if (type == 0) {
        text_section << "\tpush QWORD " << _value << endl;
    } else {
        data << "\tf" << floatCount << " dq " << _value << endl;
        text_section << "\tpush QWORD [f" << floatCount++ << "]" << endl;
    }
}

void Compiler::add(int type) {
    if (type == 0) { // Int values.
        text_section << "\tpop rax" << endl
                     << "\tadd [rsp], rax" << endl;
    } else if (type == 1) { // FP values.
        text_section << "\tfld QWORD [rsp]" << endl
                     << "\tadd rsp, 8" << endl
                     << "\tfld QWORD [rsp]" << endl
                     << "\tfaddp" << endl
                     << "\tfstp QWORD [rsp]" << endl;
    }
}

void Compiler::sub(int type) {
    if (type == 0) {
        text_section << "\tpop rax" << endl
                     << "\tsub [rsp], rax" << endl;
    } else if (type == 1) {
        text_section << "\tfld QWORD [rsp]" << endl
                     << "\tadd rsp, 8" << endl
                     << "\tfld QWORD [rsp]" << endl
                     << "\tfsub" << endl
                     << "\tfstp QWORD [rsp]" << endl;
    }
}

void Compiler::mult(int type) {
    if (type == 0) {
        text_section << "\tpop rax" << endl
                     << "\timul rax, [rsp]" << endl
                     << "\tmov [rsp], rax" << endl;
    } else if (type == 1) {
        text_section << "\tfld QWORD [rsp]" << endl
                     << "\tadd rsp, 8" << endl
                     << "\tfld QWORD [rsp]" << endl
                     << "\tfmul" << endl
                     << "\tfstp QWORD [rsp]" << endl;
    }
}

void Compiler::div(int type) {
    if (type == 0) {
        text_section << "\tpop rcx" << endl
                     << "\tpop rax" << endl
                     << "\tcqo" << endl
                     << "\tcall safe_div" << endl
                     << "\tpush QWORD rax" << endl;
    } else if (type == 1) {
        text_section << "\tfld QWORD [rsp]" << endl
                     << "\tadd rsp, 8" << endl
                     << "\tfld QWORD [rsp]" << endl
                     << "\tfdiv" << endl
                     << "\tfstp QWORD [rsp]" << endl;
    }

}

void Compiler::mod(int type) {
    if (type == 0) {
        text_section << "\tpop rcx" << endl
                     << "\tpop rax" << endl
                     << "\tcqo" << endl
                     << "\tcall safe_div" << endl
                     << "\tpush QWORD rdx" << endl;
    } else if (type == 1) {
        text_section << "\tmovq xmm0, QWORD [rsp]" << endl
                     << "\tadd rsp, 8" << endl
                     << "\tmovq xmm1, QWORD [rsp]" << endl
                     << "\tmov al, 2" << endl
                     << "\tcall fmod" << endl
                     << "\tmovq QWORD [rsp], xmm0" << endl;
    }
}

void Compiler::exp(int type) {
    if (type == 0) {
        text_section << "\tpop rsi" << endl
                     << "\tpop rdi" << endl
                     << "\tcall intpow" << endl
                     << "\tpush QWORD rax" << endl;
    } else if (type == 1) {        
        text_section << "\tmovq xmm0, QWORD [rsp]" << endl
                     << "\tadd rsp, 8" << endl
                     << "\tmovq xmm1, QWORD [rsp]" << endl
                     << "\tmov al, 2" << endl
                     << "\tcall pow" << endl
                     << "\tmovq QWORD [rsp], xmm0" << endl;
    }
}

void Compiler::negate(int type) {
    if (type == 0) {
        text_section << "\tneg QWORD [rsp]" << endl;
    } else if (type == 1) {
        text_section << "\tfchs" << endl;
    }
}

void Compiler::assign(char* id, int type) {
    // Put value in the data section.
    if (type == 0) {
        data << "\t" << id << " dq 0" << endl;
    } else if (type == 1) {
        data << "\t" << id << " dq 0.0" << endl;
    }

    text_section << "\tpop QWORD [" << id << "]" << endl;
    
    // Convert char* to string (because char* don't always behave as you would
    // hope...)
    string id_str(id);
    sym_table[id_str] = type;
};

void Compiler::output() {
    // Complete and merge streams.
    endData();
    endBoilerplate();

    output_stream << data.str() << text_section.str() << end_stream.str() << endl;
    cout << output_stream.str() << endl;

    // Flush streams
    text_section.str("");
    data.str("");
    end_stream.str("");
}

void Compiler::startData() {
    data << "\textern printf" << endl
         << "\textern pow" << endl
         << "\textern fmod" << endl
         << "\tSECTION .data" << endl
         << "\tfmt_decimal:\tdb \"%ld\", 0" << endl
         << "\tfmt_decimal_nl:\tdb \"%ld\", 10, 0" << endl
         << "\tfmt_fp:\tdb \"%lf\", 0" << endl
         << "\tfmt_fp_nl:\tdb \"%lf\", 10, 0" << endl
         << "\tfmt_div_zero:\tdb \"ERROR: divide by zero!\", 10, 0" << endl
         << "\tresult dq 0" << endl << endl;
}

void Compiler::endData() {
     data  << "\tSECTION .text" << endl
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

void Compiler::print(char* id, int type, bool newline) {
    if (id == NULL) id = strdup("result");
    if (type == 0) {    
        if (strcmp(id, "result") == 0)
            end_stream << "\tpop QWORD [" << id << "]" << endl;

        end_stream << "\tpush QWORD [" << id << "]" << endl
                   << "\tmov rdi, fmt_decimal";
        if (newline) end_stream << "_nl";
        end_stream << endl
                   << "\tpop rsi" << endl
                   << "\tmov al, 0" << endl
                   << "\tcall printf" << endl;
    } else if (type == 1) { 
        if (strcmp(id, "result") == 0)
            end_stream << "\tpop QWORD [" << id << "]" << endl;

        end_stream << "\tpush QWORD [" << id << "]" << endl
                   << "\tmov rdi, fmt_fp";
        if (newline) end_stream << "_nl";
        end_stream << endl
                   << "\tmovq xmm0, QWORD [rsp]" << endl
                   << "\tadd rsp, 8" << endl
                   << "\tmov al, 1" << endl
                   << "\tcall printf" << endl;
    }
}

int Compiler::getType(char* id) {
    string id_str(id);
    int type;

    // Find symbol in table.
    symbol_table::iterator it = sym_table.find(id_str);
    if (it == sym_table.end()) {
        type = -1;
    } else {
        type = it->second;
    }
    return type;
}

void Compiler::endBoilerplate() {
    end_stream << "\tmov rsp, rbp" << endl
               << "\tpop rbp" << endl
               << "\tret" << endl;
}

