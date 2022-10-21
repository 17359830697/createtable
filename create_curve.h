#ifndef CREATE_CURVE_H
#define CREATE_CURVE_H

#include <QWidget>

namespace Ui {
class create_curve;
}

class create_curve : public QWidget
{
    Q_OBJECT

public:
    explicit create_curve(QWidget *parent = nullptr);
    ~create_curve();
signals:
    void Create_curve(QString title,int num,bool Is_title,bool Is_pos,QString X_name,QString Y_name,double X_min,
                      double X_max,double Y_min,double Y_max,QString text,QString data );


private slots:
    void on_btn_create_clicked();

    void on_btn_cancel_clicked();

private:
    Ui::create_curve *ui;
};

#endif // CREATE_CURVE_H
