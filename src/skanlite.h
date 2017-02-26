/* ============================================================
 *
 * Copyright (C) 2007-2012 by Kåre Särs <kare.sars@iki .fi>
 * Copyright (C) 2014 by Gregor Mitsch: port to KDE5 frameworks
 * Copyright (C) 2017 by Alexander Trufanov: D-Bus interface
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

#ifndef Skanlite_h
#define Skanlite_h

#include <QDir>
#include <QDialog>

#include <KSaneWidget>

#include "ui_settings.h"
#include "ImageViewer.h"
#include "DBusInterface.h"

class SaveLocation;
class KAboutData;

using namespace KSaneIface;

class Skanlite : public QDialog
{
    Q_OBJECT

public:
    explicit Skanlite(const QString &device, QWidget *parent);
    void setAboutData(KAboutData *aboutData);

private:
    // Order of items in save mode combo-box
    enum SaveMode {
        SaveModeManual = 0,
        SaveModeAskFirst = 1,
    };

    void readSettings();
    void doSaveImage(bool askFilename = true);
    void loadScannerOptions();

    void readScannerOptions(const QString groupName, QMap <QString, QString> &opts);
    void writeScannerOptions(const QString groupName, const QMap <QString, QString> &opts);
    QStringList serializeScannerOptions(QMap<QString, QString> &opts);
    void deserializeScannerOptions(QStringList settings, QMap<QString, QString> &opts);


public Q_SLOTS:
    void showSettingsDialog();
    void getDir();
    void imageReady(QByteArray &, int, int, int, int);
    void saveImage();
    void showAboutDialog();
    void saveWindowSize();

    void saveScannerOptions();
    void resetToDefaultScannerOptions();

    void availableDevices(const QList<KSaneWidget::DeviceInfo> &deviceList);

    void alertUser(int type, const QString &strStatus);
    void buttonPressed(const QString &optionName, const QString &optionLabel, bool pressed);

    void showHelp();

    // for D-Bus interface
    void sendCurrentScannerOptions();
    void sendDefaultScannerOptions();
    void saveScannerOptionsToProfile(QStringList options, QString profile);
    void switchToProfile(QString profile);
    void sendDeviceName();

protected:
    void closeEvent(QCloseEvent *event);   

public: KSaneWidget             *m_ksanew = nullptr;
private:
    KAboutData              *m_aboutData;    
    Ui::SkanliteSettings     m_settingsUi;
    QDialog                 *m_settingsDialog = nullptr;
    QDialog                 *m_showImgDialog = nullptr;
    // having this variable here is not so nice; ShowImgageDialog should be separate class
    QPushButton             *m_showImgDialogSaveButton = nullptr;
    SaveLocation            *m_saveLocation = nullptr;
    QString                  m_deviceName;
    QMap<QString, QString>    m_defaultScanOpts;
    QImage                   m_img;
    QByteArray               m_data;
    int                      m_width;
    int                      m_height;
    int                      m_bytesPerLine;
    int                      m_format;

    ImageViewer              m_imageViewer;
    DBusInterface            m_dbusInterface;
    QStringList              m_filterList;
    QStringList              m_filter16BitList;
    QStringList              m_typeList;
    bool                     m_firstImage;
};

#endif

