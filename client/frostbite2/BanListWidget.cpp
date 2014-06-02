/*
 * Copyright (C) 2014 The OpenRcon Project.
 *
 * This file is part of OpenRcon.
 *
 * OpenRcon is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * OpenRcon is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OpenRcon.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QMenu>

#include "BanListWidget.h"
#include "ui_BanListWidget.h"
#include "FrostbiteConnection.h"
#include "BF4CommandHandler.h"

BanListWidget::BanListWidget(FrostbiteConnection *connection, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BanListWidget),
    m_connection(connection),
    m_commandHandler(dynamic_cast<Frostbite2CommandHandler *>(connection->getCommandHandler()))
{
    ui->setupUi(this);

    // Banlist
    menu_bl_banList = new QMenu(ui->tableWidget_bl_banList);
    action_bl_banList_remove = new QAction(tr("Remove"), menu_bl_banList);

    menu_bl_banList->addAction(action_bl_banList_remove);

    /* Commands */
    // BanList
    connect(m_commandHandler, &Frostbite2CommandHandler::onBanListListCommand, this, &BanListWidget::onBanListListCommand);

    /* User Interface */
    // Banlist
    connect(ui->tableWidget_bl_banList, &QTableWidget::customContextMenuRequested, this, &BanListWidget::tableWidget_bl_banList_customContextMenuRequested);
    connect(action_bl_banList_remove,   &QAction::triggered,                      this, &BanListWidget::action_bl_banList_remove_triggered);
}

BanListWidget::~BanListWidget()
{
    delete ui;
}

/* Commands */
void BanListWidget::onBanListListCommand(const BanList &banList)
{
    setBanlist(banList);
}

/* User Interface */
void BanListWidget::tableWidget_bl_banList_customContextMenuRequested(const QPoint &pos)
{
    if (ui->tableWidget_bl_banList->itemAt(pos)) {
        menu_bl_banList->exec(QCursor::pos());
    }
}

void BanListWidget::action_bl_banList_remove_triggered()
{
    int row = ui->tableWidget_bl_banList->currentRow();
    QString idType = ui->tableWidget_bl_banList->item(row, 0)->text();
    QString player = ui->tableWidget_bl_banList->item(row, 1)->text();

    if (!idType.isEmpty() && !player.isEmpty()) {
        ui->tableWidget_bl_banList->removeRow(row);

        m_commandHandler->sendBanListRemoveCommand(idType, player);
    }
}

void BanListWidget::addBanListItem(const QString &idType, const QString &id, const QString &banType, int seconds, int rounds, const QString &reason)
{
    int row = ui->tableWidget_bl_banList->rowCount();

    ui->tableWidget_bl_banList->insertRow(row);
    ui->tableWidget_bl_banList->setItem(row, 0, new QTableWidgetItem(idType));
    ui->tableWidget_bl_banList->setItem(row, 1, new QTableWidgetItem(id));
    ui->tableWidget_bl_banList->setItem(row, 2, new QTableWidgetItem(banType));
    ui->tableWidget_bl_banList->setItem(row, 3, new QTableWidgetItem(QString::number(seconds)));
    ui->tableWidget_bl_banList->setItem(row, 4, new QTableWidgetItem(QString::number(rounds)));
    ui->tableWidget_bl_banList->setItem(row, 5, new QTableWidgetItem(reason));
}

void BanListWidget::setBanlist(const QList<BanListEntry> &banList)
{
    ui->tableWidget_bl_banList->clearContents();
    ui->tableWidget_bl_banList->setRowCount(0);

    for (BanListEntry entry : banList) {
        addBanListItem(entry.idType, entry.id, entry.banType, entry.seconds, entry.rounds, entry.reason);
    }
}
