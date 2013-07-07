/*
    SnoreNotify is a Notification Framework based on Qt
    Copyright (C) 2013  Patrick von Reth <vonreth@kde.org>


    VSD is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    VSD is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with SnarlNetworkBridge.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "snorefrontend.h"
#include "../snore.h"

#include <QTimer>
#include <QPluginLoader>
#include <QDir>
#include <QDebug>

namespace Snore{

SnoreFrontend::SnoreFrontend ( const QString &name ) :
    SnorePlugin ( name )
{

}

SnoreFrontend::~SnoreFrontend()
{
    qDebug()<<"Deleting"<<name();
}

bool SnoreFrontend::init( SnoreCore *snore )
{
    if(!SnorePlugin::init(snore))
        return false;
    connect( snore,SIGNAL ( notificationClosed( Snore::Notification ) ),this,SLOT ( notificationClosed( Snore::Notification) ) );
    return true;
}
}