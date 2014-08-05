#ifndef DATECOLUMNDELEGATE_HPP
#define DATECOLUMNDELEGATE_HPP

#include <QStyledItemDelegate>

// В качестве базового класса используем QStyledItemDelegate
// так как это рекомендуется разработчиками Qt, который даёт возможность
// создавать делегат с нуля
class DateColumnDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    DateColumnDelegate(QObject *parent = 0);

    // Отрисовывает ячейку элемента внутри таблицы до и после редактирования
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
                               const QModelIndex &index) const;

    // Задаёт формат отображаемого текста
    QString displayText(const QVariant &value, const QLocale &locale) const;

    // Создаёт виджет редактора элемента
    QWidget *createEditor(QWidget *parent,
                           const QStyleOptionViewItem &option,
                           const QModelIndex &index) const;

    // Передаёт значение из модели по индексу (index) в редактор (editor)
    void setEditorData(QWidget *editor, const QModelIndex &index) const;

    // Передаёт значение из редактора (editor) в модель (model)
    // по индексу (index)
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                                      const QModelIndex &index) const;

    // Задаёт располажение редактора (editor) на форме
    void updateEditorGeometry(QWidget *editor,
                              const QStyleOptionViewItem &option,
                              const QModelIndex &index) const;
};

#endif // DATECOLUMNDELEGATE_HPP
