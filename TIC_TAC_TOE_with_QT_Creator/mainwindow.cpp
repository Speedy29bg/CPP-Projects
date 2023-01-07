#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <unordered_set>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: #80c342;");//light green
    // Variable initializations

    // for game_board
    for( size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 3; j++) {
            game_board[i][j] = 'A';
            std::cout<< game_board[i][j] << std::endl; //testing
        }
    }

    // for no_win
    no_win.reserve(9); // set size to 9
    for ( size_t i = 0; i < 9; i++) {
         no_win.push_back(0);
         std::cout<< no_win[i] << std::endl; //testing
    }

    turn_system = 'A'; // default starting turn is set to A. On starting game, the turn is set to 'X'
    win = false;
    tie = false;
    turn_count = 0;


     //UI
     ui->label_20->setPixmap(QPixmap(":/X.png"));
     ui->label_21->setPixmap(QPixmap(":/image.png"));


     // START GAME CONNECTION:
     QObject::connect(ui->start_game, SIGNAL(clicked()), this, SLOT(game_start()) );

     // SET TURN CONNECTION
     QObject::connect(this, SIGNAL(set_turn()), this, SLOT(start_turn()) );

     // BUTTON PRESS CONNECTIONS TO PLAY TURN:
     QObject::connect(ui->pushButton_2, SIGNAL(pressed()), this, SLOT(set1()) );
     QObject::connect(ui->pushButton_3, SIGNAL(pressed()), this, SLOT(set2()) );
     QObject::connect(ui->pushButton_4, SIGNAL(pressed()), this, SLOT(set3()) );
     QObject::connect(ui->pushButton_5, SIGNAL(pressed()), this, SLOT(set4()) );
     QObject::connect(ui->pushButton_6, SIGNAL(pressed()), this, SLOT(set5()) );
     QObject::connect(ui->pushButton_7, SIGNAL(pressed()), this, SLOT(set6()) );
     QObject::connect(ui->pushButton_8, SIGNAL(pressed()), this, SLOT(set7()) );
     QObject::connect(ui->pushButton_9, SIGNAL(pressed()), this, SLOT(set8()) );
     QObject::connect(ui->pushButton_10, SIGNAL(pressed()), this, SLOT(set9()) );


     // WINNING AND TIE CONNECTIONS
     QObject::connect(this, SIGNAL(turn_threshhold()), this, SLOT(check_win()) );
     QObject::connect(this, SIGNAL(set_win()), this, SLOT(winner()) );
     QObject::connect(this, SIGNAL(set_tie()), this, SLOT(tie_game()) );

}

// DEFINITIONS

bool MainWindow::areDistinct(std::vector<int> arr) { // helper function used in winning_system to help determine ties
        int n = arr.size();

        std::unordered_set<int> s;
        for (int i = 0; i < n; i++) {
            s.insert(arr[i]);
        }

        // If all the elements are distinct then size of the set should be of array
        return (s.size() == arr.size());
}

void MainWindow::winning_system() { // to check for any winner

    for(int i=0; i<3; i++) {
    // for row wins
    if( (game_board[i][0]==game_board[i][1] && game_board[i][1] == game_board[i][2] && game_board[i][0] == 'X') || (game_board[i][0]==game_board[i][1] && game_board[i][1] == game_board[i][2] && game_board[i][0] == 'O') ) {
    win = true;
    emit set_win();
    return;
       }

      // for column wins
    else if( (game_board[0][i]==game_board[1][i] && game_board[1][i] == game_board[2][i] && game_board[0][i] == 'X') || (game_board[0][i]==game_board[1][i] && game_board[1][i] == game_board[2][i] && game_board[0][i] == 'O') ) {
    win = true;
    emit set_win();
    return;
       }
   }

    // for diagonal wins
    if( (game_board[0][0] == game_board[1][1] && game_board[0][0] == game_board[2][2] && game_board[0][0] == 'X') || (game_board[0][0] == game_board[1][1] && game_board[0][0] == game_board[2][2] && game_board[0][0] == 'O')) {
    win = true;
    emit set_win();
    return;
       }

    else if ( (game_board[0][2] == game_board[1][1] && game_board[0][2] == game_board[2][0] && game_board[0][2] == 'X') || (game_board[0][2] == game_board[1][1] && game_board[0][2] == game_board[2][0] && game_board[0][2] == 'O')) {
    win = true;
    emit set_win();
    return;
        }

    else if (areDistinct(no_win)) { //to check for tie
    tie = true;
    emit set_tie();
    return;
        }
    }


