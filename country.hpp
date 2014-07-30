#ifndef COUNTRY_HPP
#define COUNTRY_HPP

#include <QString>

class Country
{
public:
    Country() {};
    Country(int num, QString alpha2, QString alpha3,
                     QString cyr3, QString comm, long telecode);

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
