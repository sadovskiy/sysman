#include "framestudet.hpp"
#include "frameaddcontract.hpp"
#include "frameaddorderadmission.hpp"
#include "ui_framestudet.h"

#include <QSqlError>
#include <QDebug>
#include <QTableWidgetItem>
#include <QMapIterator>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QDate>
#include <QRegExp>
#include <QRegExpValidator>
#include <QTreeWidgetItem>


FrameStudet::FrameStudet(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::FrameStudet)
{
    ui->setupUi(this);

    ui->splitterH->setStretchFactor(1, 1);
    ui->splitterV->setStretchFactor(1, 1);

/*
    QString phoneRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";

    QRegExp phoneRegex("^" + phoneRange
                       + "\\." + phoneRange
                       + "\\." + phoneRange
                       + "\\." + phoneRange + "$");

    QRegExpValidator *phoneValidator = new QRegExpValidator(phoneRegex, this);

    ui->lineEditPhone->setValidator(phoneValidator);
*/
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


    qmodgroup = new QSqlQueryModel(this);
    qmodyear = new QSqlQueryModel(this);
    qmodstud = new QSqlQueryModel(this);

    qmoddepartment = new QSqlQueryModel(this);
    qmodcontrtype = new QSqlQuery;
    qmodcuriculum = new QSqlQuery;
    qInsertStudent = new QSqlQuery;
    qDeleteStudent = new QSqlQuery;
    qcontract = new QSqlQuery;

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

    qmodcontrtype->exec("SELECT * FROM contract_type");

    if (qmodcontrtype->lastError().isValid())
        qDebug() << qmodcontrtype->lastError().text();

    while (qmodcontrtype->next()) {
        int CTid = qmodcontrtype->value(0).toInt();
        QString CTstr = qmodcontrtype->value(1).toString();
        cntrTypeList.insert(CTid, CTstr);
    }

    qmodcuriculum->exec("SELECT * FROM list_training_programs_students");

    if (qmodcuriculum->lastError().isValid())
        qDebug() << qmodcuriculum->lastError().text();

    while (qmodcuriculum->next()) {
        int CTid = qmodcuriculum->value(0).toInt();
        curriculumList.insert(CTid,
                              qmodcuriculum->value(1).toString() + " " +
                              qmodcuriculum->value(2).toString() + " " +
                              qmodcuriculum->value(3).toString() + " " +
                              qmodcuriculum->value(4).toString() + " " +
                              qmodcuriculum->value(5).toString() + "." +
                              qmodcuriculum->value(6).toString() + "." +
                              qmodcuriculum->value(7).toString() + " " +
                              qmodcuriculum->value(8).toString() + " " +
                              qmodcuriculum->value(9).toString() + " " +
                              qmodcuriculum->value(10).toString() + " " +
                              qmodcuriculum->value(11).toString() + "." +
                              qmodcuriculum->value(12).toString() + "." +
                              qmodcuriculum->value(13).toString() + " " +
                              qmodcuriculum->value(14).toString() + " " +
                              qmodcuriculum->value(15).toString());
    }

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
    const int num = ui->treeViewStudents->model()->index(selection.row(), 1).data(Qt::DisplayRole).toInt();
    qDebug() << num;

    QSqlQuery query;

    query.exec(QString("SELECT * FROM student WHERE student_id = %1").arg(num));

    if (query.lastError().isValid())
        qDebug() << query.lastError().text();

    query.first();

    ui->lineEditSurname->setText(query.value(1).toString());
    ui->lineEditName->setText(query.value(2).toString());
    ui->lineEditPatronym->setText(query.value(3).toString());
    int n = query.value(4).toInt();
    ui->comboBoxSex->setCurrentIndex(ui->comboBoxSex->findText(sexList.key(n)));
    ui->dateEditDateOfBirth->setDate(query.value(5).toDate());
    ui->comboBoxPlaceOfBirth->setCurrentText(query.value(6).toString());
    int indexCountry = query.value(7).toInt();
    QMapIterator<QString, int> idx(countryList);
    QString country;
    while (idx.hasNext()) {
        idx.next();
        if (idx.value() == indexCountry)
            country = idx.key();
    }
    ui->comboBoxCitizenship->setCurrentText(country);
    ui->spinBoxPassportSeries->setValue(query.value(8).toInt());
    ui->spinBoxPassportNumber->setValue(query.value(9).toInt());
    ui->lineEditPassportAuthority->setText(query.value(10).toString());
    ui->dateEditPassportDateOfIssue->setDate(query.value(11).toDate());
    ui->spinBoxPassportSubdivisionCode->setValue(query.value(12).toInt());
    ui->comboBoxRegistrationAdministrativeUnit->setCurrentText(query.value(13).toString());
    ui->lineEditRegistrationAdress->setText(query.value(14).toString());
    ui->dateEditRegistrationDate->setDate(query.value(15).toDate());
    ui->spinBoxPostcode->setValue(query.value(16).toInt());
    ui->lineEditEmail->setText(query.value(17).toString());
    ui->lineEditIndividualTaxpayerIdentificationNumber->setText(query.value(18).toString());
    QSqlQuery queryPhone(QString("SELECT telephon_code, calling_code, phone_number FROM phone "
                                 "JOIN (SELECT telephon_code FROM country WHERE num_code_country = "
                                 "(SELECT country_calling_code FROM phone WHERE student = %1)) AS tcc ON student = %1").arg(num));
    if (queryPhone.next()) {
        ui->comboBoxCountryCallingCode->setCurrentText("+" + queryPhone.value(0).toString());
        ui->lineEditPhoneCallingCode->setText(queryPhone.value(1).toString());
        ui->lineEditPhoneNumber->setText(queryPhone.value(2).toString());
    }
    ui->treeWidgetContract->clear();

    ui->treeWidgetContract->setColumnCount(2);
//    ui->treeWidgetContract->hideColumn(1);
    ui->treeWidgetContract->header()->setStretchLastSection(true);
    ui->treeWidgetContract->header()->setSortIndicator(0, Qt::AscendingOrder);
    ui->treeWidgetContract->header()->setSortIndicatorShown(true);
    ui->treeWidgetContract->header()->model()->setHeaderData(0, Qt::Horizontal, tr("Documents"));
    ui->treeWidgetContract->header()->model()->setHeaderData(1, Qt::Horizontal, tr("Id documents"));
    QTreeWidgetItem *parent = ui->treeWidgetContract->invisibleRootItem();
    parent->setFlags(Qt::ItemIsEnabled);
    //        connect(ui->treeWidgetContract->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
    //                this, SLOT(addWindow(QModelIndex,QModelIndex)));


    QSqlQuery queryadmission;

    query.exec(QString("SELECT lcontract_id FROM list_contract_student WHERE lstudent_id = %1").arg(num));
    queryadmission.exec(QString("SELECT order_admission_id FROM list_student_in_admission WHERE student_id = %1").arg(num));

    if (query.lastError().isValid())
        qDebug() << query.lastError().text();

    query.first();

    qDebug() << "lcontract_id" << query.value(0).toString();

    if (query.isValid()) {
        QSqlQuery query2;
        query2.exec(QString("SELECT ctr.contract_date || \' - \' || ctr.contract_number, ctr.contract_id FROM contract AS ctr "
                            "JOIN (SELECT lcst.lcontract_id FROM list_contract_student AS lcst WHERE lcst.lstudent_id = %1) AS stud "
                            "ON stud.lcontract_id = ctr.contract_id").arg(num));

        if (query2.lastError().isValid())
            qDebug() << query2.lastError().text();


        QTreeWidgetItem *item = new QTreeWidgetItem(parent);

        item->setText(0, "Contract");

        item->setFlags(Qt::ItemIsEnabled);

        while (query2.next()) {
            QTreeWidgetItem *item2 = new QTreeWidgetItem(item);
            item2->setText(0, query2.value(0).toString());
            item2->setText(1, query2.value(1).toString());
        }
    }

    if (queryadmission.lastError().isValid())
        qDebug() << queryadmission.lastError().text();

    queryadmission.first();

    if (queryadmission.isValid()) {
        QSqlQuery query2;
        query2.exec(QString("SELECT adm.date_of_order_admission || \' - \' || adm.order_admission_num, adm.order_admission_id FROM orders_admission AS adm "
                            "JOIN (SELECT lsia.order_admission_id FROM list_student_in_admission AS lsia WHERE lsia.student_id = %1) AS ordradm "
                            "ON ordradm.order_admission_id = adm.order_admission_id").arg(num));

        if (query2.lastError().isValid())
            qDebug() << query2.lastError().text();

        QTreeWidgetItem *item = new QTreeWidgetItem(parent);

        item->setText(0, "Order Admission");

        item->setFlags(Qt::ItemIsEnabled);

        while (query2.next()) {
            QTreeWidgetItem *item2 = new QTreeWidgetItem(item);
            if (query2.value(0).toString().isEmpty())
                item2->setText(0, "No num and date");
            else
                item2->setText(0, query2.value(0).toString());
            item2->setText(1, query2.value(1).toString());
        }

    }

    ui->listWidgetPhone->clear();

    QSqlQuery countryCode(QString("SELECT country_calling_code FROM phone WHERE student = %1").arg(num));
    QSqlQuery callingCode(QString("SELECT calling_code FROM phone WHERE student = %1").arg(num));
    QSqlQuery phoneNumber(QString("SELECT phone_number FROM phone WHERE student = %1").arg(num));
    QSqlQuery phoneComment(QString("SELECT \'(' || comment || \')' AS comment FROM phone WHERE student = %1").arg(num));



    while (countryCode.next() && callingCode.next() && phoneNumber.next() && phoneComment.next()) {
        QString number = phoneNumber.value(0).toString();
        number.insert(3, QString("-"));
        number.insert(6, QString("-"));

        qDebug() << "+" << countryCode.value(0).toString() << "("
                 << callingCode.value(0).toString() << ")"
                 << number;
        if (!phoneNumber.value(0).isNull())
            ui->listWidgetPhone->addItem(QString("+%1(%2)%3 %4").
                                         arg(countryCode.value(0).toString()).
                                         arg(callingCode.value(0).toString()).
                                         arg(number).
                                         arg(phoneComment.value(0).toString()));
    }

    ui->treeWidgetContract->expandAll();

}
/*
void FrameStudet::addWindow(QModelIndex selection, QModelIndex deselection)
{

}
*/
void FrameStudet::on_comboBoxDepartment_currentIndexChanged(int index)
{
    qDebug() << "on_comboBoxDepartment_currentIndexChanged: " << index;


    if (index)
        qmodstud->setQuery(QString("SELECT stt.surname || \' \' || stt.name || \' \' || stt.patronym AS Students, stt.student_id FROM student AS stt "
                                   "JOIN (SELECT lsiad.student_id FROM list_student_in_admission lsiad JOIN (SELECT oa.order_admission_id "
                                   "FROM orders_admission oa WHERE oa.department = %1) oai ON oai.order_admission_id = lsiad.order_admission_id) "
                                   "lss ON lss.student_id = stt.student_id ORDER BY stt.surname").arg(index));
    else
        qmodstud->setQuery("SELECT stt.surname || \' \' || stt.name || \' \' || stt.patronym AS Students, student_id FROM student AS stt ORDER BY stt.surname");


    if (qmodstud->lastError().isValid())
        qDebug() << qmodstud->lastError().text();

    QSqlQuery queryCountStudents("SELECT COUNT(*) FROM student");

    if (queryCountStudents.next())
        ui->labelTotalStudents->setText(tr("Total Students: %1").arg(queryCountStudents.value(0).toInt()));
}

