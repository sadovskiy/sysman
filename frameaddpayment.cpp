#include "frameaddpayment.hpp"
#include "ui_frameaddpayment.h"

#include <QSqlError>
#include <QDebug>
#include <QDate>
#include <QSqlRecord>
#include <QHeaderView>
#include "money.hpp"

FrameAddPayment::FrameAddPayment(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::FrameAddPayment)
{
    ui->setupUi(this);

    ui->treeViewStudents->header()->setSortIndicator(0, Qt::AscendingOrder);

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
    resultTable = new QSqlQueryModel;

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

    qmodyear->setQuery("SELECT DISTINCT(date_part('year', now()) - date_part('year', date_of_order_admission) + course_enrollment) AS year FROM orders_admission WHERE course_enrollment IS NOT NULL ORDER BY year");

    if (qmodyear->lastError().isValid())
        qDebug() << qmodyear->lastError().text();


    yearList.insert(0, tr("All"));

    qCountRows.exec("SELECT COUNT(DISTINCT (date_part('year', now()) - date_part('year', date_of_order_admission) + course_enrollment)) FROM orders_admission WHERE course_enrollment IS NOT NULL");

    qCountRows.next();


    for (int i = 0; i < qCountRows.value(0).toInt(); ++i) {
        QString duration = qmodyear->record(i).value("year").toString();
        yearList.insert(i + 1, duration);
    }

    QMapIterator<int, QString> iy(yearList);

    while (iy.hasNext()) {
        iy.next();
        ui->comboBoxYear->addItem(iy.value());
    }

    sqlproxy = new QSortFilterProxyModel(this);
    sqlproxy->setDynamicSortFilter(true);
    sqlproxy->setSourceModel(qmodstud);



    ui->treeViewStudents->setModel(qmodstud);

    ui->treeViewStudents->hideColumn(1);

    connect(ui->treeViewStudents->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            this, SLOT(handleSelectionChanged(QModelIndex)));
    if (QDate::currentDate().month() > 8)
        ui->comboBoxTimeOfYear->setCurrentIndex(1);
    ui->comboBoxAcademicYear->addItem(QString("%1 - %2").arg(QDate::currentDate().year()).arg(QDate::currentDate().year() + 1));
/*
    qmodpay->setQuery("SELECT discount, actual_amount_of_payment, date_of_pay, actual_amount_of_payment - (0.01 * discount * actual_amount_of_payment) AS discount_in_prc FROM payment AS pa WHERE pa.payment_id = 16");

    if (qmodpay->lastError().isValid())
        qDebug() << qmodpay->lastError().text();

    ui->tableView->setModel(qmodpay);*/
    qtablem->setTable("payment");
    resultTable->setQuery("SELECT ct.payment, ct.payment * 1.065 AS cof, semester, discount || \'\%\' AS discount, payment - (0.01 * discount * payment) AS discount_in_prc, penalties FROM payment AS pm JOIN (SELECT contract_id, payment FROM contract) AS ct ON pm.payment_id = ct.contract_id ORDER BY payment_id");
//    qtablem->setFilter("");
//    qtablem->columnCount();

//    qtablem->insertColumn(0, QModelIndex());
    qtablem->sort(0, Qt::AscendingOrder);

    qtablem->select();

    QString n = 0;

    qtablem->setHeaderData(qtablem->fieldIndex("semester"), Qt::Horizontal, tr("semester"));
    qtablem->setHeaderData(qtablem->fieldIndex("discount"), Qt::Horizontal, tr("discount"));
    qtablem->setHeaderData(qtablem->fieldIndex("actual_amount_of_payment"), Qt::Horizontal, tr("actual_amount_of_payment"));
    qtablem->setHeaderData(qtablem->fieldIndex("date_of_pay"), Qt::Horizontal, tr("date_of_pay"));
    qtablem->setHeaderData(qtablem->fieldIndex("penalties"), Qt::Horizontal, tr("penalties"));
//    qtablem->setData(qtablem->index(row, qtablem->fieldIndex(""), Qt::Horizontal, tr("")));

    qcontract->exec("SELECT payment FROM contract WHERE contract_id = 10");
    if (qcontract->lastError().isValid())
        qDebug() << qcontract->lastError().text();
    Money m;
    QLocale locale = QLocale::system();

    while (qcontract->next()) {
        n = qcontract->value(0).toString().remove(qcontract->value(0).toString().length() - 7, 7);
    }
    n.remove(locale.groupSeparator());
//    m.parse(n);
//    int mon = (double)n.toInt() * ui->lineEditCoefficient->text().toDouble();
//    qtablem->setData(qtablem->index(2, 1), mon);
//    qtablem->index(1, 2).data(Qt::DisplayRole).toInt();

    ui->tableViewResult->setModel(resultTable);

    ui->tableView->setModel(qtablem);
    ui->tableView->hideColumn(0);
    ui->tableView->hideColumn(qtablem->fieldIndex("resolution_pay_phase"));
    ui->tableView->hideColumn(qtablem->fieldIndex("id"));
    ui->tableView->hideColumn(qtablem->fieldIndex("phase"));
    ui->tableView->hideColumn(qtablem->fieldIndex("semester"));
    ui->tableView->hideColumn(qtablem->fieldIndex("discount"));
    ui->tableView->hideColumn(qtablem->fieldIndex("penalties"));
    ui->tableView->resizeColumnsToContents();

    ui->treeViewStudents->header()->setSectionsClickable(true);
    connect(ui->treeViewStudents->header(), SIGNAL(sortIndicatorChanged(int,Qt::SortOrder)),
            this, SLOT(sortStudent(int,Qt::SortOrder)));

}


