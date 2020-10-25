#ifndef DELEGATE_H
#define DELEGATE_H

#include <QDebug>
#include <QMessageBox>
#include <QRegExp>
#include <QPainter>
#include <QLineEdit>
#include <QItemDelegate>
#include <QEvent>
#include <QMouseEvent>

class Delegate : public QItemDelegate {
 Q_OBJECT
public:
 explicit Delegate(QObject *parent = 0, bool valid = true);
 QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option,
  const QModelIndex &index) const;
 void paint(QPainter *painter, const QStyleOptionViewItem &option,
  const QModelIndex &index) const;
 void setEditorData(QWidget *editor, const QModelIndex &index) const;
 void setModelData(QWidget *editor, QAbstractItemModel *model,
  const QModelIndex &index) const;
 bool editorEvent(QEvent *event, QAbstractItemModel *model,
  const QStyleOptionViewItem &option, const QModelIndex &index);
 void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
  const QModelIndex &index) const;
 QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
public slots:
 void setUnique(bool isUnique);
signals:
 void del(QModelIndex index);
private:
 QPoint pressPos;
 bool validate;
 bool uniqueData;
};

#endif // DELEGATE_H
