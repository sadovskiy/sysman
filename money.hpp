#ifndef MONEY_HPP
#define MONEY_HPP

#include <QString>

class Money
{
    int mInteg;
    int mFract;
public:
    Money(const int mInteg, const int mFract);
    Money();
    Money parse(const QString& input);
    int integ() const;
    void setInteg(int integ);
    int fract() const;
    void setFract(int fract);
};

#endif // MONEY_HPP
