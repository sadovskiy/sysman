#ifndef FRAMEADDPHASEPAYMENT_HPP
#define FRAMEADDPHASEPAYMENT_HPP

#include <QFrame>
#include <QSqlRelationalTableModel>
#include <QString>

namespace Ui {
class FrameAddPhasePayment;
}

class FrameAddPhasePayment : public QFrame
{
    Q_OBJECT

public:
    explicit FrameAddPhasePayment(QWidget *parent = 0);
    ~FrameAddPhasePayment();

    void setModel(QSqlRelationalTableModel *model);

private slots:
    void addRow();

private:
    Ui::FrameAddPhasePayment *ui;
    QSqlRelationalTableModel *rmodel;
};

#endif // FRAMEADDPHASEPAYMENT_HPP
