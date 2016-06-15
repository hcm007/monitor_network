
#include <QApplication>
#include <QTextCodec>
//#include "hashmapmainfunction.h"
#include "tableview.h"





int main(int argc, char *argv[])
{




    QApplication a(argc, argv);
    TableView w;
    w.initializetablewidget();
    w.show();

//+++++++++++++++++++++this is  main from the hash function






    return a.exec();
}

























