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
    Sets the list of posts to an empty list
*/
Account::Account() {
    setUsername("");
    setPassword("");
    user_posts_ = LinkedList<Post>();
    account_network = nullptr;
};

/**
     Parameterized constructor.
    @param username  : username of the Account
    @param password  : password of the Account

    Sets the username and password of the Account to what was passed by the user
    Sets the list of posts to an empty list
*/
Account::Account(const std::string username, const std::string password) {
    setUsername(username);
    setPassword(password);
    user_posts_ = LinkedList<Post>();
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
      @param body    : A POINTER to the new post
      @post          : generates a Post with the given title and body and adds it to it's list
                       of posts AND to the Network's feed if it is connected to a Network.
      @return        : Will return true if the Post does not have an empty title or body and the
                       Post is successfully added to the vector
*/
bool Account::addPost(Post* new_post) {
    if (new_post != nullptr) {
        user_posts_.insert(*new_post, 0);
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
    @post         : Prints the list of Posts using their display function
*/
void Account::viewPosts() const {
    user_posts_.viewNodes();
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

/*
    @param            :   Pointer to a Post object
    @param            :   The new title of the Post (or an empty string if you do not
                        want to change it)
    @param            :   The new body of the Post (or an empty string if you do not
                        want to change it)

    @post            :   This function will take the Post and given the new title and body,
                        update the Posts title and body as appropriate. It will also update the `timestamp_` to the current time of the update. This function should then
                        update the location of the Post in its list of `posts_` to the front of the list as well as utilizing its Network pointer to do the same in the `feed_`.

    You are encouraged to create your own helper functions for this endevour.
*/
void Account::updatePost(Post* target_post, const std::string new_title, const std::string new_body) {
    user_posts_.updateList(target_post, new_title, new_body);
    account_network->updateFeed(target_post, new_title, new_body);
};

/*
    @param            :   A pointer to a Post
    @return           :   If the Post was successfully found and removed

    This function will remove the given Post from its list as well as from the Network's feed.
    Returns True if successfully removed, False if not. Afterwards, tell the Network to remove
    the Post as well from its feed.

    You are encouraged to create your own helper functions for this endevour.
*/
bool Account::removePost(Post* target_post) {
    return user_posts_.removeFromList(target_post);
};