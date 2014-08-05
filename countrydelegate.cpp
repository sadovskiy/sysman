#include "countrydelegate.hpp"

#include <QComboBox>
#include <QDebug>
#include <QVariant>
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>

CountryDelegate::CountryDelegate(QObject *parent):
    QStyledItemDelegate(parent)
{
/*    QSqlQuery query("SELECT * FROM country_table");

    if (!query.isActive())
        qDebug() << query.lastError().text();

    while(query.next()){
        Country country = Country(query.value(0).toInt(),
                                  query.value(1).toString(),
                                  query.value(2).toString(),
                                  query.value(3).toString(),
                                  query.value(4).toString(),
                                  query.value(5).toInt());
        countryList.insert(query.value(0).toInt(), country);
    }
*/
//    QMapIterator<QString, int> i(countryList);

    countryList.insert(tr("Russia"), 643);
    countryList.insert(tr("Other"), 0);

/*
    while (i.hasNext()) {
        qDebug() << i.value().nCodeCountry() << " "
                 << i.value().a2CodeCountry() << " "
                 << i.value().a3CodeCountry() << " "
                 << i.value().c3CodeCountry() << " "
                 << i.value().comm() << " "
                 << i.value().tCode();
    }*/

}

void CountryDelegate::paint(QPainter *painter,
                              const QStyleOptionViewItem &option,
                              const QModelIndex &index) const
{

    QStyledItemDelegate::paint(painter, option, index);
}

QString CountryDelegate::displayText(const QVariant &value,
                                        const QLocale &locale) const
{
    return countryList.key(value.toInt());
}

QWidget *CountryDelegate::createEditor(QWidget *parent,
                                         const QStyleOptionViewItem &option,
                                         const QModelIndex &index) const
{
    QComboBox *comboBox = new QComboBox(parent);
    comboBox->setEditable(true);

    QMapIterator<QString, int> i(countryList);

    while (i.hasNext()) {
        i.next();
        comboBox->addItem(i.key());
    }

    i.toFront();

    return comboBox;
}

void CountryDelegate::setEditorData(QWidget *editor,
                                      const QModelIndex &index) const
{
    QComboBox *comboBox = qobject_cast<QComboBox *>(editor);
    int n = index.model()->data(index, Qt::EditRole).toInt();

    comboBox->setCurrentIndex(comboBox->findText(countryList.key(n)));
}

void CountryDelegate::setModelData(QWidget *editor,
                                     QAbstractItemModel *model,
                                     const QModelIndex &index) const
{
    QComboBox *comboBox = qobject_cast<QComboBox *>(editor);

    int n = countryList.value(comboBox->currentText());

    model->setData(index, n);
}

void CountryDelegate::updateEditorGeometry(QWidget *editor,
                                             const QStyleOptionViewItem &option,
                                             const QModelIndex &index) const
{
    // Ресуем поле ввода даты на месте редактируемой ячейки
    editor->setGeometry(option.rect);
}

