#include "create_donut.h"
#include "ui_create_donut.h"

create_donut::create_donut(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::create_donut)
{
    ui->setupUi(this);
}

create_donut::~create_donut()
{
    delete ui;
}

void create_donut::on_btn_create_clicked()//生成
{
    int num = ui->spinBox_number->value();
    double inner = ui->inner->value();
    QString title = ui->le_title->text();
    QString text = ui->textEdit->toPlainText();
    bool Is_checked = ui->checkBox_example->isChecked();
    bool Is_title = ui->checkBox_title->isChecked();
    bool Is_display = ui->checkBox_display->isChecked();
   emit createdonut(num,inner,title,text,Is_checked,Is_title,Is_display);
}

void create_donut::on_btn_cancel_clicked()//取消
{
    this->close();
}
