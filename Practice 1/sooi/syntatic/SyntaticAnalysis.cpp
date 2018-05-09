#include <iostream>
#include <cstdlib>
#include "SyntaticAnalysis.h"

#include "../interpreter/command/AssignCommand.h"
#include "../interpreter/command/Command.h"
#include "../interpreter/command/CommandsBlock.h"
#include "../interpreter/command/IfCommand.h"
#include "../interpreter/command/WhileCommand.h"
#include "../interpreter/expr/AccessExpr.h"
#include "../interpreter/expr/BoolExpr.h"
#include "../interpreter/expr/CompositeBoolExpr.h"
#include "../interpreter/expr/CompositeExpr.h"
#include "../interpreter/expr/ConstExpr.h"
#include "../interpreter/expr/Expr.h"
#include "../interpreter/expr/FunctionCallExpr.h"
#include "../interpreter/expr/FunctionRhs.h"
#include "../interpreter/expr/NotBoolExpr.h"
#include "../interpreter/expr/Rhs.h"
#include "../interpreter/expr/RelOp.h"
#include "../interpreter/expr/SingleBoolExpr.h"
#include "../interpreter/util/AccessPath.h"
#include "../interpreter/util/StandardFunction.h"
#include "../interpreter/value/IntegerValue.h"
#include "../interpreter/value/FunctionValue.h"
#include "../interpreter/value/StringValue.h"

SyntaticAnalysis::SyntaticAnalysis(LexicalAnalysis& lex) :
    m_lex(lex), m_current(m_lex.nextToken()) {
}

SyntaticAnalysis::~SyntaticAnalysis() {
}

Command* SyntaticAnalysis::start() {
    Command* c = procCode();
    matchToken(END_OF_FILE);
    return c;
}

void SyntaticAnalysis::matchToken(enum TokenType type) {
    if (type == m_current.type) {
        m_current = m_lex.nextToken();
    } else {
        showError();
    }
}

void SyntaticAnalysis::showError() {
    printf("%02d: ", m_lex.line());

    switch (m_current.type) {
        case INVALID_TOKEN:
            printf("Lexema inválido [%s]\n", m_current.token.c_str());
            break;
        case UNEXPECTED_EOF:
        case END_OF_FILE:
            printf("Fim de arquivo inesperado\n");
            break;
        default:
            printf("Lexema não esperado [%s]\n", m_current.token.c_str());
            break;
    }

    exit(1);
}


std::string SyntaticAnalysis::procName(){
    std::string name = m_current.token;
    matchToken(NAME);
    return name;
}

ConstExpr* SyntaticAnalysis::procNumber(){
    int line = m_lex.line();
    std::string tmp = m_current.token;
    matchToken(NUMBER);
    int n = atoi(tmp.c_str());
    IntegerValue* iv = new IntegerValue(n);
    ConstExpr* ce = new ConstExpr(iv, line);
    return ce;
}

ConstExpr* SyntaticAnalysis::procString(){
    int line = m_lex.line();
    std::string tmp = m_current.token;
    matchToken(STRING);
    StringValue* sv = new StringValue(tmp);
    ConstExpr* ce = new ConstExpr(sv, line);
    return ce;
}

// <code> ::= { <statement> }
CommandsBlock* SyntaticAnalysis::procCode(){
    CommandsBlock* cb = new CommandsBlock();
    while(  m_current.type == IF ||
            m_current.type == WHILE ||
            m_current.type == SYSTEM ||
            m_current.type == SELF ||
            m_current.type == ARGS ||
            m_current.type == NAME){
        Command* c = procStatement();
        cb->addCommand(c);
    }
    return cb;
}

// <statement> ::= <if> | <while> | <cmd>
Command* SyntaticAnalysis::procStatement(){
    Command* c = 0;
    switch(m_current.type){
        case IF:
            c = procIf();
            break;
        case WHILE:
            c = procWhile();
            break;
        default:
            c = procCmd();
            break;
    }
    return c;
}

// <if> ::= if '(' <boolexpr> ')' '{' <code> '}' [else '{' <code> '}']
IfCommand* SyntaticAnalysis::procIf(){
    Command* _else = 0;
    matchToken(IF);
    matchToken(OPEN_PAR);
    int line = m_lex.line();
    BoolExpr* _bool = procBoolExpr();
    matchToken(CLOSE_PAR);
    matchToken(OPEN_CUR);
    Command* _then = procCode();
    matchToken(CLOSE_CUR);
    if(m_current.type == ELSE){
        matchToken(ELSE);
        matchToken(OPEN_CUR);
        _else = procCode();
        matchToken(CLOSE_CUR);
    }
    IfCommand* _if;
    if(_else)
        _if = new IfCommand(_bool, _then, _else, line);
    else
        _if = new IfCommand(_bool, _then, line);

    return _if;
}

