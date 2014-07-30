#ifndef TABLEVIEWTABFORM_HPP
#define TABLEVIEWTABFORM_HPP

#include <QWidget>
#include <QSqlRelationalTableModel>
#include <QMenu>
#include <QDebug>

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

public slots:
    void customHeaderMenuRequested(QPoint pos);
    void addRow();

private:
    Ui::TableViewTabForm *ui;
    QMenu *contextHeaderMenu;
    QSqlRelationalTableModel *rmodel;
    QString tName;
};

#endif // TABLEVIEWTABFORM_HPP
