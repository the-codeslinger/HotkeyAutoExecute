#include <QFile>
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <QKeySequence>
#include <QJsonDocument>
#include <QStandardItemModel>

#include <hotkeyconfigreader.h>
#include <hotkeyitem.h>

HotkeyConfigReader::HotkeyConfigReader(const QString& configFilename)
    : configFilename_(configFilename)
{
}

bool
HotkeyConfigReader::read(QStandardItemModel* data)
{
    auto in = QFile{configFilename_};
    if (!in.open(QIODevice::ReadOnly)) {
        qWarning() << "Could not open config file for reading '" << configFilename_
                   << "'. " << in.errorString();
        return false;
    }
    
    // Assume a not too large file. It's a tiny tool after all.
    auto configBytes = in.readAll();
    
    auto jsonDocument = QJsonDocument::fromJson(configBytes);
    
    auto hotkeyArray = jsonDocument.array();
    for (auto arrayItem : hotkeyArray) {
        auto hotkeyItem = jsonObjectToHotkeyItem(arrayItem.toObject());
        
        auto listItemData = QVariant{};
        listItemData.setValue(hotkeyItem);
        
        auto listItem = new QStandardItem(hotkeyItem.name);
        listItem->setData(listItemData);
        data->appendRow(listItem);
    }
    
    in.close();
    return true;
}

HotkeyItem 
HotkeyConfigReader::jsonObjectToHotkeyItem(const QJsonObject& jsonObject) const
{
    auto sequenceText = jsonObject["code"].toString();
    auto nativeKey = jsonObject["native-key"].toString().toUInt();
    auto nativeModifiersArray = jsonObject["native-modifiers"].toArray(); 
    
    auto modifiers = QSet<quint32>{};
    for (auto arrayItem : nativeModifiersArray) {
        modifiers.insert(arrayItem.toString().toUInt());
    }
    
    return HotkeyItem{
        jsonObject["name"].toString(), 
        sequenceText,
        NativeKeySequence{nativeKey, modifiers}};
}
