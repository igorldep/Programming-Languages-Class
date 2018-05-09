#include "SymbolTable.h"

SymbolTable::SymbolTable() {
    // TIP: To add the tokens.
    // m_st["???"] = ???;

    // symbols
    m_st["."] = DOT;
    m_st[","] = COMMA;
    m_st[";"] = DOT_COMMA;
    m_st["="] = ASSIGN;
    m_st["+"] = ADD;
    m_st["-"] = SUB;
    m_st["*"] = MUL;
    m_st["/"] = DIV;
    m_st["%"] = MOD;
    m_st["("] = OPEN_PAR;
    m_st[")"] = CLOSE_PAR;
    m_st["{"] = OPEN_CUR;
    m_st["}"] = CLOSE_CUR;

    // keywords
    m_st["if"] = IF; //name
    m_st["else"] = ELSE;
    m_st["while"] = WHILE;
    m_st["function"] = FUNCTION;
    m_st["return"] = RETURN;
    m_st["system"] = SYSTEM;
    m_st["self"] = SELF;
    m_st["args"] = ARGS;

    // operators
    m_st["&"] = AND;
    m_st["not"] = NOT;
    m_st["|"] = OR;

    m_st["=="] = EQUAL;
    m_st["!="] = DIFFERENT;
    m_st["<"] = SMALLER;
    m_st[">"] = BIGGER;
    m_st["<="] = SMALLER_EQUAL;
    m_st[">="] = BIGGER_EQUAL;
    m_st["!"] = NEGATIVE;

}

SymbolTable::~SymbolTable() {
}

bool SymbolTable::contains(std::string token) {
    return m_st.find(token) != m_st.end();
}

enum TokenType SymbolTable::find(std::string token) {
    return this->contains(token) ?
              m_st[token] : INVALID_TOKEN;
}
