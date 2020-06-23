#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QtMath"
#include "math.h"
#define PI 3.14159265

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
       /* Присваиваем labelNumber введенное значение */
       labelNumber = ui->label->text().toDouble();
       /* Меняем знак на противоположный */
       labelNumber = labelNumber * -1;
       newLabel = QString::number(labelNumber,'g',15); 
       /* Выводим в label */ 
       ui->label->setText(newLabel); 
    }
    /* Если кнопка содержит текст '%' */
    if (button->text() == "%")  
    {
       labelNumber = ui->label->text().toDouble(); 
       /* Высчитываем процент числа */
       labelNumber = labelNumber * 0.01;     
       newLabel = QString::number(labelNumber,'g',15); 
       ui->label->setText(newLabel);  
   }
    /* Если кнопка содержит текст '√' */
    if (button->text() == "√")
    {
        labelNumber = ui->label->text().toDouble();
        /* Выводим в top_label знак корня и число */
        ui->top_label->setText("√" + ui->label->text());
        /* Находим корень числа */
        labelNumber = qSqrt(labelNumber);    
        newLabel = QString::number(labelNumber,'g',15); 
        ui->label->setText(newLabel); 
    }
    /* Если кнопка содержит текст 'x²' */
    if (button->text() == "x²")  
    {
       double a = 2;
       labelNumber = ui->label->text().toDouble();
       /* Находим число в степени 2 */
       double labelN = pow (labelNumber, a);     
       newLabel = QString::number(labelN,'g',15); 
       ui->label->setText(newLabel);  
    }
    /* Если кнопка содержит текст 'cos' */
    if (button->text() == "cos")
    {
        labelNumber = ui->label->text().toDouble();
        ui->top_label->setText("cos" + ui->label->text());
        double a = labelNumber;
        double labelN = cos(a);    
        newLabel = QString::number(labelN,'g',8); 
        ui->label->setText(newLabel);  
    }
    /* Если кнопка содержит текст 'sin' */
    if (button->text() == "sin")
    {
        labelNumber = ui->label->text().toDouble();r
        ui->top_label->setText("sin" + ui->label->text());
        double a = labelNumber;
        double labelN = sin((a * PI) / 180);    
        newLabel = QString::number(labelN,'g',8); 
        ui->label->setText(newLabel);  
    }
    /* Если кнопка содержит текст 'tan' */
    if (button->text() == "tan")
    {
        labelNumber = ui->label->text().toDouble();
        ui->top_label->setText("tan" + ui->label->text());
        double a = labelNumber;
        double labelN = tan((a * PI) / 180);     
        newLabel = QString::number(labelN,'g',8);
        ui->label->setText(newLabel); 
    }
    /* Если кнопка содержит текст 'log' */
    if (button->text() == "log")
    {
        labelNumber = ui->label->text().toDouble();
        ui->top_label->setText("log" + ui->label->text());
        double a = labelNumber;
        double labelN = log(a);     
        newLabel = QString::number(labelN,'g',8); 
        ui->label->setText(newLabel);  
    }
}

/* Если нажали кнопку очистить */
void MainWindow::on_pushButton_clear_clicked()  
{
    /* Указываем, что кнопки "+", "-", "÷" и"×" являются не активными */
    ui->pushButton_add->setChecked(false);
    ui->pushButton_subtract->setChecked(false);
    ui->pushButton_multiply->setChecked(false);
    ui->pushButton_divide->setChecked(false);
    ui->pushButton_powe->setChecked(false);



    userIsTypingSecondNumber = false;
    /* Помещаем в label "0" top_label */
    ui->label->setText("0"); 
    ui->top_label->setText("");

}

/* Если нажали кнопку равно */
void MainWindow::on_pushButton_equals_clicked()
    
    double labelNumber, secondNum;
    QString newLabel;
    
    /* secondNum равен второму введенному числу */
    secondNum = ui->label->text().toDouble(); 

    /* Если нажата кнопка '+' */
    if (ui->pushButton_add->isChecked())  
    {
        /* Складываем первое и второе число */
        labelNumber = firstNum + secondNum;  
        newLabel = QString::number(labelNumber,'g', 15); 
        ui->label->setText(newLabel);
        /* Дезактивируем кнопку */
        ui->pushButton_add->setChecked(false); 
    }
     /* Если нажата кнопка '-' */
    else if (ui->pushButton_subtract->isChecked()) 
    {
        labelNumber = firstNum - secondNum;  
        newLabel = QString::number(labelNumber,'g', 15); 
        ui->label->setText(newLabel);  
        ui->pushButton_subtract->setChecked(false); 
    }
    /* Если нажата кнопка '*' */
    else if (ui->pushButton_multiply->isChecked()) 
    {
        labelNumber = firstNum * secondNum; 
        newLabel = QString::number(labelNumber,'g', 15); 
        ui->label->setText(newLabel);  
        ui->pushButton_multiply->setChecked(false);  
    }
    /* Если нажата кнопка '/' */
    else if (ui->pushButton_divide->isChecked())  
    {
        /* Проверка, если второе число выводим сообщение об ошибке */
        if (secondNum == 0) {   
           ui->label->setText("Нельзя делить на ноль "); /
        }       
        else {
        labelNumber = firstNum / secondNum;  
        newLabel = QString::number(labelNumber,'g', 15);  
        ui->label->setText(newLabel); 
        ui->pushButton_divide->setChecked(false);  
        }
    }
    /* Если нажата кнопка 'x^n' */
    else if (ui->pushButton_powe->isChecked())   
    {
        labelNumber = pow (firstNum, secondNum);
        newLabel = QString::number(labelNumber,'g', 15); 
        ui->label->setText(newLabel); 
        ui->pushButton_powe->setChecked(false);

    }

    ui->top_label->setText("");
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




}
