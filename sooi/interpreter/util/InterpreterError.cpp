#include "InterpreterError.h"

#include <cstdio>
#include <cstdlib>

InterpreterError::InterpreterError() {
}

void InterpreterError::abort(int line) {
    printf("%02d: Operação inválida\n", line);
    exit(1);
}

void InterpreterError::abort(std::string str) {
    printf("%s\n", str.c_str());
    exit(0);
}
