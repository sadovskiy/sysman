#include "country.hpp"

Country::Country(const int num, const QString alpha2, const QString alpha3,
                 const QString cyr3, const QString comm, const long telecode):
    numCodeCountry(num), alpha2CodeCountry(alpha2), alpha3CodeCountry(alpha3),
    cyr3CodeCountry(cyr3), comment(comm), telephonCode(telecode)
{
}

int Country::nCodeCountry() const
{
    return numCodeCountry;
}

QString Country::a2CodeCountry() const
{
    return alpha2CodeCountry;
}

QString Country::a3CodeCountry() const
{
    return alpha3CodeCountry;
}

QString Country::c3CodeCountry() const
{
    return alpha3CodeCountry;
}

QString Country::comm() const
{
    return comment;
}

long Country::tCode() const
{
    return telephonCode;
}
