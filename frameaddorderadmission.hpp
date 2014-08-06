#ifndef FRAMEADDORDERADMISSION_HPP
#define FRAMEADDORDERADMISSION_HPP

#include <QFrame>
#include <QSqlRelationalTableModel>
#include <QString>

namespace Ui {
class FrameAddOrderAdmission;
}

class FrameAddOrderAdmission : public QFrame
{
    Q_OBJECT

public:
    explicit FrameAddOrderAdmission(QWidget *parent = 0);
    ~FrameAddOrderAdmission();

    void setModel(QSqlRelationalTableModel *model);

private slots:
    void addRow();

private:
    Ui::FrameAddOrderAdmission *ui;
    QSqlRelationalTableModel *rmodel;
};

#endif // FRAMEADDORDERADMISSION_HPP
