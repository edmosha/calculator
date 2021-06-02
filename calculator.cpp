#include "calculator.h"
#include "./ui_calculator.h"

double numFirst, resultOperations;
bool flagFirst = false, flagPlusOrMinus = false, flagDel = false, flagSign = true;
bool check_plus = false, check_minus = false, check_mult = false, check_div = false, check_percent = false;

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);

    connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digit_press()));
    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digit_press()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digit_press()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digit_press()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digit_press()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digit_press()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digit_press()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digit_press()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digit_press()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digit_press()));

    connect(ui->pushButton_plus_minus, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_xInCube, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_sqrtX, SIGNAL(clicked()), this, SLOT(operations()));

    connect(ui->pushButton_percent, SIGNAL(clicked()), this, SLOT(math_operations()));
    connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(math_operations()));
    connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(math_operations()));
    connect(ui->pushButton_division, SIGNAL(clicked()), this, SLOT(math_operations()));
    connect(ui->pushButton_multiplication, SIGNAL(clicked()), this, SLOT(math_operations()));

    ui->pushButton_plus->setCheckable(true);
    ui->pushButton_minus->setCheckable(true);
    ui->pushButton_division->setCheckable(true);
    ui->pushButton_multiplication->setCheckable(true);
    ui->pushButton_percent->setCheckable(true);
}


Calculator::~Calculator()
{
    delete ui;

}

void Calculator::digit_press() {
    QPushButton *button = (QPushButton *)sender();
    double allNumbers;
    QString stringAllNumbers, showLine;

    if(ui->showResult->text() == "error") {
        ui->showResult->setText("");
    }

    if(flagDel) {
        showLine = ui->showResult->text();
        ui->ShowInput->setText(showLine);
        flagDel = false;

    }

    allNumbers = (ui->showResult->text() + button->text()).toDouble();
    stringAllNumbers = QString::number(allNumbers, 'g', 15);

    ui->showResult->setText(stringAllNumbers);

    showLine = ui->ShowInput->text();
    ui->ShowInput->setText(showLine + button->text());

    flagSign = true;
}

void Calculator::on_pushButton_dot_clicked()
{
    if(!(ui->showResult->text().contains('.'))) {
        ui->showResult->setText(ui->showResult->text() + ".");
        ui->ShowInput->setText(ui->ShowInput->text() + ".");
    }
}

void Calculator::operations() {
    QPushButton *button = (QPushButton *)sender();
    double allNumbers;
    QString stringAllNumbers, allInputNum;

    allInputNum = ui->ShowInput->text();

    if(button->text() == "+/-") {
        allNumbers = (ui->showResult->text()).toDouble();
        allNumbers = allNumbers * -1;
        stringAllNumbers = QString::number(allNumbers, 'g', 15);

        ui->showResult->setText(stringAllNumbers);

        allInputNum = "(" + allInputNum + ")";
        ui->ShowInput->setText("-" + allInputNum);
    }

    else if(button->text() == "x²") {
        allNumbers = (ui->showResult->text()).toDouble();
        allNumbers *= allNumbers;
        stringAllNumbers = QString::number(allNumbers, 'g', 15);

        ui->showResult->setText(stringAllNumbers);

        allInputNum = "(" + allInputNum + ")";
        ui->ShowInput->setText(allInputNum + "²");
    }

    else if(button->text() == "√x") {
        allNumbers = (ui->showResult->text()).toDouble();
        allNumbers = sqrt(allNumbers);
        stringAllNumbers = QString::number(allNumbers, 'g', 15);

        ui->showResult->setText(stringAllNumbers);

        allInputNum = "(" + allInputNum + ")";
        ui->ShowInput->setText("√" + allInputNum);
    }

//    flagDel = false;
}

