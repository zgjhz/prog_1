#include "questionwidget.h"
#include "mainwindow.h"

#include <QDebug>
#include <QAbstractButton>

QuestionWidget::QuestionWidget(const QString &subject, QWidget *parent) : QWidget(parent){
    localSubject = subject;
    if (subject == "Математика"){
        questions << "Какой результат выражения 2 + 2?"
                  << "Что такое производная?"
                  << "Какой результат выражения 8 mod 2?";

        answers << (QStringList{"3", "4", "5"})
                << (QStringList{"Предел", "Функциональный ряд", "Степенной ряд"})
                << (QStringList{"1", "8", "0"});
    }else if (subject == "Физика") {
        questions << "Ускорение свободного падения равно?"
                  << "Масса измеряется в?"
                  << "Сколько планет в Солнечной системе?";

        answers << (QStringList{"11", "9,81", "123"})
                << (QStringList{"килограммах", "литрах", "удавах"})
                << (QStringList{"7", "8", "9"});
    }

    layout = new QVBoxLayout(this);

    layout->addStretch();
    layout->setSpacing(0);

    questionLabel = new QLabel(this);
    layout->addWidget(questionLabel);

    answerGroup = new QButtonGroup(this);

    submitButton = new QPushButton("Ответить", this);
    layout->addWidget(submitButton);

    connect(submitButton, &QPushButton::clicked, this, &QuestionWidget::onSubmitClicked);

    currentQuestionIndex = 0;
    correctAnswers = 0;
    loadNextQuestion();
}

void QuestionWidget::loadNextQuestion()
{
    if (currentQuestionIndex >= questions.size()) {
        questionLabel->setText(QString("Тест завершён! Статистика: %1 из %2").arg(correctAnswers).arg(currentQuestionIndex));
        submitButton->setText("Продолжить");
        QList<QAbstractButton*> oldButtons = answerGroup->buttons();
        for (auto button : oldButtons) {
            answerGroup->removeButton(button);
            delete button;
        }
        connect(submitButton, &QPushButton::clicked, this, &QuestionWidget::onContinueButtonClicked);
        return;
    }

    questionLabel->setText(questions[currentQuestionIndex]);

    QList<QAbstractButton*> oldButtons = answerGroup->buttons();
    for (auto button : oldButtons) {
        answerGroup->removeButton(button);
        delete button;
    }

    QStringList currentAnswers = answers[currentQuestionIndex];
    for (const QString &answer : currentAnswers) {
        QRadioButton *answerButton = new QRadioButton(answer, this);
        answerGroup->addButton(answerButton);
        layout->insertWidget(layout->count() - 1, answerButton);
    }
}

void QuestionWidget::onContinueButtonClicked(){
    this->close();
    this->destroy();
    qDebug("Destroy");
}

void QuestionWidget::onSubmitClicked()
{
    QAbstractButton *selectedButton = answerGroup->checkedButton();

    if (selectedButton) {
        QString selectedAnswer = selectedButton->text();

        QString correctAnswer;
        if (localSubject == "Математика"){
            if (currentQuestionIndex == 0) correctAnswer = "4";
            else if (currentQuestionIndex == 1) correctAnswer = "Предел";
            else if (currentQuestionIndex == 2) correctAnswer = "0";
        }else if (localSubject == "Физика"){
            if (currentQuestionIndex == 0) correctAnswer = "9,81";
            else if (currentQuestionIndex == 1) correctAnswer = "килограммах";
            else if (currentQuestionIndex == 2) correctAnswer = "8";
        }

        if (selectedAnswer == correctAnswer) {
            correctAnswers++;
            qDebug() << "Правильный ответ!";
        } else {
            qDebug() << "Неправильный ответ!";
        }

        currentQuestionIndex++;
        loadNextQuestion();
    } else {
        qDebug() << "Ответ не выбран!";
    }
}
