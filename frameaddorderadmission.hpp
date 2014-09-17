#ifndef FRAMEADDORDERADMISSION_HPP
#define FRAMEADDORDERADMISSION_HPP

#include <QFrame>
#include <QSqlQuery>
#include <QString>
#include <QMap>

#include "department.hpp"

namespace Ui {
class FrameAddOrderAdmission;
}

class FrameAddOrderAdmission : public QFrame
{
    Q_OBJECT

public:
    explicit FrameAddOrderAdmission(QWidget *parent = 0);
    ~FrameAddOrderAdmission();

    void loadData(QMap<int, Department *> &departmentList, const int num);

private slots:
    void addRow();

    void on_pushButton_clicked();

private:
    Ui::FrameAddOrderAdmission *ui;
};

#endif // FRAMEADDORDERADMISSION_HPP
