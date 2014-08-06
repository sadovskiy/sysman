#include "frameaddstudent.hpp"
#include "ui_frameaddstudent.h"

#include <QSqlError>
#include <QDebug>

FrameAddStudent::FrameAddStudent(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::FrameAddStudent)
{
    ui->setupUi(this);

    sexList.insert(tr("Not known"), 0);
    sexList.insert(tr("Male"), 1);
    sexList.insert(tr("Female"), 2);
    sexList.insert(tr("Not applicable"), 9);


    QMapIterator<QString, int> i(sexList);

    while (i.hasNext()) {
        i.next();
        ui->comboBoxSex->addItem(i.key());
    }

    i.toFront();
    ui->comboBoxSex->setCurrentIndex(1);

    connect(ui->pushButtonAddRowStudent, SIGNAL(clicked()),
            this, SLOT(addRow()));
}

FrameAddStudent::~FrameAddStudent()
{
    delete ui;
}

void FrameAddStudent::addRow()
{
    int row = rmodel->rowCount();

    rmodel->insertRow(row);

    rmodel->setData(rmodel->index(row, rmodel->fieldIndex("surname")), ui->lineEditSurname->text());
    rmodel->setData(rmodel->index(row, rmodel->fieldIndex("name")), ui->lineEditName->text());
    rmodel->setData(rmodel->index(row, rmodel->fieldIndex("patronym")), ui->lineEditPatronym->text());
    rmodel->setData(rmodel->index(row, rmodel->fieldIndex("sex")), sexList.value(ui->comboBoxSex->currentText()));
    rmodel->setData(rmodel->index(row, rmodel->fieldIndex("place_of_birth")), ui->comboBoxPlaceOfBirth->currentText());
    rmodel->setData(rmodel->index(row, rmodel->fieldIndex("date_of_birth")), ui->dateEditDateOfBirth->date());
    rmodel->setData(rmodel->index(row, rmodel->fieldIndex("citizenship")), sexList.value(ui->comboBoxCitizenship->currentText()));
    rmodel->setData(rmodel->index(row, rmodel->fieldIndex("passport_series")), ui->spinBoxPassportSeries->value());
    rmodel->setData(rmodel->index(row, rmodel->fieldIndex("passport_number")), ui->spinBoxPassportNumber->value());
    rmodel->setData(rmodel->index(row, rmodel->fieldIndex("passport_authority")), ui->lineEditPassportAuthority->text());
    rmodel->setData(rmodel->index(row, rmodel->fieldIndex("passport_date_of_issue")), ui->dateEditPassportDateOfIssue->date());
    rmodel->setData(rmodel->index(row, rmodel->fieldIndex("passport_subdivision_code")), ui->spinBoxPassportSubdivisionCode->value());
    rmodel->setData(rmodel->index(row, rmodel->fieldIndex("registration_adm_unit")), ui->comboBoxRegistrationAdministrativeUnit->currentText());
    rmodel->setData(rmodel->index(row, rmodel->fieldIndex("registration_adress")), ui->lineEditRegistrationAdress->text());
    rmodel->setData(rmodel->index(row, rmodel->fieldIndex("registration_date")), ui->dateEditRegistrationDate->date());
    rmodel->setData(rmodel->index(row, rmodel->fieldIndex("postcode")), ui->spinBoxPostcode->value());
    rmodel->setData(rmodel->index(row, rmodel->fieldIndex("phone")), ui->spinBoxPhone->value());
    rmodel->setData(rmodel->index(row, rmodel->fieldIndex("email")), ui->lineEditEmail->text());
    rmodel->setData(rmodel->index(row, rmodel->fieldIndex("individual_taxpayer_identification_number")), ui->spinBoxIndividualTaxpayerIdentificationNumber->value());
//    rmodel->setData(rmodel->index(row, rmodel->fieldIndex("")), ui->->currentText());

    rmodel->setHeaderData(rmodel->fieldIndex("order_admission_num"), Qt::Horizontal, tr("order_admission_num"));
    rmodel->setHeaderData(rmodel->fieldIndex("order_dismissal_num"), Qt::Horizontal, tr("order_dismissal_num"));
    rmodel->setHeaderData(rmodel->fieldIndex("date_of_order_admission"), Qt::Horizontal, tr("date_of_order_admission"));
    rmodel->setHeaderData(rmodel->fieldIndex("date_of_order_dismissal"), Qt::Horizontal, tr("date_of_order_dismissal"));
    rmodel->setHeaderData(rmodel->fieldIndex("amount"), Qt::Horizontal, tr("amount"));
    rmodel->setHeaderData(rmodel->fieldIndex("semester"), Qt::Horizontal, tr("semester"));
    rmodel->setHeaderData(rmodel->fieldIndex("discount"), Qt::Horizontal, tr("discount"));
    rmodel->setHeaderData(rmodel->fieldIndex("actual_amount_of_payment"), Qt::Horizontal, tr("actual_amount_of_payment"));
    rmodel->setHeaderData(rmodel->fieldIndex("date_of_pay"), Qt::Horizontal, tr("date_of_pay"));
    rmodel->setHeaderData(rmodel->fieldIndex("penalties"), Qt::Horizontal, tr("penalties"));

    rmodel->setHeaderData(rmodel->fieldIndex("contract_number"), Qt::Horizontal, tr("contract_number"));
    rmodel->setHeaderData(rmodel->fieldIndex("contract_date"), Qt::Horizontal, tr("contract_date"));
    rmodel->setHeaderData(rmodel->fieldIndex("contract_type"), Qt::Horizontal, tr("contract_type"));
    rmodel->setHeaderData(rmodel->fieldIndex("surname"), Qt::Horizontal, tr("surname"));
    rmodel->setHeaderData(rmodel->fieldIndex("name"), Qt::Horizontal, tr("name"));
    rmodel->setHeaderData(rmodel->fieldIndex("patronym"), Qt::Horizontal, tr("patronym"));
    rmodel->setHeaderData(rmodel->fieldIndex("date_of_birth"), Qt::Horizontal, tr("date_of_birth"));
    rmodel->setHeaderData(rmodel->fieldIndex("place_of_birth"), Qt::Horizontal, tr("place_of_birth"));
    rmodel->setHeaderData(rmodel->fieldIndex("citizenship"), Qt::Horizontal, tr("citizenship"));
    rmodel->setHeaderData(rmodel->fieldIndex("passport_series"), Qt::Horizontal, tr("passport_series"));
    rmodel->setHeaderData(rmodel->fieldIndex("passport_number"), Qt::Horizontal, tr("passport_number"));
    rmodel->setHeaderData(rmodel->fieldIndex("passport_authority"), Qt::Horizontal, tr("passport_authority"));
    rmodel->setHeaderData(rmodel->fieldIndex("passport_date_of_issue"), Qt::Horizontal, tr("passport_date_of_issue"));
    rmodel->setHeaderData(rmodel->fieldIndex("passport_subdivision_code"), Qt::Horizontal, tr("passport_subdivision_code"));
    rmodel->setHeaderData(rmodel->fieldIndex("registration_adm_unit"), Qt::Horizontal, tr("registration_adm_unit"));
    rmodel->setHeaderData(rmodel->fieldIndex("registration_adress"), Qt::Horizontal, tr("registration_adress"));
    rmodel->setHeaderData(rmodel->fieldIndex("registration_date"), Qt::Horizontal, tr("registration_date"));
    rmodel->setHeaderData(rmodel->fieldIndex("postcode"), Qt::Horizontal, tr("postcode"));
    rmodel->setHeaderData(rmodel->fieldIndex("phone"), Qt::Horizontal, tr("phone"));
    rmodel->setHeaderData(rmodel->fieldIndex("email"), Qt::Horizontal, tr("email"));
    rmodel->setHeaderData(rmodel->fieldIndex("individual_taxpayer_identification_number"), Qt::Horizontal, tr("individual_taxpayer_identification_number"));

    rmodel->setHeaderData(rmodel->fieldIndex("contract_number"), Qt::Horizontal, tr("contract_number"));
    rmodel->setHeaderData(rmodel->fieldIndex("contract_date"), Qt::Horizontal, tr("contract_date"));
    rmodel->setHeaderData(rmodel->fieldIndex("contract_type"), Qt::Horizontal, tr("contract_type"));

    rmodel->setHeaderData(rmodel->fieldIndex("individual_taxpayer_identification_number"), Qt::Horizontal, tr("individual_taxpayer_identification_number"));

    rmodel->setHeaderData(rmodel->fieldIndex("order_admission_num"), Qt::Horizontal, tr("order_admission_num"));
    rmodel->setHeaderData(rmodel->fieldIndex("order_dismissal_num"), Qt::Horizontal, tr("order_dismissal_num"));
    rmodel->setHeaderData(rmodel->fieldIndex("date_of_order_admission"), Qt::Horizontal, tr("date_of_order_admission"));
    rmodel->setHeaderData(rmodel->fieldIndex("date_of_order_dismissal"), Qt::Horizontal, tr("date_of_order_dismissal"));

    rmodel->setHeaderData(rmodel->fieldIndex("amount"), Qt::Horizontal, tr("amount"));
    rmodel->setHeaderData(rmodel->fieldIndex("semester"), Qt::Horizontal, tr("semester"));
    rmodel->setHeaderData(rmodel->fieldIndex("discount"), Qt::Horizontal, tr("discount"));
    rmodel->setHeaderData(rmodel->fieldIndex("actual_amount_of_payment"), Qt::Horizontal, tr("actual_amount_of_payment"));
    rmodel->setHeaderData(rmodel->fieldIndex("date_of_pay"), Qt::Horizontal, tr("date_of_pay"));
    rmodel->setHeaderData(rmodel->fieldIndex("penalties"), Qt::Horizontal, tr("penalties"));
    rmodel->setHeaderData(rmodel->fieldIndex("department"), Qt::Horizontal, tr("department"));
    rmodel->setHeaderData(rmodel->fieldIndex("student"), Qt::Horizontal, tr("student"));
    rmodel->setHeaderData(rmodel->fieldIndex("phase_1_amount"), Qt::Horizontal, tr("phase_1_amount"));
    rmodel->setHeaderData(rmodel->fieldIndex("phase_1_date"), Qt::Horizontal, tr("phase_1_date"));
    rmodel->setHeaderData(rmodel->fieldIndex("phase_2_amount"), Qt::Horizontal, tr("phase_2_amount"));
    rmodel->setHeaderData(rmodel->fieldIndex("phase_2_date"), Qt::Horizontal, tr("phase_2_date"));
    rmodel->setHeaderData(rmodel->fieldIndex("phase_3_amount"), Qt::Horizontal, tr("phase_3_amount"));
    rmodel->setHeaderData(rmodel->fieldIndex("phase_3_date"), Qt::Horizontal, tr("phase_3_date"));
    rmodel->setHeaderData(rmodel->fieldIndex("comment"), Qt::Horizontal, tr("comment"));
    rmodel->setHeaderData(rmodel->fieldIndex("resolution_pay_phase"), Qt::Horizontal, tr("resolution_pay_phase"));
    rmodel->setHeaderData(rmodel->fieldIndex("year_of_study"), Qt::Horizontal, tr("year_of_study"));
    rmodel->setHeaderData(rmodel->fieldIndex("academic_program"), Qt::Horizontal, tr("academic_program"));
    rmodel->setHeaderData(rmodel->fieldIndex("qualification"), Qt::Horizontal, tr("qualification"));
    rmodel->setHeaderData(rmodel->fieldIndex("specialty"), Qt::Horizontal, tr("specialty"));
    rmodel->setHeaderData(rmodel->fieldIndex("payment"), Qt::Horizontal, tr("payment"));
    rmodel->setHeaderData(rmodel->fieldIndex("department_contract"), Qt::Horizontal, tr("department_contract"));


    rmodel->submitAll();
    if (rmodel->lastError().isValid())
        qDebug() << rmodel->lastError().text();
}

void FrameAddStudent::setModel(QSqlRelationalTableModel *model)
{
    rmodel = model;
}
