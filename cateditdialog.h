#ifndef CATEDITDIALOG_H
#define CATEDITDIALOG_H

#include <QDialog>
#include <QtGui>
#include <QListView>
#include <QPushButton>
#include <QVBoxLayout>

namespace Ui {
 class CatEditDialog;
}

class CatEditDialog : public QDialog {
 Q_OBJECT
public:
 CatEditDialog(QWidget *parent = 0);
 ~CatEditDialog();
private:
 QListView* listView;
 QStringListModel* myModel;
 QPushButton* appendButton, * deleteButton;
 inline bool isUnique(QString &text, QAbstractItemView* view);
private slots:
 void removeItem();
 void addItem();
 void checkUniqueItem(QWidget* editor);
signals:
 void tryToWriteItem(bool on);
};

#endif // CATEDITDIALOG_H
