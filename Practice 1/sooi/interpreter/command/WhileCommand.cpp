#include "WhileCommand.h"
#include "Command.h"
#include "../value/Type.h"
#include "../command/Command.h"
#include "../expr/BoolExpr.h"
#include "../expr/Expr.h"

WhileCommand::WhileCommand(BoolExpr* expr, Command* cmd, int line)
    : Command(line), m_expr(expr), m_cmd(cmd) {
}

WhileCommand::~WhileCommand() {
}

void WhileCommand::execute(Instance* self, Arguments* args) {
    while(m_expr->expr(self, args)){
        m_cmd->execute(self, args);
    }
    //todo
}
