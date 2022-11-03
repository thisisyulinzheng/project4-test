/*
Author: Yulin Zheng
Date: September 20, 2022
File Title: Promotional.cpp
Description: This file defines the methods of the Promotional class. 
*/

#include "Promotional.hpp"
#include <string>
#include <iostream>
#include <regex>

/**
     Parameterized constructor.
        @param       : The name of the Promotional post (a string)
        @param       : The body of the Promotional post (a string)
        @param    : : The username of the Account that added this post (a string)
        @param       : The link of the Promotional post (a string)

        @post         : Sets the title, body, username and link (if it's a proper link otherwise "Broken Link")
                    of the Promotional to the value
                    of the parameters.
                    It will also generate the current time and store it.
*/
Promotional::Promotional(const std::string promo_name, const std::string promo_body, const std::string username, const std::string url): 
Post(promo_name, promo_body, username) {
    setLink(url);
};

/**
     Accessor function
    @return         : Returns the post link
*/
std::string Promotional::getLink() const {
    return url;
};

/**
     @param    : A reference to the link that is in the format 'https://www.something.something'
                or 'http://www.something.something' with the last 'something' being at least 2 characters
    @return   : true if the link is correctly formatted, false otherwise

    @post     : If the link is not correctly formatted, store "Broken Link"
                in the link member variable, otherwise store the value of the
                parameter (Hint: see <regex>)
*/
bool Promotional::setLink(const std::string url) {
    //matches the https://www part then checks for the appropriate characters a website name can have
    std::regex e1("(https://www.)[a-zA-Z0-9-]+\\.[a-zA-Z0-9-]{2,}");
    std::regex e2("(http://www.)[a-zA-Z0-9-]+\\.[a-zA-Z0-9-]{2,}");
    if (std::regex_match(url, e1) || std::regex_match(url, e2)) {
        this->url = url;
        return true;
    }   
    this->url = "Broken Link";
    return false;
};

/**
     @post      : displays the entire Promotional post (example):
                \n
                {post_title_} at {time_stamp_}:
                {post_body_}
                \n
                {link}
                \n
*/
void Promotional::displayPost() const {
    std::cout << std::endl;

    std::cout << getTitle() << " at ";
    getTimeStamp();
    std::cout << getBody() << std::endl;

    std::cout << std::endl;
    std::cout << getLink() << std::endl;
    std::cout << std::endl;
};  
