#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <mailio/message.hpp>
#include <mailio/smtp.hpp>
#include <mailio/pop3.hpp>
#include <mailio/imap.hpp>
#include <QString>

enum mailbox_type
{
    IMAP,
    POP3
};

class Account
{
public:
    Account(const QString& smtp_address, const QString& email, const QString& password, int port);
    mailio::smtps& getSmtp();
    virtual void authenticate();
    virtual ~Account();
    QString getAddress();
    QString getEmail();
    QString getPassword();
protected:
    mailio::smtps smtp_conn;
    QString address;
    QString email;
    QString password;
};

class IMAP_Account : public Account
{
public:
    IMAP_Account(const QString& smtp_address, const QString& email, const QString& password, int port, const QString& imap_address, int imap_port);
    mailio::imaps& getImap();
    ~IMAP_Account();
    void authenticate() override;
private:
    mailio::imaps imap_conn;
};

class POP3_Account : public Account
{
public:
    POP3_Account(QString& pop3_address);
private:
    mailio::pop3s pop3_conn;
};

#endif // ACCOUNT_H
