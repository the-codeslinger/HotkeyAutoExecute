#include <QFile>
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QStandardItemModel>

#include <hotkeyconfigwriter.h>
#include <hotkeyitem.h>

HotkeyConfigWriter::HotkeyConfigWriter(const QString& configFilename)
    : configFilename_(configFilename)
{
}

bool
HotkeyConfigWriter::write(QStandardItemModel* data)
{
    auto out = QFile{configFilename_};
    if (!out.open(QIODevice::WriteOnly)) {
        qWarning() << "Could not open config file for writing '" << configFilename_
                   << "'. " << out.errorString();
        return false;
    }
    
    auto configArray = QJsonArray{};
    
    auto itemCount = data->rowCount();
    for (auto c = 0; c < itemCount; c++) {
        auto listItem = data->item(c);
        auto hotkeyItem = qvariant_cast<HotkeyItem>(listItem->data());
        
        configArray.append(hotkeyItemToJsonObject(hotkeyItem));
    }
    
    out.write(QJsonDocument{configArray}.toJson());
    out.close();
    return true;
}

QJsonObject 
HotkeyConfigWriter::hotkeyItemToJsonObject(const HotkeyItem& hotkeyItem) const
{
    auto nativeModifiersArray = QJsonArray{};
    for (auto mod : hotkeyItem.nativeSequence.modifiers) {
        nativeModifiersArray.append(QString::number(mod));
    }
    
    auto hotkeyObject = QJsonObject{};
    hotkeyObject["name"] = hotkeyItem.name;
    hotkeyObject["code"] = hotkeyItem.sequenceText;
    hotkeyObject["native-key"] = QString::number(hotkeyItem.nativeSequence.key);
    hotkeyObject["native-modifiers"] = nativeModifiersArray;
    return hotkeyObject;
}