// <while> ::= while '(' <boolexpr>  ')' '{' <code> '}'
WhileCommand* SyntaticAnalysis::procWhile(){
    matchToken(WHILE);
    matchToken(OPEN_PAR);
    int line = m_lex.line();
    BoolExpr* _bool = procBoolExpr();
    matchToken(CLOSE_PAR);
    matchToken(OPEN_CUR);
    Command* _do = procCode();
    matchToken(CLOSE_CUR);
    WhileCommand* _while = new WhileCommand(_bool, _do, line);
    return _while;
}



// <cmd> ::= <access> ( <assign> | <call> ) ';'
AssignCommand* SyntaticAnalysis::procCmd(){
    AccessPath* path = procAccess();
    AssignCommand* ac = 0;

    if(m_current.type == ASSIGN){
        ac = procAssign(path);
    }else if(m_current.type == OPEN_PAR){
        int line = m_lex.line();
        FunctionCallExpr* fce = procCall(path);
        ac = new AssignCommand(0, fce, line);
    }else{
        showError();
    }
    matchToken(DOT_COMMA);
    return ac;
}

// <access> ::= <var> {'.' <name>}
AccessPath* SyntaticAnalysis::procAccess(){
    int line = m_lex.line();
    std::string name = procVar();
    AccessPath* path = new AccessPath(name, line);

    while(m_current.type == DOT){
        matchToken(DOT);
        name = procName();
        path->addName(name);
    }

    return path;
}

// <assign> ::= '=' <rhs>
AssignCommand* SyntaticAnalysis::procAssign(AccessPath* path){
    int line = m_lex.line();
    matchToken(ASSIGN);
    Rhs* rhs = procRhs();
    AssignCommand* ac = new AssignCommand(path, rhs, line);
    return ac;
}

// <call> ::= '(' [ <rhs> { ',' <rhs> } ] ')'
FunctionCallExpr* SyntaticAnalysis::procCall(AccessPath* path){
    FunctionCallExpr* fce = new FunctionCallExpr(path, m_lex.line());
    matchToken(OPEN_PAR);
    if(	m_current.type == FUNCTION ||
    	m_current.type == NUMBER ||
    	m_current.type == STRING ||
    	m_current.type == SYSTEM ||
    	m_current.type == SELF ||
    	m_current.type == ARGS ||
    	m_current.type == NAME ||
    	m_current.type == OPEN_PAR){
        Rhs* rhs = procRhs();
        fce->addParam(rhs);
        while(m_current.type == COMMA){
            matchToken(COMMA);
            rhs = procRhs();
            fce->addParam(rhs);
        }
    }
    matchToken(CLOSE_PAR);
    return fce;
}

// <boolexpr> ::= [ '!' ] <cmpexpr> [ ('&' | '|') <boolexpr> ]
BoolExpr* SyntaticAnalysis::procBoolExpr(){
    bool negative = false;
    if(m_current.type == NEGATIVE){
        matchToken(NEGATIVE);
        negative = true;
    }

    BoolExpr* _bool = procCmpExpr();

    if(m_current.type == OR|| m_current.type == AND){
        int line = m_lex.line();
        enum BoolOp _op = BOOL_INVALID;
        switch(m_current.type){
            case AND: _op = BOOL_AND; break;
            case OR: _op = BOOL_OR; break;
            default: showError(); break;
        }
        matchToken(m_current.type);
        _bool = new CompositeBoolExpr(_bool, _op, procBoolExpr(), line);
    }
    int line = m_lex.line();
    if(negative)
        _bool = new NotBoolExpr(_bool, line);

    return _bool;
}

// <cmpexpr> ::= <expr> <relop> <expr>
SingleBoolExpr* SyntaticAnalysis::procCmpExpr(){
    Expr* _left = procExpr();
    enum RelOp _relop = procRelop();
    int line = m_lex.line();
    Expr* _right = procExpr();
    SingleBoolExpr* _sbe = new SingleBoolExpr(_left, _relop, _right, line);
    return _sbe;
}

// <relop> ::= '==' | '!=' | '<' | '>' | '<=' | '>='
enum RelOp SyntaticAnalysis::procRelop(){
    if( m_current.type == EQUAL) {
        matchToken(EQUAL);
        return RELOP_EQUAL;
    } else if (m_current.type == DIFFERENT) {
        matchToken(DIFFERENT);
        return RELOP_NOTEQUAL;
    } else if (m_current.type == SMALLER) {
        matchToken(SMALLER);
        return RELOP_LOWER;
    } else if (m_current.type == BIGGER) {
        matchToken(BIGGER);
        return RELOP_GREATER;
    } else if (m_current.type == SMALLER_EQUAL) {
        matchToken(SMALLER_EQUAL);
        return RELOP_LOWEREQUAL;
    } else if (m_current.type == BIGGER_EQUAL) {
        matchToken(BIGGER_EQUAL);
        return RELOP_GREATEREQUAL;
    }

