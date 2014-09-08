#include "framestudet.hpp"
#include "ui_framestudet.h"

#include <QSqlError>
#include <QDebug>
#include <QTableWidgetItem>
#include <QMapIterator>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QDate>

FrameStudet::FrameStudet(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::FrameStudet)
{
    ui->setupUi(this);

    QSqlQuery qCountRows;

    QSqlQuery qAdmUnitm("SELECT * FROM administrative_unit");

    if (!qAdmUnitm.isActive())
        qDebug() << qAdmUnitm.lastError().text();

    int admunit = 0;

    while(qAdmUnitm.next()){
        admUnitList.insert(qAdmUnitm.value(1).toString(), admunit);
        admunit++;
    }

    QMapIterator<QString, int> iadmunit(admUnitList);

    while (iadmunit.hasNext()) {
        iadmunit.next();
        ui->comboBoxPlaceOfBirth->addItem(iadmunit.key());
    }

    iadmunit.toFront();

    while (iadmunit.hasNext()) {
        iadmunit.next();
        ui->comboBoxRegistrationAdministrativeUnit->addItem(iadmunit.key());
    }

    iadmunit.toFront();

    sexList.insert(tr("Not known"), 0);
    sexList.insert(tr("Male"), 1);
    sexList.insert(tr("Female"), 2);
    sexList.insert(tr("Not applicable"), 9);

    countryList.insert(tr("Russia"), 643);
    countryList.insert(tr("Other"), 0);


    QMapIterator<QString, int> isex(sexList);

    while (isex.hasNext()) {
        isex.next();
        ui->comboBoxSex->addItem(isex.key());
    }

    isex.toFront();

    QMapIterator<QString, int> icountry(countryList);

    while (icountry.hasNext()) {
        icountry.next();
        ui->comboBoxCitizenship->addItem(icountry.key());
    }

    icountry.toFront();

    if (QDate::currentDate().month() > 8)
        ui->comboBoxTimeOfYear->setCurrentIndex(1);
    ui->comboBoxYear_2->addItem(QString("%1 - %2").arg(QDate::currentDate().year()).arg(QDate::currentDate().year() + 1));

    qmodgroup = new QSqlQueryModel(this);
    qmodyear = new QSqlQueryModel(this);
    qmodstud = new QSqlQueryModel(this);
    qmodpay = new QSqlQueryModel(this);
    qmoddepartment = new QSqlQueryModel(this);
    qInsertStudent = new QSqlQuery;

    qmoddepartment->setQuery("SELECT department_id, department_short, department_full FROM department");

    if (qmoddepartment->lastError().isValid())
        qDebug() << qmoddepartment->lastError().text();

    departmentList.insert(0, new Department(0, tr("All"), tr("All")));

    qCountRows.exec("SELECT COUNT(*) FROM department");

    qCountRows.next();

    for (int i = 0; i < qCountRows.value(0).toInt(); ++i) {
        int depid = qmoddepartment->record(i).value("department_id").toInt();
        QString depsh = qmoddepartment->record(i).value("department_short").toString();
        QString depfl = qmoddepartment->record(i).value("department_full").toString();
        departmentList.insert(i + 1, new Department(depid, depsh, depfl));
    }

    QMapIterator<int, Department *> idepart(departmentList);

    while (idepart.hasNext()) {
        idepart.next();
        ui->comboBoxDepartment->addItem(idepart.value()->getDepShort());
    }


    qmodyear->setQuery("SELECT duration_of_studies FROM duration_of_studies");

    if (qmodyear->lastError().isValid())
        qDebug() << qmodyear->lastError().text();


    yearList.insert(0, tr("All"));

    qCountRows.exec("SELECT COUNT(*) FROM duration_of_studies");

    qCountRows.next();

    for (int i = 0; i < qCountRows.value(0).toInt(); ++i) {
        QString duration = qmodyear->record(i).value("duration_of_studies").toString();
        yearList.insert(i + 1, duration);
    }

    QMapIterator<int, QString> iy(yearList);

    while (iy.hasNext()) {
        iy.next();
        ui->comboBoxYear->addItem(iy.value());
    }

    qmodpay->setQuery("SELECT discount, actual_amount_of_payment, date_of_pay, actual_amount_of_payment * 0.25 AS discount_in_prc FROM payment AS pa WHERE pa.payment_id = 4");

    if (qmodpay->lastError().isValid())
        qDebug() << qmodpay->lastError().text();

    ui->tableView->setModel(qmodpay);

    ui->treeViewStudents->setModel(qmodstud);

    ui->treeViewStudents->hideColumn(1);

    connect(ui->treeViewStudents->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            this, SLOT(handleSelectionChanged(QModelIndex)));

}

