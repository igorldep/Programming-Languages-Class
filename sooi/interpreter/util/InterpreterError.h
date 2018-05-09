#ifndef INTERPRETER_ERROR
#define INTERPRETER_ERROR

#include <string>

class InterpreterError {
    public:
        static void abort(int line);
        static void abort(std::string str);

    private:
        InterpreterError();
};

#endif
