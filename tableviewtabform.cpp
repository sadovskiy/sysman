#include "tableviewtabform.hpp"
#include "ui_tableviewtabform.h"
#include "datecolumndelegate.hpp"
#include "sexcolumndelegate.hpp"
#include "countrydelegate.hpp"

#include <QGridLayout>
#include <QSqlError>
#include <QSpacerItem>

TableViewTabForm::TableViewTabForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TableViewTabForm)
{
    ui->setupUi(this);


    QGridLayout *glayout = new QGridLayout(this);
    QSpacerItem *horizontalSpacerButtonSHFrame = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QHBoxLayout *hspbottom = new QHBoxLayout;
    sort_filter = new QSortFilterProxyModel(this);

    hspbottom->addItem(horizontalSpacerButtonSHFrame);
    hspbottom->addWidget(ui->pushButtonShowHideFrameAddRow);

//    framecontr = new FrameAddContract(this);
    frameoadm = new FrameAddOrderAdmission(this);
    frameodism = new FrameAddOrderDismission(this);
    framepayment = new FrameAddPayment(this);
    framepp = new FrameAddPhasePayment(this);

    glayout->addWidget(ui->tableView, 0, 0);

    glayout->addWidget(framecontr, 2, 0, Qt::AlignLeft | Qt::AlignBottom);
    glayout->addWidget(frameoadm, 3, 0, Qt::AlignLeft | Qt::AlignBottom);
    glayout->addWidget(frameodism, 4, 0, Qt::AlignLeft | Qt::AlignBottom);
    glayout->addWidget(framepayment, 5, 0, Qt::AlignLeft | Qt::AlignBottom);
    glayout->addWidget(framepp, 6, 0, Qt::AlignLeft | Qt::AlignBottom);

    glayout->addLayout(hspbottom, 8, 0, Qt::AlignRight);

    this->setLayout(glayout);

    framecontr->setVisible(false);
    frameoadm->setVisible(false);
    frameodism->setVisible(false);
    framepayment->setVisible(false);
    framepp->setVisible(false);

    ui->tableView->horizontalHeader()->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tableView->horizontalHeader(), SIGNAL(customContextMenuRequested(QPoint)),
            this, SLOT(customHeaderMenuRequested(QPoint)));

    rmodel = new QSqlRelationalTableModel(this);


    sort_filter->setSourceModel(rmodel);
    sort_filter->sort(rmodel->fieldIndex("surname"));
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

    if (rmodel->lastError().isValid())
        qDebug() << rmodel->lastError().text();

