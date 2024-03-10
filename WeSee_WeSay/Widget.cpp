#include "Widget.h"
#include "ui_widget.h"
#include <QDate>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    FileSystem* file = new  FileSystem();

    //file->AddRecord(Data(3,"李伟政",QDate(2004,07,21),"李伟政就读于北京邮电大学，天天不想上课，下课就回宿舍打游戏，打累了就睡觉，有一天周六他睡了一整天"));



    qDebug() << file->FindRecord(3).ToString();

    file->DeleteRecord(3);

    qDebug() << file->FindRecord(3).ToString();

    delete file;

}

Widget::~Widget()
{
    delete ui;
}

