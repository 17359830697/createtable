#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#pragma execution_character_set("utf-8")
#include <QMainWindow>
#include<QtCharts>
#include<QtCharts/QPieSeries> //饼图系列
#include<QtCharts/QChartView> //图表视图
#include<QtCharts/QBarSet> //柱状图系列
#include<QMap>
#include<QStringList>
#include<QDebug>
#include<QMessageBox>
#include<QFile>
#include<QFileDialog>
#include<QScreen>
#include"create_pie.h"
#include"create_batgraph.h"
#include"create_polyline.h"
#include"create_curve.h"
#include"create_area.h"
#include"create_scatter.h"
#include"create_donut.h"
using namespace QtCharts;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void Clear();//清空m_chart和m_chartview
    void Legend();//设置说明样式
    void Axis(QAbstractAxis* axisX,QAbstractAxis* axisY
             ,QString Xname,QString Yname);//设置坐标轴样式
    void Show();//视图显示
    void Title(QString title);//设置标题样式

private slots:
    void on_bargraph_triggered();

    void on_pie_triggered();
    void CreatePie(int num,QString title,QString text,bool Is_checked,bool Is_title,bool Is_display); //创建饼图
    void CreateBargraph(QString title,QString X_name,QString Y_name,int num,bool Is_title,
                        QString X_text,QString Data_text,QString Barset,int min,int max); //创建柱状图
    void CreateCurve(QString title,int num,bool Is_title,bool Is_pos,QString X_name,QString Y_name,double X_min,
                     double X_max,double Y_min,double Y_max,QString text,QString data);//创建曲线图
    void CreatePolyline(QString title,int num,bool Is_title,bool Is_pos,QString X_name,QString Y_name,double X_min,
                     double X_max,double Y_min,double Y_max,QString text,QString data);//创建折线图
    void CreateArea(QString title,QString seriesname,bool Is_title,QString X_name,
                     QString Y_name,double X_min,double X_max,double Y_min,double Y_max,QString data);//创建面积图
    void CreateScatter(QString title,int num,bool Is_title,bool Is_pos,QString X_name,QString Y_name,double X_min,
                     double X_max,double Y_min,double Y_max,QString text,QString data);//创建曲线图
    void CreateDonut(int num,double inner,QString title,QString text,bool Is_checked,bool Is_title,bool Is_display); //创建圆环图


    void on_polyline_triggered();

    void on_curve_triggered();

    void on_exit_triggered();

    void on_about_triggered();

    void on_area_triggered();


    void on_scatter_triggered();

    void on_Light_triggered();

    void on_BlueCerulean_triggered();

    void on_Dark_triggered();

    void on_BrownSand_triggered();

    void on_BlueNcs_triggered();

    void on_HighContrast_triggered();

    void on_BlueIcy_triggered();

    void on_Qt_triggered();



    void on_doughont_triggered();

    void on_save_triggered();

private:
    Ui::MainWindow *ui;
    QChart *m_chart;
    QChartView *m_chartView;
    QList<QColor> colorlist;//颜色列表
    Build_Page bp; //饼图
    create_batgraph cb; //柱状图
    create_polyline cp; //折线图
    create_curve cc; //曲线图
    create_area ca; //面积图
    create_scatter cs;//散点图
    create_donut cd;//圆环图

};
#endif // MAINWINDOW_H
