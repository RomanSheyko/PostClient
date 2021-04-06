#include "addmailboxform.h"
#include "ui_addmailboxform.h"
#include "errorwindow.h"

AddMailboxForm::AddMailboxForm(QVector<IMAP_Account*>* parent_list, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddMailboxForm),
    parent_list(parent_list)
{
    ui->setupUi(this);
}

AddMailboxForm::~AddMailboxForm()
{
    delete ui;
}

void AddMailboxForm::on_buttonBox_accepted()
{
    if(ui->email_edit->text().isEmpty() ||
            ui->incoming_server_edit->text().isEmpty() ||
            ui->outgoing_server_edit->text().isEmpty() ||
            ui->password_edit->text().isEmpty())
    {
        return;
    }
    else {
        IMAP_Account* new_acc = nullptr;
        try {
            new_acc = new IMAP_Account(ui->outgoing_server_edit->text(), ui->email_edit->text(),
                                       ui->password_edit->text(), 587,
                                       ui->incoming_server_edit->text(), 993);
            new_acc->authenticate();
        }  catch (std::runtime_error& e) {
            ErrorWindow err(e.what(), this);
            err.exec();
            if(new_acc != nullptr) delete new_acc;
            return;
        }

        parent_list->push_back(new_acc);
        this->close();
    }
}

void AddMailboxForm::on_buttonBox_rejected()
{
    this->close();
}
