/*
Author: Yulin Zheng
Date: September 20, 2022
File Title: Promotional.hpp
Description: This file defines the Promotional class. 
*/

#include "Post.hpp"
#include <string>

#ifndef PROMOTIONAL_H_
#define PROMOTIONAL_H_

class Promotional : public Post {
    public:
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
        Promotional(const std::string promo_name, const std::string promo_body, const std::string username, const std::string url);

        /**
             Accessor function
            @return         : Returns the post link
        */
        std::string getLink() const;

        /**
             @param    : A reference to the link that is in the format 'https://www.something.something'
                        or 'http://www.something.something' with the last 'something' being at least 2 characters
            @return   : true if the link is correctly formatted, false otherwise

            @post     : If the link is not correctly formatted, store "Broken Link"
                        in the link member variable, otherwise store the value of the
                        parameter (Hint: see <regex>)
        */
        bool setLink(const std::string url);

        /**
             @post      : displays the entire Promotional post (example):
                        \n
                        {post_title_} at {time_stamp_}:
                        {post_body_}
                        \n
                        {link}
                        \n
        */
        void displayPost() const;  

    private:
    /* 
    The general class contains the following private data members:
    - string that represents a url
    */
        std::string url;
};

#endif