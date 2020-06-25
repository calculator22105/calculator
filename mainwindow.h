#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "form.h"

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
    
    Form *sWindow;                        // второе окно
    
private slots:
    void digit_pressed();                 // при нажатии цифры
    void on_pushButton_decimal_clicked(); // при нажатии "." (десятичной дроби)
    void unary_operation_pressed();       // для унарных операций
    void on_pushButton_clear_clicked();   // для кнопки очистки "С"
    void on_pushButton_equals_clicked();  // для кнопки "="
    void binary_operation_pressed();      // для бинарных операций
    void on_pushButton_back_clicked();    // для удаления предыдущего символа
    void on_pushButton_deg_clicked();     // для перевода значений из радиан в градусы
    
    void on_radioButton_clicked();        // для переключения на другое окно
};

#endif // MAINWINDOW_H
