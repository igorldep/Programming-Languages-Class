#include "CommandsBlock.h"

CommandsBlock::CommandsBlock() : Command(-1) {
}

CommandsBlock::~CommandsBlock() {
}

void CommandsBlock::addCommand(Command* c) {
    m_cmds.push_back(c);

}

void CommandsBlock::execute(Instance* self, Arguments* args) {
    for (std::list<Command*>::iterator it = m_cmds.begin(), ed = m_cmds.end();
         it != ed; it++) {
        Command* c = *it;
        c->execute(self, args);
    }
}