void MainWindow::start_turn() {
    ui->turn->setText(QString(turn_system));
}

void MainWindow::game_start() {
    turn_system = 'X';
    ui->label_10->setText("Choose a Number");
    emit set_turn();
    ui->start_game->hide();
}

void MainWindow::check_win() { // activated when turn_count reaches turn threshhold
    winning_system();
}

// Display Winner
void MainWindow::winner() {
if (turn_system == 'X') {
  ui->winner->setText("O WON! RESTART GAME TO PLAY AGAIN.");
    }
if (turn_system == 'O') {
  ui->winner->setText("X WON! RESTART GAME TO PLAY AGAIN.");
    }
}

void MainWindow::tie_game() {
   ui->winner->setText("IT IS A TIE! RESTART GAME TO PLAY AGAIN.");
}


// BUTTON SLOTS
void MainWindow::set1() {
   // ui->label_10->setText("ok");
    if ( turn_system == 'X') {
    ui->label->setPixmap(QPixmap(":/X.png"));
    turn_system = 'O';
    emit set_turn();
    //3
    game_board[0][0] = 'X';
    no_win[0] = 1;
    ui->pushButton_2->hide();
     ++turn_count;
    }

    else if (turn_system == 'O') {
    ui->label->setPixmap(QPixmap(":/image.png"));
    turn_system = 'X';
    emit set_turn();
    //3
    game_board[0][0] = 'O';
    no_win[0] = 1;
    ui->pushButton_2->hide();
    ++turn_count;
    }
    if (turn_count >= 5) {
        emit turn_threshhold();
       }
}

void MainWindow::set2() {
    if ( turn_system == 'X') {
    ui->label_2->setPixmap(QPixmap(":/X.png"));
    turn_system = 'O';
    emit set_turn();
    //3
    game_board[1][0] = 'X';
    no_win[1] = 2;
    ui->pushButton_3->hide();
    ++turn_count;
    }

    else if (turn_system == 'O') {
    ui->label_2->setPixmap(QPixmap(":/image.png"));
    turn_system = 'X';
    emit set_turn();
    //3
    game_board[1][0] = 'O';
    no_win[1] = 2;
    ui->pushButton_3->hide();
    ++turn_count;
    }
    if (turn_count >= 5) {
        emit turn_threshhold();
       }
}

void MainWindow::set3() {
    if ( turn_system == 'X') {
    ui->label_3->setPixmap(QPixmap(":/X.png"));
    turn_system = 'O';
    emit set_turn();
    //3
    game_board[2][0] = 'X';
    no_win[2] = 3;
    ui->pushButton_4->hide();
    ++turn_count;
    }

    else if (turn_system == 'O') {
    ui->label_3->setPixmap(QPixmap(":/image.png"));
    turn_system = 'X';
    emit set_turn();
    //3
    game_board[2][0] = 'O';
    no_win[2] = 3;
    ui->pushButton_4->hide();
    ++turn_count;
    }
    if (turn_count >= 5) {
        emit turn_threshhold();
       }
}

void MainWindow::set4(){
    if ( turn_system == 'X') {
    ui->label_4->setPixmap(QPixmap(":/X.png"));
    turn_system = 'O';
    emit set_turn();
    //3
    game_board[0][1] = 'X';
    no_win[3] = 4;
    ui->pushButton_5->hide();
    ++turn_count;
    }

    else if (turn_system == 'O') {
    ui->label_4->setPixmap(QPixmap(":/image.png"));
    turn_system = 'X';
    emit set_turn();
    //3
    game_board[0][1] = 'O';
    no_win[3] = 4;
    ui->pushButton_5->hide();
    ++turn_count;
    }
    if (turn_count >= 5) {
        emit turn_threshhold();
       }
}

