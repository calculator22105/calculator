#include "form.h"
#include "ui_form.h"
#include <cmath>   

#define PI 3.14159265

double firstNum2;                       // переменная дли бинарных операций
double trigonom2;                       // переменная для перевода из радиан в градусы
bool userIsTypingSecondNumber2 = false; // показывает, вводит ли пользователь второе число


Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);

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
    connect(ui->pushButton_plusMinus,SIGNAL(clicked()),this,SLOT(unary_operation_pressed()));
    connect(ui->pushButton_percent,SIGNAL(clicked()),this,SLOT(unary_operation_pressed()));
    connect(ui->pushButton_sqrt,SIGNAL(clicked()), this, SLOT(unary_operation_pressed()));
    connect(ui->pushButton_pow,SIGNAL(clicked()), this, SLOT(unary_operation_pressed()));
    connect(ui->pushButton_cos,SIGNAL(clicked()), this, SLOT(unary_operation_pressed()));
    connect(ui->pushButton_sin,SIGNAL(clicked()), this, SLOT(unary_operation_pressed()));
    connect(ui->pushButton_tan,SIGNAL(clicked()), this, SLOT(unary_operation_pressed()));
    connect(ui->pushButton_factorial, SIGNAL(clicked()), this, SLOT(unary_operation_pressed()));
    connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(unary_operation_pressed()));
    connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(unary_operation_pressed()));
    connect(ui->pushButton_fraction, SIGNAL(clicked()), this, SLOT(unary_operation_pressed()));
        
    /* Если был получен сигнал от бинарных операций, то переходим к слоту binary_operation_pressed() */ 
    connect(ui->pushButton_add,SIGNAL(clicked()),this,SLOT(binary_operation_pressed()));
    connect(ui->pushButton_subtract,SIGNAL(clicked()),this,SLOT(binary_operation_pressed()));
    connect(ui->pushButton_multiply,SIGNAL(clicked()),this,SLOT(binary_operation_pressed()));
    connect(ui->pushButton_divide,SIGNAL(clicked()),this,SLOT(binary_operation_pressed()));
    connect(ui->pushButton_powe,SIGNAL(clicked()), this, SLOT(binary_operation_pressed()));

    /* Указываем, что кнопки "+", "-", "÷", "×", "x^n" являются триггерными */
    ui->pushButton_add->setCheckable(true);
    ui->pushButton_subtract->setCheckable(true);
    ui->pushButton_multiply->setCheckable(true);
    ui->pushButton_divide->setCheckable(true);
    ui->pushButton_powe->setCheckable(true);

    ui->pushButton_powe->setText("x\u207F");           // Установили текст в кнопке x^n
    ui->pushButton_fraction->setText("x\u207B\u00B9"); // Помещаем на кнопку текст ( x^(-1) )
}

Form::~Form()
{
    delete ui;
}