FrameStudet::~FrameStudet()
{
    delete ui;
}

void FrameStudet::handleSelectionChanged(QModelIndex selection)
{
    long long n = ui->treeViewStudents->model()->index(selection.row(), 1).data(Qt::DisplayRole).toLongLong();
    qDebug() << n;

    if (ui->tabWidget->currentIndex() == 0) {
        QSqlQuery query;
        query.exec(QString("SELECT * FROM student WHERE student_id = %1").arg(n));


        if (query.lastError().isValid())
            qDebug() << query.lastError().text();

        query.next();

        ui->lineEditSurname->setText(query.value(1).toString());
        ui->lineEditName->setText(query.value(2).toString());
        ui->lineEditPatronym->setText(query.value(3).toString());
        int n = query.value(4).toInt();
        ui->comboBoxSex->setCurrentIndex(ui->comboBoxSex->findText(sexList.key(n)));
        ui->dateEditDateOfBirth->setDate(query.value(5).toDate());
        ui->comboBoxPlaceOfBirth->setCurrentText(query.value(6).toString());
        ui->comboBoxCitizenship->setCurrentText(query.value(7).toString());
        ui->spinBoxPassportSeries->setValue(query.value(8).toInt());
        ui->spinBoxPassportNumber->setValue(query.value(9).toInt());
        ui->lineEditPassportAuthority->setText(query.value(10).toString());
        ui->dateEditPassportDateOfIssue->setDate(query.value(11).toDate());
        ui->spinBoxPassportSubdivisionCode->setValue(query.value(12).toInt());
        ui->comboBoxRegistrationAdministrativeUnit->setCurrentText(query.value(13).toString());
        ui->lineEditRegistrationAdress->setText(query.value(14).toString());
        ui->dateEditRegistrationDate->setDate(query.value(15).toDate());
        ui->spinBoxPostcode->setValue(query.value(16).toInt());
        ui->spinBoxPhone->setValue(query.value(17).toInt());
        ui->lineEditEmail->setText(query.value(18).toString());
        ui->spinBoxIndividualTaxpayerIdentificationNumber->setValue(query.value(19).toInt());

        query.exec(QString("SELECT * FROM contract AS ctr JOIN (SELECT contract_id FROM list_contract_student WHERE student_id = %1) AS stud ON stud.contract_id = ctr.contract_id").arg(n));


        if (query.lastError().isValid())
            qDebug() << query.lastError().text();

        query.next();





        query.exec(QString("SELECT * FROM orders_admission AS orda JOIN (SELECT order_admission_id FROM list_student_orders_admission WHERE student_id = %1) AS stud ON stud.order_admission_id = orda.order_admission_id").arg(n));


        if (query.lastError().isValid())
            qDebug() << query.lastError().text();

        query.next();

    }


/*
    QModelIndexList matches = ui->tableView->model()->match(ui->tableView->model()->index(0, 0),
                                                            Qt::UserRole, n);
    foreach(const QModelIndex &index, matches)
    {
        qDebug() << "test";
    }*/
}

void FrameStudet::on_comboBoxDepartment_currentIndexChanged(int index)
{
    qDebug() << index;


    if (index)
        qmodstud->setQuery(QString("SELECT stt.surname || \' \' || stt.name || \' \' || stt.patronym AS Students, stt.student_id FROM student AS stt "
                                   "JOIN (SELECT lsiad.student_id FROM list_student_in_admission lsiad JOIN (SELECT oa.order_admission_id "
                                   "FROM orders_admission oa WHERE oa.department = %1) oai ON oai.order_admission_id = lsiad.order_admission_id) "
                                   "lss ON lss.student_id = stt.student_id").arg(index));
    else
        qmodstud->setQuery("SELECT stt.surname || \' \' || stt.name || \' \' || stt.patronym AS Students, student_id FROM student AS stt");


    if (qmodstud->lastError().isValid())
        qDebug() << qmodstud->lastError().text();
}

