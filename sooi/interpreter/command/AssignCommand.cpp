#include "AssignCommand.h"
#include "../value/Type.h"
#include "../expr/Rhs.h"
#include "../util/AccessPath.h"

AssignCommand::AssignCommand(AccessPath* lhs, Rhs* rhs, int line)
    : Command(line), m_lhs(lhs), m_rhs(rhs) {
}

AssignCommand::~AssignCommand() {
}

void AssignCommand::execute(Instance* self, Arguments* args) {
    Type* value = m_rhs->rhs(self, args);

    if (m_lhs != 0)
        m_lhs->setValue(self, args, value);
}
