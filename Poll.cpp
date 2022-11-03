/*
Author: Yulin Zheng
Date: September 20, 2022
File Title: Poll.cpp
Description: This file defines the methods of the Poll class. 
*/

#include "Poll.hpp"
#include <vector>
#include <string>
#include <iostream>

/**
     Parameterized constructor.
        @param    : The title (name) of the Poll post (a string)
        @param    : The question (body) of the Poll post (a string)
        @param    : : The username of the Account that added this poll (a string)
        @param    : A vector of options for the Poll post

        @post     :Sets the title, body and username of the Poll post to the value of the parameters.
                It will also generate the current time and store it and will initialize
                the vectors of options and their respective number of votes.
*/
Poll::Poll(const std::string poll_title, const std::string poll_body, const std::string username, std::vector<std::string> poll_options):
Post(poll_title, poll_body, username) {
    for (int i = 0; i < poll_options.size(); i++) {
        (this->poll_options).push_back(poll_options[i]);
        votes.push_back(0);
    }
};

/**
        @param     : a reference to int between 0 < number of options
        @return    : True if index is within range and we can vote for a poll,
                    false otherwise
        @post      : Increments the poll votes based on the index which
                    will refer to the index in the poll options
*/
bool Poll::votePoll(const int& option_index) {
    if (option_index >= 0 && option_index < poll_options.size()) {
        votes[option_index] += 1;
        return true;
    }
    return false;
};


/**
     Mutator function used to either add a poll or change one of the poll options
        @param     : A reference to the new poll option
        @param     : A reference to int that can either represent the index of the
                    existing option that will be replaced
                    or if choice_number > current number of options,
                    it will add this new option to the poll.

        @post       : Resets the number of votes for this option.
*/
void Poll::changePollOption(const std::string& option_name, const int& option_index) {
    if (option_index >= 0 && option_index < poll_options.size()) {
        poll_options[option_index] = option_name;
        votes[option_index] = 0;
    }
    else {
        if (option_index >= 0) {
            poll_options.push_back(option_name);
            votes.push_back(0);
        }
    }
};

/**
     Accessor function
        @post       : prints the reaction to the post in this format
                    (example where option_n is the string at position n in the poll options vector):
                    0 votes for: option_1
                    5 votes for: option_2
                    2 votes for: option_3
                    ...
*/
void Poll::getPollOptions() const {
    for (int i = 0; i < poll_options.size(); i++) {
        std::cout << votes[i] << " votes for: " << poll_options[i] << std::endl;
    }
};

/**
     Accessor function
    @param      : The index of the option
    @return     : returns the number of votes for a given option
*/
int Poll::getPollVotes(const int& option_index) {
    return votes[option_index];
};

/**
     @post   : displays the whole Poll post (example):
                \n
                {post_title_} at {time_stamp_}:
                {post_body_}
                \n
                0 votes for: option_1
                5 votes for: option_2
                2 votes for: option_3
                ...
                \n
*/
void Poll::displayPost() const {
    std::cout << std::endl;

    std::cout << Post::getTitle() << " at ";
    Post::getTimeStamp();
    std::cout << Post::getBody() << std::endl;
    
    getPollOptions();
};