void FrameStudet::on_comboBoxYear_currentIndexChanged(int index)
{
    qDebug() << index;

    if (index)
        qmodstud->setQuery(QString("SELECT stt.surname || \' \' || stt.name || \' \' || stt.patronym AS Students, stt.student_id FROM student AS stt "
                                   "JOIN (SELECT lsiad.student_id FROM list_student_in_admission lsiad JOIN "
                                   "(SELECT oa.order_admission_id, date_part('year', now()) - date_part('year', oa.date_of_order_admission) + "
                                   "oa.course_enrollment AS year FROM orders_admission AS oa WHERE (date_part('year', now()) - date_part('year', oa.date_of_order_admission) + oa.course_enrollment) = %1) "
                                   "oai ON oai.order_admission_id = lsiad.order_admission_id) "
                                   "lss ON lss.student_id = stt.student_id").arg(index));
    else
        qmodstud->setQuery("SELECT stt.surname || \' \' || stt.name || \' \' || stt.patronym AS Students, student_id FROM student AS stt ORDER BY stt.surname");


    if (qmodstud->lastError().isValid())
        qDebug() << qmodstud->lastError().text();

    QSqlQuery queryCountStudents("SELECT COUNT(*) FROM student");

    if (queryCountStudents.next())
        ui->labelTotalStudents->setText(tr("Total Students: %1").arg(queryCountStudents.value(0).toInt()));
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
        qmodstud->setQuery("SELECT stt.surname || \' \' || stt.name || \' \' || stt.patronym AS Students, student_id FROM student AS stt ORDER BY stt.surname");


    if (qmodstud->lastError().isValid())
        qDebug() << qmodstud->lastError().text();

    QSqlQuery queryCountStudents("SELECT COUNT(*) FROM student");

    if (queryCountStudents.next())
        ui->labelTotalStudents->setText(tr("Total Students: %1").arg(queryCountStudents.value(0).toInt()));
}

