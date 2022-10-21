#ifndef CREATE_DONUT_H
#define CREATE_DONUT_H

#include <QWidget>

namespace Ui {
class create_donut;
}

class create_donut : public QWidget
{
    Q_OBJECT

public:
    explicit create_donut(QWidget *parent = nullptr);
    ~create_donut();
signals:
    void createdonut(int n,double inner,QString title,QString text,bool is_checked,bool Is_title,bool Is_display);

private slots:
    void on_btn_create_clicked();

    void on_btn_cancel_clicked();

private:
    Ui::create_donut *ui;
};

#endif // CREATE_DONUT_H
