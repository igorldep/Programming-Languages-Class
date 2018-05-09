#ifndef FUNCTION_H
#define FUNCTION_H

class Type;
class Instance;
class Arguments;
class IntegerValue;

class Function {
    public:
        virtual ~Function();
        virtual Type* call(Instance* self, Arguments* args) = 0;

    protected:
        Function();

};

#endif