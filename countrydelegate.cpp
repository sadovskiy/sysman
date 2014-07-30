#include "countrydelegate.hpp"

#include <QComboBox>
#include <QDebug>
#include <QVariant>
#include <QSqlError>

CountryDelegate::CountryDelegate(QObject *parent):
    QStyledItemDelegate(parent)
{

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
    //return sexList.key(value.toInt());
}
/*
QWidget *CountryDelegate::createEditor(QWidget *parent,
                                         const QStyleOptionViewItem &option,
                                         const QModelIndex &index) const
{
    QComboBox *comboBox = new QComboBox(parent);
    comboBox->setEditable(true);



    return comboBox;
}

void CountryDelegate::setEditorData(QWidget *editor,
                                      const QModelIndex &index) const
{
    QComboBox *comboBox = qobject_cast<QComboBox *>(editor);
    int n = index.model()->data(index, Qt::EditRole).toInt();

 //   comboBox->setCurrentIndex(comboBox->findText(sexList.key(n)));
}

void CountryDelegate::setModelData(QWidget *editor,
                                     QAbstractItemModel *model,
                                     const QModelIndex &index) const
{
    QComboBox *comboBox = qobject_cast<QComboBox *>(editor);

//    int n = sexList.value(comboBox->currentText());

  //  model->setData(index, n);
}

void CountryDelegate::updateEditorGeometry(QWidget *editor,
                                             const QStyleOptionViewItem &option,
                                             const QModelIndex &index) const
{
    // Ресуем поле ввода даты на месте редактируемой ячейки
    editor->setGeometry(option.rect);
}
*/
