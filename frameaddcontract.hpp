#ifndef FRAMEADDCONTRACT_HPP
#define FRAMEADDCONTRACT_HPP

#include <QFrame>
#include <QSqlQuery>
#include <QString>
#include <QMap>

namespace Ui {
class FrameAddContract;
}

class FrameAddContract : public QFrame
{
    Q_OBJECT

public:
    explicit FrameAddContract(QWidget *parent = 0);
    ~FrameAddContract();

    void loadData(QMap<int, QString> &cntrTypeList, QMap<int, QString> &curriculumList, QMap<int, QString> &yearList, const int numStr);

private slots:
    void on_pushButton_clicked();

private:
    Ui::FrameAddContract *ui;
/*
    QMap<int, QString> mcntrTypeList;
    QMap<int, QString> mdurationList;
    QMap<int, QString> myearList;
*/
};

#endif // FRAMEADDCONTRACT_HPP
