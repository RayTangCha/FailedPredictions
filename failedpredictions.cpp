#include "failedpredictions.h"
#include "ui_failedpredictions.h"
#include <QtCharts/QChartView>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QPieSeries>
#include <QLineSeries>
#include <QMessageBox>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <cmath>
long long datax[100000]={},datay[100000]={},curnextdata=0;
long double funca,funcb;
bool m_bPressed=false;
QPoint m_point;

void LeastSquare(){
       double t1=0, t2=0, t3=0, t4=0;
       int cnt=0;
       for(int i=0;datax[i];i++){
            t1+=datax[i]*datax[i];
            t2+=datax[i];
            t3+=datax[i]*datay[i];
            t4+=datay[i];
            cnt++;
        }
        funca=(t3*cnt-t2*t4)/(t1*cnt-t2*t2);
        funcb=(t1*t4-t2*t3)/(t1*cnt-t2*t2);
}

void FailedPredictions::refreshpic(){
    QChart *chart = new QChart();
    QScatterSeries *scatterSeries1 = new QScatterSeries(chart);
    chart->setTitle("Data View");//name
    //add series
    scatterSeries1->setName("Data");
    scatterSeries1->setPointLabelsFormat("@yPoint");
    scatterSeries1->setPointLabelsVisible(1);
    scatterSeries1->setMarkerSize(10);
    for(int cnt=0;datax[cnt];cnt++)
        scatterSeries1->append(datax[cnt],datay[cnt]);
    chart->addSeries(scatterSeries1);
    //add axis
    chart->createDefaultAxes();
    //add to widget
    QChartView *chartView;
    chartView = new QChartView(chart);
    chartView->setRubberBand(QChartView::HorizontalRubberBand);
    chartView->setRenderHint(QPainter::Antialiasing);
    ui->verticalLayout->addWidget(chartView);
}

void FailedPredictions::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton){
        m_bPressed = true;
        m_point = event->pos();
    }
}

void FailedPredictions::mouseReleaseEvent(QMouseEvent *event){
    Q_UNUSED(event);
    m_bPressed = false;
}

void FailedPredictions::mouseMoveEvent(QMouseEvent *event){
    if (m_bPressed)
        move(event->pos() - m_point + pos());
}

FailedPredictions::FailedPredictions(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FailedPredictions)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    QChart *chart = new QChart();
    chart->setTitle("Data View");
    chart->setAnimationOptions(QChart::AllAnimations);
    //add axis
    QValueAxis *axisX;
    QValueAxis *axisY;
    axisX = new QValueAxis;
    axisX->setRange(0,50);
    axisX->setTitleText("X Value");
    axisY = new QValueAxis;
    axisY->setRange(0,50);
    axisY->setTitleText("Y Value");
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    //add to widget
    QChartView *chartView;
    chartView = new QChartView(chart);
    ui->verticalLayout->addWidget(chartView);
}

FailedPredictions::~FailedPredictions()
{
    delete ui;
}


void FailedPredictions::on_commandLinkButton_clicked()
{
    QApplication::exit();
}


void FailedPredictions::on_pushButton_clicked()
{
    LeastSquare();
    ui->label_7->setText("y="+QString::number((double)funca)+"x+"+QString::number((double)funcb));
    QLayoutItem *child;
    while ((child=ui->verticalLayout->takeAt(0))!=0){
        if(child->widget()) child->widget()->setParent(NULL);
        delete child;
    }
    int highscale=*std::max_element(datax,datax+100000),lowscale=*std::min_element(datax,datax+100000);
    QChart *chart = new QChart();
    QScatterSeries *scatterSeries1 = new QScatterSeries(chart);
    QLineSeries *lineSeries1 = new QLineSeries(chart);
    chart->setTitle("Data View");//name
    //add series
    scatterSeries1->setName("Data");
    scatterSeries1->setPointLabelsFormat("@yPoint");
    scatterSeries1->setPointLabelsVisible(1);
    scatterSeries1->setMarkerSize(10);
    lineSeries1->setName("Data");
    lineSeries1->setPointLabelsFormat("@yPoint");
    lineSeries1->setPointLabelsVisible(1);
    lineSeries1->setMarkerSize(10);
    for(int cnt=0;datax[cnt];cnt++)
        scatterSeries1->append(datax[cnt],datay[cnt]);
    lineSeries1->append(lowscale,funcb+funca*lowscale);
    lineSeries1->append(highscale,funcb+funca*highscale);
    chart->addSeries(scatterSeries1);
    chart->addSeries(lineSeries1);
    //add axis
    chart->createDefaultAxes();
    //add to widget
    QChartView *chartView;
    chartView = new QChartView(chart);
    chartView->setRubberBand(QChartView::HorizontalRubberBand);
    chartView->setRenderHint(QPainter::Antialiasing);
    ui->verticalLayout->addWidget(chartView);
}


