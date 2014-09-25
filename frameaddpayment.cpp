#include "frameaddpayment.hpp"
#include "ui_frameaddpayment.h"

#include <QSqlError>
#include <QDebug>
#include <QDate>
#include <QSqlRecord>


FrameAddPayment::FrameAddPayment(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::FrameAddPayment)
{
    ui->setupUi(this);

    ui->splitterH->setStretchFactor(1, 1);

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
/*
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
*/

    qmodgroup = new QSqlQueryModel(this);
    qmodyear = new QSqlQueryModel(this);
    qmodstud = new QSqlQueryModel(this);

    qmoddepartment = new QSqlQueryModel(this);
    qmodpay = new QSqlQueryModel(this);
    qtablem = new QSqlTableModel(this);
    qmodcontrtype = new QSqlQuery;
    qmodcuriculum = new QSqlQuery;
    qInsertStudent = new QSqlQuery;
    qDeleteStudent = new QSqlQuery;
    qcontract = new QSqlQuery;
    qphone = new QSqlQueryModel;

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
/*
    for (int i = 0; i < qCountRows.value(0).toInt(); ++i) {
        QString duration = qmodyear->record(i).value("duration_of_studies").toString();
        yearList.insert(i + 1, duration);
    }

    QMapIterator<int, QString> iy(yearList);

    while (iy.hasNext()) {
        iy.next();
        ui->comboBoxYear->addItem(iy.value());
    }

*/

    ui->treeViewStudents->setModel(qmodstud);

    ui->treeViewStudents->hideColumn(1);

    connect(ui->treeViewStudents->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            this, SLOT(handleSelectionChanged(QModelIndex)));
    if (QDate::currentDate().month() > 8)
        ui->comboBoxTimeOfYear->setCurrentIndex(1);
    ui->comboBoxYear_2->addItem(QString("%1 - %2").arg(QDate::currentDate().year()).arg(QDate::currentDate().year() + 1));
/*
    qmodpay->setQuery("SELECT discount, actual_amount_of_payment, date_of_pay, actual_amount_of_payment - (0.01 * discount * actual_amount_of_payment) AS discount_in_prc FROM payment AS pa WHERE pa.payment_id = 16");

    if (qmodpay->lastError().isValid())
        qDebug() << qmodpay->lastError().text();

    ui->tableView->setModel(qmodpay);*/
    qtablem->setTable("payment");
    qtablem->select();
    ui->tableView->setModel(qtablem);
    ui->tableView->hideColumn(qtablem->columnCount()-1);
    ui->tableView->hideColumn(qtablem->columnCount()-2);
    ui->tableView->hideColumn(0);
}


FrameAddPayment::~FrameAddPayment()
{
    delete ui;
}

void FrameAddPayment::handleSelectionChanged(QModelIndex selection)
{
    const int num = ui->treeViewStudents->model()->index(selection.row(), 1).data(Qt::DisplayRole).toInt();
    qDebug() << num;


    ui->tableView->selectRow(num - 1);

    qphone->setQuery(QString("SELECT \'+' || country_calling_code || \'(' || "
                             "calling_code || \')' || phone_number AS phone FROM phone WHERE student = %1").arg(num));

    ui->listViewPhone->setModel(qphone);

}

void FrameAddPayment::on_comboBoxDepartment_currentIndexChanged(int index)
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

void FrameAddPayment::on_comboBoxYear_currentIndexChanged(int index)
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

void FrameAddPayment::on_comboBoxGroup_currentIndexChanged(int index)
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

void FrameAddPayment::on_lineEditFind_textEdited(const QString &arg1)
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
