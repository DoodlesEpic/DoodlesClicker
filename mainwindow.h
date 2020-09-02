#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_gameLoopButton_clicked();

    void on_firstUpgradeButton_clicked();
    void on_secondUpgradeButton_clicked();
    void on_thirdUpgradeButton_clicked();
    void on_finalUpgradeButton_clicked();

    void on_actionNewGame_triggered();
    void on_actionSaveGame_triggered();
    void on_actionOpenGame_triggered();

private:
    Ui::MainWindow *ui;

    void gameLoop();
    void buyUpgrade(unsigned int upgradeNumber, unsigned int upgradeCost, unsigned int upgradeReward, QPushButton* button);

    unsigned int score = 0;
    unsigned int scoreIncrement = 1;

    bool upgrades[4] = {false, false, false, false};

};
#endif // MAINWINDOW_H
