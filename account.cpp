#include "account.h"

Account::Account(const QString& smtp_address, const QString& email, const QString& password, int port) : smtp_conn(smtp_address.toStdString(), port),
    email(email), password(password)
{
}

QString Account::getAddress()
{
    return address;
}

QString Account::getEmail()
{
    return email;
}

QString Account::getPassword()
{
    return password;
}

IMAP_Account::IMAP_Account(const QString& smtp_address, const QString& email, const QString& password, int port, const QString& imap_address, int imap_port) :
    Account(smtp_address, email, password, port),
    imap_conn(imap_address.toStdString(), imap_port)
{
}

Account::~Account() = default;

mailio::smtps& Account::getSmtp()
{
    return smtp_conn;
}

IMAP_Account::~IMAP_Account() = default;

void Account::authenticate()
{
    smtp_conn.authenticate(email.toStdString(), password.toStdString(),
                           mailio::smtps::auth_method_t::START_TLS);
}

void IMAP_Account::authenticate()
{
    smtp_conn.authenticate(email.toStdString(), password.toStdString(),
                           mailio::smtps::auth_method_t::START_TLS);
    imap_conn.authenticate(email.toStdString(), password.toStdString(),
                           mailio::imaps::auth_method_t::LOGIN);
}

mailio::imaps& IMAP_Account::getImap()
{
    return imap_conn;
}
