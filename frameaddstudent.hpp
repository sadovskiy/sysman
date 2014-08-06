#ifndef FRAMEADDSTUDENT_HPP
#define FRAMEADDSTUDENT_HPP

#include <QFrame>
#include <QSqlRelationalTableModel>
#include <QString>

namespace Ui {
class FrameAddStudent;
}

class FrameAddStudent : public QFrame
{
    Q_OBJECT

public:
    explicit FrameAddStudent(QWidget *parent = 0);
    ~FrameAddStudent();

    void setModel(QSqlRelationalTableModel *model);

private slots:
    void addRow();

private:
    Ui::FrameAddStudent *ui;
    QSqlRelationalTableModel *rmodel;
    QMap<QString, int> sexList;
};

#endif // FRAMEADDSTUDENT_HPP
