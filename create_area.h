#ifndef CREATE_AREA_H
#define CREATE_AREA_H

#include <QWidget>

namespace Ui {
class create_area;
}

class create_area : public QWidget
{
    Q_OBJECT

public:
    explicit create_area(QWidget *parent = nullptr);
    ~create_area();
signals:
    void Create_area(QString title,QString seriesname,bool Is_title,QString X_name,
                     QString Y_name,double X_min,double X_max,double Y_min,double Y_max,QString data);

private slots:
    void on_btn_create_clicked();

    void on_btn_cancel_clicked();

private:
    Ui::create_area *ui;
};

#endif // CREATE_AREA_H
