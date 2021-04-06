#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addmailboxform.h"
#include <QMdiSubWindow>
#include "errorwindow.h"
#include "newmessageform.h"
#include <cstdio>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->download_attach->setEnabled(false);
}

MainWindow::~MainWindow()
{
    for(auto el : account_list)
    {
        delete el;
    }
    delete ui;
}


void MainWindow::on_actionAdd_account_triggered()
{
    auto *w = new AddMailboxForm(&account_list);
    w->setParent(this);
    w->setWindowFlags(Qt::Window);
    w->setAttribute(Qt::WA_DeleteOnClose);
    w->setAttribute(Qt::WA_ShowModal);
    QObject::connect(w, SIGNAL(destroyed()), this, SLOT(on_add_mailbox_close()));
    w->show();
}

void MainWindow::on_add_mailbox_close()
{
    ui->treeWidget->clear();
    QTreeWidget * tree = ui->treeWidget;

    for(auto& el : account_list)
    {
        QTreeWidgetItem * topLevel = new QTreeWidgetItem();
        topLevel->setText(0, el->getEmail());

        for(int i=0; i<1; i++)
        {
            QTreeWidgetItem * item = new QTreeWidgetItem();
            item->setText(0,"inbox");
            topLevel->addChild(item);
        }

        tree->addTopLevelItem(topLevel);
    }
}

void MainWindow::on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    QTreeWidgetItem *parent = item->parent();
    if(parent != nullptr)
    {
        QString acc = parent->text(0);
        for(auto& el : account_list)
        {
            if(el->getEmail() == acc)
            {
                ui->listWidget->clear();
                mailio::imaps::mailbox_stat_t stat = el->getImap().statistics(item->text(0).toStdString());
                unsigned long mailcount = stat.messages_no;
                for(int i = static_cast<int>(mailcount) - 1; i > static_cast<int>(mailcount) - 100; i--)
                {
                    try {
                        mailio::message msg;
                        msg.line_policy(mailio::codec::line_len_policy_t::MANDATORY, mailio::codec::line_len_policy_t::MANDATORY);
                        el->getImap().fetch(item->text(0).toStdString(), i, msg);
                        QListWidgetItem *newItem = new QListWidgetItem;
                        messages[i] = msg;
                        newItem->setData(Qt::UserRole, QVariant(i));
                        QString sub(msg.subject().c_str());
                        if(sub.isEmpty()) sub = "(No subject)";
                        newItem->setText(sub);
                        ui->listWidget->addItem(newItem);
                    }
                    catch (std::runtime_error& e)
                    {
                        std::cout << e.what() << std::endl;
                    }
                }
            }
        }
    }
}

void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    int num = item->data(Qt::UserRole).toInt();
    mailio::message msg = messages[num];
    mailio::mailboxes mailbox = msg.from();
    std::vector<mailio::mail_address> addrs = mailbox.addresses;
    QString from = "From: ";
    for(auto& el : addrs)
    {
        from += QString(el.address.c_str());
    }
    ui->from_label->setText(from);
    ui->title_label->setText(QString("Subject: ") + QString(msg.subject().c_str()));
    ui->textBrowser->clear();
    ui->textBrowser->setText(QString(msg.content().c_str()));
    if(msg.attachments_size() > 0)
        ui->download_attach->setEnabled(true);
    else ui->download_attach->setEnabled(false);
    cur_msg = msg;
}

void MainWindow::on_actionNew_message_triggered()
{
    auto *w = new NewMessageForm(&account_list);
    w->setParent(this);
    w->setWindowFlags(Qt::Window);
    w->setAttribute(Qt::WA_DeleteOnClose);
    w->setAttribute(Qt::WA_ShowModal);
    w->show();
}

void MainWindow::on_download_attach_clicked()
{
    if(cur_msg.attachments_size() > 0)
    {
        for(size_t i = 1; i < cur_msg.attachments_size() + 1; i++)
        {
            std::string file_name = "attachment" + std::to_string(i);
            std::ofstream attch(file_name, std::ios::binary);
            std::string rname;
            cur_msg.attachment(i, attch, rname);
            std::rename(file_name.c_str(), rname.c_str());
        }
    }
}