void FrameStudet::on_comboBoxYear_currentIndexChanged(int index)
{
    qDebug() << index;

    if (index)
        qmodstud->setQuery(QString("SELECT stt.surname || \' \' || stt.name || \' \' || stt.patronym AS Students, stt.student_id FROM student AS stt "
                                   "JOIN (SELECT lsiad.student_id FROM list_student_in_admission lsiad JOIN "
                                   "(SELECT oa.order_admission_id, date_part('year', now()) - date_part('year', oa.date_of_order_admission) + "
                                   "oa.course_enrollment AS year FROM orders_admission AS oa ORDER BY year) "
                                   "oai ON oai.order_admission_id = lsiad.order_admission_id) "
                                   "lss ON lss.student_id = stt.student_id").arg(index));
    else
        qmodstud->setQuery("SELECT stt.surname || \' \' || stt.name || \' \' || stt.patronym AS Students, student_id FROM student AS stt");


    if (qmodstud->lastError().isValid())
        qDebug() << qmodstud->lastError().text();
}

void FrameStudet::on_comboBoxGroup_currentIndexChanged(int index)
{
    qDebug() << index;

    if (index)
        qmodstud->setQuery(QString("SELECT stt.surname || \' \' || stt.name || \' \' || stt.patronym AS Students, stt.student_id FROM student AS stt "
                                   "JOIN (SELECT lsiad.student_id FROM list_student_in_admission lsiad JOIN (SELECT oa.order_admission_id "
                                   "FROM orders_admission oa WHERE oa.group = %1) oai ON oai.order_admission_id = lsiad.order_admission_id) "
                                   "lss ON lss.student_id = stt.student_id").arg(index));
    else
        qmodstud->setQuery("SELECT stt.surname || \' \' || stt.name || \' \' || stt.patronym AS Students, student_id FROM student AS stt");


    if (qmodstud->lastError().isValid())
        qDebug() << qmodstud->lastError().text();
}

void FrameStudet::on_pushButton_clicked()
{

    qInsertStudent->prepare("INSERT INTO student (surname, name, patronym, sex, date_of_birth, "
                            "place_of_birth, citizenship, passport_series, passport_number, "
                            "passport_authority, passport_date_of_issue, passport_subdivision_code, "
                            "registration_adm_unit, registration_adress, registration_date, "
                            "postcode, phone, email, individual_taxpayer_identification_number) "
                            "VALUES (:surname, :name, :patronym, :sex, :date_of_birth, "
                            ":place_of_birth, :citizenship, :passport_series, :passport_number, "
                            ":passport_authority, :passport_date_of_issue, :passport_subdivision_code, "
                            ":registration_adm_unit, :registration_adress, :registration_date, "
                            ":postcode, :phone, :email, :individual_taxpayer_identification_number)");

    qInsertStudent->bindValue(":surname", ui->lineEditSurname->text());
    qInsertStudent->bindValue(":name", ui->lineEditName->text());
    qInsertStudent->bindValue(":patronym", ui->lineEditPatronym->text());
    qInsertStudent->bindValue(":sex", sexList.value(ui->comboBoxSex->currentText()));
    qInsertStudent->bindValue(":date_of_birth", ui->dateEditDateOfBirth->date());
    qInsertStudent->bindValue(":place_of_birth", ui->comboBoxPlaceOfBirth->currentText());
    qInsertStudent->bindValue(":citizenship", ui->comboBoxCitizenship->currentText());
    qInsertStudent->bindValue(":passport_series", ui->spinBoxPassportSeries->text().toInt());
    qInsertStudent->bindValue(":passport_number", ui->spinBoxPassportNumber->text().toInt());
    qInsertStudent->bindValue(":passport_authority", ui->lineEditPassportAuthority->text());
    qInsertStudent->bindValue(":passport_date_of_issue", ui->dateEditPassportDateOfIssue->date());
    qInsertStudent->bindValue(":passport_subdivision_code", ui->spinBoxPassportSubdivisionCode->text().toInt());
    qInsertStudent->bindValue(":registration_adm_unit", ui->comboBoxRegistrationAdministrativeUnit->currentText());
    qInsertStudent->bindValue(":registration_adress", ui->lineEditRegistrationAdress->text());
    qInsertStudent->bindValue(":registration_date", ui->dateEditRegistrationDate->date());
    qInsertStudent->bindValue(":postcode", ui->spinBoxPostcode->text().toInt());
    qInsertStudent->bindValue(":phone", ui->spinBoxPhone->text().toInt());
    qInsertStudent->bindValue(":email", ui->lineEditEmail->text());
    qInsertStudent->bindValue(":individual_taxpayer_identification_number", ui->spinBoxIndividualTaxpayerIdentificationNumber->text().toInt());
    qInsertStudent->exec();

    if (qInsertStudent->lastError().isValid())
        qDebug() << qInsertStudent->lastError().text();


    qmodstud->setQuery("SELECT stt.surname || \' \' || stt.name || \' \' || stt.patronym AS Students, student_id FROM student AS stt");
}