void FailedPredictions::on_pushButton_4_clicked()
{
    datax[curnextdata]=ui->lineEdit->text().toInt();
    datay[curnextdata++]=ui->lineEdit_2->text().toInt();
    ui->listWidget->addItem("("+ui->lineEdit->text()+","+ui->lineEdit_2->text()+")");
    ui->listWidget_2->addItem(QString::number(curnextdata-1));
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lcdNumber->display(ui->lcdNumber->intValue()+1);
    QLayoutItem *child;
    while ((child=ui->verticalLayout->takeAt(0))!=0){
        if(child->widget()) child->widget()->setParent(NULL);
        delete child;
    }
    int tmpcnt=0,cnt=0;
    for(;datax[cnt];cnt++)
        tmpcnt+=datax[cnt];
    ui->label_8->setText("Average Number:"+QString::number(tmpcnt/cnt));
    refreshpic();
}

void FailedPredictions::on_commandLinkButton_2_clicked()
{
    ShowWindow(GetForegroundWindow(),SW_MINIMIZE);
}


void FailedPredictions::on_pushButton_2_clicked()
{
    ui->lcdNumber->display(0);
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    while(curnextdata>=0){
        ui->listWidget->takeItem(curnextdata);
        datax[curnextdata]=0;
        datay[curnextdata--]=0;
    }
    QLayoutItem *child;
    while ((child=ui->verticalLayout->takeAt(0))!=0){
        if(child->widget()) child->widget()->setParent(NULL);
        delete child;
    }
    refreshpic();
    ui->label_8->setText("Average Number:0");
}


void FailedPredictions::on_pushButton_6_clicked()
{
    int tmpcnt=0,cnt=0;
    for(;datax[cnt];cnt++)
        tmpcnt+=datax[cnt];
    tmpcnt/=cnt;
    QLayoutItem *child;
    while ((child=ui->verticalLayout->takeAt(0))!=0){
        if(child->widget()) child->widget()->setParent(NULL);
        delete child;
    }
    QChart *chart = new QChart();
    QScatterSeries *scatterSeries1 = new QScatterSeries(chart);
    QScatterSeries *scatterSeries2 = new QScatterSeries(chart);
    chart->setTitle("Data View");
    //add series
    scatterSeries1->setName("Above Average");
    scatterSeries1->setPointLabelsFormat("@yPoint");
    scatterSeries1->setPointLabelsVisible(1);
    scatterSeries1->setMarkerSize(10);
    scatterSeries2->setName("Below Average");
    scatterSeries2->setPointLabelsFormat("@yPoint");
    scatterSeries2->setPointLabelsVisible(1);
    scatterSeries2->setMarkerSize(10);
    for(int cnt=0;datax[cnt];cnt++){
        if(datax[cnt]>=tmpcnt)scatterSeries1->append(datay[cnt],datax[cnt]);
        else scatterSeries2->append(datax[cnt],datay[cnt]);
    }
    chart->addSeries(scatterSeries1);
    chart->addSeries(scatterSeries2);
    //add axis
    chart->createDefaultAxes();
    //add to widget
    QChartView *chartView;
    chartView = new QChartView(chart);
    chartView->setRubberBand(QChartView::HorizontalRubberBand);
    chartView->setRenderHint(QPainter::Antialiasing);
    ui->verticalLayout->addWidget(chartView);
}