/* Если нажата цифра */
void Form::digit_pressed() 
{
 
 /* sender возвращает указатель на объект, объектом является кнопка, на которую нажали */
 QPushButton * button = (QPushButton*)sender(); 

 double labelNumber;
 QString newLabel;

 /* Если установлена одна из клавиш "+", "-", "÷", "×", "x^n" и пользователь вводит второе число */
 if((ui->pushButton_add->isChecked() || ui->pushButton_subtract->isChecked() ||
     ui->pushButton_multiply->isChecked() || ui->pushButton_divide->isChecked() ||
     ui->pushButton_powe->isChecked() ) && (!userIsTypingSecondNumber2)) {
   
   /* Текст с кнопки преобразуем к типу double */  
   labelNumber = button->text().toDouble();  
   userIsTypingSecondNumber2 = true;
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
void Form::on_pushButton_decimal_clicked() 
{
  /* Если label не содержит '.' */
  if (!ui->label->text().contains('.'))
  {
   /* Выводим текст с точкой */   
   ui->label->setText(ui->label->text() + ".");
  }
}

/* Функция, высчитывающая факториал полученного числа */
double fact(double x) {
    if (x == 0)
        return 1;
    else
        return x * fact(x-1);
}

/* Если нажата унарная операция */
void Form::unary_operation_pressed() 
{
    double labelNumber, Num1, Num2;
    QString newLabel;

    QPushButton * button = (QPushButton*) sender(); 
    
    /* Если кнопка содержит текст '+/-' */
    if (button->text() == "+/-")   
    {       
       labelNumber = ui->label->text().toDouble();      // Присваиваем labelNumber введенное значение
       labelNumber = labelNumber * -1;                  // Меняем знак на противоположный
        
       newLabel = QString::number(labelNumber,'g',15);  // присваиваем отформатированную строку в формате g с точностью 15 знаков
       ui->label->setText(newLabel);                    // Выводим в label новую строку
    }
    /* Если кнопка содержит текст '%' */
    if (button->text() == "%")  
    {
       /* если в верхнем поле не пусто и была нажата кнопка вычитаяния или сложения */
        if (ui->top_label->text() != "" && (ui->pushButton_subtract->isChecked() || ui->pushButton_add->isChecked()) ) {

            labelNumber = ui->label->text().toDouble();          // для процента: второе введенное число

            /* значит нам нужно высчитать процент от первого числа, которое находися в верхнем поле */
            Num1 = firstNum2 * 0.01;
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
    
    /* Если кнопка содержит текст '√' */
    if (button->text() == "√")
    {
        labelNumber = ui->label->text().toDouble();    
        ui->top_label->setText("√" + ui->label->text());   // Выводим в top_label знак корня и число
        
         /* Если введенное число отрицательное */
         if (labelNumber < 0) {
            ui->label->setText("undefined");               // то корень из этого числа не определен
            ui->top_label->setText("");                    // очищаем верхнее поле

        } else {

        /* Иначе высчитываем квадратный корень числа */
        labelNumber = sqrt(labelNumber);

        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label->setText(newLabel);
        }
    }
    /* Если кнопка содержит текст 'x²' */
    if (button->text() == "x²")
    {
       const double a = 2;
       double labelNum = ui->label->text().toDouble();
       labelNumber = pow(labelNum, a);                         // Находим число в степени 2

       newLabel = QString::number(labelNumber, 'g', 15);
       ui->top_label->setText(QString::number(labelNum) + "²");
       ui->label->setText(newLabel);
    }
    
    /* Если текст на кнопке "x!" */
    if (button->text() == "x!")
    {
        labelNumber = ui->label->text().toDouble();

        /* Если число дробное или отрицательное */
        if (std::floor(labelNumber) != labelNumber || labelNumber < 0) {
            ui->label->setText("undefined");       // то факториал такого числа не определен
            return;
        }

        /* Иначе будем считать факториал */
        ui->top_label->setText(ui->label->text() + "!");

        labelNumber = fact(labelNumber);           // вызываем функцию, которая высчитывает факториал введенного числа

        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label->setText(newLabel);
    }
    
    /* Если кнопка содержит текст 'cos' */
    if (button->text() == "cos")
    {
        labelNumber = ui->label->text().toDouble();
        trigonom2 = ui->label->text().toDouble();            // помещаем число, чтобы потом можно было использовать его в переводе из радиан в градусы
       
        ui->top_label->setText("cos" + ui->label->text());
        labelNumber = std::cos(labelNumber);                // считаем косинус в радианах

        newLabel = QString::number(labelNumber, 'g', 8);
        ui->label->setText(newLabel);
    }
    
    /* Если кнопка содержит текст 'sin' */
    if (button->text() == "sin")
    {
        labelNumber = ui->label->text().toDouble();
        trigonom2 = ui->label->text().toDouble();
        
        ui->top_label->setText("sin" + ui->label->text());
        labelNumber = std::sin(labelNumber);               // считаем синус в радианах

        newLabel = QString::number(labelNumber, 'g', 8);
        ui->label->setText(newLabel);
    }
    
    /* Если кнопка содержит текст 'tan' */
    if (button->text() == "tan")
    {
        labelNumber = ui->label->text().toDouble();
        trigonom2 = ui->label->text().toDouble();
        
        ui->top_label->setText("tan" + ui->label->text());
        labelNumber = std::tan(labelNumber);               // считаем тангенс в радианах

        newLabel = QString::number(labelNumber, 'g', 8);
        ui->label->setText(newLabel);
    }
    
    /* Если текст на кнопке "ln" */
    if (button->text() == "ln")
    {
        labelNumber = ui->label->text().toDouble();
        ui->top_label->setText("ln" + ui->label->text());

        /* Если число отрицательное или равно 0 */
        if (labelNumber <= 0) {
            ui->label->setText("undefined");             // то натур. логарифм такого числа не определен
            ui->top_label->setText("");

        } else {

        labelNumber = std::log(labelNumber);            // иначе, высчитываем натуральный логарифм введенного числа

        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label->setText(newLabel);
        }
    }

    /* Если текст на кнопке "log" */
    if (button->text() == "log")
    {
        labelNumber = ui->label->text().toDouble();
        ui->top_label->setText("log" + ui->label->text());

        if (labelNumber <= 0) {
            ui->label->setText("undefined");
            ui->top_label->setText("");

        } else {

        labelNumber = std::log10(labelNumber);             // иначе, высчитываем логарифм по основанию 10 введенного числа

        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label->setText(newLabel);
        }
    }

    /* Если текст на кнопке "x^(-1)" */
    if (button->text() == "x\u207B\u00B9")
    {
        labelNumber = ui->label->text().toDouble();

        /* Если введено число 0 */
        if (labelNumber == 0) {

            ui->label->setText("undefined");        // то обратное число не определено (делить на 0 нельзя)
            ui->top_label->setText("");
        } else {

        labelNumber = 1 / labelNumber;              // иначе находим обратное число

        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label->setText(newLabel);
        }
    }
}

/* Если нажали кнопку очистить */
void Form::on_pushButton_clear_clicked()  
{
    /* Указываем, что данные кнопки не являются установленными */
    ui->pushButton_add->setChecked(false);
    ui->pushButton_subtract->setChecked(false);
    ui->pushButton_multiply->setChecked(false);
    ui->pushButton_divide->setChecked(false);
    ui->pushButton_powe->setChecked(false);

    /* Указываем, что второе число не вводится */
    userIsTypingSecondNumber2 = false;
    
    /* Помещаем в label "0" */
    ui->label->setText("0"); 
    ui->top_label->setText(""); // очищаем

}

/* Если нажали кнопку равно */
void Form::on_pushButton_equals_clicked() {
    
    double labelNumber, secondNum;
    QString newLabel;
    
    /* secondNum равен второму введенному числу */
    secondNum = ui->label->text().toDouble(); 

    /* Если нажата кнопка '+' */
    if (ui->pushButton_add->isChecked())  
    {
        {
        /* Складываем первое и второе число */
        labelNumber = firstNum2 + secondNum;  
        newLabel = QString::number(labelNumber,'g', 15); 
        ui->label->setText(newLabel);
        /* Дезактивируем кнопку */
        ui->pushButton_add->setChecked(false); 
    }
        ui->top_label->setText(QString::number(firstNum2) + "+" + QString::number(secondNum));
    }
     /* Если нажата кнопка '-' */
    else if (ui->pushButton_subtract->isChecked()) 
    {
        {
        labelNumber = firstNum2 - secondNum;  
        newLabel = QString::number(labelNumber,'g', 15); 
        ui->label->setText(newLabel);  
        ui->pushButton_subtract->setChecked(false); 
    }
         ui->top_label->setText(QString::number(firstNum2) + "-" + QString::number(secondNum));
    }
    /* Если нажата кнопка '*' */
    else if (ui->pushButton_multiply->isChecked()) 
    {
        {
        labelNumber = firstNum2 * secondNum; 
        newLabel = QString::number(labelNumber,'g', 15); 
        ui->label->setText(newLabel);  
        ui->pushButton_multiply->setChecked(false);  
    }
        ui->top_label->setText(QString::number(firstNum2) + "×" + QString::number(secondNum));
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
            
        labelNumber = firstNum2 / secondNum;  
        newLabel = QString::number(labelNumber,'g', 15);  
        ui->label->setText(newLabel); 
        ui->pushButton_divide->setChecked(false);  
        }
    }
        ui->top_label->setText(QString::number(firstNum2) + "÷" + QString::number(secondNum));
    }
        

    /* Если нажата кнопка 'x^n' */
    else if (ui->pushButton_powe->isChecked())   
    {
        {
        labelNumber = pow (firstNum2, secondNum);
        newLabel = QString::number(labelNumber,'g', 15); 
        ui->label->setText(newLabel); 
        ui->pushButton_powe->setChecked(false);

    }
        ui->top_label->setText(QString::number(firstNum2) + "^" + QString::number(secondNum));
    }

    userIsTypingSecondNumber2 = false;
}

/* Если нажата бинарная операция */
void Form::binary_operation_pressed() 
{
    QPushButton * button = (QPushButton*) sender(); 
    
    /* firstNum2 равен первому введенному числу */
    firstNum2 = ui->label->text().toDouble();  
    
    ui->top_label->setText(ui->label->text()); 
    ui->label->setText("0");  
    /* Активируем нажатую кнопку */
    button->setChecked(true); 

    /* Добавляем текст нажатой кнопки в top_label */
    if (ui->top_label->text().length() && button->text() != "x\u207F")
    ui->top_label->setText(ui->top_label->text() + button->text());

    userIsTypingSecondNumber2 = false; 
}

/* Если нажата кнопка "<-" */
void Form::on_pushButton_back_clicked()
{
    int length = ui->label->text().length();                    // вычисляем длину введенного числа
        ui->label->setText(ui->label->text().left(length - 1)); // выводим строку, содержащую на 1 символ меньше (последний удалился)
        /* Если символов в строке нет */
        if (length == 1) {
            ui->label->setText("0"); // выводим 0
        }
}

/* Если нажата кнопка для перевода из радиан в градусы */
void Form::on_pushButton_deg_clicked()
{
    QString newLabel;
    double labelNumber;

    /* Если в верхнем поле есть "sin" */
    if (ui->top_label->text().contains("sin")) {

        /* Если число делится на 90 с остатком == 0 */
        if ((std::remainder(trigonom2, 90)) == 0) {

            labelNumber = trigonom2 / 90;        // получаем целую часть от деления числа на 90
            labelNumber = (int)labelNumber % 4; // находим остаток от деления на 4 целой части

            /* Если остаток равен 0, 2 или -2 */
            if (labelNumber == 0 || labelNumber == 2 ||
                   labelNumber == -2) {

                ui->label->setText("0");        // Значит синус = 0

            } else 
                /* Если остаток равен 1 или 3 */
                if (labelNumber == 1 || labelNumber == -3) { 

                ui->label->setText("1");        // Значит синус = 1

            } else
                    /* Если остаток равен 3 или -1 */
                    if (labelNumber == 3 || labelNumber == -1) {

                ui->label->setText("-1");       // Значит синус = -1
            }

            } else {

            /* Иначе, если число не делится нацело на 90, то вычисляем синус в градусах по формуле */
                labelNumber = std::sin(trigonom2 * PI / 180);

                newLabel = QString::number(labelNumber, 'g', 8);
                ui->label->setText(newLabel);
        }
    }

    /* Если в верхнем поле есть "cos" */
    if (ui->top_label->text().contains("cos")) {

        if ((std::remainder(trigonom2, 90)) == 0) {

            labelNumber = trigonom2 / 90;
            labelNumber = (int)labelNumber % 4;

            if (labelNumber == 1 || labelNumber == 3 ||
                  labelNumber == -1 || labelNumber == -3) {

                ui->label->setText("0");

            } else if (labelNumber == 0) {

                ui->label->setText("1");

            } else if (labelNumber == 2 || labelNumber == -2) {

                ui->label->setText("-1");
            }
        } else {

        labelNumber = std::cos(trigonom2 * PI / 180);

        newLabel = QString::number(labelNumber, 'g', 8);
        ui->label->setText(newLabel);
        }
    }

    /* Если в верхнем поле есть "tan" */
    if (ui->top_label->text().contains("tan")) {

        if ((std::remainder(trigonom2, 90)) == 0) {

            labelNumber = trigonom2 / 90;
            labelNumber = (int)labelNumber % 4;

            if (labelNumber == 1 || labelNumber == 3 ||
                    labelNumber == -1 || labelNumber == -3) {

                ui->label->setText("undefined");              // тангенс не определен, если косинус = 0 

            } else if (labelNumber == 0 || labelNumber == 2 ||
                       labelNumber == -2) {

                ui->label->setText("0");
            }

        } else {
            labelNumber = std::tan(trigonom2 * PI / 180);

            newLabel = QString::number(labelNumber, 'g', 8);
            ui->label->setText(newLabel);
        }
    }
}

/* если была нажата кнопка, чтобы переклчюится на окно "обычного калькулятора" */
void Form::on_radioButton_clicked()
{
    this->close();      // это окно закрываем
    emit firstWindow(); // и вызываем сигнал на открытие главного окна
}
