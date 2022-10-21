#ifndef CREATE_POLYLINE_H
#define CREATE_POLYLINE_H

#include <QWidget>

namespace Ui {
class create_polyline;
}

class create_polyline : public QWidget
{
    Q_OBJECT

public:
    explicit create_polyline(QWidget *parent = nullptr);
    ~create_polyline();
signals:
    void Create_polyline(QString title,int num,bool Is_title,bool Is_pos,QString X_name,QString Y_name,double X_min,
                      double X_max,double Y_min,double Y_max,QString text,QString data);

private slots:
    void on_btn_create_clicked();

    void on_btn_cancel_clicked();

private:
    Ui::create_polyline *ui;
};

#endif // CREATE_POLYLINE_H
