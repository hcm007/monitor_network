#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include <QMainWindow>
#include <QProcess>

namespace Ui {//this is created by the ui interface
class TableView;
}

class TableView : public QMainWindow
{
    Q_OBJECT

public:
    explicit TableView(QWidget *parent = 0);

    ~TableView();



private:
    Ui::TableView *ui;

public:
    void initializetablewidget();


private slots:
    void touchOkButton();

void changejudge();




};

#endif // TABLEVIEW_H
