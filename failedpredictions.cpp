#include "failedpredictions.h"
#include "ui_failedpredictions.h"
#include <QtCharts/QChartView>
#include <QtCharts/QScatterSeries>
#include <QMessageBox>
int datax[100000]={},datay[100000]={},curnextdata=0;

void FailedPredictions::refreshpic(){
    QChart *chart = new QChart();
    QScatterSeries *scatterSeries1 = new QScatterSeries(chart);
    chart->setTitle("Data View");
    //add series
    scatterSeries1->setName("Data");
    scatterSeries1->setPointLabelsFormat("@yPoint");
    scatterSeries1->setPointLabelsVisible(1);
    scatterSeries1->setMarkerSize(10);
    for(int cnt=0;datax[cnt];cnt++)
        scatterSeries1->append(datay[cnt],datax[cnt]);
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

}


void FailedPredictions::on_pushButton_4_clicked()
{
    datax[curnextdata]=ui->lineEdit->text().toInt();
    datay[curnextdata++]=ui->lineEdit_2->text().toInt();
    ui->listWidget->addItem("("+ui->lineEdit->text()+","+ui->lineEdit_2->text()+")");
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lcdNumber->display(ui->lcdNumber->intValue()+1);
    QLayoutItem *child;
    while ((child = ui->verticalLayout->takeAt(0)) != 0){
        if(child->widget()) child->widget()->setParent(NULL);
        delete child;
    }
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
}


void FailedPredictions::on_pushButton_5_clicked()
{
    QMessageBox::information(this,"About FailedPredictions","FailedPredictions1.0 (C)Project Contributors");
}
