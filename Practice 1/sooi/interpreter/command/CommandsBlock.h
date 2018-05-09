#ifndef COMMANDS_BLOCK_H
#define COMMANDS_BLOCK_H

#include "Command.h"
#include <list>

class Instance;
class Arguments;

class CommandsBlock : public Command {
    public:
        CommandsBlock();
        virtual ~CommandsBlock();
        void addCommand(Command* c);
        virtual void execute(Instance* self, Arguments* args);

    private:
        std::list<Command*> m_cmds;

};

#endif

