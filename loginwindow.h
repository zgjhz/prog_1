#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>

class LoginWindow : public QWidget {
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

signals:
    void loginSuccess(const QString &username, const QString &subject);

private slots:
    void onContinueButtonClicked();

private:
    QLineEdit *loginEdit;
    QComboBox *subjectBox;
    QPushButton *continueButton;
};

#endif // LOGINWINDOW_H
