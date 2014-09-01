#include "dialogconnecttodatabase.hpp"
#include "ui_dialogconnecttodatabase.h"

#include <QDebug>

DialogConnectToDataBase::DialogConnectToDataBase(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogConnectToDataBase)
{
    ui->setupUi(this);
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(dataAccepted()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(dataRejected()));
}

DialogConnectToDataBase::~DialogConnectToDataBase()
{
    delete ui;
}

QString DialogConnectToDataBase::getUserName()
{
    return userName;
}

QString DialogConnectToDataBase::getPassword()
{
    return password;
}

void DialogConnectToDataBase::dataAccepted()
{
    userName = ui->lineEditUserName->text();
    password = ui->lineEditPassword->text();
}

void DialogConnectToDataBase::dataRejected()
{
    userName.clear();
    password.clear();
    qDebug() << "Rejected";
}

bool DialogConnectToDataBase::getUseSSL()
{
    return ui->checkBoxUseSSL->isChecked();
}
