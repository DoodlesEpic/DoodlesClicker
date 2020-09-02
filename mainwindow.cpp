#include "mainwindow.h"
#include "ui_mainwindow.h"

//
// JANELA
//

MainWindow::MainWindow(QWidget *parent)
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
    if(score >= upgradeCost)
    {
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
    if(!upgrades[0])
    {
        buyUpgrade(0, 10, 5, ui->firstUpgradeButton);
    }
}

void MainWindow::on_secondUpgradeButton_clicked()
{
    if(!upgrades[1])
    {
        buyUpgrade(1, 500, 10, ui->secondUpgradeButton);
    }
}

void MainWindow::on_thirdUpgradeButton_clicked()
{
    if(!upgrades[2])
    {
        buyUpgrade(1, 2500, 20, ui->thirdUpgradeButton);
    }
}

void MainWindow::on_finalUpgradeButton_clicked()
{
    if(!upgrades[3])
    {
        buyUpgrade(1, 25000, 50, ui->finalUpgradeButton);
    }
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
