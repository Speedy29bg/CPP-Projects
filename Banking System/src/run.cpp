#include <iostream>
#include <cstring>
#include "../headers/user.h"
#include "../headers/run.h"

const int MAX_INPUT_SIZE = 50;

void menu()
{
    std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n"
                 "|                                |\n"
                 "|--------------Menu--------------|\n"
                 "|                                |\n"
                 "|---Choose one of the commands---|\n"
                 "|----------create-user-----------|\n"
                 "|----------remove-user-----------|\n"
                 "|----------send-coins------------|\n"
                 "|-------verify-transaction-------|\n"
                 "|--------wealthiest-users--------|\n"
                 "|-------------exit---------------|\n"
                 "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n";
}

void isCommandValid(char command[])
{
    if (strcmp(command, "create-user") != 0 &&
        strcmp(command, "remove-user") != 0 &&
        strcmp(command, "send-coins") != 0 &&
        strcmp(command, "verify-transaction") != 0 &&
        strcmp(command, "wealthiest-users") != 0 &&
        strcmp(command, "exit") != 0)
    {
        std::cout << "Invalid command!\n";
        menu();
    }
}