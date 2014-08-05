#include "sexcolumndelegate.hpp"

#include <QComboBox>
#include <QDebug>
#include <QVariant>

SexColumnDelegate::SexColumnDelegate(QObject *parent):
    QStyledItemDelegate(parent)
{
    sexList.insert(tr("Not known"), 0);
    sexList.insert(tr("Male"), 1);
    sexList.insert(tr("Female"), 2);
    sexList.insert(tr("Not applicable"), 9);
}

void SexColumnDelegate::paint(QPainter *painter,
                              const QStyleOptionViewItem &option,
                              const QModelIndex &index) const
{
    QStyledItemDelegate::paint(painter, option, index);
}

QString SexColumnDelegate::displayText(const QVariant &value,
                                        const QLocale &locale) const
{
    return sexList.key(value.toInt());
}

QWidget *SexColumnDelegate::createEditor(QWidget *parent,
                                         const QStyleOptionViewItem &option,
                                         const QModelIndex &index) const
{
    QComboBox *comboBox = new QComboBox(parent);
    comboBox->setEditable(true);

    QMapIterator<QString, int> i(sexList);

    while (i.hasNext()) {
        i.next();
        comboBox->addItem(i.key());
    }

    i.toFront();

    return comboBox;
}

void SexColumnDelegate::setEditorData(QWidget *editor,
                                      const QModelIndex &index) const
{
    QComboBox *comboBox = qobject_cast<QComboBox *>(editor);
    int n = index.model()->data(index, Qt::EditRole).toInt();

    comboBox->setCurrentIndex(comboBox->findText(sexList.key(n)));
}

void SexColumnDelegate::setModelData(QWidget *editor,
                                     QAbstractItemModel *model,
                                     const QModelIndex &index) const
{
    QComboBox *comboBox = qobject_cast<QComboBox *>(editor);

    int n = sexList.value(comboBox->currentText());

    model->setData(index, n);
}

void SexColumnDelegate::updateEditorGeometry(QWidget *editor,
                                             const QStyleOptionViewItem &option,
                                             const QModelIndex &index) const
{
    // Ресуем поле ввода даты на месте редактируемой ячейки
    editor->setGeometry(option.rect);
}
