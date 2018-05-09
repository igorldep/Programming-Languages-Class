#include <cstdio>
#include <cctype>

#include "LexicalAnalysis.h"
#include "TokenType.h"

LexicalAnalysis::LexicalAnalysis(const char* filename) : m_line(1) {
    m_file = fopen(filename, "r");
    if (!m_file)
        throw "Unable to open file";
}

LexicalAnalysis::~LexicalAnalysis() {
    fclose(m_file);
}

int LexicalAnalysis::line() const {
    return m_line;
}

struct Lexeme LexicalAnalysis::nextToken() {
    int estado = 1;
    struct Lexeme lex = { "", END_OF_FILE };

    while(estado != 9 && estado != 10){
        int c = getc(m_file);
        switch(estado){
            case 1:
                if (c == ' ' || c == '\t' || c== '\r'){
                } else if (c == '\n') {
                    m_line++;
                } else if (c == '/'){
                    lex.token += (char) c;
                    estado = 2;
                } else if (isdigit(c)){
                    lex.token += (char) c;
                    lex.type = NUMBER;
                    estado = 5;
                } else if (c == '<' || c == '>' || c == '!' || c == '='){
                    lex.token += (char) c;
                    estado = 6;
                } else if (isalpha(c)){
                    lex.token += (char) c;
                    estado = 7;
                } else if (c == '\"') {
                    lex.type = STRING;
                    estado = 8;
                } else if (c == ';' || c == ',' || c == '.' || c == '(' || c == ')' || c == '{' || c == '}' || c == '+' || c == '-' || c == '*' || c == '%' || c == '&' || c == '|'){
                    lex.token += (char) c;
                    estado = 9;
                } else if (c == -1) {
                    lex.type = END_OF_FILE;
                    estado = 10;
                } else {
                    lex.token += (char) c;
                    lex.type = INVALID_TOKEN;
                    estado = 10;
                }
                break;
            case 2:
                if(c == '*'){
                    // todo retirar '/' ?
                    lex.token = "";
                    estado = 3;
                } else {
                    if (c != -1)
                        ungetc(c, m_file);

                    estado = 9;
                }
                break;
            case 3:
                if(c == '*'){
                    estado = 4;
                } else {
                    estado = 3;
                }
                break;
            case 4:
                if(c == '*'){
                    estado = 4;
                } else if(c == '/'){
                    estado = 1;
                } else {
                    estado = 3;
                }
                break;
            case 5:
                if (isdigit(c)){
                    lex.token += (char) c;
                    estado = 5;
                }else{
                    if (c != -1)
                        ungetc(c, m_file);
                    estado = 10;
                }
                break;
            case 6:
                if (c == '='){
                    lex.token += (char) c;
                }else{
                    if (c != -1)
                        ungetc(c, m_file);
                }
                estado = 9;
                break;
            case 7:
                if (isdigit(c) || isalpha(c)){
                    lex.token += (char) c;
                    estado = 7;
                }else{
                    if (c != -1)
                        ungetc(c, m_file);
                    estado = 9;
                }
                break;
            case 8:
                if (c != '\"'){
                    estado = 8;
                    lex.token += (char) c;
                }else{
                    estado = 10;
                }
                break;
            default:
                break;
        }
        if(estado == 9){
            if (m_st.contains(lex.token)) {
                lex.type = m_st.find(lex.token);
            } else {
                lex.type = NAME;
            }
        }
    }

    return lex;
}
