#ifndef UTIL_H
#define UTIL_H

class Util {
public:
    virtual ~Util() {}

    int line() const { return m_line; }

protected:
    explicit Util(int line) : m_line(line) {}

private:
    int m_line;

};

#endif
