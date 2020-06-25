#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cmath>   

#define PI 3.14159265

double firstNum;                       // переменная дли бинарных операций
bool userIsTypingSecondNumber = false; // показывает, вводит ли пользователь второе число


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
        
    sWindow = new Form();                                          //инициализируем второе окно
    connect(sWindow, &Form::firstWindow, this, &MainWindow::show); //подключаем к слоту запуска главного окна по кнопке во втором окне

    /* Если был получен сигнал от кнопки [0-9], то переходим к слоту digit_pressed() */
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

    /* Если был получен сигнал от унарных математических операций, то переходим к слоту unary_operation_pressed() */  
    connect(ui->pushButton_percent,SIGNAL(clicked()),this,SLOT(unary_operation_pressed()));
        
    /* Если был получен сигнал от бинарных операций, то переходим к слоту binary_operation_pressed() */ 
    connect(ui->pushButton_add,SIGNAL(clicked()),this,SLOT(binary_operation_pressed()));
    connect(ui->pushButton_subtract,SIGNAL(clicked()),this,SLOT(binary_operation_pressed()));
    connect(ui->pushButton_multiply,SIGNAL(clicked()),this,SLOT(binary_operation_pressed()));
    connect(ui->pushButton_divide,SIGNAL(clicked()),this,SLOT(binary_operation_pressed()));

    /* Указываем, что кнопки "+", "-", "÷", "×", "x^n" являются триггерными */
    ui->pushButton_add->setCheckable(true);
    ui->pushButton_subtract->setCheckable(true);
    ui->pushButton_multiply->setCheckable(true);
    ui->pushButton_divide->setCheckable(true);
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

 /* Если установлена одна из клавиш "+", "-", "÷", "×", "x^n" и пользователь вводит второе число */
 if((ui->pushButton_add->isChecked() || ui->pushButton_subtract->isChecked() ||
     ui->pushButton_multiply->isChecked() || ui->pushButton_divide->isChecked()) && (!userIsTypingSecondNumber)) {
   
   /* Текст с кнопки преобразуем к типу double */  
   labelNumber = button->text().toDouble();  
   userIsTypingSecondNumber = true;
   /* Присваиваем отформатированную строку формата 'g' длиной не более 15 символов */
   newLabel = QString::number(labelNumber,'g',15);

 }
     else
 {
     /* Иначе, если в label есть '.', нажатая кнопка является "0" и длина строки не превышает 14 символов */
     if (ui->label->text().contains('.')  && button->text() == "0" && ui->label->text().length() <= 14)  
     {
        /* Тогда newLabel равен '*.0' */
        newLabel = ui->label->text() + button->text();
     }
     else
     {
       /* Иначе, если число от 0-9 */
       labelNumber = (ui->label->text() + button->text()).toDouble(); // Cоставляем строку из нажатых символов, преобразовывая в тип double
       newLabel = QString::number(labelNumber,'g',15);                // Присваиваем отформатированную строку формата 'g' длиной не более 15 символов
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
    double labelNumber, Num1, Num2;
    QString newLabel;

    QPushButton * button = (QPushButton*) sender(); 
    
    /* Если кнопка содержит текст '%' */
    if (button->text() == "%")  
    {
       /* если в верхнем поле не пусто и была нажата кнопка вычитаяния или сложения */
        if (ui->top_label->text() != "" && (ui->pushButton_subtract->isChecked() || ui->pushButton_add->isChecked()) ) {

            labelNumber = ui->label->text().toDouble();          // для процента: второе введенное число

            /* значит нам нужно высчитать процент от первого числа, которое находися в верхнем поле */
            Num1 = firstNum * 0.01;
            Num2 = labelNumber * Num1;

            newLabel = QString::number(Num2, 'g', 15);
            ui->label->setText(newLabel);                       // выводим на label получившееся число

        } else {

        /* Иначе просто высчитываем процент числа */
        labelNumber = ui->label->text().toDouble();
        labelNumber = labelNumber * 0.01;

        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label->setText(newLabel);
        }
    }
}

/* Если нажали кнопку очистить */
void MainWindow::on_pushButton_clear_clicked()  
{
    /* Указываем, что данные кнопки не являются установленными */
    ui->pushButton_add->setChecked(false);
    ui->pushButton_subtract->setChecked(false);
    ui->pushButton_multiply->setChecked(false);
    ui->pushButton_divide->setChecked(false);

    /* Указываем, что второе число не вводится */
    userIsTypingSecondNumber = false;
    
    /* Помещаем в label "0" */
    ui->label->setText("0"); 
    ui->top_label->setText(""); // очищаем

}

/* Если нажали кнопку равно */
void MainWindow::on_pushButton_equals_clicked() {
    
    double labelNumber, secondNum;
    QString newLabel;
    
    /* secondNum равен второму введенному числу */
    secondNum = ui->label->text().toDouble(); 

    /* Если нажата кнопка '+' */
    if (ui->pushButton_add->isChecked())  
    {
        {
        /* Складываем первое и второе число */
        labelNumber = firstNum + secondNum;  
        newLabel = QString::number(labelNumber,'g', 15); 
        ui->label->setText(newLabel);
        /* Дезактивируем кнопку */
        ui->pushButton_add->setChecked(false); 
    }
        ui->top_label->setText(QString::number(firstNum) + "+" + QString::number(secondNum));
    }
     /* Если нажата кнопка '-' */
    else if (ui->pushButton_subtract->isChecked()) 
    {
        {
        labelNumber = firstNum - secondNum;  
        newLabel = QString::number(labelNumber,'g', 15); 
        ui->label->setText(newLabel);  
        ui->pushButton_subtract->setChecked(false); 
    }
         ui->top_label->setText(QString::number(firstNum) + "-" + QString::number(secondNum));
    }
    /* Если нажата кнопка '*' */
    else if (ui->pushButton_multiply->isChecked()) 
    {
        {
        labelNumber = firstNum * secondNum; 
        newLabel = QString::number(labelNumber,'g', 15); 
        ui->label->setText(newLabel);  
        ui->pushButton_multiply->setChecked(false);  
    }
        ui->top_label->setText(QString::number(firstNum) + "×" + QString::number(secondNum));
    }
    /* Если нажата кнопка '/' */
    else if (ui->pushButton_divide->isChecked())  
    {
        {
        /* Проверка, если второе число выводим сообщение об ошибке */
        if (secondNum == 0) {   
           ui->label->setText("You cannot divide by 0!"); 
           ui->pushButton_divide->setChecked(false);
        } else {
            
        labelNumber = firstNum / secondNum;  
        newLabel = QString::number(labelNumber,'g', 15);  
        ui->label->setText(newLabel); 
        ui->pushButton_divide->setChecked(false);  
        }
    }
        ui->top_label->setText(QString::number(firstNum) + "÷" + QString::number(secondNum));
    }
    userIsTypingSecondNumber = false;
}

/* Если нажата бинарная операция */
void MainWindow::binary_operation_pressed() 
{
    QPushButton * button = (QPushButton*) sender(); 
    
    /* firstNum равен первому введенному числу */
    firstNum = ui->label->text().toDouble();  
    
    ui->top_label->setText(ui->label->text()); 
    ui->label->setText("0");  
    /* Активируем нажатую кнопку */
    button->setChecked(true); 
    
    if (ui->top_label->text().length() )
    ui->top_label->setText(ui->top_label->text() + button->text());

    userIsTypingSecondNumber = false; 
}

/* Если нажата кнопка "<-" */
void MainWindow::on_pushButton_back_clicked()
{
    int length = ui->label->text().length();                    // вычисляем длину введенного числа
        ui->label->setText(ui->label->text().left(length - 1)); // выводим строку, содержащую на 1 символ меньше (последний удалился)
        /* Если символов в строке нет */
        if (length == 1) {
            ui->label->setText("0");                            // выводим 0
        }
}

void MainWindow::on_radioButton_clicked()
{
    sWindow->show();                        //показываем второе окно
    sWindow->setFixedSize(sWindow->size()); // фиксируем размеры окна
    this->close();                          //закрываем основное окно
}
