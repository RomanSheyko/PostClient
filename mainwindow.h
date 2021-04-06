#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "account.h"
#include <QVector>
#include <QTreeWidget>
#include <QMap>
#include <QListWidget>
#include <QListWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionAdd_account_triggered();
    void on_add_mailbox_close();

    void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_actionNew_message_triggered();

    void on_download_attach_clicked();

private:
    Ui::MainWindow *ui;
    QVector<IMAP_Account*> account_list;
    QMap<int, mailio::message> messages;
    mailio::message cur_msg;
};
#endif // MAINWINDOW_H
