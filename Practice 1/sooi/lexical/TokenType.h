#ifndef TOKENTYPE_H
#define TOKENTYPE_H

enum TokenType {
    // special tokens
    INVALID_TOKEN  = -2,
    UNEXPECTED_EOF = -1,
    END_OF_FILE    = 0,

    // symbols
    DOT = 1,
    COMMA = 2,
    DOT_COMMA = 3,
    ASSIGN = 4,
    ADD = 5,
    SUB = 6,
    MUL = 7,
    DIV = 8,
    MOD = 9,
    OPEN_PAR = 10,
    CLOSE_PAR = 11,
    OPEN_CUR = 12,
    CLOSE_CUR = 13,

    // keywords
    IF = 14,
    ELSE = 15,
    WHILE = 16,
    FUNCTION = 17,
    RETURN = 18,
    SYSTEM = 19,
    SELF = 20,
    ARGS = 21,

    // operators
    AND = 21,
    NOT = 22,
    OR = 23,

    EQUAL = 24,
    DIFFERENT = 25,
    SMALLER = 26,
    BIGGER = 27,
    SMALLER_EQUAL = 28,
    BIGGER_EQUAL = 29,
    NEGATIVE = 30,

    // others
    NAME = 40,
    NUMBER = 41,
    STRING = 42,

};

#endif