void FrameStudet::on_pushButtonAddStudent_clicked()
{
    int row = ui->treeViewStudents->currentIndex().row();

    qInsertStudent->prepare(QString("INSERT INTO student (surname, name, patronym, sex, date_of_birth, "
                            "place_of_birth, citizenship, passport_series, passport_number, "
                            "passport_authority, passport_date_of_issue, passport_subdivision_code, "
                            "registration_adm_unit, registration_adress, registration_date, "
                            "postcode, email, individual_taxpayer_identification_number) "
                            "VALUES (:surname, :name, :patronym, :sex, :date_of_birth, "
                            ":place_of_birth, :citizenship, :passport_series, :passport_number, "
                            ":passport_authority, :passport_date_of_issue, :passport_subdivision_code, "
                            ":registration_adm_unit, :registration_adress, :registration_date, "
                            ":postcode, :email, :individual_taxpayer_identification_number)"));

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

    qInsertStudent->bindValue(":email", ui->lineEditEmail->text());
    qInsertStudent->bindValue(":individual_taxpayer_identification_number", ui->lineEditIndividualTaxpayerIdentificationNumber->text());
    qInsertStudent->exec();

    if (qInsertStudent->lastError().isValid())
        qDebug() << qInsertStudent->lastError().text();

    QSqlQuery query;
    query.exec("SELECT max(student_id) FROM student");
    // currval('"student_table_ID_student_seq"'::regclass)
    if (!query.isValid()) {
                qDebug() << query.lastError().text();
    }

    query.value(0).toInt();

//TODO: Доделать выделение только, что добавленной строки

    // Сгененрируем сигнал, для обновления списка студентов с учётом фильтра
    ui->comboBoxDepartment->currentIndexChanged(ui->comboBoxDepartment->currentIndex());


    ui->treeViewStudents->setCurrentIndex(ui->treeViewStudents->model()->index(row, 1));

    QSqlQuery queryCountStudents("SELECT COUNT(*) FROM student");

    if (queryCountStudents.next())
        ui->labelTotalStudents->setText(tr("Total Students: %1").arg(queryCountStudents.value(0).toInt()));
}