void FailedPredictions::on_pushButton_3_clicked()
{
    int tmpcnt=0,cnt=0;
    for(;datax[cnt];cnt++)
        tmpcnt+=datax[cnt];
    tmpcnt/=cnt;
    QLayoutItem *child;
    while ((child=ui->verticalLayout->takeAt(0))!=0){
        if(child->widget()) child->widget()->setParent(NULL);
        delete child;
    }
    QChart *chart = new QChart();
    QScatterSeries *scatterSeries1 = new QScatterSeries(chart);
    QScatterSeries *scatterSeries2 = new QScatterSeries(chart);
    QScatterSeries *scatterSeries3 = new QScatterSeries(chart);
    chart->setTitle("Data View");
    //add series
    scatterSeries1->setName("Above Average");
    scatterSeries1->setPointLabelsFormat("@yPoint");
    scatterSeries1->setPointLabelsVisible(1);
    scatterSeries1->setMarkerSize(10);
    scatterSeries2->setName("Below Average");
    scatterSeries2->setPointLabelsFormat("@yPoint");
    scatterSeries2->setPointLabelsVisible(1);
    scatterSeries2->setMarkerSize(10);
    scatterSeries3->setName("This dot");
    scatterSeries3->setPointLabelsFormat("@yPoint");
    scatterSeries3->setPointLabelsVisible(1);
    scatterSeries3->setMarkerSize(10);
    for(int cnt=0;datax[cnt];cnt++){
        if(datax[cnt]>=tmpcnt)scatterSeries1->append(datax[cnt],datay[cnt]);
        else scatterSeries2->append(datax[cnt],datay[cnt]);
    }
    scatterSeries3->append(ui->lineEdit_2->text().toInt(),ui->lineEdit->text().toInt());
    chart->addSeries(scatterSeries1);
    chart->addSeries(scatterSeries2);
    chart->addSeries(scatterSeries3);
    //add axis
    chart->createDefaultAxes();
    //add to widget
    QChartView *chartView;
    chartView = new QChartView(chart);
    chartView->setRubberBand(QChartView::HorizontalRubberBand);
    chartView->setRenderHint(QPainter::Antialiasing);
    ui->verticalLayout->addWidget(chartView);
}


void FailedPredictions::on_pushButton_5_clicked()
{
    int tmpcnt=0,cnt=0;
    for(;datax[cnt];cnt++)
        tmpcnt+=datax[cnt];
    tmpcnt/=cnt;
    QLayoutItem *child;
    while ((child=ui->verticalLayout->takeAt(0))!=0){
        if(child->widget()) child->widget()->setParent(NULL);
        delete child;
    }
    QChart *chart = new QChart();
    QScatterSeries *scatterSeries1 = new QScatterSeries(chart);
    QScatterSeries *scatterSeries2 = new QScatterSeries(chart);
    QScatterSeries *scatterSeries3 = new QScatterSeries(chart);
    chart->setTitle("Data View");
    //add series
    scatterSeries1->setName("Above Average");
    scatterSeries1->setPointLabelsFormat("@yPoint");
    scatterSeries1->setPointLabelsVisible(1);
    scatterSeries1->setMarkerSize(10);
    scatterSeries2->setName("Below Average");
    scatterSeries2->setPointLabelsFormat("@yPoint");
    scatterSeries2->setPointLabelsVisible(1);
    scatterSeries2->setMarkerSize(10);
    scatterSeries3->setName("This dot");
    scatterSeries3->setPointLabelsFormat("@yPoint");
    scatterSeries3->setPointLabelsVisible(1);
    scatterSeries3->setMarkerSize(10);
    for(int cnt=0;datax[cnt];cnt++){
        if(datax[cnt]>=tmpcnt)scatterSeries1->append(datax[cnt],datay[cnt]);
        else scatterSeries2->append(datax[cnt],datay[cnt]);
    }
    scatterSeries3->append(datax[ui->lineEdit_3->text().toInt()],datay[ui->lineEdit_3->text().toInt()]);
    chart->addSeries(scatterSeries1);
    chart->addSeries(scatterSeries2);
    chart->addSeries(scatterSeries3);
    //add axis
    chart->createDefaultAxes();
    //add to widget
    QChartView *chartView;
    chartView = new QChartView(chart);
    chartView->setRubberBand(QChartView::HorizontalRubberBand);
    chartView->setRenderHint(QPainter::Antialiasing);
    ui->verticalLayout->addWidget(chartView);
}


