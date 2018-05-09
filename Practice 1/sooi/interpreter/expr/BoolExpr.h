#ifndef BOOLEXPR_H
#define BOOLEXPR_H

class Instance;
class Arguments;

class BoolExpr {
    public:
        virtual ~BoolExpr() {}
        virtual bool expr(Instance* self, Arguments* args) = 0;
        int line() const { return m_line; }

    protected:
        BoolExpr(int line) : m_line(line) {}

    private:
        int m_line;

};

#endif
