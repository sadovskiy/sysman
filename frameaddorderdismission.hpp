#ifndef FRAMEADDORDERDISMISSION_HPP
#define FRAMEADDORDERDISMISSION_HPP

#include <QFrame>
#include <QSqlRelationalTableModel>
#include <QString>

namespace Ui {
class FrameAddOrderDismission;
}

class FrameAddOrderDismission : public QFrame
{
    Q_OBJECT

public:
    explicit FrameAddOrderDismission(QWidget *parent = 0);
    ~FrameAddOrderDismission();

    void setModel(QSqlRelationalTableModel *model);

private slots:
    void addRow();

private:
    Ui::FrameAddOrderDismission *ui;
    QSqlRelationalTableModel *rmodel;
};

#endif // FRAMEADDORDERDISMISSION_HPP
