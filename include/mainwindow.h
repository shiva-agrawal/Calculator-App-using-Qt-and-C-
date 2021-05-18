#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    // variable to hold one number during binary operation
    double firstNum;

    bool secondInputByUser = false;

private slots:
    void digit_pressed();
    void decimal_pressed();
    void uniary_operation_pressed();
    void binary_operation_pressed();
    void clear_button_pressed();
    void equal_button_pressed();
};
#endif // MAINWINDOW_H
