#include "delegate.h"
#include "cateditdialog.h"
#include "ui_cateditdialog.h"

CatEditDialog::CatEditDialog(QWidget *parent) {
 QVBoxLayout *layout = new QVBoxLayout(this);
 listView = new QListView(this);
 Delegate *myDelegate = new Delegate(this);
 myModel = new QStringListModel(this);
 listView->setModel(myModel);
 listView->setItemDelegate(myDelegate);
 appendButton = new QPushButton("Append", this);
 deleteButton = new QPushButton("Delete", this);
 layout->addWidget(listView);
 layout->addWidget(appendButton);
 layout->addWidget(deleteButton);
 setLayout(layout);
 connect(myDelegate, SIGNAL(closeEditor(QWidget*)), this, SLOT(checkUniqueItem(QWidget*)));
  //связываем сигнал закрытия редактора со слотом проверки
 connect(this, SIGNAL(tryToWriteItem(bool)), myDelegate, SLOT(setUnique(bool)));
  //для передачи в делегат булевой переменной
 connect(appendButton, SIGNAL(clicked()), this, SLOT(addItem()));
 connect(deleteButton, SIGNAL(clicked()), this, SLOT(removeItem()));
 listView->setCurrentIndex(myModel->index(0));
}

CatEditDialog::~CatEditDialog() { }

bool CatEditDialog::isUnique(QString &text, QAbstractItemView *view) {
 //метод, проверяющий уникальность элемента
 int item = view->currentIndex().row();
 QStringListModel* model = static_cast<QStringListModel*>(view->model());
 for (int i=0; i<model->rowCount(); i++) {
  if (i != item)
   if (model->data(model->index(i), Qt::DisplayRole).toString() == text)
    return false;
 }
 return true;
}

void CatEditDialog::removeItem() {
 QModelIndex index = listView->currentIndex();
 myModel->removeRow(index.row());
 listView->setCurrentIndex(index.row() != myModel->rowCount() ?
  index : myModel->index(index.row()-1));
}

void CatEditDialog::addItem() {
 QModelIndex index = listView->currentIndex();
 int i=myModel->rowCount();
 myModel->insertRow(i);
 myModel->setData(myModel->index(i), QString("Iptem%1").arg(i));
 listView->setCurrentIndex(myModel->index(myModel->rowCount()-1));
}

void CatEditDialog::checkUniqueItem(QWidget *editor) {
 qDebug() << "CLOSE EDITOR";
 QString text = static_cast<QLineEdit*>(editor)->text();
 emit tryToWriteItem(isUnique(text, listView));
  //сигнал делегату, isUnique(text, catView) - результат проверки
}
