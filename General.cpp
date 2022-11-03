/*
Author: Yulin Zheng
Date: September 20, 2022
File Title: General.cpp
Description: This file defines the methods of the General class. 
*/

#include "General.hpp"
#include <string>
#include <iostream>

/**
 Parameterized constructor.
@param    : The name of the General post (a string)
@param    : The body of the General post (a string)
@param    : : The username of the Account that added this post (a string)

@post     : Sets the title, body and username to the value of the parameters.
            It will also generate the current time and store it
            and it initializes the array with default values
*/
General::General(const std::string post_title, const std::string post_body, const std::string username)
:Post(post_title, post_body, username) 
{
     for (int i = 0; i < 6; i++) {
          reactions_arr[i] = 0;
     }
};

/**
     Mutator function to add a reaction
    @param    : A reference to reaction (represented by a value of type Reaction)
    @return   : return True if the react to the post is successful or false
                if the reaction provided is not within a valid Reaction value.

    @post     : Increments the array at the index corresponding to the input Reaction
*/
bool General::reactToPost(const Reactions reaction_type) {
     for (int i = 0; i < 6; i++) {
          if (i == reaction_type) {
               reactions_arr[i] += 1;
               return true;
          }
     }
     return false;
};

/**
     @post     : Prints the reaction to the post in this format (example):
                Like : 2 | Dislike : 0 | Laugh : 4 | Wow : 2 | Sad : 1 |  Angry : 5
*/
void General::getReactions() const {
     std::cout 
     << "Like : " << reactions_arr[LIKE] 
     << " | Dislike : " << reactions_arr[DISLIKE]  
     << " | Laugh : " << reactions_arr[LAUGH]  
     << " | Wow : " << reactions_arr[WOW]  
     << " | Sad : " << reactions_arr[SAD]  
     << " |  Angry : " << reactions_arr[ANGRY] 
     << std::endl;
};

/**
     @post     : Displays the General post (example):
                \n
                {post_title_} at {time_stamp_}:
                {post_body_}
                \n
                Like : 2 | Dislike : 0 | Laugh : 4 | Wow : 2 | Sad : 1 |  Angry : 5
                \n
*/
void General::displayPost() const {
     std::cout << std::endl;
     
     std::cout << getTitle() << " at ";
     getTimeStamp();
     std::cout << getBody() << std::endl;

     getReactions();
}; 