#ifndef BUILD_PAGE_H
#define BUILD_PAGE_H

#include <QWidget>

namespace Ui {
class Build_Page;
}

class Build_Page : public QWidget
{
    Q_OBJECT

public:
    explicit Build_Page(QWidget *parent = nullptr);

    ~Build_Page();

signals:
    void createpie(int n,QString title,QString text,bool is_checked,bool Is_title,bool Is_display);
private slots:
    void on_btn_cancel_clicked();

    void on_btn_create_clicked();

    void on_checkBox_title_toggled(bool checked);

private:
    Ui::Build_Page *ui;

};

#endif // BUILD_PAGE_H