void Calculator::math_operations()
{
    QPushButton *button = (QPushButton *)sender();
    QString showLine;

    if(flagDel) {
        showLine = ui->showResult->text();
        ui->ShowInput->setText(showLine);
        flagDel = false;
    }

    if (flagFirst) {
        calcResult();
    }
    flagFirst = true;

    button->setChecked(true);

    showLine = ui->ShowInput->text();
    numFirst = ui->showResult->text().toDouble();

    if(flagSign) {
        if(ui->pushButton_plus->isChecked()) {
            ui->ShowInput->setText(showLine + "+");

            check_plus = true;
            flagPlusOrMinus = true;

        } else if(ui->pushButton_minus->isChecked()) {
            ui->ShowInput->setText(showLine + "-");

            check_minus = true;
            flagPlusOrMinus = true;

        } else if(ui->pushButton_division->isChecked()) {
            if(flagPlusOrMinus) {
                ui->ShowInput->setText("(" + showLine+ ")" + "÷");
            } else {
                ui->ShowInput->setText(showLine + "÷");
            }
            check_div = true;
            flagPlusOrMinus = false;

            if(!flagFirst){
               ui->ShowInput->setText(ui->ShowInput->text() + "-");
               ui->showResult->setText("-");
            }

        } else if(ui->pushButton_multiplication->isChecked()) {
            if(flagPlusOrMinus) {
                ui->ShowInput->setText("(" + showLine+ ")" + "×");
            } else {
                ui->ShowInput->setText(showLine + "×");
            }

             check_mult = true;
             flagPlusOrMinus = false;

        } else if(ui->pushButton_percent->isChecked()) {
            if(flagPlusOrMinus) {
                ui->ShowInput->setText("(" + showLine+ ")" + "%");
            } else {
                ui->ShowInput->setText(showLine + "%");
            }

            check_percent = true;
            flagPlusOrMinus = false;
        }
        flagSign = false;
    }
    ui->showResult->setText("");

}

void Calculator::calcResult() {
    double numSecond;
    QString newLine;

    numSecond = ui->showResult->text().toDouble();

    if (check_plus) {

        resultOperations = numFirst + numSecond;
        newLine = QString::number(resultOperations,'g', 15);

        ui->showResult->setText(QString::number(resultOperations,'g', 15));
        ui->pushButton_plus->setChecked(false);

        check_plus = false;

    } else if(check_minus) {
        resultOperations = numFirst - numSecond;
        newLine = QString::number(resultOperations,'g', 15);

        ui->showResult->setText(newLine);
        ui->pushButton_minus->setChecked(false);

        check_minus = false;

    } else if(check_div) {
        if (numSecond == 0) {
            on_pushButton_clearAll_clicked();
            ui->showResult->setText("error");
        } else {
            resultOperations = numFirst / numSecond;
            newLine = QString::number(resultOperations,'g', 15);

            ui->showResult->setText(newLine);
        }
        ui->pushButton_division->setChecked(false);

        check_div = false;

    } else if(check_mult) {
        resultOperations = numFirst * numSecond;
        newLine = QString::number(resultOperations,'g', 15);

        ui->showResult->setText(newLine);
        ui->pushButton_multiplication->setChecked(false);

        check_mult = false;

    } else if(check_percent) {
        resultOperations = numFirst * (numSecond/100);
        newLine = QString::number(resultOperations,'g', 15);

        ui->showResult->setText(newLine);
        ui->pushButton_percent->setChecked(false);

        check_percent = false;

    }
}

void Calculator::on_pushButton_equalSign_clicked()
{
    calcResult();
    flagFirst = false;
    flagDel = true;
    flagPlusOrMinus = false;
}

void Calculator::on_pushButton_clearAll_clicked()
{
    ui->ShowInput->setText("");
    ui->showResult->setText("");
    flagFirst = false;
    flagPlusOrMinus = false;
    flagDel = false;
    flagSign = true;
    check_plus = false;
    check_minus = false;
    check_mult = false;
    check_div = false;
    check_percent = false;


}

void Calculator::on_pushButton_clearLast_clicked()
{
    QString str;
    int strSize;

    str = ui->ShowInput->text();
    strSize = str.size();

    if(str.right(1) == "+") {
        ui->pushButton_plus->setChecked(false);
        check_plus = false;
    } else if(str.right(1) == "-") {
        ui->pushButton_minus->setChecked(false);
        check_minus = false;
    } else if(str.right(1) == "÷") {
        ui->pushButton_division->setChecked(false);
        check_div = false;
    } else if(str.right(1) == "×") {
        ui->pushButton_multiplication->setChecked(false);
        check_mult = false;
    } else if(str.right(1) == "%") {
        ui->pushButton_percent->setChecked(false);
        check_percent = false;
    }

    str.resize(strSize-1);
    ui->ShowInput->setText(str);
}








