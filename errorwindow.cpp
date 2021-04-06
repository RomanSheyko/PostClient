#include "errorwindow.h"
#include "ui_errorwindow.h"

ErrorWindow::ErrorWindow(const QString& error_message, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ErrorWindow)
{
    ui->setupUi(this);
    ui->error_text->setText(error_message);
}

ErrorWindow::~ErrorWindow()
{
    delete ui;
}

void ErrorWindow::on_ok_button_clicked()
{
    this->close();
}
