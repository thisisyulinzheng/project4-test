/*
Author: Yulin Zheng
Date: October 11, 2022
File Title: Account.hpp
Description: This file defines the Account class of the project. 
*/

#include <vector>
#include "Post.hpp"
#include "Network.hpp"
#ifndef ACCOUNT_H_
#define ACCOUNT_H_

class Account {
    public:
        /**
             Default constructor.
            Sets the username and password of the Account to an empty string
            Sets the vector of posts to an empty vector
        */
        Account();

        /**
             Parameterized constructor.
            @param username  : username of the Account
            @param password  : password of the Account

            Sets the username and password of the Account to what was passed by the user
            Sets the vector of posts to an empty vector
        */
        Account(const std::string username, const std::string password);

        /**
            @param a reference to the username of the Account
        */
        void setUsername(const std::string& username);

        /**
             @return the username of the Account
        */
        std::string getUsername() const;

        /**
             @param a reference to the password of the Account
        */
        void setPassword(const std::string& password);

        /**
             @return the password of the Account
        */
        std::string getPassword() const;

        /**
            @param title   : A reference to the title used to generate the Post object
            @param body    : A reference to the body used to generate the Post object
            @post         : generates a Post with the given title and body and adds it to it's vector of posts
            @return       : Will return true if the Post does not have an empty title or body and the Post is successfully added to the vector
        */
        bool addPost(Post* new_post);

        /*
            @post         : Prints the vector of Posts using their display function
        */
        void viewPosts() const;

        /**
             Accessor function
            @return           :   the pointer to the Network the account is in
        */
        Network<Account>* getNetwork() const;

        /**
             Mutator function
            @param            :   a pointer to a Network
            @post             :   the Network pointer private member points to the input Network
        */
        void setNetwork(Network<Account> *new_network);

        /**
             @param            :   the username of the Account to follow
            @return           :   true if the account was successfully able to follow, false otherwise
            @post             :   adds the username to the vector of following accounts only if
                                    it is affiliated to a Network AND it is not already following an account
                                    with the same username.
        */
        bool followAccount(const std::string& username);

        /**
             @return           :   the vector of usernames the Account is following
        */
        std::vector<std::string> viewFollowing() const;

    private:
        /**
            The Account class ontains the following private data members:
            The account username (a string)
            The account password (a string)
            A vector of Post objects that stores all the Posts posted by this account
        */
        std::string username;
        std::string password;
        LinkedList<Post> posts_;
        std::vector<std::string> users_following; // A vector of usernames the Account is following  
        Network<Account> *account_network; // A pointer to the Network this account is part of. Before the Account is added to a Network, the pointer is `nullptr`.
};

#endif