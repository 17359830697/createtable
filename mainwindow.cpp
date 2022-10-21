#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("图表生成器");
     m_chart = new QChart();
    m_chartView = new QChartView(ui->centralwidget);

    colorlist = {QColor(51,102,204),
                QColor(153,204,51),
                QColor(153,51,255),
                 QColor(204,102,153),
                QColor(255,153,51),
                QColor(0,153,153),
                 QColor(204,51,153),
                QColor(204,204,255)};

    //饼图
    connect(&bp,SIGNAL(createpie(int,QString,QString,bool,bool,bool)),
            this,SLOT(CreatePie(int,QString,QString,bool,bool,bool)));
    //柱状图
    connect(&cb,SIGNAL(create_bargraph(QString,QString,QString,int,bool,QString,QString,QString,int,int)),
            this,SLOT(CreateBargraph(QString,QString,QString,int,bool,QString,QString,QString,int,int)));
    //曲线图
    connect(&cc,SIGNAL(Create_curve(QString,int,bool,bool,QString,QString,double,double,double,double,QString,QString)),
            this,SLOT(CreateCurve(QString,int,bool,bool,QString,QString,double,double,double,double,QString,QString)));
    //折线图
    connect(&cp,SIGNAL(Create_polyline(QString,int,bool,bool,QString,QString,double,double,double,double,QString,QString)),
            this,SLOT(CreatePolyline(QString,int,bool,bool,QString,QString,double,double,double,double,QString,QString)));
    //面积图
    connect(&ca,SIGNAL(Create_area(QString,QString,bool,QString,QString,double,double,double,double,QString)),
            this,SLOT(CreateArea(QString,QString,bool,QString,QString,double,double,double,double,QString)));
    //散点图
    connect(&cs,SIGNAL(Create_scatter(QString,int,bool,bool,QString,QString,double,double,double,double,QString,QString)),
            this,SLOT(CreateScatter(QString,int,bool,bool,QString,QString,double,double,double,double,QString,QString)));
    //圆环图
    connect(&cd,SIGNAL(createdonut(int,double,QString,QString,bool,bool,bool)),
            this,SLOT(CreateDonut(int,double,QString,QString,bool,bool,bool)));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Clear()
{
    if(m_chart!=NULL)
    {
        delete m_chart;
        m_chart = new QChart();
    }
    if(m_chartView!=NULL)
    {
        delete m_chartView;
        m_chartView = new QChartView(ui->centralwidget);
    }
}

void MainWindow::Legend()//设置说明样式
{
    //修改说明样例
    m_chart->legend()->setVisible(true);
    m_chart->legend()->setAlignment(Qt::AlignBottom);//底部对齐
    m_chart->legend()->setBackgroundVisible(true);//设置背景是否可视
    m_chart->legend()->setAutoFillBackground(true);//设置背景自动填充
    m_chart->legend()->setColor(QColor(222,233,251));//设置颜色
    m_chart->legend()->setLabelColor(QColor(0,100,255));//设置标签颜色
    m_chart->legend()->setFont(QFont("微软雅黑",15));
}

void MainWindow::Axis(QAbstractAxis* axisX,QAbstractAxis* axisY,
                      QString Xname,QString Yname)//设置坐标轴样式
{
    //设置坐标轴样式
    axisX->setTitleFont(QFont("楷体",15));//坐标轴名称
    axisY->setTitleFont(QFont("楷体",15));
    axisX->setLabelsFont(QFont("楷体",14));//坐标轴数值
    axisY->setLabelsFont(QFont("楷体",14));
    axisX->setLabelsColor(colorlist.at(5));
    axisX->setTitleText(Xname);
    axisY->setLabelsColor(colorlist.at(6));
    axisY->setTitleText(Yname);
}

void MainWindow::Show()//视图显示
{
    //图表添加到视图
    m_chartView->setRenderHints(QPainter::Antialiasing);//反锯齿
    m_chartView->setChart(m_chart);
    m_chartView->show();
    m_chartView->resize(ui->centralwidget->width(),ui->centralwidget->height());
}

