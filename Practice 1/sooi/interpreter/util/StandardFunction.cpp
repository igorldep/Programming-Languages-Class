#include "StandardFunction.h"

#include "Arguments.h"
#include "Instance.h"
#include "../command/Command.h"
#include "../expr/Rhs.h"
#include "../value/Type.h"


StandardFunction::StandardFunction(Command* cmds, Rhs* ret) : m_cmds(cmds), m_ret(ret) {
}

StandardFunction::StandardFunction(Command* cmds) : m_cmds(cmds) {
}

StandardFunction::~StandardFunction() {
}

Type* StandardFunction::call(Instance* self, Arguments* args) {
    Type* value = 0;
    m_cmds->execute(self, args);
    if (m_ret){
        value = m_ret->rhs(self, args);
    }
    return value;
}
