#include "cateditdialog.h"
#include <QApplication>

int main(int argc, char *argv[]) {
 QApplication a(argc, argv);
 CatEditDialog w;
 w.show();
 return a.exec();
}
