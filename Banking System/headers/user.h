#ifndef HOMEWORK1_USER_H
#define HOMEWORK1_USER_H
struct User
{
    unsigned id;
    char name[128];
};

constexpr User systemUser = {0, "System"};

double moneyToOOPCoin(double amountOfMoney);
void createUser(std::fstream &usersFile, std::fstream &blocksFile);
// printUserInfo(usersFile, blocksFile, user, id);
void printUsers(std::fstream &usersFile);
void printUsersCoins(std::fstream &usersFile, std::fstream &blocksFile);
void printUserInfo(std::fstream &usersFile, std::fstream &blocksFile, User &user, unsigned userID);
void swapWealth(unsigned id1, unsigned id2);
static User findUser(unsigned id);
void deleteUser();
void printUserInfoFromFile(std::ifstream &file, User user);
void printWealthiestUsers(size_t count);
#endif // HOMEWORK1_USER_H