void FrameStudet::on_pushButtonApplyChanges_clicked()
{
    int row = ui->treeViewStudents->currentIndex().row();
    qDebug() << "pushButtonApplyChanges_clicked row: " << row;
    int index = ui->treeViewStudents->model()->index(row, 1).data(Qt::DisplayRole).toInt();
    qDebug() << "pushButtonApplyChanges_clicked index: " << index;
    qInsertStudent->prepare(QString("UPDATE student SET surname = :surname, "
                                    "name = :name, patronym = :patronym, "
                                    "sex = :sex, date_of_birth = :date_of_birth, "
                                    "place_of_birth = :place_of_birth, "
                                    "citizenship = :citizenship, "
                                    "passport_series = :passport_series, "
                                    "passport_number = :passport_number, "
                                    "passport_authority = :passport_authority, "
                                    "passport_date_of_issue = :passport_date_of_issue, "
                                    "passport_subdivision_code = :passport_subdivision_code, "
                                    "registration_adm_unit = :registration_adm_unit, "
                                    "registration_adress = :registration_adress, "
                                    "registration_date = :registration_date, "
                                    "postcode = :postcode, "
                                    "email = :email, "
                                    "individual_taxpayer_identification_number = :individual_taxpayer_identification_number "
                                    "WHERE student_id = %1").arg(index));

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
    QString str = ui->lineEditPhoneNumber->text();
    str.remove(3, 1);
    str.remove(5, 1);
    qInsertStudent->bindValue(":email", ui->lineEditEmail->text());
    qInsertStudent->bindValue(":individual_taxpayer_identification_number", ui->lineEditIndividualTaxpayerIdentificationNumber->text());
    qInsertStudent->exec();

    if (qInsertStudent->lastError().isValid())
        qDebug() << "UPDATE student: "  << qInsertStudent->lastError().text();

    // Сгененрируем сигнал, для обновления списка студентов с учётом фильтра
    ui->comboBoxDepartment->currentIndexChanged(ui->comboBoxDepartment->currentIndex());

    ui->treeViewStudents->setCurrentIndex(ui->treeViewStudents->model()->index(row, 1));
}

