#ifndef ADDMAILBOXFORM_H
#define ADDMAILBOXFORM_H

#include <QWidget>
#include "account.h"

namespace Ui {
class AddMailboxForm;
}

class AddMailboxForm : public QWidget
{
    Q_OBJECT

public:
    explicit AddMailboxForm(QVector<IMAP_Account*>* parent_list, QWidget *parent = nullptr);
    ~AddMailboxForm();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::AddMailboxForm *ui;
    QVector<IMAP_Account*>* parent_list;
};

#endif // ADDMAILBOXFORM_H
