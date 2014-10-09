#ifndef FRAMEADDPAYMENT_HPP
#define FRAMEADDPAYMENT_HPP

#include <QFrame>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QString>
#include <QMap>
#include <QSortFilterProxyModel>
#include "department.hpp"

namespace Ui {
class FrameAddPayment;
}

class FrameAddPayment : public QFrame
{
    Q_OBJECT

public:
    explicit FrameAddPayment(QWidget *parent = 0);
    ~FrameAddPayment();

private slots:
    void on_comboBoxYear_currentIndexChanged(int index);
    void on_comboBoxDepartment_currentIndexChanged(int index);
    void on_comboBoxGroup_currentIndexChanged(int index);
    void handleSelectionChanged(QModelIndex selection);
    void on_lineEditFind_textEdited(const QString &arg1);
    void sortStudent(int index, Qt::SortOrder order);

private:
    Ui::FrameAddPayment *ui;

    QMap<QString, int> sexList;
    QMap<QString, int> countryList;
    QMap<QString, int> admUnitList;

    QMap<int, Department *> departmentList;
    QMap<int, QString> yearList;
    QMap<int, QString> groupList;
    QMap<int, QString> cntrTypeList;
    QMap<int, QString> durationList;
    QMap<int, QString> curriculumList;

    QSqlQueryModel *qmodstud;

    QSqlQueryModel *qmoddepartment;
    QSqlQueryModel *qmodyear;
    QSqlQueryModel *qmodgroup;
    QSqlQuery *qmodcontrtype;
    QSqlQuery *qmodcuriculum;

    QSqlQuery *qcontract;
    QSqlQuery *qInsertStudent;
    QSqlQuery *qDeleteStudent;
    QSqlQueryModel *qmodpay;
    QSqlQueryModel *qphone;
    QSqlTableModel *qtablem;
    QSqlQueryModel *resultTable;
    QSortFilterProxyModel *sqlproxy;
};

#endif // FRAMEADDPAYMENT_HPP