FrameAddPayment::~FrameAddPayment()
{
    delete ui;
}

void FrameAddPayment::sortStudent(int index, Qt::SortOrder order)
{
//    ui->treeViewStudents->sortByColumn(0, order);

    //    ui->treeViewStudents->setSortingEnabled(true);
    //    sqlproxy->sort(0, order);
    if (ui->comboBoxDepartment->currentIndex() == 0)
        ui->comboBoxDepartment->currentIndexChanged(ui->comboBoxDepartment->currentIndex());
    else
        ui->comboBoxYear->currentIndexChanged(ui->comboBoxYear->currentIndex());

}

void FrameAddPayment::handleSelectionChanged(QModelIndex selection)
{
    const int num = ui->treeViewStudents->model()->index(selection.row(), 1).data(Qt::DisplayRole).toInt();
    qDebug() << num;

    ui->listWidgetPhone->clear();

    ui->tableView->selectRow(num - 2);
    ui->tableViewResult->selectRow(num);

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




//    ui->listViewPhone->setModel(qphone);

}

void FrameAddPayment::on_comboBoxDepartment_currentIndexChanged(int index)
{
    qDebug() << "on_comboBoxDepartment_currentIndexChanged: " << index;


    if (index) {
        if (ui->treeViewStudents->header()->sortIndicatorOrder() == Qt::AscendingOrder)
            qmodstud->setQuery(QString("SELECT stt.surname || \' \' || stt.name || \' \' || stt.patronym AS Students, stt.student_id FROM student AS stt "
                                       "JOIN (SELECT lsiad.student_id FROM list_student_in_admission lsiad JOIN (SELECT oa.order_admission_id "
                                       "FROM orders_admission oa WHERE oa.department = %1) oai ON oai.order_admission_id = lsiad.order_admission_id) "
                                       "lss ON lss.student_id = stt.student_id ORDER BY stt.surname").arg(index));
        else
            qmodstud->setQuery(QString("SELECT stt.surname || \' \' || stt.name || \' \' || stt.patronym AS Students, stt.student_id FROM student AS stt "
                                       "JOIN (SELECT lsiad.student_id FROM list_student_in_admission lsiad JOIN (SELECT oa.order_admission_id "
                                       "FROM orders_admission oa WHERE oa.department = %1) oai ON oai.order_admission_id = lsiad.order_admission_id) "
                                       "lss ON lss.student_id = stt.student_id ORDER BY stt.surname DESC").arg(index));
        if (qmodstud->lastError().isValid())
            qDebug() << qmodstud->lastError().text();

        QSqlQuery queryCountStudents("SELECT COUNT(*) FROM orders_admission WHERE course_enrollment IS NOT NULL");
        QSqlQuery queryCountDepartmentStudents(QString("SELECT COUNT(*) AS count "
                                                 "FROM orders_admission "
                                                 "WHERE department = %1").arg(index));


        if (queryCountStudents.next() && queryCountDepartmentStudents.next())
            ui->labelTotalStudents->setText(tr("Total Students: %1/%2").arg(queryCountStudents.value(0).toInt()).
                                            arg(queryCountDepartmentStudents.value(0).toInt()));
    }
    else {
        if (ui->treeViewStudents->header()->sortIndicatorOrder() == Qt::AscendingOrder)
            qmodstud->setQuery("SELECT stt.surname || \' \' || stt.name || \' \' || stt.patronym AS Students, stt.student_id FROM student AS stt JOIN (SELECT lsa.student_id FROM list_student_in_admission AS lsa JOIN (SELECT order_admission_id FROM orders_admission WHERE course_enrollment IS NOT NULL) AS adm ON adm.order_admission_id = lsa.order_admission_id) AS lss ON lss.student_id = stt.student_id ORDER BY stt.surname");
        else
            qmodstud->setQuery("SELECT stt.surname || \' \' || stt.name || \' \' || stt.patronym AS Students, stt.student_id FROM student AS stt JOIN (SELECT lsa.student_id FROM list_student_in_admission AS lsa JOIN (SELECT order_admission_id FROM orders_admission WHERE course_enrollment IS NOT NULL) AS adm ON adm.order_admission_id = lsa.order_admission_id) AS lss ON lss.student_id = stt.student_id ORDER BY stt.surname DESC");

        if (qmodstud->lastError().isValid())
            qDebug() << qmodstud->lastError().text();

        QSqlQuery queryCountStudents("SELECT COUNT(*) FROM orders_admission WHERE course_enrollment IS NOT NULL");

        if (queryCountStudents.next())
            ui->labelTotalStudents->setText(tr("Total Students: %1").arg(queryCountStudents.value(0).toInt()));
    }
}