void MainWindow::set5(){
    if ( turn_system == 'X') {
    ui->label_5->setPixmap(QPixmap(":/X.png"));
    turn_system = 'O';
    emit set_turn();
    //3
    game_board[1][1] = 'X';
    no_win[4] = 5;
    ui->pushButton_6->hide();
    ++turn_count;
    }

    else if (turn_system == 'O') {
    ui->label_5->setPixmap(QPixmap(":/image.png"));
    turn_system = 'X';
    emit set_turn();
    //3
    game_board[1][1] = 'O';
    no_win[4] = 5;
    ui->pushButton_6->hide();
    ++turn_count;
    }
    if (turn_count >= 5) {
        emit turn_threshhold();
       }
}

void MainWindow::set6(){
    if ( turn_system == 'X') {
    ui->label_6->setPixmap(QPixmap(":/X.png"));
    turn_system = 'O';
    emit set_turn();
    //3
    game_board[2][1] = 'X';
    no_win[5] = 6;
    ui->pushButton_7->hide();
    ++turn_count;
    }

    else if (turn_system == 'O') {
    ui->label_6->setPixmap(QPixmap(":/image.png"));
    turn_system = 'X';
    emit set_turn();
    //3
    game_board[2][1] = 'O';
    no_win[5] = 6;
    ui->pushButton_7->hide();
    ++turn_count;
    }
    if (turn_count >= 5) {
        emit turn_threshhold();
       }
}

void MainWindow::set7(){
    if ( turn_system == 'X') {
    ui->label_7->setPixmap(QPixmap(":/X.png"));
    turn_system = 'O';
    emit set_turn();
    //3
    game_board[0][2] = 'X';
    no_win[6] = 7;
    ui->pushButton_8->hide();
    ++turn_count;
    }

    else if (turn_system == 'O') {
    ui->label_7->setPixmap(QPixmap(":/image.png"));
    turn_system = 'X';
    emit set_turn();
    //3
    game_board[0][2] = 'O';
    no_win[6] = 7;
    ui->pushButton_8->hide();
    ++turn_count;
    }
    if (turn_count >= 5) {
        emit turn_threshhold();
       }
}

void MainWindow::set8(){
    if ( turn_system == 'X') {
    ui->label_8->setPixmap(QPixmap(":/X.png"));
    turn_system = 'O';
    emit set_turn();
    //3
    game_board[1][2] = 'X';
    no_win[7] = 8;
    ui->pushButton_9->hide();
    ++turn_count;
    }

    else if (turn_system == 'O') {
    ui->label_8->setPixmap(QPixmap(":/image.png"));
    turn_system = 'X';
    emit set_turn();
    //3
    game_board[1][2] = 'O';
    no_win[7] = 8;
    ui->pushButton_9->hide();
    ++turn_count;
    }
    if (turn_count >= 5) {
        emit turn_threshhold();
       }
}

void MainWindow::set9(){
    if ( turn_system == 'X') {
    ui->label_9->setPixmap(QPixmap(":/X.png"));
    turn_system = 'O';
    emit set_turn();
    //3
    game_board[2][2] = 'X';
    no_win[8] = 9;
    ui->pushButton_10->hide();
    ++turn_count;
    }

    else if (turn_system == 'O') {
    ui->label_9->setPixmap(QPixmap(":/image.png"));
    turn_system = 'X';
    emit set_turn();
    //3
    game_board[2][2] = 'O';
    no_win[8] = 9;
    ui->pushButton_10->hide();
    ++turn_count;
    }
    if (turn_count >= 5) {
        emit turn_threshhold();
       }
}

MainWindow::~MainWindow()
{
    delete ui;
}

