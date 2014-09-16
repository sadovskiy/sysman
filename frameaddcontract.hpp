#ifndef FRAMEADDCONTRACT_HPP
#define FRAMEADDCONTRACT_HPP

#include <QFrame>
#include <QSqlQuery>
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

    void setModel(QSqlQuery *query);
    void loadData(const int numStr);

private slots:


private:
    Ui::FrameAddContract *ui;
//    QSqlQuery *mQuery;
};

#endif // FRAMEADDCONTRACT_HPP
