#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QSqlRelationalTableModel>
#include <QTranslator>
#include <QHeaderView>
#include <QSortFilterProxyModel>

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
    void closeTab(int Index);
    void CrMenu();

private:
    Ui::MainWindow *ui;
    QTranslator appTranslator;
    QHeaderView *pHeader;
    QSortFilterProxyModel *proxyModel;
    QSqlRelationalTableModel *rmodel1;
    QSqlRelationalTableModel *rmodel2;
    QSqlRelationalTableModel *rmodel3;
    QSqlRelationalTableModel *rmodel4;
};

#endif // MAINWINDOW_HPP
