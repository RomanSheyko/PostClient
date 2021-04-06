#ifndef NEWMESSAGEFORM_H
#define NEWMESSAGEFORM_H

#include <QWidget>
#include <QVector>
#include "account.h"
#include <mailio/message.hpp>

namespace Ui {
class NewMessageForm;
}

class NewMessageForm : public QWidget
{
    Q_OBJECT

public:
    explicit NewMessageForm(QVector<IMAP_Account*>* parent_list, QWidget *parent = nullptr);
    ~NewMessageForm();

private slots:
    void on_attachment_button_clicked();

    void on_send_button_clicked();

private:
    Ui::NewMessageForm *ui;
    QVector<IMAP_Account*> *parent_list;
    mailio::message message;
};

#endif // NEWMESSAGEFORM_H
