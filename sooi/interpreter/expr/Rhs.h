#ifndef RHS_H
#define RHS_H

class Type;
class Instance;
class Arguments;

class Rhs {
    public:
        virtual ~Rhs() {}

        int line() const { return m_line; }
        virtual Type* rhs(Instance* self, Arguments* args) = 0;

    protected:
        Rhs(int line) : m_line(line) {}

    private:
        int m_line;

};

#endif
