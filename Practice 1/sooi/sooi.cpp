#include <iostream>

#include "lexical/LexicalAnalysis.h"
#include "syntatic/SyntaticAnalysis.h"
#include "interpreter/command/Command.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s [SmallOO File]\n", argv[0]);
        return 1;
    }

    try {
        LexicalAnalysis l(argv[1]);
        SyntaticAnalysis s(l);

        Command* c = s.start();
        c->execute(0, 0);
        delete c;

    /*
       struct Lexeme lex;
        while ((lex = l.nextToken()).type > 0) {
            printf("(\"%s\", %d)\n", lex.token.c_str(), lex.type);
        }

        switch (lex.type) {
            case INVALID_TOKEN:
                printf("%02d: Lexema inválido [%s]\n", l.line(), lex.token.c_str());
                break;
            case UNEXPECTED_EOF:
                printf("%02d: Fim de arquivo inesperado\n", l.line());
                break;
            default:
                printf("(\"%s\", %d)\n", lex.token.c_str(), lex.type);
                break;
        }
    */
    } catch (std::string msg) {
        fprintf(stderr, "Internal error: %s\n", msg.c_str());
        return 2;
    }

    return 0;
}
