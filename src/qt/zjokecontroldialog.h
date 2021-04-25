// Copyright (c) 2017-2018 The JokeCoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ZJOKECONTROLDIALOG_H
#define ZJOKECONTROLDIALOG_H

#include <QDialog>
#include <QTreeWidgetItem>
#include "zjoke/zerocoin.h"
#include "privacydialog.h"

class CZerocoinMint;
class WalletModel;

namespace Ui {
class ZJokeControlDialog;
}

class CZJokeControlWidgetItem : public QTreeWidgetItem
{
public:
    explicit CZJokeControlWidgetItem(QTreeWidget *parent, int type = Type) : QTreeWidgetItem(parent, type) {}
    explicit CZJokeControlWidgetItem(int type = Type) : QTreeWidgetItem(type) {}
    explicit CZJokeControlWidgetItem(QTreeWidgetItem *parent, int type = Type) : QTreeWidgetItem(parent, type) {}

    bool operator<(const QTreeWidgetItem &other) const;
};

class ZJokeControlDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ZJokeControlDialog(QWidget *parent);
    ~ZJokeControlDialog();

    void setModel(WalletModel* model);

    static std::set<std::string> setSelectedMints;
    static std::set<CMintMeta> setMints;
    static std::vector<CMintMeta> GetSelectedMints();

private:
    Ui::ZJokeControlDialog *ui;
    WalletModel* model;
    PrivacyDialog* privacyDialog;

    void updateList();
    void updateLabels();

    enum {
        COLUMN_CHECKBOX,
        COLUMN_DENOMINATION,
        COLUMN_PUBCOIN,
        COLUMN_VERSION,
        COLUMN_PRECOMPUTE,
        COLUMN_CONFIRMATIONS,
        COLUMN_ISSPENDABLE
    };
    friend class CZJokeControlWidgetItem;

private slots:
    void updateSelection(QTreeWidgetItem* item, int column);
    void ButtonAllClicked();
};

#endif // ZJOKECONTROLDIALOG_H
