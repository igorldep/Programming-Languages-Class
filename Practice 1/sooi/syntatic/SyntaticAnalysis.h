#ifndef SYNTATIC_ANALYSIS_H
#define SYNTATIC_ANALYSIS_H

#include "../interpreter/expr/RelOp.h"
#include "../lexical/LexicalAnalysis.h"
#include <map>

class AccessPath;
class AssignCommand;
class BoolExpr;
class Command;
class CommandsBlock;
class ConstExpr;
class Expr;
class FunctionCallExpr;
class FunctionRhs;
class IfCommand;
class Rhs;
class SingleBoolExpr;
class WhileCommand;


class SyntaticAnalysis {
public:
    explicit SyntaticAnalysis(LexicalAnalysis& lex);
    virtual ~SyntaticAnalysis();

    Command* start();

private:
    LexicalAnalysis& m_lex;
    Lexeme m_current;

    void matchToken(enum TokenType type);
    void showError();

    std::string procName();
    ConstExpr* procNumber();
    ConstExpr* procString();
    CommandsBlock* procCode();
    Command* procStatement();
    IfCommand* procIf();
    WhileCommand* procWhile();
    AssignCommand* procCmd();
    AccessPath* procAccess();
    AssignCommand* procAssign(AccessPath* path);
    FunctionCallExpr* procCall(AccessPath* path);
    BoolExpr* procBoolExpr();
    SingleBoolExpr* procCmpExpr();
    enum RelOp procRelop();
    Rhs* procRhs();
    FunctionRhs* procFunction();
    Expr* procExpr();
    Expr* procTerm();
    Expr* procFactor();
    std::string procVar();

};

#endif
