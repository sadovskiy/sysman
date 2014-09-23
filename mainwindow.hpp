#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QSqlRelationalTableModel>
#include <QTranslator>
#include <QTreeWidgetItem>
#include <QVector>

#include "country.hpp"
#include "tableviewtabform.hpp"
#include "framestudet.hpp"
#include "frameaddpayment.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionConnect_triggered();
    void update();
    void closeTab(int index);
    void itemTabNewOrOpenCurrent(QTreeWidgetItem *item, int col);
    void setCurrentItem(int index);
    void newTabStudentsList();
    void newTabStudentsPayment();


private:
    Ui::MainWindow *ui;

    QTranslator appTranslator;
    QTranslator  qtTranslator;

    TableViewTabForm *tvtab;
    FrameStudet *fs1;
    FrameAddPayment *fs2;

    QVector<Country> countryList;
};

#endif // MAINWINDOW_HPP
