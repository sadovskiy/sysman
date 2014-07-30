#include "tableviewtabform.hpp"
#include "ui_tableviewtabform.h"
#include "datecolumndelegate.hpp"
#include "sexcolumndelegate.hpp"
#include "countrydelegate.hpp"

#include <QSqlError>

TableViewTabForm::TableViewTabForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TableViewTabForm)
{
    ui->setupUi(this);

    rmodel = new QSqlRelationalTableModel(this);

    connect(ui->pushButtonAddRow, SIGNAL(clicked()),
            this, SLOT(addRow()));
}

TableViewTabForm::~TableViewTabForm()
{
    delete ui;
}

void TableViewTabForm::setTableName(QString name)
{
    tName = name;
    rmodel->setTable(tName);
    rmodel->setSort(0, Qt::AscendingOrder);

    rmodel->select();

    qDebug() << rmodel->lastError().text();

    ui->tableView->setModel(rmodel);
    ui->tableView->resizeColumnsToContents();

    ui->tableView->setColumnHidden(0, true);

    ui->tableView->setItemDelegateForColumn(rmodel->fieldIndex("date_of_birth"),
                                            new DateColumnDelegate(this));
    ui->tableView->setItemDelegateForColumn(rmodel->fieldIndex("passport_date_of_issue"),
                                            new DateColumnDelegate(this));
    ui->tableView->setItemDelegateForColumn(rmodel->fieldIndex("registration_date"),
                                            new DateColumnDelegate(this));
    ui->tableView->setItemDelegateForColumn(rmodel->fieldIndex("sex"),
                                            new SexColumnDelegate(this));
/*
    ui->tableView->setItemDelegateForColumn(rmodel->fieldIndex("citizenship"),
                                            new CountryDelegate(this));*/

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
    rmodel->setHeaderData(rmodel->fieldIndex("Sex"), Qt::Horizontal, tr("Sex"));
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
    rmodel->setHeaderData(rmodel->fieldIndex("surname"), Qt::Horizontal, tr("surname"));
    rmodel->setHeaderData(rmodel->fieldIndex("name"), Qt::Horizontal, tr("name"));
    rmodel->setHeaderData(rmodel->fieldIndex("patronym"), Qt::Horizontal, tr("patronym"));
    rmodel->setHeaderData(rmodel->fieldIndex("Sex"), Qt::Horizontal, tr("Sex"));
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

}

QString TableViewTabForm::tableName() const
{
    return tName;
}

void TableViewTabForm::customHeaderMenuRequested(QPoint pos)
{
    contextHeaderMenu = new QMenu(this);
    contextHeaderMenu->addAction(new QAction(tr("Hide"), this));
    contextHeaderMenu->popup(ui->tableView->horizontalHeader()->viewport()->mapToGlobal(pos));
}

void TableViewTabForm::clear() const
{
    rmodel->clear();
}

void TableViewTabForm::addRow()
{
    int row = rmodel->rowCount();
    rmodel->insertRow(row);
/*    QModelIndex index = model->index(row, );
    ui->tableView->setCurrentIndex(index);
    ui->tableView->edit(index);*/
    rmodel->setData(rmodel->index(row, 0), ui->lineEditName->text());
    rmodel->setData(rmodel->index(row, 1), ui->lineEditSurname->text());
    rmodel->setData(rmodel->index(row, 2), ui->lineEditPatronym->text());
    rmodel->setData(rmodel->index(row, 3), ui->comboBoxSex->currentText());
    rmodel->setData(rmodel->index(row, 4), ui->dateEditDateOfBirth->date());
    rmodel->setData(rmodel->index(row, 3), ui->comboBoxCitizenship->currentText());

    rmodel->submitAll();
}