    return RELOP_INVALID;
}

// <rhs> ::= <function> | <expr>
Rhs* SyntaticAnalysis::procRhs(){
    Rhs* rhs = 0;
    if(m_current.type == FUNCTION){
        rhs = procFunction();
    }else{
        rhs = procExpr();
    }

    return rhs;
}

// <function> ::= function '{' <code> [ return <rhs> ] '}'
FunctionRhs* SyntaticAnalysis::procFunction(){
    matchToken(FUNCTION);
    matchToken(OPEN_CUR);
    int line = m_lex.line();
    Command* _cmd = procCode();
    StandardFunction* sf = new StandardFunction(_cmd);
    if(m_current.type == RETURN){
        matchToken(RETURN);
        Rhs* _rhs = procRhs();
        sf = new StandardFunction(_cmd, _rhs);
        matchToken(DOT_COMMA);
    }
    FunctionValue* func = new FunctionValue(sf);
    FunctionRhs* fr = new FunctionRhs(line, func);
    matchToken(CLOSE_CUR);
    return fr;
}

// <expr> ::= <term> { ('+' | '-') <term> }
/*Expr* SyntaticAnalysis::procExpr(){
    Expr* e = procTerm();
    while(m_current.type == ADD || m_current.type == SUB){

        if(m_current.type == ADD)
            matchToken(ADD);
        else
            matchToken(SUB);

        Expr* e2 = procTerm();
    }
    return e;
}*/

Expr* SyntaticAnalysis::procExpr(){
    Expr* e = procTerm();
    while(m_current.type == ADD || m_current.type == SUB){

        int line = m_lex.line();
        enum CompositeExpr::CompOp _op = CompositeExpr::INVALID;

        if(m_current.type == ADD){
            _op = CompositeExpr::ADD;
            matchToken(ADD);
        }else{
            _op = CompositeExpr::SUB;
            matchToken(SUB);
        }

        Expr* e2 = procExpr(); // procTerm
        e = new CompositeExpr(e, _op, e2, line);
    }
    return e;
}
// <term> ::= <factor> { ('*' | '/' | '%') <factor> }
/*Expr* SyntaticAnalysis::procTerm(){
    Expr* e = procFactor();
    while(m_current.type == MUL || m_current.type == DIV || m_current.type == MOD){

        if(m_current.type == MUL)
            matchToken(MUL);
        else if(m_current.type == DIV)
            matchToken(DIV);
        else
            matchToken(MOD);

        Expr* e2 = procFactor();
        //e = new CompositeExpr(e, e2, ...);
    }

    return e;
}*/

Expr* SyntaticAnalysis::procTerm(){
    Expr* e = procFactor();
    while(m_current.type == MUL || m_current.type == DIV || m_current.type == MOD){

        int line = m_lex.line();
        enum CompositeExpr::CompOp _op = CompositeExpr::INVALID;

        if(m_current.type == MUL){
            _op = CompositeExpr::MUL;
            matchToken(MUL);
        }else if(m_current.type == DIV){
            _op = CompositeExpr::DIV;
            matchToken(DIV);
        }else{
            _op = CompositeExpr::MOD;
            matchToken(MOD);
        }

        Expr* e2 = procTerm();
        e = new CompositeExpr(e, _op, e2, line);
    }

    return e;
}

// <factor> ::= <number> | <string> | <access> [ <call> ] | '(' <expr> ')'
Expr* SyntaticAnalysis::procFactor(){
    Expr* e = 0;
    switch(m_current.type){
        case NUMBER:
            e = procNumber();
            break;
        case STRING:
            e = procString();
            break;
        case OPEN_PAR:
        	matchToken(OPEN_PAR);
        	e = procExpr();
        	matchToken(CLOSE_PAR);
        	break;
        default:
            int line = m_lex.line();
            AccessPath* path = procAccess();

		    if(m_current.type == OPEN_PAR){
		        e = procCall(path);
		    } else {
                e = new AccessExpr(path, line);
                //e = ae;
		    }
            break;
    }
    return e;
}

// <var> ::= system | self | args | <name>
std::string SyntaticAnalysis::procVar(){
    std::string var = "";
    switch(m_current.type){
        case SYSTEM:
            matchToken(SYSTEM);
            var = "system";
            break;
        case SELF:
            matchToken(SELF);
            var = "self";
            break;
        case ARGS:
            matchToken(ARGS);
            var = "args";
            break;
        default: // case NAME:
            var = procName();
            break;
    }
    return var;
}
