#include <QDir>
#include <QTimer>
#include <QMessageBox>
#include <QStandardItem>
#include <QStandardPaths>

#include <mainwindow.h>
#include <hotkeyitem.h>
#include "ui_mainwindow.h"

static const QString TIME_UNIT_MINUTES = QObject::tr("Minutes");
static const QString TIME_UNIT_SECONDS = QObject::tr("Seconds");

static const int SECONDS_MULTIPLIER = 1000;
static const int MINUTES_MULTIPLIER = 60 * SECONDS_MULTIPLIER;

MainWindow::MainWindow(
        HotkeyConfigWriter* configWriter,
        HotkeyConfigReader* configReader,
        HotkeyExecutor* executor,
        QWidget *parent)
    : QMainWindow(parent)
    , ui_(new Ui::MainWindow)
    , availableHotkeysModel_(new QStandardItemModel())
    , configWriter_(configWriter)
    , configReader_(configReader)
    , executor_(executor)
{
    ui_->setupUi(this);
    ui_->timeUnitBox->addItem(TIME_UNIT_MINUTES);
    ui_->timeUnitBox->addItem(TIME_UNIT_SECONDS);
    ui_->availableHotkeys->setModel(availableHotkeysModel_);

    timer_ = new QTimer{this};
    connect(timer_, &QTimer::timeout, this, &MainWindow::triggerHotkey);

    ui_->intervalBox->setValue(10);
    
    // Form designer wouldn't pick up on these slots...
    connect(ui_->enableSpecialKeysCheck, &QCheckBox::toggled, this, &MainWindow::toggleSpecialKeys);
    connect(ui_->removeHotkeyButton, &QPushButton::clicked, this, &MainWindow::removeHotkey);
    
    configReader->read(availableHotkeysModel_);
}

MainWindow::~MainWindow()
{
    delete ui_;
    delete configWriter_;
    delete configReader_;
    delete availableHotkeysModel_;
    delete executor_;
}

void 
MainWindow::toggleSpecialKeys(bool toggled)
{
    ui_->specialKeysGroup->setEnabled(toggled);
    ui_->keySequenceEdit->setDisabled(toggled);
    
    if (!toggled) {
        resetSpecialKeys();
    }
}

void
MainWindow::addHotkey()
{
    auto name = ui_->hotkeyName->text();
    if (name.isEmpty())   {
        QMessageBox::information(
                    this, 
                    tr("Missing Hotkey Name"), 
                    tr("A name for the hotkey is required."));
        return;
    }
    
    auto keySequence = QKeySequence{};
    auto nativeKeySequence = NativeKeySequence{};
    if (!ui_->enableSpecialKeysCheck->isChecked()) {
        keySequence = ui_->keySequenceEdit->keySequence();
        nativeKeySequence = ui_->keySequenceEdit->nativeKeySequence();
    }
    
    auto hotkeyItem = HotkeyItem{
            name, 
            keySequence.toString(QKeySequence::NativeText),
            nativeKeySequence,
            selectedSpecialModifiers(), 
            selectedSpecialKeys()};
    
    auto listItemData = QVariant{};
    listItemData.setValue(hotkeyItem);
    
    auto listItem = new QStandardItem{hotkeyItem.name};
    listItem->setData(listItemData);
    
    availableHotkeysModel_->appendRow(listItem);
    configWriter_->write(availableHotkeysModel_);
    
    resetHotkeyName();
    resetKeySequenceEdit();
    resetModifiers();
    resetSpecialKeys();
}

void
MainWindow::removeHotkey()
{
    auto index = ui_->availableHotkeys->currentIndex();
    if (!availableHotkeysModel_->removeRow(index.row())) {
        auto item = qvariant_cast<HotkeyItem>(availableHotkeysModel_->data(index));
        qWarning() << "Could not remove hotkey '" << item.name << "'.";
        return;
    }
    
    if (!configWriter_->write(availableHotkeysModel_)) {
        qWarning() << "Could not write hotkey config file.";
    }
}

void
MainWindow::executeHotkeyInterval()
{
    if (timer_->isActive()) {
        stopHotkeyInterval();
    } else {
        startHotkeyInterval();
    }
}

void
MainWindow::triggerHotkey()
{
    auto index = ui_->availableHotkeys->currentIndex();
    auto item = availableHotkeysModel_->data(index, Qt::UserRole + 1);
    auto hotkeyItem = qvariant_cast<HotkeyItem>(item);
    
    if (nullptr != executor_) {
        executor_->execute(hotkeyItem);
    }
}

void
MainWindow::startHotkeyInterval()
{
    ui_->startButton->setText(tr("Stop"));
    toggleUiElements(false);

    auto interval = ui_->intervalBox->value();
    auto intervalUnit = ui_->timeUnitBox->currentText();

    timer_->stop();
    auto multiplier = determineIntervalMultiplier(intervalUnit);
    timer_->start(interval * multiplier);
}

void
MainWindow::stopHotkeyInterval()
{
    timer_->stop();
    ui_->startButton->setText(tr("Start"));
    toggleUiElements(true);
}

int
MainWindow::determineIntervalMultiplier(const QString& value) const
{
    // Available values are hard-coded. No plain-text user input to validate.
    // Therefore, the else case can only be seconds.
    if (value == TIME_UNIT_MINUTES) {
        return MINUTES_MULTIPLIER;
    } else {
        return SECONDS_MULTIPLIER;
    }
}

SpecialModifiers
MainWindow::selectedSpecialModifiers() const
{
    return SpecialModifiers{
        ui_->shiftModifierCheck->isChecked(),
        ui_->controlModifierCheck->isChecked(),
        ui_->metaModifierCheck->isChecked(),
        ui_->altModifierCheck->isChecked()
    };
}
            
SpecialKeys 
MainWindow::selectedSpecialKeys() const
{
    return SpecialKeys{
        ui_->printModifierCheck->isChecked()
    };
}

void
MainWindow::resetHotkeyName()
{
    ui_->hotkeyName->setText("");
}

void 
MainWindow::resetModifiers()
{
    ui_->shiftModifierCheck->setChecked(false);
    ui_->controlModifierCheck->setChecked(false);
    ui_->metaModifierCheck->setChecked(false);
    ui_->altModifierCheck->setChecked(false);
}

void 
MainWindow::resetSpecialKeys()
{
    ui_->enableSpecialKeysCheck->setChecked(false);
    ui_->printModifierCheck->setChecked(false);
}

void 
MainWindow::resetKeySequenceEdit()
{
    ui_->keySequenceEdit->clear();
}

void 
MainWindow::toggleUiElements(bool enabled)
{
    ui_->intervalBox->setEnabled(enabled);
    ui_->timeUnitBox->setEnabled(enabled);
    ui_->availableHotkeys->setEnabled(enabled);
    ui_->removeHotkeyButton->setEnabled(enabled);
    ui_->hotkeyName->setEnabled(enabled);
    ui_->keySequenceEdit->setEnabled(enabled);
    ui_->modifiersGroup->setEnabled(enabled);
    ui_->specialKeysGroup->setEnabled(enabled);
    ui_->addHotkeyButton->setEnabled(enabled);
    ui_->enableSpecialKeysCheck->setEnabled(enabled);
}