/*
    if (tName == "student")
        framestud->setModel(rmodel);
    if (tName == "contract")
        framecontr->setModel(rmodel);
    if (tName == "orders_admission")
        frameoadm->setModel(rmodel);
    if (tName == "orders_dismissal")
        frameodism->setModel(rmodel);
    if (tName == "payment")
        framepayment->setModel(rmodel);
    if (tName == "phase_payment")
        framepp->setModel(rmodel);
    if (tName == "all_data")
        frameall->setModel(rmodel);

*/

    ui->tableView->setModel(sort_filter);
    ui->tableView->resizeColumnsToContents();


    ui->tableView->setColumnHidden(0, true);



    ui->tableView->setItemDelegateForColumn(rmodel->fieldIndex("date_of_birth"),
                                            new DateColumnDelegate(this));
    ui->tableView->setItemDelegateForColumn(rmodel->fieldIndex("passport_date_of_issue"),
                                            new DateColumnDelegate(this));
    ui->tableView->setItemDelegateForColumn(rmodel->fieldIndex("registration_date"),
                                            new DateColumnDelegate(this));
    ui->tableView->setItemDelegateForColumn(rmodel->fieldIndex("contract_date"),
                                            new DateColumnDelegate(this));
    ui->tableView->setItemDelegateForColumn(rmodel->fieldIndex("date_of_order_admission"),
                                            new DateColumnDelegate(this));
    ui->tableView->setItemDelegateForColumn(rmodel->fieldIndex("date_of_order_dismissal"),
                                            new DateColumnDelegate(this));
    ui->tableView->setItemDelegateForColumn(rmodel->fieldIndex("date_of_pay"),
                                            new DateColumnDelegate(this));
    ui->tableView->setItemDelegateForColumn(rmodel->fieldIndex("phase_1_date"),
                                            new DateColumnDelegate(this));
    ui->tableView->setItemDelegateForColumn(rmodel->fieldIndex("phase_2_date"),
                                            new DateColumnDelegate(this));
    ui->tableView->setItemDelegateForColumn(rmodel->fieldIndex("phase_3_date"),
                                            new DateColumnDelegate(this));

    ui->tableView->setItemDelegateForColumn(rmodel->fieldIndex("sex"),
                                            new SexColumnDelegate(this));
    ui->tableView->setColumnWidth(rmodel->fieldIndex("sex"), 120);


    ui->tableView->setItemDelegateForColumn(rmodel->fieldIndex("citizenship"),
                                            new CountryDelegate(this));
    ui->tableView->setColumnWidth(rmodel->fieldIndex("citizenship"), 250);

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
    rmodel->setHeaderData(rmodel->fieldIndex("surname"), Qt::Horizontal, tr("surname"));
    rmodel->setHeaderData(rmodel->fieldIndex("name"), Qt::Horizontal, tr("name"));
    rmodel->setHeaderData(rmodel->fieldIndex("patronym"), Qt::Horizontal, tr("patronym"));
    rmodel->setHeaderData(rmodel->fieldIndex("sex"), Qt::Horizontal, tr("sex"));
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
/*    rmodel->setHeaderData(rmodel->fieldIndex(""), Qt::Horizontal, tr(""));
    rmodel->setHeaderData(rmodel->fieldIndex(""), Qt::Horizontal, tr(""));
    rmodel->setHeaderData(rmodel->fieldIndex(""), Qt::Horizontal, tr(""));*/

    // Для кнопки сокрытия фрэйма с полями для ввода данных в таблицу
    connect(ui->pushButtonShowHideFrameAddRow, SIGNAL(clicked()),
            this, SLOT(ShowHideFrameAddRow()));



}

QString TableViewTabForm::tableName() const
{
    return tName;
}

void TableViewTabForm::customHeaderMenuRequested(QPoint pos)
{
    contextHeaderMenu = new QMenu(this);
    actionHeader = new QAction(tr("Hide"), this);
    contextHeaderMenu->addAction(actionHeader);
    contextHeaderMenu->popup(ui->tableView->horizontalHeader()->viewport()->mapToGlobal(pos));
    connect(actionHeader, SIGNAL(triggered()), this, SLOT(HideHeader()));
    mPos = pos;
}

void TableViewTabForm::HideHeader()
{
    int indexHeader = ui->tableView->horizontalHeader()->logicalIndexAt(mPos);
    ui->tableView->hideColumn(indexHeader);
}

void TableViewTabForm::clear() const
{
    rmodel->clear();
}



void TableViewTabForm::ShowHideFrameAddRow()
{
    QFrame *frame = 0;
    if (tName == "contract")
        frame = framecontr;
    if (tName == "orders_admission")
        frame = frameoadm;
    if (tName == "orders_dismissal")
        frame = frameodism;
    if (tName == "payment")
        frame = framepayment;
    if (tName == "phase_payment")
        frame = framepp;

    if (frame) {
        if (frame->isVisible()) {
            frame->setVisible(false);
            ui->pushButtonShowHideFrameAddRow->setText(tr("Show Frame Add Row"));
        }
        else {
            frame->setVisible(true);
            ui->pushButtonShowHideFrameAddRow->setText(tr("Hide Frame Add Row"));
        }
    }
}