void MainWindow::Title(QString title)//标题样式
{
    m_chart->setTitleBrush(QBrush(QColor(0,0,255)));//设置标题Brush
       m_chart->setTitleFont(QFont("微软雅黑",19));//设置标题字体
       m_chart->setTitle(title);
}

void MainWindow::CreatePie(int num,QString title,QString text,bool Is_checked,bool Is_title,bool Is_display)
{
    this->Clear();
     QPieSeries *m_pieSeries = new QPieSeries();
    QMap<QString,int> map;
    QMap<QString,double> map_per;
    QStringList list;
    //获取用户输入的标签以及相应占比
    {
        for(int i = 0;i<num;i++)
        {
            QString str = text.section(',',i,i);
            QString example = str.section(' ',0,0);
            int value = str.section(' ',1,1).toUInt();
            map.insert(example,value);
            list.append(example);
        }
    }
    //处理数据,根据用户输入的数值算出相应百分比
    {
        int sum = 0;
        for(int i = 0;i<num;i++)
        {
            sum += map.value(list.at(i)); //算出总数据
        }
        for(int i = 0;i<num;i++)
        {
            double percent = map.value(list.at(i))*1.0/sum * 100;   // 24 30
            map_per.insert(list.at(i),percent);
        }

    }
    //添加标签
    if(Is_display)
    {
        for(int i = 0;i<num;i++)
        {
            QString str = QString(list.at(i) + "%1").arg(QString::number(map_per.value(list.at(i)),'f',1) + "%");
            m_pieSeries->append(str,map_per.value(list.at(i)));
        }
    }
    else
    {
        for(int i = 0;i<num;i++)
        {
            m_pieSeries->append(list.at(i),map_per.value(list.at(i)));
        }
    }


     if(Is_checked) //片标签选项被勾选
     {
         m_pieSeries->setLabelsVisible(true);//设置所有片标签为可见
     }
     m_pieSeries->setUseOpenGL(true);

     //设置颜色
     for(int i = 0;i<num;i++)
     {
         m_pieSeries->slices().at(i)->setColor(colorlist.at(i)); //饼图颜色
         m_pieSeries->slices().at(i)->setLabelColor(colorlist.at(i));//标签颜色
     }
     //设置主题
     m_chart->setTheme(QChart::ChartThemeBlueCerulean);

//     m_chart->setBackgroundBrush(QBrush(colorlist.at(3)));
     //添加系列到QChart
     m_chart->addSeries(m_pieSeries);
     if(Is_title)
     Title(title);//标题样式
      Legend();//说明样例
      Show();//视图显示
}

void MainWindow::CreateBargraph(QString title, QString X_name, QString Y_name,
int num, bool Is_title, QString X_text, QString Data_text,QString Barset,int min,int max)
{
    this->Clear();
    QStringList barsetlist;
    //获取用户输入的系列信息
    for(int i = 0;i<num;i++)  //水果,零食,饮料
    {
        QString barset = Barset.section(',',i,i);
        barsetlist.append(barset);
    }
    //获取用户输入的系列数据 112,150,153,124 145,152,163,123
     QStringList datalist = Data_text.split(' ');
     QBarSeries *series = new QBarSeries();
    //创建系列数据
    for(int i = 0;i<num;i++)
    {
        QList<QString> dlist = datalist.at(i).split(',');
         QBarSet* set = new QBarSet(barsetlist.at(i));
        for(int j = 0;j<dlist.size();j++)
        {
            set->append(dlist.at(j).toDouble());//向系列添加数据
        }
        set->setColor(colorlist.at(i));//设置系列颜色
        series->append(set);
     }
    series->setVisible(true);
     series->setLabelsVisible(true);

     //设置m_chart主题,并将系列添加到m_chart上
     m_chart->setTheme(QChart::ChartThemeLight);//设置白色主题
     m_chart->setDropShadowEnabled(true);//背景阴影
     m_chart->addSeries(series);//添加系列到QChart上

     //创建X轴和Y轴
     QBarCategoryAxis *axisX = new QBarCategoryAxis;
     QStringList X_List = X_text.split(','); //一月,二月,三月,四月
     for(int i = 0;i<X_List.size();i++)
     {
         axisX->append(X_List.at(i));
     }
     QValueAxis *axisY = new QValueAxis;
     //设置Y坐标的范围
     axisY->setRange(min,max);
     axisY->setLabelFormat("%d");//设置数值格式     

     Axis(axisX,axisY,X_name,Y_name);//设置坐标轴样式
     //将坐标添加到图表
     m_chart->setAxisX(axisX,series);
     m_chart->setAxisY(axisY,series);


     if(Is_title) //显示标题勾选
     Title(title);//标题样式
     Legend();//说明样例
     Show();//视图显示


}

