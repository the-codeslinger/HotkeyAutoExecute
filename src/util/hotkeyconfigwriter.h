#pragma once

#include <QString>

class QJsonObject;
class QStandardItemModel;

class HotkeyItem;

class HotkeyConfigWriter
{
public:
    HotkeyConfigWriter(const QString& configFilename);

    bool write(QStandardItemModel* data);
    
private:
    QString configFilename_;
    
    QJsonObject hotkeyItemToJsonObject(const HotkeyItem& hotkeyItem) const;
};
