#ifndef CREATE_BATGRAPH_H
#define CREATE_BATGRAPH_H

#include <QWidget>

namespace Ui {
class create_batgraph;
}

class create_batgraph : public QWidget
{
    Q_OBJECT

public:
    explicit create_batgraph(QWidget *parent = nullptr);
    ~create_batgraph();
signals:
    void create_bargraph(QString title,QString X_name,QString Y_name,int num,bool Is_title,
                         QString X_text,QString Data_text,QString Barset,int min,int max);

private slots:
    void on_btn_cancel_clicked();

    void on_btn_create_clicked();

private:
    Ui::create_batgraph *ui;
};

#endif // CREATE_BATGRAPH_H
