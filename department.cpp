#include "department.hpp"

Department::Department()
{
}

Department::Department(const int depId, const QString depShort, const QString depFull):
    departmentId(depId),
    departmentShort(depShort),
    departmentFull(depFull)
{
}

void Department::setDepId(const int depId)
{
    departmentId = depId;
}

void Department::setDepShort(const QString depShort)
{
    departmentShort = depShort;
}

void Department::setDepFull(const QString depFull)
{
    departmentFull = depFull;
}

int Department::getDepId() const
{
    return departmentId;
}

QString Department::getDepShort() const
{
    return departmentShort;
}

QString Department::getDepFull() const
{
    return departmentFull;
}