void FrameAddPayment::on_comboBoxYear_currentIndexChanged(int index)
{
    qDebug() << "on_comboBoxYear_currentIndexChanged: " << index;

    int year = ui->comboBoxYear->itemText(index).toInt();

    if (index) {
        if (ui->treeViewStudents->header()->sortIndicatorOrder() == Qt::AscendingOrder)
            qmodstud->setQuery(QString("SELECT stt.surname || \' \' || stt.name || \' \' || stt.patronym AS Students, stt.student_id FROM student AS stt "
                                       "JOIN (SELECT lsiad.student_id FROM list_student_in_admission lsiad JOIN "
                                       "(SELECT oa.order_admission_id, date_part('year', now()) - date_part('year', oa.date_of_order_admission) + "
                                       "oa.course_enrollment AS year FROM orders_admission AS oa WHERE (date_part('year', now()) - date_part('year', oa.date_of_order_admission) + oa.course_enrollment) = %1) "
                                       "oai ON oai.order_admission_id = lsiad.order_admission_id) "
                                       "lss ON lss.student_id = stt.student_id ORDER BY stt.surname").arg(year));
        else
            qmodstud->setQuery(QString("SELECT stt.surname || \' \' || stt.name || \' \' || stt.patronym AS Students, stt.student_id FROM student AS stt "
                                       "JOIN (SELECT lsiad.student_id FROM list_student_in_admission lsiad JOIN "
                                       "(SELECT oa.order_admission_id, date_part('year', now()) - date_part('year', oa.date_of_order_admission) + "
                                       "oa.course_enrollment AS year FROM orders_admission AS oa WHERE (date_part('year', now()) - date_part('year', oa.date_of_order_admission) + oa.course_enrollment) = %1) "
                                       "oai ON oai.order_admission_id = lsiad.order_admission_id) "
                                       "lss ON lss.student_id = stt.student_id ORDER BY stt.surname DESC").arg(year));

        QSqlQuery queryCountYearStudents(QString("SELECT COUNT(*) AS count "
                                                 "FROM orders_admission "
                                                 "WHERE (date_part('year', now()) - date_part('year', date_of_order_admission) + course_enrollment) = %1").arg(year));

        if (qmodstud->lastError().isValid())
            qDebug() << qmodstud->lastError().text();

        QSqlQuery queryCountStudents("SELECT COUNT(*) FROM orders_admission WHERE course_enrollment IS NOT NULL");

        if (queryCountStudents.next() && queryCountYearStudents.next())
            ui->labelTotalStudents->setText(tr("Total Students: %1/%2").arg(queryCountStudents.value(0).toInt()).
                                            arg(queryCountYearStudents.value(0).toInt()));
    }
    else {
        if (ui->treeViewStudents->header()->sortIndicatorOrder() == Qt::AscendingOrder)
            qmodstud->setQuery("SELECT stt.surname || \' \' || stt.name || \' \' || stt.patronym AS Students, stt.student_id FROM student AS stt JOIN (SELECT lsa.student_id FROM list_student_in_admission AS lsa JOIN (SELECT order_admission_id FROM orders_admission WHERE course_enrollment IS NOT NULL) AS adm ON adm.order_admission_id = lsa.order_admission_id) AS lss ON lss.student_id = stt.student_id ORDER BY stt.surname");
        else
            qmodstud->setQuery("SELECT stt.surname || \' \' || stt.name || \' \' || stt.patronym AS Students, stt.student_id FROM student AS stt JOIN (SELECT lsa.student_id FROM list_student_in_admission AS lsa JOIN (SELECT order_admission_id FROM orders_admission WHERE course_enrollment IS NOT NULL) AS adm ON adm.order_admission_id = lsa.order_admission_id) AS lss ON lss.student_id = stt.student_id ORDER BY stt.surname DESC");

        if (qmodstud->lastError().isValid())
            qDebug() << qmodstud->lastError().text();

        QSqlQuery queryCountStudents("SELECT COUNT(*) FROM orders_admission WHERE course_enrollment IS NOT NULL");

        if (queryCountStudents.next())
            ui->labelTotalStudents->setText(tr("Total Students: %1").arg(queryCountStudents.value(0).toInt()));
    }
}

