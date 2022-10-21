#include "create_scatter.h"
#include "ui_create_scatter.h"

create_scatter::create_scatter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::create_scatter)
{
    ui->setupUi(this);
}

create_scatter::~create_scatter()
{
    delete ui;
}

void create_scatter::on_btn_create_clicked()//生成
{
    QString title = ui->le_title->text();
    int num = ui->spinBox_number->value();
    bool Is_title = ui->checkBox_title->isChecked();
    bool Is_pos =ui->checkBox_pos->isChecked();
    QString X_name = ui->le_X->text();
    QString Y_name = ui->le_Y->text();
    double X_min = ui->X_Min->value();
    double X_max = ui->X_Max->value();
    double Y_min = ui->Y_Min->value();
    double Y_max = ui->Y_Max->value();
    QString text = ui->textEdit_curve->toPlainText();
    QString data = ui->textEdit_data->toPlainText();
    emit Create_scatter(title,num,Is_title,Is_pos,X_name,Y_name,X_min,X_max,Y_min,Y_max,text,data);
}

void create_scatter::on_btn_cancel_clicked()//取消
{
    this->close();
}
