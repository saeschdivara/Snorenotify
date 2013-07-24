/*
    SnoreNotify is a Notification Framework based on Qt
    Copyright (C) 2013  Patrick von Reth <vonreth@kde.org>


    SnoreNotify is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    SnoreNotify is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with SnoreNotify.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "snorebackend.h"
#include "../snore.h"
#include "../application.h"
#include "../notification/notification.h"

#include <QTimer>
#include <QDir>
#include <QDebug>

namespace Snore{

SnoreBackend::SnoreBackend (const QString &name , bool canCloseNotification, bool supportsRichtext) :
    SnorePlugin ( name ),
    m_canCloseNotification(canCloseNotification),
    m_supportsRichtext(supportsRichtext)
{

}

SnoreBackend::~SnoreBackend()
{
    qDebug()<<"Deleting"<<name();
}


bool SnoreBackend::init( SnoreCore *snore )
{
    if(!SnorePlugin::init(snore))
        return false;
    connect( snore,SIGNAL( applicationInitialized( Snore::Application* ) ),this,SLOT( slotRegisterApplication( Snore::Application* ) ) );
    connect( snore,SIGNAL( applicationRemoved( Snore::Application* ) ),this,SLOT( slotUnregisterApplication( Snore::Application* ) ) );

    foreach(Application *a,snore->aplications()){
        this->slotRegisterApplication(a);
    }

    return true;
}


void SnoreBackend::requestCloseNotification ( Notification notification,NotificationEnums::CloseReasons::closeReasons reason )
{
    if(canCloseNotification())
    {
        closeNotification(notification,reason);
    }
}

void SnoreBackend::closeNotification(Notification n, NotificationEnums::CloseReasons::closeReasons reason)
{
    if(!n.isValid())
    {
        qWarning() << "Closing a notification a second time, this should not heappen";
        return;
    }
    if(m_activeNotifications.contains(n.id()))
    {
        m_activeNotifications.remove(n.id());
    }
    n.setCloseReason(reason);
    slotCloseNotification(n);
    emit closeNotification(n);
}

void SnoreBackend::slotCloseNotification(Notification notification)
{
    Q_UNUSED(notification)
}

SnoreSecondaryBackend::SnoreSecondaryBackend(const QString &name, bool supportsRhichtext)
    :SnoreBackend(name,false,supportsRhichtext)
{

}

SnoreSecondaryBackend::~SnoreSecondaryBackend()
{
    qDebug()<<"Deleting"<<name();
}

bool SnoreSecondaryBackend::init(SnoreCore *snore)
{
    connect( snore,SIGNAL( slotNotify(SnoreCore::Notification) ),this,SLOT( slotNotify( SnoreCore::Notification ) ) );
    return SnoreBackend::init(snore);
}

Snore::Notification SnoreBackend::getActiveNotificationByID(uint id)
{
    return m_activeNotifications[id];
}

bool SnoreBackend::canCloseNotification()
{
    return m_canCloseNotification;
}

bool SnoreBackend::supportsRichtext()
{
    return m_supportsRichtext;
}

void SnoreBackend::addActiveNotification(Notification n)
{
    m_activeNotifications[n.id()] = n;
}


}
