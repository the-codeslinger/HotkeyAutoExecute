#pragma once

#include <QSet>
#include <QTimer>
#include <QMainWindow>
#include <QStandardItemModel>

#include <specialkeys.h>
#include <specialmodifiers.h>
#include <hotkeyconfigreader.h>
#include <hotkeyconfigwriter.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * The main and only window of the application.
 * 
 * It contains input widgets for the user to configure one or more frequently used
 * hotkeys. It contains all the UI handling logic, and also reads and writes the user
 * settings from and to a JSON configuration file (using `HotkeyConfigReader` and
 * `HotkeyConfigReader`).
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    /**
     * Construct a new MainWindow object.
     * 
     * @param configWriter Writes the configuration to a JSON file.
     * @param configReader Reads the configuration from a JSON file.
     * @param parent `QWidget` that own this window. `nullptr` in this applciation.
     */
    MainWindow(
            HotkeyConfigWriter* configWriter,
            HotkeyConfigReader* configReader,
            QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    /**
     * User toggles the special keys group box.
     */
    void toggleSpecialKeys(bool toggled);
    /**
     * User clicked on the "Start" button to begin the periodic hotkey emulation.
     */
    void executeHotkeyInterval();
    /**
     * The user clicked the "Add hotkey" button.
     */
    void addHotkey();
    /**
     * The user clicked the "Remove hotkey" button.
     */
    void removeHotkey();
    /**
     * Periodically triggered by the `QTimer` to execute the selected hotkey.
     */
    void triggerHotkey();

private:
    Ui::MainWindow* ui_;
    QStandardItemModel* availableHotkeysModel_;
    QTimer* timer_;
    
    HotkeyConfigWriter* configWriter_;
    HotkeyConfigReader* configReader_;

    void startHotkeyInterval();
    void stopHotkeyInterval();

    int determineIntervalMultiplier(const QString& value) const;
    
    SpecialModifiers selectedSpecialModifiers() const;
    SpecialKeys selectedSpecialKeys() const;
    
    void resetHotkeyName();
    void resetModifiers();
    void resetSpecialKeys();
    void resetKeySequenceEdit();
    
    void toggleUiElements(bool enable);
};
