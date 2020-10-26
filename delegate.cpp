#include "delegate.h"

Delegate::Delegate(QObject *parent, bool valid) : QItemDelegate(parent), validate(valid)
{
    uniqueData = true;  // по умолчанию
}

QWidget* Delegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QLineEdit* e = new QLineEdit(parent);
    if (validate)
    {
        QRegExp rx("[a-zA-Z0-9]{1,12}");
        QValidator *validator = new QRegExpValidator(rx, (QObject*)this);
        e->setValidator(validator);
    }
    return e;
}

void Delegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QRect r = option.rect;
    if (option.state & QStyle::State_Selected)
    {
        painter->fillRect(r, QColor(230, 230, 230));
    }
    painter->save();
    QString data = index.model()->data(index).toString();
    painter->setBrush(option.palette.text());
    painter->drawText(r, Qt::AlignVCenter, data);
    painter->restore();
}

void Delegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QLineEdit* e = qobject_cast<QLineEdit*>(editor);
    e->setText(index.model()->data(index).toString());
}

void Delegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    //этот метод вызывается раньше, чем эмитятся сигналы closeEditor и commitData
    QLineEdit* e = qobject_cast<QLineEdit*>(editor);
    QString text = e->text();
    int item = index.row();
    bool isUnique = true;
    for (int i=0; i<model->rowCount(); i++)
    if (i != item)
    if (model->data(model->index(i, 0)).toString() == text)
    {
        isUnique = false;
        break;
    }
    if (!isUnique)
    {
        qDebug() << "ERROR: The text already exists";
        return;
    }
    model->setData(index, text);
}

bool Delegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    qDebug() << "EDITOR EVENT";
    QRect r(option.rect.width()-20, option.rect.y(), 20, 20);
    if (event->type() == QEvent::MouseButtonPress)
    {
        pressPos = static_cast <QMouseEvent*> (event)->pos();
        return r.contains(pressPos);
    }
    else if(event->type() == QEvent::MouseButtonRelease)
    {
        QPoint releasePos = static_cast <QMouseEvent*> (event)->pos();
        if (r.contains(pressPos) && r.contains(releasePos))
        {
            emit del(index);
            return true;
        }
    }
    return false;
}

void Delegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QRect r = option.rect;
    r.setWidth(r.width() - 25);
    editor->setGeometry(r);
    qDebug() << r;
}

QSize Delegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize(option.rect.width(), 20);
}

void Delegate::setUnique(bool isUnique)
{
    uniqueData = isUnique;
}