void FailedPredictions::on_pushButton_7_clicked()
{
    int tmpcnt=0,cnt=0;
    for(;datax[cnt];cnt++)
        tmpcnt+=datax[cnt];
    tmpcnt/=cnt;
    QLayoutItem *child;
    while ((child=ui->verticalLayout->takeAt(0))!=0){
        if(child->widget()) child->widget()->setParent(NULL);
        delete child;
    }
    QChart *chart = new QChart();
    QScatterSeries *scatterSeries1 = new QScatterSeries(chart);
    QScatterSeries *scatterSeries2 = new QScatterSeries(chart);
    QScatterSeries *scatterSeries3 = new QScatterSeries(chart);
    chart->setTitle("Data View");
    //add series
    scatterSeries1->setName("Above Average");
    scatterSeries1->setPointLabelsFormat("@yPoint");
    scatterSeries1->setPointLabelsVisible(1);
    scatterSeries1->setMarkerSize(10);
    scatterSeries2->setName("Below Average");
    scatterSeries2->setPointLabelsFormat("@yPoint");
    scatterSeries2->setPointLabelsVisible(1);
    scatterSeries2->setMarkerSize(10);
    scatterSeries3->setName("Zero");
    scatterSeries3->setPointLabelsFormat("@yPoint");
    scatterSeries3->setPointLabelsVisible(1);
    scatterSeries3->setMarkerSize(10);
    for(int cnt=0;datax[cnt];cnt++){
        if(datax[cnt]>=tmpcnt)scatterSeries1->append(datax[cnt],datay[cnt]);
        else scatterSeries2->append(datax[cnt],datay[cnt]);
    }
    scatterSeries3->append(0,0);
    chart->addSeries(scatterSeries1);
    chart->addSeries(scatterSeries2);
    chart->addSeries(scatterSeries3);
    //add axis
    chart->createDefaultAxes();
    //add to widget
    QChartView *chartView;
    chartView = new QChartView(chart);
    chartView->setRubberBand(QChartView::HorizontalRubberBand);
    chartView->setRenderHint(QPainter::Antialiasing);
    ui->verticalLayout->addWidget(chartView);
}


void FailedPredictions::on_pushButton_8_clicked()
{
    QLayoutItem *child;
    while ((child=ui->verticalLayout->takeAt(0))!=0){
        if(child->widget()) child->widget()->setParent(NULL);
        delete child;
    }
    QChart *chart = new QChart();
    QBarSeries *barSeries1 = new QBarSeries(chart);
    chart->setTitle("Data View");//name
    //add series
    barSeries1->setName("Data");
    QBarSet *set0;
    set0 = new QBarSet("Data");
    for(int cnt=0;datax[cnt];cnt++)
        *set0<<datax[cnt];
    barSeries1->append(set0);
    chart->addSeries(barSeries1);
    //add axis
    chart->createDefaultAxes();
    //add to widget
    QChartView *chartView;
    chartView = new QChartView(chart);
    chartView->setRubberBand(QChartView::HorizontalRubberBand);
    chartView->setRenderHint(QPainter::Antialiasing);
    ui->verticalLayout->addWidget(chartView);
}


void FailedPredictions::on_pushButton_9_clicked()
{
    QLayoutItem *child;
    while ((child=ui->verticalLayout->takeAt(0))!=0){
        if(child->widget()) child->widget()->setParent(NULL);
        delete child;
    }
    QChart *chart = new QChart();
    QLineSeries *lineSeries1 = new QLineSeries(chart);
    chart->setTitle("Data View");//name
    //add series
    lineSeries1->setName("Data");
    lineSeries1->setPointLabelsFormat("@yPoint");
    lineSeries1->setPointLabelsVisible(1);
    lineSeries1->setMarkerSize(10);
    for(int cnt=0;datax[cnt];cnt++)
        lineSeries1->append(datax[cnt],datay[cnt]);
    chart->addSeries(lineSeries1);
    //add axis
    chart->createDefaultAxes();
    //add to widget
    QChartView *chartView;
    chartView = new QChartView(chart);
    chartView->setRubberBand(QChartView::HorizontalRubberBand);
    chartView->setRenderHint(QPainter::Antialiasing);
    ui->verticalLayout->addWidget(chartView);
}

