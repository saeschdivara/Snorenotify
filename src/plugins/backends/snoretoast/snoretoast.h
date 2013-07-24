#ifndef TOASTER_H
#define TOASTER_H

#include "core/plugins/snorebackend.h"
#include <QProcess>

class SnoreToast : public Snore::SnoreBackend
{
    Q_OBJECT
    Q_INTERFACES(Snore::SnoreBackend)
    Q_PLUGIN_METADATA(IID "org.Snore.NotificationBackend/1.0")
public:
    SnoreToast();
    ~SnoreToast();
    bool init(Snore::SnoreCore *snore);


    // SnoreBackend interface
public slots:
    void slotRegisterApplication(Snore::Application *application);
    void slotUnregisterApplication(Snore::Application *application);
    void slotNotify(Snore::Notification notification);

private slots:
    void slotToastNotificationClosed(int code, QProcess::ExitStatus);

private:
    QString m_appID;


};

#endif // TOASTER_H