void FrameAddPayment::on_comboBoxGroup_currentIndexChanged(int index)
{
    qDebug() << "on_comboBoxGroup_currentIndexChanged: " << index;

    if (index)
        qmodstud->setQuery(QString("SELECT stt.surname || \' \' || stt.name || \' \' || stt.patronym AS Students, stt.student_id FROM student AS stt "
                                   "JOIN (SELECT lsiad.student_id FROM list_student_in_admission lsiad JOIN (SELECT oa.order_admission_id "
                                   "FROM orders_admission oa WHERE oa.group = %1) oai ON oai.order_admission_id = lsiad.order_admission_id) "
                                   "lss ON lss.student_id = stt.student_id").arg(index));
    else
        qmodstud->setQuery("SELECT stt.surname || \' \' || stt.name || \' \' || stt.patronym AS Students, student_id FROM student AS stt");


    if (qmodstud->lastError().isValid())
        qDebug() << qmodstud->lastError().text();

    QSqlQuery queryCountStudents("SELECT COUNT(*) FROM student");

    if (queryCountStudents.next())
        ui->labelTotalStudents->setText(tr("Total Students: %1").arg(queryCountStudents.value(0).toInt()));
}

void FrameAddPayment::on_lineEditFind_textEdited(const QString &arg1)
{
    // Для поиска с любым регистром при вводе
    QString str = arg1;
    if (!arg1.isEmpty()) {
        str[0] = arg1.at(0).toTitleCase();
    }
    qmodstud->setQuery(QString("SELECT stt.surname || \' \' || stt.name || \' \' || stt.patronym AS Students, stt.student_id FROM student AS stt "
                               "WHERE surname LIKE \'%1\%\' ").arg(str));
    if (qmodstud->lastError().isValid())
        qDebug() << qmodstud->lastError().text();

}

