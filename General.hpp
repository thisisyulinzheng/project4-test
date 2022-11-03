/*
Author: Yulin Zheng
Date: September 20, 2022
File Title: General.hpp
Description: This file defines the General class. 
*/

#include "Post.hpp"
#include <string>
#ifndef GENERAL_H_
#define GENERAL_H_

enum Reactions {LIKE, DISLIKE, LAUGH, WOW, SAD, ANGRY};

class General: public Post{
    public:
        /**
         Parameterized constructor.
        @param    : The name of the General post (a string)
        @param    : The body of the General post (a string)
        @param    : : The username of the Account that added this post (a string)

        @post     : Sets the title, body and username to the value of the parameters.
                    It will also generate the current time and store it
                    and it initializes the array with default values
        */
        General(const std::string post_title, const std::string post_body, const std::string username);
    
        /**
             Mutator function to add a reaction
            @param    : A reference to reaction (represented by a value of type Reaction)
            @return   : return True if the react to the post is successful or false
                        if the reaction provided is not within a valid Reaction value.

            @post     : Increments the array at the index corresponding to the input Reaction
        */
        bool reactToPost(const Reactions reaction_type);

        /**
             @post     : Prints the reaction to the post in this format (example):
                        Like : 2 | Dislike : 0 | Laugh : 4 | Wow : 2 | Sad : 1 |  Angry : 5
        */
        void getReactions() const;

        /**
             @post     : Displays the General post (example):
                        \n
                        {post_title_} at {time_stamp_}:
                        {post_body_}
                        \n
                        Like : 2 | Dislike : 0 | Laugh : 4 | Wow : 2 | Sad : 1 |  Angry : 5
                        \n
        */
        void displayPost() const;  

    private:
    /* 
    The general class contains the following private data members:
    - An integer array of size 6 that, indexed by Reactions, will store the number of reactions of each type the post has received.   
    */
        int reactions_arr[6];
};

#endif