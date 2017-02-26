/* ============================================================
 *
 * Copyright (C) 2017 by Alexander Trufanov
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License or (at your option) version 3 or any later version
 * accepted by the membership of KDE e.V. (or its successor approved
 *  by the membership of KDE e.V.), which shall act as a proxy
 * defined in Section 14 of version 3 of the license.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License.
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 *
 * ============================================================ */

#ifndef DBusInterface_h
#define DBusInterface_h

#include <QtDBus/QDBusConnection>
#include <QDebug>
#include <KSaneWidget>
#include <QStringList>


#define dbus_adress "org.kde.skanlite"
const QLatin1String default_profile("1");

class DBusInterface : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", dbus_adress)

public:

    DBusInterface(QObject* parent = NULL) : QObject(parent) {}
    bool setupDBusInterface();
    QStringList response;

private:
    //QTBUG-7341
    void QDBusViewer_String_to_QStrigList(QStringList &sl);

Q_SIGNALS:
    void requested_scan();
    void requested_scan_cancel();
    void requested_current_scanner_options();
    void requested_default_scanner_options();
    void requested_device_name();
    void requested_save_scanner_options_to_profile(QStringList options, QString profile);
    void requested_switch_to_profile(QString profile);

public Q_SLOTS:

    Q_SCRIPTABLE void scan() { emit requested_scan(); }
    Q_SCRIPTABLE void scan_cancel() { emit requested_scan_cancel(); }

    Q_SCRIPTABLE QStringList get_selected_device_name()
    {
        response.clear();
        emit requested_device_name();
        return response;
    }

    Q_SCRIPTABLE QStringList get_current_scanner_options()
    {
        response.clear();
        emit requested_current_scanner_options();
        return response;
    }

    Q_SCRIPTABLE QStringList get_default_scanner_options()
    {
        response.clear();
        emit requested_default_scanner_options();
        return response;
    }

    Q_SCRIPTABLE void save_scanner_options_to_profile(QStringList options, QString profile = default_profile)
    {
        QDBusViewer_String_to_QStrigList(options);
        emit requested_save_scanner_options_to_profile(options, profile);
    }

    Q_SCRIPTABLE void save_current_scanner_options_to_profile(QString profile = default_profile)
    {
        response.clear();
        emit requested_current_scanner_options();
        emit requested_save_scanner_options_to_profile(response, profile);
    }

    Q_SCRIPTABLE void switch_to_profile(QString profile = default_profile)
    {
        emit requested_switch_to_profile(profile);
    }



Q_SIGNALS:

    // Below are 5 signals which are just forwarded from KSaneWidget.
    // You can take a look in KSaneWidget.h for detailed arguments description

    Q_SCRIPTABLE void scanDone(int status, const QString &strStatus);
    Q_SCRIPTABLE void userMessage(int type, const QString &strStatus);
    Q_SCRIPTABLE void scanProgress(int percent);
    //    Q_SCRIPTABLE void availableDevices(const QList<KSaneIface::KSaneWidget::DeviceInfo> &deviceList);
    Q_SCRIPTABLE void buttonPressed(const QString &optionName, const QString &optionLabel, bool pressed);
};

#endif

