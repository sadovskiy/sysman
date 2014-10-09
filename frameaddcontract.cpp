#include "frameaddcontract.hpp"
#include "ui_frameaddcontract.h"

#include <QSqlError>
#include <QDebug>
#include <QMapIterator>

FrameAddContract::FrameAddContract(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::FrameAddContract)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);


}

FrameAddContract::~FrameAddContract()
{
    delete ui;
}

void FrameAddContract::loadData(QMap<int, QString> &cntrTypeList, QMap<int, QString> &curriculumList, QMap<int, QString> &yearList, const int numStr)
{
    QMapIterator<int, QString> ict(cntrTypeList);

    while (ict.hasNext()) {
        ict.next();
        ui->comboBoxAcademicProgram->addItem(ict.value());
    }

    QMapIterator<int, QString> idr(curriculumList);

    while (idr.hasNext()) {
        idr.next();
        ui->comboBoxContractType->addItem(idr.value());
    }

    QMapIterator<int, QString> iy(yearList);

    while (iy.hasNext()) {
        iy.next();
        ui->comboBoxDurationOfStudy->addItem(iy.value());
    }
    QSqlQuery query;
    query.exec(QString("SELECT * FROM contract AS ctr WHERE contract_id = %1").arg(numStr));

    if (query.lastError().isValid())
        qDebug() << query.lastError().text();

    query.first();
    ui->lineEditContractNumber->setText(query.value(1).toString());
    ui->dateEditContractDate->setDate(query.value(2).toDate());
    ui->lineEditPayment->setText(query.value(3).toString());

    int indexAP = query.value(5).toInt();
    QMapIterator<int, QString> idict(cntrTypeList);
    QString iCntrTypeList;
    while (idict.hasNext()) {
        idict.next();
        if (idict.key() == indexAP)
            iCntrTypeList = idict.value();
    }
    ui->comboBoxAcademicProgram->setCurrentText(iCntrTypeList);

    int indexCT = query.value(6).toInt();
    QMapIterator<int, QString> idl(curriculumList);
    QString icurriculumList;
    while (idl.hasNext()) {
        idl.next();
        if (idl.key() == indexCT)
            icurriculumList = idl.value();
    }
    ui->comboBoxContractType->setCurrentText(icurriculumList);

    int indexDoS = query.value(6).toInt();
    QMapIterator<int, QString> idys(yearList);
    QString iyearList;
    while (idys.hasNext()) {
        idys.next();
        if (idys.key() == indexDoS)
            iyearList = idys.value();
    }
    ui->comboBoxDurationOfStudy->setCurrentText(iyearList);
}

void FrameAddContract::on_pushButton_clicked()
{
/*    int row = ui->treeViewStudents->currentIndex().row();
    qDebug() << "pushButtonApplyChanges_clicked row: " << row;
    int index = ui->treeViewStudents->model()->index(row, 1).data(Qt::DisplayRole).toInt();
    qDebug() << "pushButtonApplyChanges_clicked index: " << index;
    qInsertStudent->prepare(QString("UPDATE contract SET contract_number = :contract_number, "
                                    "contract_date = :contract_date, payment = :payment, "
                                    "curriculum = :curriculum, contract_type = :contract_type, "
                                    "duration_of_studies = :duration_of_studies, "
                                    "WHERE contract_id = %1").arg(index));

    qInsertStudent->bindValue(":surname", ui->lineEditSurname->text());
    qInsertStudent->bindValue(":name", ui->lineEditName->text());
    qInsertStudent->bindValue(":patronym", ui->lineEditPatronym->text());
    qInsertStudent->bindValue(":sex", sexList.value(ui->comboBoxSex->currentText()));
    qInsertStudent->bindValue(":date_of_birth", ui->dateEditDateOfBirth->date());
    qInsertStudent->bindValue(":place_of_birth", ui->comboBoxPlaceOfBirth->currentText());
    countryList.find(ui->comboBoxCitizenship->currentText());
    QMap<QString, int>::const_iterator idx  = countryList.find(ui->comboBoxCitizenship->currentText());
    if (idx != countryList.end() && idx.key() == ui->comboBoxCitizenship->currentText())
        qInsertStudent->bindValue(":citizenship", idx.value());
    else
        qInsertStudent->bindValue(":citizenship", 0);
    qInsertStudent->bindValue(":passport_series", ui->spinBoxPassportSeries->text().toInt());
    qInsertStudent->bindValue(":passport_number", ui->spinBoxPassportNumber->text().toInt());
    qInsertStudent->bindValue(":passport_authority", ui->lineEditPassportAuthority->text());
    qInsertStudent->bindValue(":passport_date_of_issue", ui->dateEditPassportDateOfIssue->date());
    qInsertStudent->bindValue(":passport_subdivision_code", ui->spinBoxPassportSubdivisionCode->text().toInt());
    qInsertStudent->bindValue(":registration_adm_unit", ui->comboBoxRegistrationAdministrativeUnit->currentText());
    qInsertStudent->bindValue(":registration_adress", ui->lineEditRegistrationAdress->text());
    qInsertStudent->bindValue(":registration_date", ui->dateEditRegistrationDate->date());
    qInsertStudent->bindValue(":postcode", ui->spinBoxPostcode->text().toInt());

    qInsertStudent->exec();

    if (qInsertStudent->lastError().isValid())
        qDebug() << "UPDATE student: "  << qInsertStudent->lastError().text();*/
}
