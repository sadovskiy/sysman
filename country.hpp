#ifndef COUNTRY_HPP
#define COUNTRY_HPP

#include <QString>

class Country
{
public:
    Country() {}
    Country(const int num, const QString alpha2, const QString alpha3,
            const QString cyr3, const QString comm, const long telecode);

    int nCodeCountry() const;
    QString a2CodeCountry() const;
    QString a3CodeCountry() const;
    QString c3CodeCountry() const;
    QString comm() const;
    long tCode() const;

private:
    int numCodeCountry;
    QString alpha2CodeCountry;
    QString alpha3CodeCountry;
    QString cyr3CodeCountry;
    QString comment;
    long telephonCode;
};

#endif // COUNTRY_HPP
