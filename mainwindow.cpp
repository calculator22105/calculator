#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QtMath"
#include "math.h"
#define PI 3.14159265

ааааааааааааааааааааааааааА

double firstNum;
bool userIsTypingSecondNumber = false;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* Если был получен сигнал от кнопки 0-9, то переходим к digit_pressed() */
    connect(ui->pushButton_0,SIGNAL(clicked()),this,SLOT(digit_pressed())); 
    connect(ui->pushButton_1,SIGNAL(clicked()),this,SLOT(digit_pressed())); 
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(digit_pressed())); 
    connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_4,SIGNAL(clicked()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_5,SIGNAL(clicked()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_6,SIGNAL(clicked()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_7,SIGNAL(clicked()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_8,SIGNAL(clicked()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_9,SIGNAL(clicked()),this,SLOT(digit_pressed()));

    /* Если был получен сигнал от унарных математических операций, то переходим к unary_operation_pressed() */  
    connect(ui->pushButton_plusMinus,SIGNAL(clicked()),this,SLOT(unary_operation_pressed()));
    connect(ui->pushButton_percent,SIGNAL(clicked()),this,SLOT(unary_operation_pressed()));
    connect(ui->pushButton_sqrt,SIGNAL(clicked()), this, SLOT(unary_operation_pressed()));
    connect(ui->pushButton_pow,SIGNAL(clicked()), this, SLOT(unary_operation_pressed()));
    connect(ui->pushButton_cos,SIGNAL(clicked()), this, SLOT(unary_operation_pressed()));
    connect(ui->pushButton_sin,SIGNAL(clicked()), this, SLOT(unary_operation_pressed()));
    connect(ui->pushButton_tang,SIGNAL(clicked()), this, SLOT(unary_operation_pressed()));
    connect(ui->pushButton_abs,SIGNAL(clicked()), this, SLOT(unary_operation_pressed()));
    connect(ui->pushButton_log,SIGNAL(clicked()), this, SLOT(unary_operation_pressed()));

    /* Если был получен сигнал от бинарных операций, то переходим к binary_operation_pressed() */ 
    connect(ui->pushButton_add,SIGNAL(clicked()),this,SLOT(binary_operation_pressed()));
    connect(ui->pushButton_subtract,SIGNAL(clicked()),this,SLOT(binary_operation_pressed()));
    connect(ui->pushButton_multiply,SIGNAL(clicked()),this,SLOT(binary_operation_pressed()));
    connect(ui->pushButton_divide,SIGNAL(clicked()),this,SLOT(binary_operation_pressed()));
    connect(ui->pushButton_powe,SIGNAL(clicked()), this, SLOT(binary_operation_pressed()));

    /* Указываем, что кнопки "+", "-", "÷" и"×" являются активными */
    ui->pushButton_add->setCheckable(true);
    ui->pushButton_subtract->setCheckable(true);
    ui->pushButton_multiply->setCheckable(true);
    ui->pushButton_divide->setCheckable(true);
    ui->pushButton_powe->setCheckable(true);
    ui->pushButton_percent->setCheckable(true);

    /* Установили текст в кнопке x^n */
    ui->pushButton_powe->setText("x\u207F"); 
}

MainWindow::~MainWindow()
{
    delete ui;
}

/* Если нажата цифра */
void MainWindow::digit_pressed() 
{
 
 /* sender возвращает указатель на объект, объектом является кнопка, на которую нажали */
 QPushButton * button = (QPushButton*)sender(); 

 double labelNumber;
 QString newLabel;

 if((ui->pushButton_add->isChecked() || ui->pushButton_subtract->isChecked() ||
         ui->pushButton_multiply->isChecked() || ui->pushButton_divide->isChecked() || ui->pushButton_powe->isChecked() ) && (!userIsTypingSecondNumber)) 
   
   /* Текст с кнопки преобразуем к типу double */  
   labelNumber = button->text().toDouble();  
   userIsTypingSecondNumber = true;
   /* Присваиваем отформатированную строку формата 'g' длbной не более 15 символов */
   newLabel = QString::number(labelNumber,'g',15);

 }
     else
 {
     /* Если в label '.' и нажата кнопка 0 */
     if (ui->label->text().contains('.')  && button->text() == "0")  
     {
        /* Тогда newLabel равен '.0' */
        newLabel = ui->label->text() + button->text();
     }
     else
     {
       /* Иначе если число от 0-9, выводим его */
       labelNumber = (ui->label->text() + button->text()).toDouble();
       newLabel = QString::number(labelNumber,'g',15);
         }
     }
       /* Выводим значение переменной newLabel в label */
       ui->label->setText(newLabel);
}

/* При нажатии десятичной дроби */
void MainWindow::on_pushButton_decimal_clicked() 
{
  /* Если label не содержит '.' */
  if (!ui->label->text().contains('.'))
  {
   /* Выводим текст с точкой */   
   ui->label->setText(ui->label->text() + ".");
  }
}

/* Если нажата унарная операция */
void MainWindow::unary_operation_pressed() 
{
    double labelNumber;
    QString newLabel;

    QPushButton * button = (QPushButton*) sender(); 
    
    /* Если кнопка содержит текст '+/-' */
    if (button->text() == "+/-")   
    {
       labelNumber = ui->label->text().toDouble();   // получаем число которое у нас написано в label  записываем его в labelNumber
       labelNumber = labelNumber * -1;   // умножаем это число на -1
       newLabel = QString::number(labelNumber,'g',15);  // число длиной не больше 15. QString предоставляет строку символов
       ui->label->setText(newLabel);  // выводим на label полученое число
    }
    if (button->text() == "%")  // если нажат "%"
    {
      labelNumber = ui->label->text().toDouble(); // получаем число которое у нас написано в label и записываем его в labelNumber
       labelNumber = labelNumber * 0.01;     // умножаем это число на 0.01
       newLabel = QString::number(labelNumber,'g',15); //выводим число длиной не больше 15, g - формат. QString предоставляет строку символов
       ui->label->setText(newLabel);  // выводим на label полученое число
   }
    if (button->text() == "√")
    {
        labelNumber = ui->label->text().toDouble();// получаем число которое у нас написано в label и записываем его в labelNumber
        ui->top_label->setText("√" + ui->label->text());
        labelNumber = qSqrt(labelNumber);     // находим корень
        newLabel = QString::number(labelNumber,'g',15); //выводим число длиной не больше 15, g - формат. QString предоставляет строку символов
        ui->label->setText(newLabel);  // выводим на label полученое число
    }
    if (button->text() == "^")  // если нажат "^"
    {
       double a = 2;
       labelNumber = ui->label->text().toDouble(); // получаем число которое у нас написано в label и записываем его в labelNumber
       double labelN = pow (labelNumber, a);     // умножаем это число на 0.01
       newLabel = QString::number(labelN,'g',15); //выводим число длиной не больше 15, g - формат. QString предоставляет строку символов
       ui->label->setText(newLabel);  // выводим на label полученое число
    }
    if (button->text() == "cos")
    {
        labelNumber = ui->label->text().toDouble();// получаем число которое у нас написано в label и записываем его в labelNumber
        ui->top_label->setText("cos" + ui->label->text());
        double a = labelNumber;
        double labelN = cos(a);     // находим корень
        newLabel = QString::number(labelN,'g',8); //выводим число длиной не больше 15, g - формат. QString предоставляет строку символов
        ui->label->setText(newLabel);  // выводим на label полученое число
    }
    if (button->text() == "sin")
    {
        labelNumber = ui->label->text().toDouble();// получаем число которое у нас написано в label и записываем его в labelNumber
        ui->top_label->setText("sin" + ui->label->text());
        double a = labelNumber;
        double labelN = sin((a * PI) / 180);     // находим корень
        newLabel = QString::number(labelN,'g',8); //выводим число длиной не больше 15, g - формат. QString предоставляет строку символов
        ui->label->setText(newLabel);  // выводим на label полученое число
    }
    if (button->text() == "tan")
    {
        labelNumber = ui->label->text().toDouble();// получаем число которое у нас написано в label и записываем его в labelNumber
        ui->top_label->setText("tan" + ui->label->text());
        double a = labelNumber;
        double labelN = tan((a * PI) / 180);     // находим корень
        newLabel = QString::number(labelN,'g',8); //выводим число длиной не больше 15, g - формат. QString предоставляет строку символов
        ui->label->setText(newLabel);  // выводим на label полученое число
    }
    if (button->text() == "|x|")
    {
        labelNumber = ui->label->text().toDouble();// получаем число которое у нас написано в label и записываем его в labelNumber
        ui->top_label->setText("|" + ui->label->text() + "|");
        double a = labelNumber;
        double labelN = abs(a);     // находим корень
        newLabel = QString::number(labelN,'g',8); //выводим число длиной не больше 15, g - формат. QString предоставляет строку символов
        ui->label->setText(newLabel);  // выводим на label полученое число
    }
    if (button->text() == "log")
    {
        labelNumber = ui->label->text().toDouble();// получаем число которое у нас написано в label и записываем его в labelNumber
        ui->top_label->setText("log" + ui->label->text());
        double a = labelNumber;
        double labelN = log(a);     // находим корень
        newLabel = QString::number(labelN,'g',8); //выводим число длиной не больше 15, g - формат. QString предоставляет строку символов
        ui->label->setText(newLabel);  // выводим на label полученое число
    }
}

void MainWindow::on_pushButton_clear_clicked()  // нажали кнопку очистить
{
    /* Указываем, что кнопки "+", "-", "÷" и"×" являются не активными */
    ui->pushButton_add->setChecked(false);
    ui->pushButton_subtract->setChecked(false);
    ui->pushButton_multiply->setChecked(false);
    ui->pushButton_divide->setChecked(false);
    ui->pushButton_powe->setChecked(false);



    userIsTypingSecondNumber = false;

    ui->label->setText("0"); // выводим в label 0
    ui->top_label->setText("");

}

void MainWindow::on_pushButton_equals_clicked()  // нажали кнопку равно
{
    double labelNumber, secondNum;
    QString newLabel;

    secondNum = ui->label->text().toDouble(); // secondNum равен последнему введенному числу в label

    if (ui->pushButton_add->isChecked())  // если сложение
    {
        labelNumber = firstNum + secondNum;  // labelNumber равен сумме первого числа и второго(secondNum)
        newLabel = QString::number(labelNumber,'g', 15); // число длиной не больше 15, g - формат. QString предоставляет строку символов
        ui->label->setText(newLabel); // выводим число в label
        ui->pushButton_add->setChecked(false); // дезактивирует кнопку
    }
    else if (ui->pushButton_subtract->isChecked()) // если вычитание
    {
        labelNumber = firstNum - secondNum;  // labelNumber равен разности первого числа и второго(secondNum)
        newLabel = QString::number(labelNumber,'g', 15); // число длиной не больше 15, g - формат. QString предоставляет строку символов
        ui->label->setText(newLabel);  // выводим число в label
        ui->pushButton_subtract->setChecked(false); // дезактивирует кнопку
    }
    else if (ui->pushButton_multiply->isChecked()) // если умножение
    {
        labelNumber = firstNum * secondNum; // labelNumber равен произведению первого числа и второго(secondNum)
        newLabel = QString::number(labelNumber,'g', 15); // число длиной не больше 15, g - формат. QString предоставляет строку символов
        ui->label->setText(newLabel);  // выводим число в label
        ui->pushButton_multiply->setChecked(false);  // дезактивирует кнопку
    }
    else if (ui->pushButton_divide->isChecked())  // если деление
    {
        if (secondNum == 0) {   // если делим на 0
           ui->label->setText("Нельзя делить на ноль "); // вывести ошибку
        }
        else {
        labelNumber = firstNum / secondNum;  // если деление
        newLabel = QString::number(labelNumber,'g', 15);  // число длиной не больше 15, g - формат. QString предоставляет строку символов
        ui->label->setText(newLabel); // выводим число в label
        ui->pushButton_divide->setChecked(false);  // дезактивирует кнопку
        }
    }
    else if (ui->pushButton_powe->isChecked())   // если возводим в степень
    {
        labelNumber = pow (firstNum, secondNum);
        newLabel = QString::number(labelNumber,'g', 15); // число длиной не больше 15, g - формат. QString предоставляет строку символов
        ui->label->setText(newLabel); // выводим число в label
        ui->pushButton_powe->setChecked(false);

    }

    ui->top_label->setText(""); // выводим в верхний label ничего
    userIsTypingSecondNumber = false;
}

void MainWindow::binary_operation_pressed() // бинарная операция нажата
{
    QPushButton * button = (QPushButton*) sender(); // получаем информацию о сигнале

    firstNum = ui->label->text().toDouble();  // firstNum равен первому введенному числу
    ui->top_label->setText(ui->label->text()); // помещаем его в top_label
    ui->label->setText("0");  // в label ставим 0

    button->setChecked(true); // активируем нажатую кнопку




}
