#include "mainwindow.h"
#include "ui_mainwindow.h"

//
// WINDOW
//

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//
// UPGRADES
//

void MainWindow::buyUpgrade(unsigned int upgradeNumber, unsigned int upgradeCost, unsigned int upgradeReward, QPushButton* button)
{
    if (!upgrades[upgradeNumber] && score >= upgradeCost) {
        upgrades[upgradeNumber] = true;
        score -= upgradeCost;
        scoreIncrement += upgradeReward;
        ui->label->setText(QString::number(score));
        ui->incrementLabel->setText(" + " + QString::number(scoreIncrement));
        button->setEnabled(false);
    }
}

void MainWindow::on_firstUpgradeButton_clicked()
{
    buyUpgrade(0, 10, 5, ui->firstUpgradeButton);
}

void MainWindow::on_secondUpgradeButton_clicked()
{
    buyUpgrade(1, 500, 10, ui->secondUpgradeButton);
}

void MainWindow::on_thirdUpgradeButton_clicked()
{
    buyUpgrade(2, 2500, 20, ui->thirdUpgradeButton);
}

void MainWindow::on_finalUpgradeButton_clicked()
{
    buyUpgrade(3, 25000, 50, ui->finalUpgradeButton);
}

//
// GAME LOOP
//

void MainWindow::on_gameLoopButton_clicked()
{
    gameLoop();
}

void MainWindow::gameLoop()
{
    score += scoreIncrement;
    ui->label->setText(QString::number(score));
}

//
// SAVE GAME
//

void MainWindow::on_actionOpenGame_triggered()
{
    // Open file prompt
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Game"), "",
        tr("Doodles Clicker Save (*.doodlesclicker);;All Files (*)"));

    if (fileName.isEmpty())
        return;
    else {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(this, tr("Unable to open file"),
                file.errorString());
            return;
        }

        // Create stream from file
        QDataStream in(&file);
        in.setVersion(QDataStream::Qt_4_5);

        // Reset variables
        score = NULL;
        scoreIncrement = NULL;

        // Stream variables from file
        in >> score;
        in >> scoreIncrement;
        in >> upgrades[0];
        in >> upgrades[1];
        in >> upgrades[2];
        in >> upgrades[3];
        ui->firstUpgradeButton->setEnabled(!upgrades[0]);
        ui->secondUpgradeButton->setEnabled(!upgrades[1]);
        ui->thirdUpgradeButton->setEnabled(!upgrades[2]);
        ui->finalUpgradeButton->setEnabled(!upgrades[3]);

        // Check if save game was corrupted
        if (score == NULL || scoreIncrement == NULL) {
            QMessageBox::information(this, tr("No data in file"),
                tr("The save game you are attempting to open contains no score or score increment."));
        }
    }

    // Update game state
    ui->label->setText(QString::number(score));
    ui->incrementLabel->setText(" + " + QString::number(scoreIncrement));
}

void MainWindow::on_actionSaveGame_triggered()
{
    // Open file prompt
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save Game"), "",
        tr("Doodles Clicker Save (*.doodlesclicker);;All Files (*)"));

    if (fileName.isEmpty())
        return;
    else {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::information(this, tr("Unable to open file"),
                file.errorString());
            return;
        }

        // Create stream for file
        QDataStream out(&file);
        out.setVersion(QDataStream::Qt_4_5);

        // Stream variables from file
        out << score;
        out << scoreIncrement;
        out << upgrades[0];
        out << upgrades[1];
        out << upgrades[2];
        out << upgrades[3];
    }
}

void MainWindow::on_actionNewGame_triggered()
{
    score = 0;
    scoreIncrement = 1;
    upgrades[0] = false;
    upgrades[1] = false;
    upgrades[2] = false;
    upgrades[3] = false;
    ui->firstUpgradeButton->setEnabled(true);
    ui->secondUpgradeButton->setEnabled(true);
    ui->thirdUpgradeButton->setEnabled(true);
    ui->finalUpgradeButton->setEnabled(true);
    ui->label->setText(QString::number(score));
    ui->incrementLabel->setText(" + " + QString::number(scoreIncrement));
}
