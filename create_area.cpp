#include "create_area.h"
#include "ui_create_area.h"

create_area::create_area(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::create_area)
{
    ui->setupUi(this);
}

create_area::~create_area()
{
    delete ui;
}

void create_area::on_btn_create_clicked()//生成
{
    QString title = ui->le_title->text();
    QString seriesname = ui->le_series->text();
    bool Is_title = ui->checkBox_title->isChecked();
    QString X_name = ui->le_X->text();
    QString Y_name = ui->le_Y->text();
    double X_min = ui->X_Min->value();
    double X_max = ui->X_Max->value();
    double Y_min = ui->Y_Min->value();
    double Y_max = ui->Y_Max->value();
    QString data = ui->textEdit_data->toPlainText();
    emit Create_area(title,seriesname,Is_title,X_name,Y_name,X_min,X_max,Y_min,Y_max,data);
}

void create_area::on_btn_cancel_clicked()//取消
{
    this->close();
}
