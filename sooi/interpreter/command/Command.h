#ifndef COMMAND_H
#define COMMAND_H

class Instance;
class Arguments;

class Command {
public:
    virtual ~Command() {}

    int line() const { return m_line; }
    virtual void execute(Instance* self, Arguments* args) = 0;

protected:
    explicit Command(int line) : m_line(line) {}

private:
    int m_line;

};

#endif
