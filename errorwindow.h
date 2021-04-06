#ifndef ERRORWINDOW_H
#define ERRORWINDOW_H

#include <QDialog>

namespace Ui {
class ErrorWindow;
}

class ErrorWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ErrorWindow(const QString& error_message, QWidget *parent = nullptr);
    ~ErrorWindow();

private slots:
    void on_ok_button_clicked();

private:
    Ui::ErrorWindow *ui;
};

#endif // ERRORWINDOW_H
