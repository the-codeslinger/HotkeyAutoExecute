#include "mainwindow.h"

#include <QDir>
#include <QDebug>
#include <QApplication>
#include <QStandardPaths>

static QString CONFIG_FILENAME = "hotkeys.json";

QString createConfigDir()
{
    auto configDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    auto dir = QDir{};
    if (!dir.exists(configDir)) {
        if (!dir.mkpath(configDir)) {
            qWarning() << "Could not create config folder '" << configDir << "'.";
            return "";
        }
    }
    return configDir;
}

QString createConfigFilename(const QString& configDir)
{
    auto filename = configDir;
    if (!configDir.endsWith(QDir::separator())) {
        filename += QDir::separator();
    }
    filename += CONFIG_FILENAME;
    return filename;
}

int main(int argc, char *argv[])
{
    QApplication a{argc, argv};
    a.setOrganizationName("The-Codeslinger");
    a.setApplicationName("HotkeyAutoExecute");
    
    
    auto configDir = createConfigDir();
    if (configDir.isEmpty()) {
        return 1;
    }
    
    auto configFilename = createConfigFilename(configDir);
    auto configWriter = new HotkeyConfigWriter(configFilename);
    auto configReader = new HotkeyConfigReader(configFilename);
    
    MainWindow w{configWriter, configReader};
    w.show();
    return a.exec();
}