void FailedPredictions::on_pushButton_10_clicked()
{
    QLayoutItem *child;
    while ((child=ui->verticalLayout->takeAt(0))!=0){
        if(child->widget()) child->widget()->setParent(NULL);
        delete child;
    }
    QChart *chart = new QChart();
    QPieSeries *pieSeries = new QPieSeries(chart);
    chart->setTitle("Data View");//name
    //add series
    pieSeries->setName("Data");
    int tmpcnt=0,cnt=0,aboveaver=0;
    for(;datax[cnt];cnt++)
        tmpcnt+=datax[cnt];
    tmpcnt/=cnt;
    for(int i=0;datax[i];i++)
        if(datax[i]>tmpcnt)
            aboveaver++;
    pieSeries->append("Above Average",aboveaver*100/cnt);
    pieSeries->append("Below Average",100-aboveaver*100/cnt);
    chart->addSeries(pieSeries);
    //add axis
    chart->createDefaultAxes();
    //add to widget
    QChartView *chartView;
    chartView = new QChartView(chart);
    chartView->setRubberBand(QChartView::HorizontalRubberBand);
    chartView->setRenderHint(QPainter::Antialiasing);
    ui->verticalLayout->addWidget(chartView);
}

void FailedPredictions::on_pushButton_15_clicked()
{
    for(int cnt=ui->lineEdit_4->text().toInt();datax[cnt+1];cnt++){
        datax[cnt]=datax[cnt+1];
        datay[cnt]=datay[cnt+1];
    }
    ui->listWidget->takeItem(ui->lineEdit_4->text().toInt());
    ui->listWidget_2->takeItem(ui->lineEdit_4->text().toInt());
    ui->listWidget->clear();
    for(int cnt=0;datax[cnt];cnt++)
        ui->listWidget_2->addItem(QString::number(cnt));
    QLayoutItem *child;
    while ((child=ui->verticalLayout->takeAt(0))!=0){
        if(child->widget()) child->widget()->setParent(NULL);
        delete child;
    }
    refreshpic();
}


void FailedPredictions::on_pushButton_16_clicked()
{
    std::swap(datax[ui->lineEdit_4->text().toInt()],datay[ui->lineEdit_4->text().toInt()]);
    QLayoutItem *child;
    while ((child=ui->verticalLayout->takeAt(0))!=0){
        if(child->widget()) child->widget()->setParent(NULL);
        delete child;
    }
    refreshpic();
    ui->listWidget->clear();
    for(int cnt=0;datax[cnt];cnt++)
        ui->listWidget->addItem("("+QString::number(datax[cnt])+","+QString::number(datay[cnt])+")");
    int tmpcnt=0,cnt=0;
    for(;datax[cnt];cnt++)
        tmpcnt+=datax[cnt];
    ui->label_8->setText("Average Number:"+QString::number(tmpcnt/cnt));
}


void FailedPredictions::on_pushButton_17_clicked()
{
    datax[ui->lineEdit_5->text().toInt()]=datax[ui->lineEdit_4->text().toInt()];
    datay[ui->lineEdit_5->text().toInt()]=datay[ui->lineEdit_4->text().toInt()];
    QLayoutItem *child;
    while ((child=ui->verticalLayout->takeAt(0))!=0){
        if(child->widget()) child->widget()->setParent(NULL);
        delete child;
    }
    refreshpic();
    ui->listWidget->clear();
    for(int cnt=0;datax[cnt];cnt++)
        ui->listWidget->addItem("("+QString::number(datax[cnt])+","+QString::number(datay[cnt])+")");
    int tmpcnt=0,cnt=0;
    for(;datax[cnt];cnt++)
        tmpcnt+=datax[cnt];
    ui->label_8->setText("Average Number:"+QString::number(tmpcnt/cnt));
}


void FailedPredictions::on_pushButton_18_clicked()
{
    datax[ui->lineEdit_4->text().toInt()]=ui->lineEdit_6->text().toInt();
    QLayoutItem *child;
    while ((child=ui->verticalLayout->takeAt(0))!=0){
        if(child->widget()) child->widget()->setParent(NULL);
        delete child;
    }
    refreshpic();
    ui->listWidget->clear();
    for(int cnt=0;datax[cnt];cnt++)
        ui->listWidget->addItem("("+QString::number(datax[cnt])+","+QString::number(datay[cnt])+")");
    int tmpcnt=0,cnt=0;
    for(;datax[cnt];cnt++)
        tmpcnt+=datax[cnt];
    ui->label_8->setText("Average Number:"+QString::number(tmpcnt/cnt));
}


void FailedPredictions::on_pushButton_19_clicked()
{
    datay[ui->lineEdit_4->text().toInt()]=ui->lineEdit_6->text().toInt();
    QLayoutItem *child;
    while ((child=ui->verticalLayout->takeAt(0))!=0){
        if(child->widget()) child->widget()->setParent(NULL);
        delete child;
    }
    refreshpic();
    ui->listWidget->clear();
    for(int cnt=0;datax[cnt];cnt++)
        ui->listWidget->addItem("("+QString::number(datax[cnt])+","+QString::number(datay[cnt])+")");
    int tmpcnt=0,cnt=0;
    for(;datax[cnt];cnt++)
        tmpcnt+=datax[cnt];
    ui->label_8->setText("Average Number:"+QString::number(tmpcnt/cnt));
}


