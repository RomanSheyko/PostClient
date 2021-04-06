#include "newmessageform.h"
#include "ui_newmessageform.h"
#include <QFileDialog>
#include <fstream>

NewMessageForm::NewMessageForm(QVector<IMAP_Account*>* parent_list,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewMessageForm),
    parent_list(parent_list)
{
    ui->setupUi(this);
    for(auto el : *parent_list)
    {
        ui->from_box->addItem(el->getEmail());
    }
    ui->message->append("\n\n\n\n");
}

NewMessageForm::~NewMessageForm()
{
    delete ui;
}



void NewMessageForm::on_attachment_button_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("File to attach"));
    std::string extantion;
    int ext_pos = fileName.toStdString().find(".");
    extantion = fileName.toStdString().substr(ext_pos);
    std::size_t found = fileName.toStdString().rfind("/");
    std::string name = "";
    if (found!=std::string::npos)
        name = fileName.toStdString().substr(found + 1);
    std::ifstream ifs(fileName.toStdString());
    message.attach(ifs, name, mailio::message::media_type_t::MULTIPART, extantion);
    QString cap = "<figure><img src=\"/Users/roman/Documents/regular-document.png\" width=\"60\" height=\"50\"><br><figcaption>" + QString(name.c_str()) + "</figcaption></figure><br>";
    ui->message->insertHtml(cap);
}

void NewMessageForm::on_send_button_clicked()
{
    message.from(mailio::mail_address("Roman", ui->from_box->currentText().toStdString()));
    message.subject(ui->subject->text().toStdString());
    message.content(ui->message->toPlainText().toStdString());
    message.add_recipient(mailio::mail_address("Roman", ui->to->text().toStdString()));
    message.content_transfer_encoding(mailio::mime::content_transfer_encoding_t::BASE_64);
    message.content_type(mailio::message::media_type_t::MULTIPART, "mixed");
    for(auto el : *parent_list)
    {
        if(el->getEmail() == ui->from_box->currentText())
        {
            el->getSmtp().submit(message);
        }
    }
    this->close();
}
