/*
Author: Yulin Zheng
Date: October 11, 2022
File Title: Post.cpp
Description: This file defines the methods of the Post class. 
*/

#include <string>
#include <iostream>
#include "Post.hpp"

Post::Post() {
};

/**
     Parameterized constructor.
    @param      : The title of the post (a string)
    @param      : The body content of the post (a string)
    @param      : The username of the Account that added this post (a string)

    @post         : Sets the title, body and username to the value of the parameters
                    It will also generate the current time and store it
*/

Post::Post(const std::string post_title, const std::string post_body, const std::string username) {
    setTitle(post_title);
    setBody(post_body);
    setUsername(username);
    time(&time_stamp_);
};

/**
    @param  : a reference to title of the Post
*/
void Post::setTitle(const std::string& post_title) {
    this->post_title = post_title;
};

/**
     @return : the title of the Post
*/
std::string Post::getTitle() const {
    return post_title;
};

/**
     @param  : a reference to body of the Post
*/
void Post::setBody(const std::string& post_body) {
    this->post_body = post_body;
};

/**
     @return : the body of the Post
*/
std::string Post::getBody() const {
    return post_body;
};

/**
     @post   : prints the time the Post was created to the standard output as asctime(localtime(&time_stamp_))
*/
void Post::getTimeStamp() const {
    std::cout << asctime(localtime(&time_stamp_));
};

/**
     Print the Post in the following format:

    {title} posted at {time}:
    {body}

*/
void Post::displayPost() const {
    std::cout << getTitle() << " at ";
    getTimeStamp();
    std::cout << getBody() << std::endl;
}

/*
    Accessor Function
    @return       : username associated with this Post
*/
std::string Post::getUsername() const {
    return username;
};

/*
    Mutator Function
    @param        : a reference to the username associated with this Post
*/
void Post::setUsername(const std::string& username) {
    this->username = username;
};
