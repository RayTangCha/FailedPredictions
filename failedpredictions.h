#ifndef FAILEDPREDICTIONS_H
#define FAILEDPREDICTIONS_H

#include <QtCharts>

QT_BEGIN_NAMESPACE
namespace Ui { class FailedPredictions; }
QT_END_NAMESPACE

class FailedPredictions : public QMainWindow
{
    Q_OBJECT

public:
    FailedPredictions(QWidget *parent = nullptr);
    ~FailedPredictions();
    void refreshpic();
    void mouseReleaseEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);


private slots:
    void on_commandLinkButton_clicked();

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_commandLinkButton_2_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_19_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_21_clicked();

    void on_pushButton_22_clicked();

private:
    Ui::FailedPredictions *ui;
};
#endif // FAILEDPREDICTIONS_H
