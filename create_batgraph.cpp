#include "create_batgraph.h"
#include "ui_create_batgraph.h"

create_batgraph::create_batgraph(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::create_batgraph)
{
    ui->setupUi(this);
}

create_batgraph::~create_batgraph()
{
    delete ui;
}

void create_batgraph::on_btn_cancel_clicked()//取消
{
    this->close();
}

void create_batgraph::on_btn_create_clicked()//生成
{
    QString title = ui->le_title->text();
    QString X_name = ui->le_X->text();
    QString Y_name = ui->le_Y->text();
    int num = ui->spinBox_number->value();
    bool Is_title = ui->checkBox_title->isChecked();
    QString X_text = ui->textEdit_X->toPlainText();
    QString Data_text = ui->textEdit_data->toPlainText();
    QString Barset = ui->textEdit_barset->toPlainText();
    int min = ui->Y_Min->value();
    int max = ui->Y_Max->value();
    emit create_bargraph(title,X_name,Y_name,num,Is_title,X_text,Data_text,Barset,min,max);
}
