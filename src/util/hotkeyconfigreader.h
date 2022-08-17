#pragma once

#include <QString>

class QJsonObject;
class QStandardItemModel;

class HotkeyItem;

class HotkeyConfigReader
{
public:
    HotkeyConfigReader(const QString& configFilename);

    bool read(QStandardItemModel* data);
    
private:
    QString configFilename_;
    
    HotkeyItem jsonObjectToHotkeyItem(const QJsonObject& jsonObject) const;
};
