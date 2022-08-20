#pragma once

#include <QString>

class QJsonObject;
class QStandardItemModel;

class HotkeyItem;

/**
 * Writes the hotkey settings the user created to a JSON file.
 * 
 * For simplicity, this class operates directly on the data model of the `QListView`.
 */
class HotkeyConfigWriter
{
public:
    /**
     * Construct a new HotkeyConfigWriter object.
     * 
     * @param configFilename The filename of the JSON settings file. If this is an
     *                       absolute filename then the path hierarchy must be created
     *                       before trying to write the file.
     */
    HotkeyConfigWriter(const QString& configFilename);

    /**
     * Writes the contents of the `QListView` data model to the JSON file at the location
     * specified in the constructor.
     * 
     * @param data The data model that contains the `HotkeyItem` objects with the relevant
     *             information.
     * 
     * @return true Writing was successful.
     * @return false Writing failed, e.g., the folder hierarchy does not exist and the
     *               file cannot be created.
     */
    bool write(QStandardItemModel* data);
    
private:
    QString configFilename_;
    
    /**
     * Creates a JSON object from the `HotkeyItem` object with the following structure.
     * 
     * \code {.json}
     * {
     *   "name": "<user defined name>",
     *   "code": "<currently unused>",
     *   "native-key": "<Windows virtual key code>",
     *   "native-modifiers": [
     *     "<List of Windows virtual key codes for the modifier keys, e.g. SHIFT>"
     *   ]
     * }
     * \endcode
     */
    QJsonObject hotkeyItemToJsonObject(const HotkeyItem& hotkeyItem) const;
};
