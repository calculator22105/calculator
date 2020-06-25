#ifndef FORM_H
#define FORM_H

#include <QWidget>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();

signals:
    void firstWindow();                   // сигнал для первого окна на открытие

private slots:
    void on_radioButton_clicked();        // для переключения на другое окно

    void digit_pressed();                 // при нажатии цифры

    void on_pushButton_decimal_clicked(); // при нажатии "." (десятичной дроби)

    void unary_operation_pressed();       // для унарных операций "+/-", "%"
    void on_pushButton_clear_clicked();   // для кнопки очистки "С"
    void on_pushButton_equals_clicked();  // для кнопки "="
    void binary_operation_pressed();      // для бинарных операций
    void on_pushButton_back_clicked();    // для удаления предыдущего символа
    void on_pushButton_deg_clicked();     // для перевода значений из радиан в градусы

private:
    Ui::Form *ui;
};

#endif // FORM_H