void FrameStudet::updateStudent()
{
    int row = ui->treeViewStudents->currentIndex().row();
    int index = ui->treeViewStudents->model()->index(row, 1).data(Qt::DisplayRole).toInt();
    qDebug() << index;
    qInsertStudent->prepare(QString("UPDATE payment SET semester = :semester, "
                                    "discount = :discount, "
                                    "actual_amount_of_payment = :actual_amount_of_payment, "
                                    "date_of_pay = :date_of_pay, "
                                    "penalties = :penalties, "
                                    "resolution_pay_phase = :resolution_pay_phase, "
                                    "WHERE payment_id = %1").arg(index));

    qInsertStudent->bindValue(":semester", ui->lineEditSurname->text());
    qInsertStudent->bindValue(":discount", ui->lineEditName->text());
    qInsertStudent->bindValue(":actual_amount_of_payment", ui->lineEditPatronym->text());
    qInsertStudent->bindValue(":date_of_pay", sexList.value(ui->comboBoxSex->currentText()));
    qInsertStudent->bindValue(":penalties", ui->dateEditDateOfBirth->date());
    qInsertStudent->bindValue(":resolution_pay_phase", ui->comboBoxPlaceOfBirth->currentText());
    qInsertStudent->exec();

    if (qInsertStudent->lastError().isValid())
        qDebug() << "UPDATE payment: " << qInsertStudent->lastError().text();

    qInsertStudent->prepare(QString("UPDATE orders_admission SET order_admission_num = :order_admission_num, "
                                    "date_of_order_admission = :date_of_order_admission, "
                                    "course_enrollment = :course_enrollment, "
                                    "group = :group, "
                                    "department = :department, "
                                    "resolution_pay_phase = :resolution_pay_phase, "
                                    "WHERE order_admission_id = %1").arg(index));

    qInsertStudent->bindValue(":orders_admission", ui->lineEditSurname->text());
    qInsertStudent->bindValue(":date_of_order_admission", ui->lineEditName->text());
    qInsertStudent->bindValue(":course_enrollment", ui->lineEditPatronym->text());
    qInsertStudent->bindValue(":group", sexList.value(ui->comboBoxSex->currentText()));
    qInsertStudent->bindValue(":department", ui->dateEditDateOfBirth->date());
    qInsertStudent->bindValue(":resolution_pay_phase", ui->comboBoxPlaceOfBirth->currentText());
    qInsertStudent->exec();

    if (qInsertStudent->lastError().isValid())
        qDebug() << "UPDATE orders_admission: " << qInsertStudent->lastError().text();
}

