#ifndef TABLEVIEWTABFORM_HPP
#define TABLEVIEWTABFORM_HPP

#include <QWidget>
#include <QSqlRelationalTableModel>
#include <QMenu>
#include <QDebug>
#include <QAction>
#include <QSortFilterProxyModel>

#include "frameaddcontract.hpp"
#include "frameaddorderadmission.hpp"
#include "frameaddorderdismission.hpp"
#include "frameaddpayment.hpp"
#include "frameaddphasepayment.hpp"

namespace Ui {
class TableViewTabForm;
}

class TableViewTabForm : public QWidget
{
    Q_OBJECT

public:
    explicit TableViewTabForm(QWidget *parent = 0);
    ~TableViewTabForm();
    void setTableName(QString name);
    QString tableName() const;
    void clear() const;
    QSqlRelationalTableModel *rmodel;

public slots:
    void customHeaderMenuRequested(QPoint pos);


private slots:
    void ShowHideFrameAddRow();
    void HideHeader();

private:
    Ui::TableViewTabForm *ui;
    QMenu *contextHeaderMenu;

    QString tName;
    QAction *actionHeader;
    QPoint mPos;

    FrameAddContract *framecontr;
    FrameAddOrderAdmission *frameoadm;
    FrameAddOrderDismission *frameodism;
    FrameAddPayment *framepayment;
    FrameAddPhasePayment *framepp;
    QSortFilterProxyModel *sort_filter;
};

#endif // TABLEVIEWTABFORM_HPP
