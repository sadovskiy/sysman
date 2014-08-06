#ifndef FRAMEADDCONTRACT_HPP
#define FRAMEADDCONTRACT_HPP

#include <QFrame>
#include <QSqlRelationalTableModel>
#include <QString>

namespace Ui {
class FrameAddContract;
}

class FrameAddContract : public QFrame
{
    Q_OBJECT

public:
    explicit FrameAddContract(QWidget *parent = 0);
    ~FrameAddContract();

    void setModel(QSqlRelationalTableModel *model);

private slots:
    void addRow();

private:
    Ui::FrameAddContract *ui;
    QSqlRelationalTableModel *rmodel;
};

#endif // FRAMEADDCONTRACT_HPP
