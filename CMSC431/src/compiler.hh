#include <sstream>
#include <string>
#include <unordered_map>

class Compiler
{
    private:
        std::stringstream data;
        std::stringstream text_section;
        std::stringstream end_stream;
        std::stringstream output_stream;
        int floatCount;
        typedef std::unordered_map<std::string, int> symbol_table;
        symbol_table sym_table;

    public:
        Compiler();
        void startData();
        void endData();
        void endBoilerplate();
        void add(int);
        void sub(int);
        void mult(int);
        void div(int);
        void mod(int);
        void exp(int);
        void negate(int);
        void output();
        void push(char*, int, bool);
        void assign(char*, int);
        void print(char*, int, bool);
        int getType(char*);
};
