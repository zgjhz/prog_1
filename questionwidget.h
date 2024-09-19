#ifndef QUESTIONWIDGET_H
#define QUESTIONWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QButtonGroup>
#include <QPushButton>

class QuestionWidget :public QWidget {
    Q_OBJECT

public:
    explicit QuestionWidget(const QString &subject, QWidget *parent = nullptr);

private slots:
    void onSubmitClicked();
    void onContinueButtonClicked();

private:
    QLabel *questionLabel;
    QButtonGroup *answerGroup;
    QVBoxLayout *layout;
    QPushButton *submitButton;

    QStringList questions;
    QList<QStringList> answers;
    int correctAnswers;
    int currentQuestionIndex;
    QString localSubject;

    void loadNextQuestion();

};

#endif // QUESTIONWIDGET_H
