#ifndef FRAMEADDPAYMENT_HPP
#define FRAMEADDPAYMENT_HPP

#include <QFrame>
#include <QSqlRelationalTableModel>
#include <QString>

namespace Ui {
class FrameAddPayment;
}

class FrameAddPayment : public QFrame
{
    Q_OBJECT

public:
    explicit FrameAddPayment(QWidget *parent = 0);
    ~FrameAddPayment();

    void setModel(QSqlRelationalTableModel *model);

private slots:
    void addRow();

private:
    Ui::FrameAddPayment *ui;
    QSqlRelationalTableModel *rmodel;
};

#endif // FRAMEADDPAYMENT_HPP
