#ifndef DIALOGCONNECTTODATABASE_HPP
#define DIALOGCONNECTTODATABASE_HPP

#include <QDialog>
#include <QString>

namespace Ui {
class DialogConnectToDataBase;
}

class DialogConnectToDataBase : public QDialog
{
    Q_OBJECT

public:
    explicit DialogConnectToDataBase(QWidget *parent = 0);
    ~DialogConnectToDataBase();

    QString getUserName();
    QString getPassword();
    bool getUseSSL();

private:
    Ui::DialogConnectToDataBase *ui;
    QString userName;
    QString password;

private slots:
    void dataAccepted();
    void dataRejected();
};

#endif // DIALOGCONNECTTODATABASE_HPP
