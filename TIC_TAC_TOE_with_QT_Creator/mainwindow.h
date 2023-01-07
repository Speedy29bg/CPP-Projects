#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<iostream>
#include<vector>
#define BOARD_SIZE 3

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void winning_system();

    bool areDistinct(std::vector<int> arr);


public slots:

    void set1();
    void set2();
    void set3();
    void set4();
    void set5();
    void set6();
    void set7();
    void set8();
    void set9();
    void game_start();
    void start_turn();
    void check_win();
    void winner();
    void tie_game();

signals:
    void set_turn();
    void turn_threshhold();
    void set_win();
    void set_tie();

private:
    Ui::MainWindow *ui;

    char game_board[BOARD_SIZE][BOARD_SIZE];

    char turn_system;

    std::vector<int> no_win;

    bool win;

    bool tie;

    int turn_count;
};
#endif // MAINWINDOW_H
