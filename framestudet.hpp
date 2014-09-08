#ifndef FRAMESTUDET_HPP
#define FRAMESTUDET_HPP

#include <QFrame>
#include <QSqlQueryModel>
#include <QSqlRelationalTableModel>
#include <QItemSelection>
#include <QModelIndex>
#include <QMap>

#include "department.hpp"

namespace Ui {
class FrameStudet;
}

class FrameStudet : public QFrame
{
    Q_OBJECT

public:
    explicit FrameStudet(QWidget *parent = 0);
    ~FrameStudet();

private slots:
    void handleSelectionChanged(QModelIndex selection);

    void on_comboBoxDepartment_currentIndexChanged(int index);

    void on_comboBoxYear_currentIndexChanged(int index);

    void on_comboBoxGroup_currentIndexChanged(int index);

    void on_pushButton_clicked();

private:
    Ui::FrameStudet *ui;

    QMap<QString, int> sexList;
    QMap<QString, int> countryList;
    QMap<QString, int> admUnitList;

    QMap<int, Department *> departmentList;
    QMap<int, QString> yearList;
    QMap<int, QString> groupList;

    QSqlQueryModel *qmodstud;
    QSqlQueryModel *qmodpay;
    QSqlQueryModel *qmoddepartment;
    QSqlQueryModel *qmodyear;
    QSqlQueryModel *qmodgroup;
    QSqlQuery *qInsertStudent;


};

#endif // FRAMESTUDET_HPP