void MainWindow::CreateCurve(QString title,int num,bool Is_title,bool Is_pos,QString X_name,QString Y_name,double X_min,
                             double X_max,double Y_min,double Y_max,QString text,QString data )
{
    this->Clear();
    QList<QPointF> plist;
    QStringList namelist = text.split(',');
    //创建X轴和Y轴
    QValueAxis *axisX = new QValueAxis(m_chart);
    axisX->setRange(X_min,X_max);    //默认则坐标为动态计算大小的
    axisX->setLabelFormat("%.2f");
    QValueAxis *axisY = new QValueAxis(m_chart);
    axisY->setRange(Y_min,Y_max);    //默认则坐标为动态计算大小的
     axisY->setLabelFormat("%.2f");

    Axis(axisX,axisY,X_name,Y_name);//设置坐标轴样式

    //20,50 30,60 40,70#30,60 40,45 55,60
    for(int i = 0;i<num;i++)
    {
        QSplineSeries *series1 = new QSplineSeries();//实例化QLineSeries(曲线数据)
        series1->setColor(colorlist.at(i)); //设置曲线颜色
        series1->setName(namelist.at(i)); //设置名字
        series1->setVisible(true);
        series1->setPointLabelsFormat("(@xPoint,@yPoint)");
        series1->setPointLabelsFont(QFont("楷体",12));
        if(Is_pos)
            series1->setPointLabelsVisible(true);
        else
            series1->setPointLabelsVisible(false);

        QString pos = data.section('#',i,i);
        QStringList list = pos.split(' ');
        for(int j = 0;j<list.size();j++)
        {
            double x = list.at(j).section(',',0,0).toDouble();
            double y = list.at(j).section(',',1,1).toDouble();
            series1->append(x,y);
        }
        m_chart->addSeries(series1);//添加系列到QChart上
        m_chart->setAxisX(axisX,series1);
        m_chart->setAxisY(axisY,series1);
    }
        m_chart->setTheme(QChart::ChartThemeBlueNcs);//设置蓝色主题
        m_chart->setDropShadowEnabled(true);//背景阴影
        m_chart->setAutoFillBackground(true);  //设置背景自动填充

        //m_chart->createDefaultAxes();             //或者创建默认轴
       if(Is_title) //显示标题勾选
       Title(title);//标题样式
       Legend();//说明样例
       Show();//视图显示

}

