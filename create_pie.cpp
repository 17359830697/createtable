#include "create_pie.h"
#include "ui_build_page.h"

Build_Page::Build_Page(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Build_Page)
{
    ui->setupUi(this);
   this->setWindowIcon(QIcon(":/src/prefix/src/pie.png"));
}

Build_Page::~Build_Page()
{
    delete ui;
}

void Build_Page::on_btn_cancel_clicked()//取消
{
    this->close();
}

void Build_Page::on_btn_create_clicked() //生成
{
    int num = ui->spinBox_number->value();
    QString title = ui->le_title->text();
    QString text = ui->textEdit->toPlainText();
    bool Is_checked = ui->checkBox_example->isChecked();
    bool Is_title = ui->checkBox_title->isChecked();
    bool Is_display = ui->checkBox_display->isChecked();
   emit createpie(num,title,text,Is_checked,Is_title,Is_display);
}


void Build_Page::on_checkBox_title_toggled(bool checked)
{
    if(checked == false)
    {
        ui->le_title->clear();
        ui->le_title->setEnabled(false);
    }
    else if(checked == true)
    {
        ui->le_title->setEnabled(true);
    }
}
