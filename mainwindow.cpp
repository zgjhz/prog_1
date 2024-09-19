#include "mainwindow.h"
#include "loginwindow.h"
#include "questionwidget.h"
#include "./ui_mainwindow.h"
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    loginLabel = new QLabel("ЛОГИН: ", this);
    loginButton = new QPushButton("Настройка", this);
    loginWindow = new LoginWindow(this);
    loginWindow->hide();

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(loginLabel);
    hLayout->addStretch();
    hLayout->setSpacing(0);
    hLayout->addWidget(loginButton);

    vLayout = new QVBoxLayout;
    //vLayout->setSpacing(10);
    vLayout->addLayout(hLayout);
    vLayout->addWidget(loginWindow);
    vLayout->addStretch();

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(vLayout);
    setCentralWidget(centralWidget);

    connect(loginButton, &QPushButton::clicked, this, &MainWindow::onLoginButtonClicked);

    questionWidget = nullptr;
}

MainWindow::~MainWindow()
{
    if (questionWidget != nullptr) {
        delete questionWidget;
    }
    delete ui;
}

void MainWindow::onLoginButtonClicked()
{
    connect(loginWindow, &LoginWindow::loginSuccess, this, &MainWindow::onLoginSucces);
    loginWindow->setWindowTitle("Логин");
    loginWindow->showMaximized();
}

void MainWindow::onLoginSucces(const QString &username, const QString &subject) {
    loginLabel->setText(QString("Логин: %1").arg(username));

    if (questionWidget != nullptr) {
        delete questionWidget;
    }

    questionWidget = new QuestionWidget(subject, this);
    vLayout->addWidget(questionWidget, 2, Qt::AlignVCenter);
}

