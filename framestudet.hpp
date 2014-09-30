#ifndef FRAMESTUDET_HPP
#define FRAMESTUDET_HPP

#include <QFrame>
#include <QSqlQueryModel>
#include <QSqlRelationalTableModel>
#include <QItemSelection>
#include <QModelIndex>
#include <QMap>
#include <QMdiSubWindow>

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

//    void addWindow(QModelIndex selection, QModelIndex deselection);

    void on_comboBoxDepartment_currentIndexChanged(int index);

    void on_comboBoxYear_currentIndexChanged(int index);

    void on_comboBoxGroup_currentIndexChanged(int index);

    void on_pushButtonAddStudent_clicked();

    void on_pushButtonApplyChanges_clicked();

    void on_lineEditFind_textEdited(const QString &arg1);

    void on_pushButtonDelStudent_clicked();

    void on_treeWidgetContract_clicked(const QModelIndex &index);

    void on_pushButtonAddPhonNum_clicked();

    void on_listWidgetPhone_currentRowChanged(int currentRow);

    void on_pushButtonDelPhone_clicked();

    void on_pushButtonAddContract_clicked();

    void on_pushButtonAddOrder_clicked();

private:
    Ui::FrameStudet *ui;

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


    void updateStudent();

};

#endif // FRAMESTUDET_HPP
