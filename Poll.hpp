/****************************************************************************************************************************
Title         :   Poll.hpp
Author        :   Dream Team
Description   :   header/interface for Poll class
****************************************************************************************************************************/




#ifndef POLL_
#define POLL_

#include "Post.hpp"
#include <string>
#include <vector>


class Poll :public Post {
    public:

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
        Poll(std::string name, std::string description, std::string username, std::vector<std::string> poll_options);



        /**

              @param     : a reference to int between 0 < number of options
              @return    : True if index is within range and we can vote for a poll,
                           false otherwise
              @post      : Increments the poll votes based on the index which
                           will refer to the index in the poll options
        */
        bool votePoll(const int& poll_option);


        /**
           Mutator function used to either add a poll or change one of the poll options
              @param     : A reference to the new poll option
              @param     : A reference to int that can either represent the index of the
                           existing option that will be replaced
                           or if choice_number > current number of options,
                           it will add this new option to the poll.

             @post       : Resets the number of votes for this option.
        */
        void changePollOption(const std::string& new_poll, const int& poll_option);




        /**
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
        int getPollVotes(int poll_option) const;




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
        std::vector<std::string> poll_options_;
        std::vector<int> poll_votes_;


}; //end Promotional
#endif