void MainWindow::CreatePolyline(QString title, int num, bool Is_title,bool Is_pos,QString X_name, QString Y_name,
                                double X_min, double X_max, double Y_min, double Y_max, QString text, QString data)
{
    this->Clear();
    QList<QPointF> plist;
    QStringList namelist = text.split(',');
    //创建X轴和Y轴
    QValueAxis *axisX = new QValueAxis;
    axisX->setRange(X_min,X_max);    //默认则坐标为动态计算大小的(会根据数据输入的X,Y最大值确定)
    axisX->setLabelFormat("%.2f");
    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(Y_min,Y_max);    //默认则坐标为动态计算大小的
     axisY->setLabelFormat("%.2f");

     Axis(axisX,axisY,X_name,Y_name);//设置坐标轴样式

    //20,50 30,60 40,70#30,60 40,45 55,60
    for(int i = 0;i<num;i++)
    {
        QLineSeries *series1 = new QLineSeries();//实例化QLineSeries(曲线数据)
        series1->setColor(colorlist.at(i)); //设置曲线颜色
        series1->setName(namelist.at(i)); //设置名字
        series1->setVisible(true);
        series1->setPointLabelsFormat("(@xPoint,@yPoint)");
        series1->setPointLabelsFont(QFont("楷体",12));
        if(Is_pos)
            series1->setPointLabelsVisible(true);
        else
            series1->setPointLabelsVisible(false);

        QString pos = data.section('#',i,i);
        QStringList list = pos.split(' ');
        for(int j = 0;j<list.size();j++)
        {
            double x = list.at(j).section(',',0,0).toDouble();
            double y = list.at(j).section(',',1,1).toDouble();
            series1->append(x,y);
        }
        m_chart->addSeries(series1);//添加系列到QChart上
        m_chart->setAxisX(axisX,series1);
        m_chart->setAxisY(axisY,series1);
    }
    //m_chart->createDefaultAxes();             //或者创建默认轴

        m_chart->setTheme(QChart::ChartThemeBlueNcs);//设置蓝色主题
        m_chart->setDropShadowEnabled(true);//背景阴影
        m_chart->setAutoFillBackground(true);  //设置背景自动填充

        if(Is_title) //显示标题勾选
        Title(title);//标题样式
         Legend();//说明样例
       Show();//视图显示
}

void MainWindow::CreateArea(QString title, QString seriesname, bool Is_title,QString X_name,
                            QString Y_name, double X_min, double X_max, double Y_min, double Y_max, QString data)
{
   this->Clear();
   //25,20 26,21 30,25#25,30 26,27 29,29
   QStringList linelist = data.split('#');
   QSplineSeries* series1 = new QSplineSeries();
   QSplineSeries* series2 = new QSplineSeries();  
   for(int i = 0;i<linelist.size();i++)
   {
       QStringList poslist = linelist.at(i).split(' ');
       for(int j = 0;j<poslist.size();j++)
       {
           double x = poslist.at(j).section(',',0,0).toDouble();
           double y = poslist.at(j).section(',',1,1).toDouble();
           if(i == 0)
           {
               series1->append(x,y);
           }
           else if(i == 1)
           {
               series2->append(x,y);
           }
       }
   }
   QAreaSeries* areaseries = new QAreaSeries(series1,series2);
   areaseries->setName(seriesname);
   QPen pen(0x059605);
   pen.setWidth(4);
   areaseries->setPen(pen);

      m_chart->addSeries(areaseries);
      m_chart->setTheme(QChart::ChartTheme::ChartThemeBlueIcy);

   QValueAxis* axisX = new QValueAxis();
   axisX->setRange(X_min,X_max);

   QValueAxis* axisY = new QValueAxis();
   axisY->setRange(Y_min,Y_max);

   Axis(axisX,axisY,X_name,Y_name);//设置坐标轴样式

   m_chart->setAxisX(axisX,areaseries);
   m_chart->setAxisY(axisY,areaseries);

   if(Is_title) //显示标题勾选
   Title(title);//标题样式
   Legend();//说明样例
   Show();//视图显示

}

