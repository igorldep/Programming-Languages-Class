#ifndef GLOBAL_H
#define GLOBAL_H

#include "Memory.h"

class Global : public Memory {
    public:
        virtual ~Global();
        static Global* getGlobalTable();

    private:
        static Global* global;

        Global();

};

#endif