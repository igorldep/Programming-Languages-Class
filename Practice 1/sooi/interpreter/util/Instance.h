#ifndef INSTANCE_H
#define INSTANCE_H

#include "Memory.h"

class Instance : public Memory {
    public:
        Instance();
        virtual ~Instance();

        Instance* dup() const;

};

#endif
