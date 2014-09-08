#ifndef DEPARTMENT_HPP
#define DEPARTMENT_HPP

#include <QString>

class Department
{
    int departmentId;
    QString departmentShort;
    QString departmentFull;

public:
    Department();
    Department(const int depId, const QString depShort, const QString depFull);

    void setDepId(const int depId);
    void setDepShort(const QString depShort);
    void setDepFull(const QString depFull);

    int getDepId() const;
    QString getDepShort() const;
    QString getDepFull() const;
};

#endif // DEPARTMENT_HPP
