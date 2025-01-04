#ifndef HOMEWORK1_USER_H
#define HOMEWORK1_USER_H
#include <cstdint>
#include <string>
class User
{
private:
    uint16_t id{};
    std::string name;

public:
    User() = default;
    User(uint16_t id, std::string name);
    User(const User& user);
    User(const User&& user) noexcept;
    User& operator=(const User& user);

    const uint16_t getId()const;
    const std::string& getName()const;

    const void printUserInformation(const User& user)const;
    ~User() = default;

};


#endif // HOMEWORK1_USER_H