void FrameStudet::on_lineEditFind_textEdited(const QString &arg1)
{
    QString str = arg1;
    if (!arg1.isEmpty()) {
        str[0] = arg1.at(0).toTitleCase();
    }
    qmodstud->setQuery(QString("SELECT stt.surname || \' \' || stt.name || \' \' || stt.patronym AS Students, stt.student_id FROM student AS stt "
                               "WHERE surname LIKE \'%1\%\' ").arg(str));
    if (qmodstud->lastError().isValid())
        qDebug() << qmodstud->lastError().text();
}

void FrameStudet::on_pushButtonDelStudent_clicked()
{
    int row = ui->treeViewStudents->currentIndex().row();
    int index = ui->treeViewStudents->model()->index(row, 1).data(Qt::DisplayRole).toInt();
    qDebug() << index;
    qDeleteStudent->prepare(QString("DELETE FROM student WHERE student_id = %1").arg(index));
    if (qDeleteStudent->lastError().isValid())
        qDebug() << "UPDATE orders_admission: " << qInsertStudent->lastError().text();
    qDeleteStudent->exec();
    qmodstud->setQuery("SELECT stt.surname || \' \' || stt.name || \' \' || stt.patronym AS Students, student_id FROM student AS stt ORDER BY stt.surname");
    QSqlQuery queryCountStudents("SELECT COUNT(*) FROM student");

    if (queryCountStudents.next())
        ui->labelTotalStudents->setText(tr("Total Students: %1").arg(queryCountStudents.value(0).toInt()));
}



void FrameStudet::on_treeWidgetContract_clicked(const QModelIndex &index)
{
    QMdiSubWindow *subWindow = ui->mdiArea->activeSubWindow();
    int num = 0;
    if (ui->treeWidgetContract->currentItem()->parent()) {
        if (ui->treeWidgetContract->currentItem()->parent()->text(0) == "Contract") {
            FrameAddContract *fcontract = 0;
            if (subWindow) {
                fcontract = qobject_cast<FrameAddContract *>(subWindow->widget()->window());
                ui->mdiArea->setActiveSubWindow(subWindow);
            }
            if (!fcontract) {
                fcontract = new FrameAddContract(this);
                QMdiSubWindow *subWin = ui->mdiArea->addSubWindow(fcontract);
                subWin->setAttribute(Qt::WA_DeleteOnClose);
                subWin->setWindowFlags(Qt::SubWindow | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint | Qt::WindowMinimizeButtonHint);
                subWin->setWindowTitle(ui->treeWidgetContract->currentItem()->data(0, Qt::DisplayRole).toString());
                num = ui->treeWidgetContract->currentItem()->data(1, Qt::DisplayRole).toInt();
                qDebug() << num;
                subWin->show();
                fcontract->loadData(cntrTypeList, curriculumList, yearList, num);
            }
        }
        if (ui->treeWidgetContract->currentItem()->parent()->text(0) == "Order Admission") {
            FrameAddOrderAdmission *fadm = 0;
            if (subWindow) {
                fadm = qobject_cast<FrameAddOrderAdmission *>(subWindow->widget());
                ui->mdiArea->setActiveSubWindow(subWindow);
            }
            if (!fadm) {
                fadm = new FrameAddOrderAdmission(this);
                QMdiSubWindow *subWin = ui->mdiArea->addSubWindow(fadm);
                subWin->setAttribute(Qt::WA_DeleteOnClose);
                subWin->setWindowFlags(Qt::SubWindow | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint | Qt::WindowMinimizeButtonHint);
                subWin->setWindowTitle(ui->treeWidgetContract->currentItem()->data(0, Qt::DisplayRole).toString());
                num = ui->treeWidgetContract->currentItem()->data(1, Qt::DisplayRole).toInt();
                qDebug() << num;
                subWin->show();
                fadm->loadData(departmentList, num);
            }
        }
    }
}

