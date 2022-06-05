#ifndef FAILEDPREDICTIONS_H
#define FAILEDPREDICTIONS_H

#include <QtWidgets/QWidget>
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

private slots:
    void on_commandLinkButton_clicked();

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_commandLinkButton_2_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_5_clicked();


private:
    Ui::FailedPredictions *ui;
};
#endif // FAILEDPREDICTIONS_H
