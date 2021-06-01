#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Calculator; }
QT_END_NAMESPACE

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private slots:
    void on_pushButton_dot_clicked();
    void digit_press();
    void operations();
    void math_operations();
    //void calcResult();
    void on_pushButton_equalSign_clicked();
    void on_pushButton_clearAll_clicked();
    void on_pushButton_clearLast_clicked();

private:
    Ui::Calculator *ui;
};
#endif // CALCULATOR_H
