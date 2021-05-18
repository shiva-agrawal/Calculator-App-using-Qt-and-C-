#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // signal slot connections for digits 0 to 9
    connect(ui->pushButton_one,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_two,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_three,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_four,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_five,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_six,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_seven,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_eight,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_nine,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_zero,SIGNAL(released()),this,SLOT(digit_pressed()));

    // signal slot connection for decimal
    connect(ui->pushButton_decimal,SIGNAL(released()),this,SLOT(decimal_pressed()));

    // signal slots for unary operations (+/- , clear, %)
    connect(ui->pushButton_sign,SIGNAL(released()),this,SLOT(uniary_operation_pressed()));
    connect(ui->pushButton_percentage,SIGNAL(released()),this,SLOT(uniary_operation_pressed()));

    // clear button signal-slot connection
    connect(ui->pushButton_clear,SIGNAL(released()),this,SLOT(clear_button_pressed()));

    // equal to button signal slot connection
    connect(ui->pushButton_equal,SIGNAL(released()),this,SLOT(equal_button_pressed()));

    // binary operations signal-slot connections
    connect(ui->pushButton_minus,SIGNAL(released()),this,SLOT(binary_operation_pressed()));
    connect(ui->pushButton_plus,SIGNAL(released()),this,SLOT(binary_operation_pressed()));
    connect(ui->pushButton_multiply,SIGNAL(released()),this,SLOT(binary_operation_pressed()));
    connect(ui->pushButton_divide,SIGNAL(released()),this,SLOT(binary_operation_pressed()));

    ui->pushButton_plus->setCheckable(true);
    ui->pushButton_minus->setCheckable(true);
    ui->pushButton_multiply->setCheckable(true);
    ui->pushButton_divide->setCheckable(true);
    ui->pushButton_equal->setCheckable(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digit_pressed()
{
    if (ui->pushButton_equal->isChecked())
    {
        ui->label->setText("");
        ui->pushButton_equal->setChecked(false);
    }
    if((ui->pushButton_divide->isChecked()
            || ui->pushButton_minus->isChecked()
            || ui->pushButton_plus->isChecked()
            || ui->pushButton_multiply->isChecked()) && (!secondInputByUser))
    {
        ui->label->setText("");
        secondInputByUser = true;
    }

    // send the activated signal as text to button of type QPushbutton
    QPushButton *button = (QPushButton*)sender();

    double labelText;
    QString newLabel;

    labelText = (ui->label->text() + button->text()).toDouble();

    newLabel = QString::number(labelText,'g',15);
    ui->label->setText(newLabel);
}


void MainWindow::decimal_pressed()
{
    if (ui->pushButton_equal->isChecked())
    {
        ui->label->setText("");
        ui->pushButton_equal->setChecked(false);
    }
    if (!(ui->label->text().contains('.')))
    {
        ui->label->setText(ui->label->text() + ".");
    }

}

void MainWindow::uniary_operation_pressed()
{
    QPushButton *button = (QPushButton*)sender();

    double labelText;
    QString newLabel;

    if (button->text() == "+/-")
    {
        labelText = ui->label->text().toDouble();
        labelText = labelText * (-1);
        newLabel = QString::number(labelText,'g',15);

        ui->label->setText(newLabel);
    }
    if (button->text() == "%")
    {
        labelText = ui->label->text().toDouble();
        labelText = labelText /100 ;
        newLabel = QString::number(labelText,'g', 15);

        ui->label->setText(newLabel);
    }
}

void MainWindow::clear_button_pressed()
{
    ui->label->setText("");

}

void MainWindow::equal_button_pressed()
{
    double secondNum, result;
    QString newLabel;

    if(ui->pushButton_plus->isChecked())
    {
        secondNum = ui->label->text().toDouble();
        result = this->firstNum + secondNum;
        newLabel = QString::number(result,'g',15);

        ui->label->setText(newLabel);
        ui->pushButton_plus->setChecked(false);
    }

    else if(ui->pushButton_minus->isChecked())
    {
        secondNum = ui->label->text().toDouble();
        result = this->firstNum - secondNum;
        newLabel = QString::number(result,'g',15);

        ui->label->setText(newLabel);
        ui->pushButton_minus->setChecked(false);
    }
    else if(ui->pushButton_multiply->isChecked())
    {
        secondNum = ui->label->text().toDouble();
        result = this->firstNum * secondNum;
        newLabel = QString::number(result,'g',15);

        ui->label->setText(newLabel);
        ui->pushButton_multiply->setChecked(false);
    }
    else if(ui->pushButton_divide->isChecked())
    {
        secondNum = ui->label->text().toDouble();
        result = this->firstNum / secondNum;
        newLabel = QString::number(result,'g',15);

        ui->label->setText(newLabel);
        ui->pushButton_divide->setChecked(false);
    }
    else
    {}
    ui->pushButton_equal->setChecked(true);
     secondInputByUser = false;
}

void MainWindow::binary_operation_pressed()
{
    QPushButton *button = (QPushButton*)sender();
    firstNum = ui->label->text().toDouble();

    button->setChecked(true);

}
