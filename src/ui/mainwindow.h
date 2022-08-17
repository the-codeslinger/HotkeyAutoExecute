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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(
            HotkeyConfigWriter* configWriter,
            HotkeyConfigReader* configReader,
            QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void toggleSpecialKeys(bool toggled);
    void executeHotkeyInterval();
    void addHotkey();
    void removeHotkey();
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
