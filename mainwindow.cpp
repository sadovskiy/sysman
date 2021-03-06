#include "mainwindow.hpp"
#include "dialogconnecttodatabase.hpp"
#include "ui_mainwindow.h"

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QTableWidgetItem>
#include <QSqlRecord>
#include <QModelIndex>
#include <QMessageBox>
#include <QDir>
#include <QLibraryInfo>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Загружаем перевод
    qApp->installTranslator(&appTranslator);
    qApp->installTranslator(&qtTranslator);

    appTranslator.load("sysman_" + QLocale::system().name(),
                       QLibraryInfo::location(QLibraryInfo::TranslationsPath));

    qtTranslator.load("qt_" + QLocale::system().name(),
                      QLibraryInfo::location(QLibraryInfo::TranslationsPath));

    qDebug() << qApp->applicationDirPath();
    qDebug() << QLibraryInfo::location(QLibraryInfo::TranslationsPath);
    qDebug() << QLibraryInfo::location(QLibraryInfo::LibrariesPath);
    qDebug() << QLibraryInfo::location(QLibraryInfo::PluginsPath);
    qDebug() << QLibraryInfo::location(QLibraryInfo::PrefixPath);
    qDebug() << QLibraryInfo::location(QLibraryInfo::LibraryExecutablesPath);
    qDebug() << QLibraryInfo::location(QLibraryInfo::BinariesPath);
    qDebug() << QLibraryInfo::location(QLibraryInfo::DataPath);
    qDebug() << QLibraryInfo::location(QLibraryInfo::ArchDataPath);
    qDebug() << QLibraryInfo::location(QLibraryInfo::HeadersPath);

    // Так как библиотеки драйвера PostgeSQL ищются в каталогах
    // перечисленных в переменной PATH, не плохо бы посмотреть,
    // какие там перечислены каталоги.
//    qDebug() << getenv("PATH");
    qDebug() << getenv("PGLOCALEDIR");
    // Перевести сообщения на русский.
    ui->retranslateUi(this);

    // Проверяем наличи драйвера
    if (QSqlDatabase::isDriverAvailable("QPSQL"))
        qDebug() << "SUCCESS: PostgreSQL Database driver found." << endl;
    else
        qDebug() << "FAILURE: No PostgreSQL Database driver available." << endl;

    // Развернуть всё дерево
//    ui->treeWidget->expandAll();

    connect(ui->tabWidget, SIGNAL(tabCloseRequested(int)),
            this, SLOT(closeTab(int)));

/*    connect(ui->treeWidget, SIGNAL(itemClicked(QTreeWidgetItem*,int)),
            this, SLOT(itemTabNewOrOpenCurrent(QTreeWidgetItem*,int)));
            */
    connect(ui->actionOpenStudentsList, SIGNAL(triggered()),
                this, SLOT(newTabStudentsList()));
    connect(ui->actionOpenStudentsPayments, SIGNAL(triggered()),
                this, SLOT(newTabStudentsPayment()));
    connect(ui->tabWidget, SIGNAL(currentChanged(int)),
            this, SLOT(setCurrentItem(int)));

    connect(ui->actionAbout, SIGNAL(triggered()),
            qApp, SLOT(aboutQt()));

    // Прячем первую колонку списка так как там хранятся названия таблиц БД
    //ui->treeWidget->hideColumn(1);


//    ui->treeWidget->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newTabStudentsList()
{
    fs1 = new FrameStudet(this);
    fs1->setAttribute(Qt::WA_DeleteOnClose);
    ui->tabWidget->addTab(fs1, "Students List");
    ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 1);
}

void MainWindow::newTabStudentsPayment()
{
    fs2 = new FrameAddPayment(this);
    fs2->setAttribute(Qt::WA_DeleteOnClose);
    ui->tabWidget->addTab(fs2, "Students List");
    ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 1);
}

void MainWindow::on_actionConnect_triggered()
{
    ui->statusBar->clearMessage();
    DialogConnectToDataBase dialogConnectToDataBase;
    int result = dialogConnectToDataBase.exec();

    if (result == DialogConnectToDataBase::Accepted) {
        QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");

        db.setHostName("217.172.21.199");
        db.setDatabaseName("smdb");
        db.setUserName(dialogConnectToDataBase.getUserName());
        db.setPassword(dialogConnectToDataBase.getPassword());
        db.setConnectOptions("requiressl=" + QString("%1").arg(dialogConnectToDataBase.getUseSSL()));

        if (!db.open()) {
            qDebug() << db.lastError().text();
            ui->statusBar->showMessage(db.lastError().text());
            ui->actionConnect->setChecked(false);
 //           ui->treeWidget->setEnabled(false);
            ui->tabWidget->clear();
        }
        else {
 //           ui->treeWidget->setEnabled(true);
            ui->statusBar->showMessage("Connected!", 2000);
        }
    }

    if (result == DialogConnectToDataBase::Rejected) {
        ui->actionConnect->setChecked(false);
        QSqlDatabase db = QSqlDatabase::database();
        db.close();
    }

    {
        QSqlDatabase db = QSqlDatabase::database();
        if (db.isOpen())
            ui->actionConnect->setChecked(true);
    }
}

void MainWindow::update()
{

}

void MainWindow::closeTab(int index)
{
    ui->tabWidget->removeTab(index);
}

void MainWindow::itemTabNewOrOpenCurrent(QTreeWidgetItem *item, int col)
{
    if (!item->text(1).isEmpty()) {
        int flag = -1;
        FrameStudet *fs = 0;

        for (int i = 0; i < ui->tabWidget->count(); i++)
            if (ui->tabWidget->widget(i)->windowTitle() == item->text(col))
                flag = i;

        if (flag != -1)
            ui->tabWidget->setCurrentIndex(flag);
        else {
            fs = new FrameStudet(this);

            fs->setWindowTitle(item->text(col));
            ui->tabWidget->addTab(fs, item->text(col));
            ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 1);
        }
        fs = qobject_cast<FrameStudet *>(ui->tabWidget->currentWidget());
//        fs->clear();
//        fs->setTableName(item->text(1));
    }

}

void MainWindow::setCurrentItem(int index)
{
/*    if (index != -1) {
        QString s = ui->tabWidget->widget(index)->windowTitle();
        QList<QTreeWidgetItem*> items;
        items = ui->treeWidget->findItems(s, Qt::MatchRecursive, 0);
        if (!items.isEmpty())
            ui->treeWidget->setCurrentItem(items.at(0));
    }*/
}

