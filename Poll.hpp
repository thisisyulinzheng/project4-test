/*
Author: Yulin Zheng
Date: September 20, 2022
File Title: Poll.hpp
Description: This file defines the Poll class. 
*/

#include "Post.hpp"
#include <string>
#include <vector>

#ifndef POLL_H_
#define POLL_H_

class Poll : public Post {
    public:
        /**
             Parameteriszed constructor.
                @param    : The title (name) of the Poll post (a string)
                @param    : The question (body) of the Poll post (a string)
                @param    : : The username of the Account that added this poll (a string)
                @param    : A vector of options for the Poll post

                @post     :Sets the title, body and username of the Poll post to the value of the parameters.
                        It will also generate the current time and store it and will initialize
                        the vectors of options and their respective number of votes.
        */
        Poll(const std::string poll_title, const std::string poll_body, const std::string username, std::vector<std::string> poll_options);

        /**
                @param     : a reference to int between 0 < number of options
                @return    : True if index is within range and we can vote for a poll,
                            false otherwise
                @post      : Increments the poll votes based on the index which
                            will refer to the index in the poll options
        */
        bool votePoll(const int& option_index);

        /**
             Mutator function used to either add a poll or change one of the poll options
                @param     : A reference to the new poll option
                @param     : A reference to int that can either represent the index of the
                            existing option that will be replaced
                            or if choice_number > current number of options,
                            it will add this new option to the poll.

                @post       : Resets the number of votes for this option.
        */
        void changePollOption(const std::string& option_name, const int& option_index);

        /**
             Accessor function
                @post       : prints the reaction to the post in this format
                            (example where option_n is the string at position n in the poll options vector):
                            0 votes for: option_1
                            5 votes for: option_2
                            2 votes for: option_3
                            ...
        */
        void getPollOptions() const;

        /**
             Accessor function
            @param      : The index of the option
            @return     : returns the number of votes for a given option
        */
        int getPollVotes(const int& option_index);

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
        void displayPost() const;

    private:
        /* 
        The general class contains the following private data members:
        - A vector of strings containing the poll options
        - A vector of integers containing the number of votes for each poll option,   
            where the integer in the first position indicates the number of votes for
            the poll option in the first position , the second integer indicates the number of votes
            for the second poll option, etc.
        */
        std::vector<std::string> poll_options;
        std::vector<int> votes;
};

#endif