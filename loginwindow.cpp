#include "loginwindow.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>

LoginWindow::LoginWindow(QWidget *parent) : QWidget(parent) {

    QVBoxLayout *layout = new QVBoxLayout(this);

    loginEdit = new QLineEdit(this);
    subjectBox = new QComboBox(this);
    continueButton = new QPushButton("Продолжить", this);

    subjectBox->addItems({"Математика", "Физика"});

    layout->addStretch();
    layout->setSpacing(0);
    layout->addWidget(new QLabel("Введите логин:", this));
    layout->addWidget(loginEdit);
    layout->addWidget(new QLabel("Выберите предмет:", this));
    layout->addWidget(subjectBox);
    layout->addWidget(continueButton);

    connect(continueButton, &QPushButton::clicked, this, &LoginWindow::onContinueButtonClicked);
}

LoginWindow::~LoginWindow() {

}

void LoginWindow::onContinueButtonClicked() {
    QString username = loginEdit->text();
    QString subject = subjectBox->currentText();

    if (username.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите логин!");
        return;
    }

    emit loginSuccess(username, subject);

    close();
}