void MainWindow::CreateScatter(QString title, int num, bool Is_title, bool Is_pos, QString X_name, QString Y_name,
                               double X_min, double X_max, double Y_min, double Y_max, QString text, QString data)
{
    this->Clear();
    QList<QPointF> plist;
    QStringList namelist = text.split(',');
    //创建X轴和Y轴
    QValueAxis *axisX = new QValueAxis();
    axisX->setRange(X_min,X_max);    //默认则坐标为动态计算大小的
    axisX->setLabelFormat("%.2f");
    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(Y_min,Y_max);    //默认则坐标为动态计算大小的
     axisY->setLabelFormat("%.2f");

    Axis(axisX,axisY,X_name,Y_name);//设置坐标轴样式
    for(int i = 0;i<num;i++)
    {
        QScatterSeries *series1 = new QScatterSeries();//实例化QScatterSeries(散点数据)
        if(i%2==1)
        series1->setMarkerShape(QScatterSeries::MarkerShapeRectangle); //圆形图标
        else
        series1->setMarkerShape(QScatterSeries::MarkerShapeCircle); //矩形图标
        series1->setMarkerSize(15.0); //设置大小
        series1->setName(namelist.at(i)); //设置名字
        series1->setVisible(true);
        series1->setPointLabelsFormat("(@xPoint,@yPoint)");
        series1->setPointLabelsFont(QFont("楷体",12));
        if(Is_pos) //显示坐标
            series1->setPointLabelsVisible(true);
        else
            series1->setPointLabelsVisible(false);
        //20,50 30,60 40,70#30,60 40,45 55,60
        QString pos = data.section('#',i,i);
        QStringList list = pos.split(' ');
        for(int j = 0;j<list.size();j++)
        {
            double x = list.at(j).section(',',0,0).toDouble();
            double y = list.at(j).section(',',1,1).toDouble();
            series1->append(x,y);
        }
        m_chart->addSeries(series1);//添加系列到QChart上
        m_chart->setAxisX(axisX,series1);
        m_chart->setAxisY(axisY,series1);
    }
        m_chart->setTheme(QChart::ChartThemeBlueNcs);//设置蓝色主题
        m_chart->setDropShadowEnabled(true);//背景阴影
        m_chart->setAutoFillBackground(true);  //设置背景自动填充

        //m_chart->createDefaultAxes();             //或者创建默认轴
       if(Is_title) //显示标题勾选
       Title(title);//标题样式
       Legend();//说明样例
       Show();//视图显示

}

void MainWindow::CreateDonut(int num,double inner,QString title, QString text, bool Is_checked, bool Is_title, bool Is_display)
{
    this->Clear();
     QPieSeries *m_pieSeries = new QPieSeries();
     m_pieSeries->setHoleSize(inner);
    QMap<QString,int> map;
    QMap<QString,double> map_per;
    QStringList list;
    //获取用户输入的标签以及相应占比
    {
        for(int i = 0;i<num;i++)
        {
            QString str = text.section(',',i,i);
            QString example = str.section(' ',0,0);
            int value = str.section(' ',1,1).toUInt();
            map.insert(example,value);
            list.append(example);
        }
    }
    //处理数据,根据用户输入的数值算出相应百分比
    {
        int sum = 0;
        for(int i = 0;i<num;i++)
        {
            sum += map.value(list.at(i)); //算出总数据
        }
        for(int i = 0;i<num;i++)
        {
            double percent = map.value(list.at(i))*1.0/sum * 100;   // 24 30
            map_per.insert(list.at(i),percent);
        }
    }
    //添加标签
    if(Is_display)
    {
        for(int i = 0;i<num;i++)
        {
            QString str = QString(list.at(i) + "%1").arg(QString::number(map_per.value(list.at(i)),'f',1) + "%");
            m_pieSeries->append(str,map_per.value(list.at(i)));
        }
    }
    else
    {
        for(int i = 0;i<num;i++)
        {
            m_pieSeries->append(list.at(i),map_per.value(list.at(i)));
        }
    }


     if(Is_checked) //片标签选项被勾选
     {
         m_pieSeries->setLabelsVisible(true);//设置所有片标签为可见
     }
     m_pieSeries->setUseOpenGL(true);

     //设置颜色
     for(int i = 0;i<num;i++)
     {
         m_pieSeries->slices().at(i)->setColor(colorlist.at(i)); //饼图颜色
         m_pieSeries->slices().at(i)->setLabelColor(colorlist.at(i));//标签颜色
     }
     //设置主题
     m_chart->setTheme(QChart::ChartThemeBlueCerulean);

//     m_chart->setBackgroundBrush(QBrush(colorlist.at(3)));
     //添加系列到QChart
     m_chart->addSeries(m_pieSeries);
     if(Is_title)
     Title(title);//标题样式
      Legend();//说明样例
      Show();//视图显示
}


void MainWindow::on_bargraph_triggered()//柱状图
{
    cb.setWindowTitle("创建柱状图");
    cb.show();
}

