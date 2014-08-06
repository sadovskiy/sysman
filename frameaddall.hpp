#ifndef FRAMEADDALL_HPP
#define FRAMEADDALL_HPP

#include <QFrame>
#include <QSqlRelationalTableModel>
#include <QString>

namespace Ui {
class FrameAddAll;
}

class FrameAddAll : public QFrame
{
    Q_OBJECT

public:
    explicit FrameAddAll(QWidget *parent = 0);
    ~FrameAddAll();

    void setModel(QSqlRelationalTableModel *model);

private slots:
    void addRow();

private:
    Ui::FrameAddAll *ui;
    QSqlRelationalTableModel *rmodel;
};

#endif // FRAMEADDALL_HPP
