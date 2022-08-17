#pragma once

#include <QString>

class QJsonObject;
class QStandardItemModel;

class HotkeyItem;

/**
 * Reads the hotkey settings the user created from a JSON file.
 * 
 * For simplicity, this class operates directly on the data model of the `QListView`.
 */
class HotkeyConfigReader
{
public:
    /**
     * Construct a new HotkeyConfigReader object.
     * 
     * @param configFilename The filename of the JSON settings file.
     */
    HotkeyConfigReader(const QString& configFilename);

    /**
     * Reads the contents of the `QListView` data model from the JSON file at the location
     * specified in the constructor.
     * 
     * @param data The `HotkeyItem` object read from the file are appended to the data 
     *             model of the `QListView`.
     * 
     * @return true Reading was successful.
     * @return false Reading failed, e.g., the file does not exist.
     */
    bool read(QStandardItemModel* data);
    
private:
    QString configFilename_;
    
    /**
     * Parses the JSON representation of a `HotkeyItem` back into a C++ object.
     */
    HotkeyItem jsonObjectToHotkeyItem(const QJsonObject& jsonObject) const;
};
