#ifndef CREATE_SCATTER_H
#define CREATE_SCATTER_H

#include <QWidget>

namespace Ui {
class create_scatter;
}

class create_scatter : public QWidget
{
    Q_OBJECT

public:
    explicit create_scatter(QWidget *parent = nullptr);
    ~create_scatter();
signals:
    void Create_scatter(QString title,int num,bool Is_title,bool Is_pos,QString X_name,QString Y_name,double X_min,
                      double X_max,double Y_min,double Y_max,QString text,QString data );

private slots:
    void on_btn_create_clicked();

    void on_btn_cancel_clicked();

private:
    Ui::create_scatter *ui;
};

#endif // CREATE_SCATTER_H
