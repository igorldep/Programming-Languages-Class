#include "IfCommand.h"
#include "Command.h"
#include "../value/Type.h"
#include "../expr/BoolExpr.h"

IfCommand::IfCommand(BoolExpr* cond, Command* then, Command* ifelse, int line)
    : Command(line), m_cond(cond), m_then(then), m_else(ifelse) {
}

IfCommand::IfCommand(BoolExpr* cond, Command* then, int line)
    : Command(line), m_cond(cond), m_then(then) {
}

IfCommand::~IfCommand() {
}

void IfCommand::execute(Instance* self, Arguments* args) {
    if(m_cond->expr(self, args))
        m_then->execute(self, args);
    else {
        if (m_else != 0)
            m_else->execute(self, args);
    }
}
