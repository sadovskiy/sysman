#include "money.hpp"

#include <QLocale>
#include <QStringList>
#include <QDebug>

Money::Money(const int integ, const int fract) :
    mInteg(integ), mFract(fract)
{
}

Money::Money() :
    mInteg(0), mFract(0)
{

}

int Money::integ() const
{
    return mInteg;
}

void Money::setInteg(int integ)
{
    mInteg = integ;
}

int Money::fract() const
{
    return mFract;
}

void Money::setFract(int fract)
{
    mFract = fract;
}

Money Money::parse(const QString& input) {
    QString cleanInput = input;
    Money result;

    // remove group separators
    QLocale locale = QLocale::system();
    cleanInput.remove(locale.groupSeparator());

    // convert to money
    QStringList parts = cleanInput.split(locale.decimalPoint());

    qDebug() << QString("%1").arg(locale.currencySymbol());

    if (parts.count() == 1) {
       result.setInteg(parts[0].toInt());
    } else if (parts.count() == 2) {
       result.setInteg(parts[0].toInt());
       result.mFract = parts[1].toInt() * 10;
    } else {
         // error, not a number
    }

    return result;
}
