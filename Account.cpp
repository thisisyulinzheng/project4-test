/*
Author: Yulin Zheng
Date: October 11, 2022
File Title: Account.cpp
Description: This file defines the methods of the Account class. 
*/

#include <string>
#include "Account.hpp"

/**
    Default constructor.
    Sets the username and password of the Account to an empty string
    Sets the vector of posts to an empty vector
*/
Account::Account() {
    setUsername("");
    setPassword("");
    LinkedList<Post> posts_;
    account_network = nullptr;
};

/**
     Parameterized constructor.
    @param username  : username of the Account
    @param password  : password of the Account

    Sets the username and password of the Account to what was passed by the user
    Sets the vector of posts to an empty vector
*/
Account::Account(const std::string username, const std::string password) {
    setUsername(username);
    setPassword(password);
    LinkedList<Post> posts_;
    account_network = nullptr;
};

/**
    @param a reference to the username of the Account
*/
void Account::setUsername(const std::string& username) {
    this->username = username;
};

/**
     @return the username of the Account
*/
std::string Account::getUsername() const {
    return username;
};

/**
     @param a reference to the password of the Account
*/
void Account::setPassword(const std::string& password) {
    this->password = password;
};

/**
     @return the password of the Account
*/
std::string Account::getPassword() const {
    return password;
}

/*
    @param title   : A reference to the title used to generate the Post object
      @param body    : A reference to the body used to generate the Post object
      @post          : generates a Post with the given title and body and adds it to it's vector
                       of posts AND to the Network's feed if it is connected to a Network.
      @return        : Will return true if the Post does not have an empty title or body and the
                       Post is successfully added to the vector
*/
bool Account::addPost(Post* new_post) {
    if (new_post != nullptr) {
        posts_.insert(*new_post, 0);
        if (account_network != nullptr) {
            account_network->addToFeed(*new_post);
        }
        return true;
    }
    else {
        return false;
    }
}

/*
    @post         : Prints the vector of Posts using their display function
*/
void Account::viewPosts() const {
    posts_.viewNodes();
};

/**
     Accessor function
    @return           :   the pointer to the Network the account is in
*/
Network<Account>* Account::getNetwork() const {
    return account_network;
};

/**
     Mutator function
    @param            :   a pointer to a Network
    @post             :   the Network pointer private member points to the input Network
*/
void Account::setNetwork(Network<Account>* new_network) {
    account_network = new_network;
};

/**
     @param            :   the username of the Account to follow
    @return           :   true if the account was successfully able to follow, false otherwise
    @post             :   adds the username to the vector of following accounts only if
                            it is affiliated to a Network AND it is not already following an account
                            with the same username.
*/
bool Account::followAccount(const std::string& user) {
    //this for loop checks if we are already following the given account
    for (int i = 0; i < users_following.size(); i++) {
        if (users_following[i] == user) {
           return false;
        }
    }
    if (account_network != nullptr) {
        users_following.push_back(user);
        return true;
    }

    return false;
};

/**
     @return           :   the vector of usernames the Account is following
*/
std::vector<std::string> Account::viewFollowing() const {
    return users_following;
};
