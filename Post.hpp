/*
Author: Yulin Zheng
Date: October 11, 2022
File Title: Post.hpp
Description: This file defines the Post class of the project. 
*/

#include <time.h>
#include <string>
#ifndef POST_H_
#define POST_H_

class Post {
    public:
        /**
             Parameterized constructor.
            @param      : The title of the post (a string)
            @param      : The body content of the post (a string)
            @param      : The username of the Account that added this post (a string)

            @post         : Sets the title, body and username to the value of the parameters
                            It will also generate the current time and store it
        */
        Post();
        Post(const std::string post_title, const std::string post_body, const std::string username);

        /**
            @param  : a reference to title of the Post
        */
        void setTitle(const std::string& post_title);

        /**
             @return : the title of the Post
        */
        std::string getTitle() const;

        /**
             @param  : a reference to body of the Post
        */
        void setBody(const std::string& post_body);

        /**
             @return : the body of the Post
        */
        std::string getBody() const;

        /**
             @post   : prints the time the Post was created to the standard output as asctime(localtime(&time_stamp_))
        */
        void getTimeStamp() const;

        /**
             Print the Post in the following format:

            {title} posted at {time}:
            {body}

        */
        virtual void displayPost() const = 0;

        /*
            Accessor Function
            @return       : username associated with this Post
        */
        std::string getUsername() const;

        /*
            Mutator Function
            @param        : a reference to the username associated with this Post
        */
        void setUsername(const std::string& username);

    private:
        /**
            The Post class ontains the following private data members:
            - The title of the post (a string)
            - The body of the post (a string)
            - The time that the post was created (a time_t object, using the time.h library)
            - A string representing the username of the Account that created it. This will be useful in future projects.
        */
        std::string post_title;
        std::string post_body;
        time_t time_stamp_;
        std::string username;
};

#endif