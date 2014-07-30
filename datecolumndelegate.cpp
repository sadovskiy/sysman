#include "datecolumndelegate.hpp"

#include <QDate>
#include <QDateEdit>
#include <QCalendarWidget>
#include <QPainter>

DateColumnDelegate::DateColumnDelegate(QObject *parent):
    QStyledItemDelegate(parent)
{
}

void DateColumnDelegate::paint(QPainter *painter,
                               const QStyleOptionViewItem &option,
                               const QModelIndex &index) const
{
    QStyledItemDelegate::paint(painter, option, index);
}

QString DateColumnDelegate::displayText(const QVariant &value,
                                        const QLocale &locale) const
{
    return locale.toString(value.toDate(), "dd.MM.yyyy (ddd)");
}

QWidget *DateColumnDelegate::createEditor(QWidget *parent,
                                          const QStyleOptionViewItem &option,
                                          const QModelIndex &index) const
{
    QDateEdit *dateEdit = new QDateEdit(parent);

    dateEdit->setDisplayFormat("dd.MM.yyyy (ddd)");
    dateEdit->setAutoFillBackground(true);

    // Включение выпадающего меню календаря
    dateEdit->setCalendarPopup(true);

    // Настройки календаря ставим сетку и первый день недели понедельник
    dateEdit->calendarWidget()->setGridVisible(true);
    dateEdit->calendarWidget()->setFirstDayOfWeek(Qt::Monday);

    return dateEdit;
}

void DateColumnDelegate::setEditorData(QWidget *editor,
                                       const QModelIndex &index) const
{
    QDateEdit *dateEdit = qobject_cast<QDateEdit *>(editor);
    QDate date = index.model()->data(index, Qt::DisplayRole).toDate();

    // Если значение даты в поле отсутствует,
    // то ставим по умалчанию текущую дату
    if (date == QDate()) date = QDate::currentDate();

    dateEdit->setDate(date);
}

void DateColumnDelegate::setModelData(QWidget *editor,
                                      QAbstractItemModel *model,
                                      const QModelIndex &index) const
{
    QDateEdit *dateEdit = qobject_cast<QDateEdit *>(editor);

    model->setData(index, dateEdit->date());
}

void DateColumnDelegate::updateEditorGeometry(QWidget *editor,
                                              const QStyleOptionViewItem &option,
                                              const QModelIndex &index) const
{
    // Ресуем поле ввода даты на месте редактируемой ячейки
    editor->setGeometry(option.rect);
}