void FailedPredictions::on_pushButton_20_clicked()
{
    srand(clock());
    datax[ui->lineEdit_4->text().toInt()]=rand()%(*std::max_element(datax,datax+100000)-*std::min_element(datax,datax+100000))+*std::min_element(datax,datax+100000);
    QLayoutItem *child;
    while ((child=ui->verticalLayout->takeAt(0))!=0){
        if(child->widget()) child->widget()->setParent(NULL);
        delete child;
    }
    refreshpic();
    ui->listWidget->clear();
    for(int cnt=0;datax[cnt];cnt++)
        ui->listWidget->addItem("("+QString::number(datax[cnt])+","+QString::number(datay[cnt])+")");
    int tmpcnt=0,cnt=0;
    for(;datax[cnt];cnt++)
        tmpcnt+=datax[cnt];
    ui->label_8->setText("Average Number:"+QString::number(tmpcnt/cnt));
}


void FailedPredictions::on_pushButton_21_clicked()
{
    QLayoutItem *child;
    while ((child=ui->verticalLayout->takeAt(0))!=0){
        if(child->widget()) child->widget()->setParent(NULL);
        delete child;
    }
    QChart *chart = new QChart();
    QScatterSeries *scatterSeries1 = new QScatterSeries(chart);
    QScatterSeries *scatterSeries2 = new QScatterSeries(chart);
    QScatterSeries *scatterSeries3 = new QScatterSeries(chart);
    chart->setTitle("Data View");
    //add series
    scatterSeries1->setName("Above Criteria");
    scatterSeries1->setPointLabelsFormat("@yPoint");
    scatterSeries1->setPointLabelsVisible(1);
    scatterSeries1->setMarkerSize(10);
    scatterSeries2->setName("Below Criteria");
    scatterSeries2->setPointLabelsFormat("@yPoint");
    scatterSeries2->setPointLabelsVisible(1);
    scatterSeries2->setMarkerSize(10);
    scatterSeries3->setName("Criteria");
    scatterSeries3->setPointLabelsFormat("@yPoint");
    scatterSeries3->setPointLabelsVisible(1);
    scatterSeries3->setMarkerSize(10);
    for(int cnt=0;datax[cnt];cnt++){
        if(datax[cnt]>=datax[ui->lineEdit_4->text().toInt()])scatterSeries1->append(datax[cnt],datay[cnt]);
        else scatterSeries2->append(datax[cnt],datay[cnt]);
    }
    scatterSeries3->append(datax[ui->lineEdit_4->text().toInt()],datay[ui->lineEdit_4->text().toInt()]);
    chart->addSeries(scatterSeries1);
    chart->addSeries(scatterSeries2);
    chart->addSeries(scatterSeries3);
    //add axis
    chart->createDefaultAxes();
    //add to widget
    QChartView *chartView;
    chartView = new QChartView(chart);
    chartView->setRubberBand(QChartView::HorizontalRubberBand);
    chartView->setRenderHint(QPainter::Antialiasing);
    ui->verticalLayout->addWidget(chartView);
}


void FailedPredictions::on_pushButton_22_clicked()
{
    datax[ui->lineEdit_4->text().toInt()]=abs(datax[ui->lineEdit_4->text().toInt()]);
    datay[ui->lineEdit_4->text().toInt()]=abs(datay[ui->lineEdit_4->text().toInt()]);
    QLayoutItem *child;
    while ((child=ui->verticalLayout->takeAt(0))!=0){
        if(child->widget()) child->widget()->setParent(NULL);
        delete child;
    }
    refreshpic();
    ui->listWidget->clear();
    for(int cnt=0;datax[cnt];cnt++)
        ui->listWidget->addItem("("+QString::number(datax[cnt])+","+QString::number(datay[cnt])+")");
    int tmpcnt=0,cnt=0;
    for(;datax[cnt];cnt++)
        tmpcnt+=datax[cnt];
    ui->label_8->setText("Average Number:"+QString::number(tmpcnt/cnt));
}

