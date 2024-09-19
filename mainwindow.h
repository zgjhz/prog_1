#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include "loginwindow.h"
#include "questionwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onLoginButtonClicked();
    void onLoginSucces(const QString &username, const QString &subject);

private:
    Ui::MainWindow *ui;
    QLabel *loginLabel;
    QPushButton *loginButton;
    LoginWindow *loginWindow;
    QuestionWidget *questionWidget;
    QVBoxLayout *vLayout;
};
#endif // MAINWINDOW_H