void MainWindow::on_pie_triggered() //饼图
{

    bp.setWindowTitle("创建饼图");
    bp.show();
}

void MainWindow::on_polyline_triggered()//折线图
{
    cp.setWindowTitle("创建折线图");
    cp.show();
}

void MainWindow::on_curve_triggered()//曲线图
{
    cc.setWindowTitle("创建曲线图");
    cc.show();
}

void MainWindow::on_exit_triggered()//退出
{
    this->close();
}

void MainWindow::on_about_triggered()//关于
{
    QFile file(":/src/prefix/about.txt");
    file.open(QIODevice::ReadOnly);
    QString text = file.readAll();
    QMessageBox::information(this,"关于软件",text,QMessageBox::Ok);
}

void MainWindow::on_area_triggered()//面积图
{
    ca.setWindowTitle("创建面积图");
    ca.show();
}

void MainWindow::on_scatter_triggered()
{
    cs.setWindowTitle("创建散点图");
    cs.show();
}

void MainWindow::on_Light_triggered()//灯光主题
{
    m_chart->setTheme(QChart::ChartThemeLight);
     m_chart->legend()->setFont(QFont("微软雅黑",15));
     m_chart->setTitleFont(QFont("微软雅黑",19));//设置标题字体
}

void MainWindow::on_BlueCerulean_triggered()//天蓝色主题
{
    m_chart->setTheme(QChart::ChartThemeBlueCerulean);
    m_chart->legend()->setFont(QFont("微软雅黑",15));
    m_chart->setTitleFont(QFont("微软雅黑",19));//设置标题字体
}

void MainWindow::on_Dark_triggered()//黑暗
{
    m_chart->setTheme(QChart::ChartThemeDark);
    m_chart->legend()->setFont(QFont("微软雅黑",15));
    m_chart->setTitleFont(QFont("微软雅黑",19));//设置标题字体
}

void MainWindow::on_BrownSand_triggered()//沙棕色主题
{
    m_chart->setTheme(QChart::ChartThemeBrownSand);
    m_chart->legend()->setFont(QFont("微软雅黑",15));
    m_chart->setTitleFont(QFont("微软雅黑",19));//设置标题字体
}

void MainWindow::on_BlueNcs_triggered()//蓝色主题
{
    m_chart->setTheme(QChart::ChartThemeBlueNcs);
    m_chart->legend()->setFont(QFont("微软雅黑",15));
    m_chart->setTitleFont(QFont("微软雅黑",19));//设置标题字体
}

void MainWindow::on_HighContrast_triggered()//高对比度主题
{
    m_chart->setTheme(QChart::ChartThemeHighContrast);
    m_chart->legend()->setFont(QFont("微软雅黑",15));
    m_chart->setTitleFont(QFont("微软雅黑",19));//设置标题字体
}

void MainWindow::on_BlueIcy_triggered()//冰蓝色主题
{
    m_chart->setTheme(QChart::ChartThemeBlueIcy);
    m_chart->legend()->setFont(QFont("微软雅黑",15));
    m_chart->setTitleFont(QFont("微软雅黑",19));//设置标题字体
}

void MainWindow::on_Qt_triggered()//Qt主题
{
    m_chart->setTheme(QChart::ChartThemeQt);
    m_chart->legend()->setFont(QFont("微软雅黑",15));
    m_chart->setTitleFont(QFont("微软雅黑",19));//设置标题字体
}

void MainWindow::on_doughont_triggered()//圆环图
{
    cd.setWindowTitle("创建圆环图");
    cd.show();
}

void MainWindow::on_save_triggered() //保存
{
    QString path = QFileDialog::getSaveFileName(this,"保存","/home","*.png");
    //"C:/Users/86173/Desktop/home.png"
//    QDesktopWidget *desk = QApplication::desktop();
//    QScreen* screen = QGuiApplication::primaryScreen();
    QPixmap pixmap = QPixmap::grabWidget(ui->centralwidget); //截取窗口内容
    pixmap.save(path); //保存
}