void FrameStudet::on_pushButtonAddPhonNum_clicked()
{
    ui->listWidgetPhone->addItem(QString("+" + ui->comboBoxCountryCallingCode->currentText() + "(" +
                                         ui->lineEditPhoneCallingCode->text() + ")" +
                                         ui->lineEditPhoneNumber->text() +
                                         ui->lineEditCommentPhon->text()));

    QSqlQuery queryAddPhone;
    queryAddPhone.prepare(QString("INSERT INTO phone(student, country_calling_code, calling_code, phone_number, comment)"
                                   "VALUES (:student, :country_calling_code, :calling_code, :phone_number, :comment)"));
    queryAddPhone.bindValue(":student", ui->treeViewStudents->model()->index(ui->treeViewStudents->currentIndex().row(), 1).data(Qt::DisplayRole).toInt());
    queryAddPhone.bindValue(":country_calling_code", ui->comboBoxCountryCallingCode->currentText());
    queryAddPhone.bindValue(":calling_code", ui->lineEditPhoneCallingCode->text());
    queryAddPhone.bindValue(":phone_number", ui->lineEditPhoneNumber->text().remove(3, 1).remove(5, 1));
    queryAddPhone.bindValue(":comment", ui->lineEditCommentPhon->text());

    queryAddPhone.exec();
    if (queryAddPhone.lastError().isValid())
        qDebug() << "INSERT phone: " << queryAddPhone.lastError().text();
    ui->comboBoxCountryCallingCode->clear();
    ui->lineEditPhoneCallingCode->clear();
    ui->lineEditPhoneNumber->clear();
    ui->lineEditCommentPhon->clear();
}

void FrameStudet::on_listWidgetPhone_currentRowChanged(int currentRow)
{
    qDebug() << currentRow;
}

void FrameStudet::on_pushButtonDelPhone_clicked()
{
    int index = ui->treeViewStudents->model()->index(ui->treeViewStudents->currentIndex().row(), 1).data(Qt::DisplayRole).toInt();
    QSqlQuery queryDel;
    queryDel.prepare(QString("DELETE FROM phone WHERE student = %1").arg(index));
    queryDel.exec();
    if (queryDel.lastError().isValid())
        qDebug() << "DELETE phone: " << queryDel.lastError().text();

    ui->listWidgetPhone->takeItem(ui->listWidgetPhone->currentIndex().row());
}

void FrameStudet::on_pushButtonAddContract_clicked()
{
    QMdiSubWindow *subWindow = ui->mdiArea->activeSubWindow();
    FrameAddContract *fcontract = 0;
    if (subWindow) {
        fcontract = qobject_cast<FrameAddContract *>(subWindow->widget()->window());
        ui->mdiArea->setActiveSubWindow(subWindow);
    }
    if (!fcontract) {
        fcontract = new FrameAddContract(this);
        QMdiSubWindow *subWin = ui->mdiArea->addSubWindow(fcontract);
        subWin->setAttribute(Qt::WA_DeleteOnClose);
        subWin->setWindowFlags(Qt::SubWindow | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint | Qt::WindowMinimizeButtonHint);
        subWin->setWindowTitle("New Contract");
        subWin->show();
        fcontract->loadData(cntrTypeList, curriculumList, yearList, 0);
    }
}

void FrameStudet::on_pushButtonAddOrder_clicked()
{
    QMdiSubWindow *subWindow = ui->mdiArea->activeSubWindow();
    FrameAddOrderAdmission *fadm = 0;
    if (subWindow) {
        fadm = qobject_cast<FrameAddOrderAdmission *>(subWindow->widget());
        ui->mdiArea->setActiveSubWindow(subWindow);
    }
    if (!fadm) {
        fadm = new FrameAddOrderAdmission(this);
        QMdiSubWindow *subWin = ui->mdiArea->addSubWindow(fadm);
        subWin->setAttribute(Qt::WA_DeleteOnClose);
        subWin->setWindowFlags(Qt::SubWindow | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint | Qt::WindowMinimizeButtonHint);
        subWin->setWindowTitle("New Order");
        subWin->show();
        fadm->loadData(departmentList, 0);
    }
}
