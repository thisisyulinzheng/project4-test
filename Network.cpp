/*
Author: Yulin Zheng
Date: October 11, 2022
File Title: Network.cpp
Description: This file defines the methods of the Network class. 
*/

/**
 Default constructor.

    Initializes private variables to default initial values.
*/
template<class ItemType>
Network<ItemType>::Network() {
    num_of_accounts = 0;
    feed_ = LinkedList<Post>();
};

/*
A function that returns the index of a given account within the Network.

@param            :   string - the username of item we want the index of
@return           :   int - the index of the item, -1 if the account is not found
*/
template<class ItemType>
int  Network<ItemType>::getIndexOf(const std::string user) {
    //copied and modified from ArrayBag.cpp
    bool found = false;
    int result = -1;
    int search_index = 0;

    while (!found && (search_index < num_of_accounts)) {
        if ((account_arr[search_index])->getUsername() == user) {
            found = true;
            result = search_index;
        }
        else {
            search_index++;
        }
    } 
    return result;
};

/**
     Accessor function
    @return           : int -  the current size of the network (number of items in the array)
*/
template<class ItemType>
int Network<ItemType>::getSizeOfNetwork() const {
    return num_of_accounts;
};

/**
     @return           : bool -  true if the bag is empty, false otherwise
*/
template<class ItemType>
bool Network<ItemType>::isEmpty() const {
    return (num_of_accounts == 0);
};

/**
     @param            : a POINTER to the item that will be added to the Network
    @return           : bool- true  if the item was successfully added, false otherwise
    @post             : stores a pointer to the item, if there is room. This is a network specific function,
                        it has an additional constraint: the item will be added only if no other item in the network
                        has the same username (usernames are considered unique)
                        REMEMBER WE ARE STORING POINTERS TO ITEMS, NOT ITEMS.
                        Finally, the Account being added to the network will update it's private member to point to this network
                        (see Account class modifications below, you may come back and implement this feature after
                        you work on Task 2, but don't forget!!!).
                        NOTE: every object in C++ has access to a pointer to itself called `this`, thus the nework can pass `this` pointer to the account!
*/
template<class ItemType>
bool Network<ItemType>::addAccount(ItemType *new_entry) {
    if (num_of_accounts < 200 && (getIndexOf(new_entry->getUsername()) == -1)) {
        account_arr[num_of_accounts] = new_entry;
        num_of_accounts++;
        new_entry->setNetwork(this);
        return true;
    }
    return false;
};

/**
     Mutator function
    @param            :   a POINTER to the item that will be removed from Network
    @return           :   true if if the item was successfully removed, false otherwise
    @post             :   updates the bag/network to remove the pointer, if a pointer to that item was found.
*/
template<class ItemType>
bool Network<ItemType>::removeAccount(const ItemType *entry) {
    int item_index = getIndexOf(entry->getUsername());
    if (item_index > -1 && (!isEmpty())) {
        num_of_accounts--;
        account_arr[item_index] = account_arr[num_of_accounts];
        return true;
    }
    return false;
};

/**
     Mutator function
    @post             :   Empties the bag/network
*/
template<class ItemType>
void Network<ItemType>::clear() {
    num_of_accounts = 0;
};

/**
     @param            :   a POINTER to the item to find
    @return           :   true if the item was successfully found, false otherwise
*/
template<class ItemType>
bool Network<ItemType>::containsAccount(const ItemType *entry) {
    for (int i = 0; i < num_of_accounts; i++) {
        if (entry == account_arr[i]) {
            return true;
        }
    }
    return false;
};

/**
     Mutator function
    @param            :   the name of an input file
    @pre              :   The format of the text file is as follows:
                            username password
                            username password
                            ;

                            where ';' signals the end of the file. Check the provided example (accounts.txt).

    @post             :   Reads every line in the input file, creates an Account from that information and
                            adds the Account to the network. If a line of input is missing some required information,
                            it prints out "Improper Format" and terminates.
                            Keep in mind that, although the input will always be an Account, the Network class is
                            a template, thus it will store a pointer to a generic type. It will do so by creating a new
                            dynamic object of type ItemType but passing the account information (username and password)
                            as to the Account constructor. This is a bit hacky, but it will work for our Network.
*/

template <typename ItemType>
void Network<ItemType>::populateNetwork(const std::string input){
    std::fstream fin;
    fin.open(input, std::ios::in);
    std::string usr = "";
    std::string pswd = "";
    std::string line;
    std::string word;
    while (std::getline(fin, line)){
        if(line == ";") {
            break;
        }
        std::stringstream s(line);
        s >> usr;
        s >> pswd;
        if(usr == "" || pswd == "") {
            std::cout << "Improper format" << std::endl;
            break;
        }
        ItemType* new_entry = new ItemType(usr,pswd);
        bool is_added = addAccount(new_entry);
        if(!is_added) {
            std::cout << "Error when adding account" << std::endl;
            break;
        }
        usr = "";
        pswd = "";
    }
    fin.close();
}

/**
    Accessor function
    @param            :   index to account
    @return             :  account from the index
*/
template<class ItemType>
ItemType* Network<ItemType>::getAccountByIndex(const int index) {
    return account_arr[index];
};

/**
     Mutator function
    @param            :   a reference to another Network

    @post             :  Removes from the Network any items that also appear in the other Network.
                        In other words, removes elements from the network on the left of the operator that
                        are also found in the network on the right of the operator.
    Why is this useful? For example, given a network of known bot accounts, remove all bots from this Network.
*/
template<class ItemType>
void Network<ItemType>::operator-=(const Network<ItemType>& other_network) {
    for (int i = 0; i < other_network.getSizeOfNetwork(); i++) {
        if(containsAccount(account_arr[i])) {  
            removeAccount(account_arr[i]);
        }
    }
};

/**
     Accessor function
    @param            :   a reference to the item whose feed will be displayed
    @post             :   prints the feed of the given account by checking who they are following
                            and displaying all the posts from the feed that were made by those accounts.
                            Keep in mind that the Network parameters are general template types
                            in this project rather than accounts, although this functionality is
                            specific to accounts.
*/
template<class ItemType>
void Network<ItemType>::printFeedForAccount(const ItemType &acct) {
    std::vector<std::string> f_accounts = acct.viewFollowing(); //gets the list of accounts its following, but they are usernames
    for (int i = 0; i < f_accounts.size(); i++) {
        ItemType *each_acct = account_arr[getIndexOf(f_accounts[i])]; //so we get index of username from network and get its pointer
        each_acct->viewPosts();
    }
};

/**
     @param            :   a reference to an item (account) and the username of the account
                            it wants to follow
    @return           :   true if the item was authorized to follow, false otherwise

    @post             :   the referenced Account follows another account with the username
                            specified by the second argument if they both exist in the network
*/
template<class ItemType>
bool Network<ItemType>::authenticateFollow(ItemType &acct, const std::string user) {
    if (getIndexOf(acct.getUsername()) == -1 || (getIndexOf(user) == -1)) {
        return false;
    }
    acct.followAccount(user);
    return true;
};

/**
     Mutator function
    @param            :   a reference to a Post be added to the feed
    @return           :   returns true if the Post was successfully added to the feed, false otherwise
    @post             :   Adds the post to its feed only if the Post was created by an Account
                            in this Network.
*/
template<class ItemType>
bool Network<ItemType>::addToFeed(Post &post) {
    std::string created_by = post.getUsername();
    if (getIndexOf(created_by) > -1) {
        feed_.insert(post, 0);
        return true;
    }
    return false;
};

template<class ItemType>
void Network<ItemType>::printList() const {
    feed_.viewNodes();
}

template<class ItemType>
void Network<ItemType>::updateFeed(Post* target_post, const std::string new_title, const std::string new_body) {
    feed_.updateList(target_post, new_title, new_body);
};

/*
    @param            :   A string (word or phrase, case-sensitive) passed by reference
    @return           :   The number of items removed from the list

    @post              :  Any Post that contains the provided word or phrase in it's title,
                            body or both is removed from the Network's `feed_` as well as
                            the Account's `posts_`.

    You are encouraged to create your own helper functions for this endeavour.
    */
template<class ItemType>
int Network<ItemType>::removeIfContains(const std::string phrase) {
    Node<Post>* current = feed_.getHeadPtr();
    int num_removed = 0;
    while (current != nullptr) {
        std::string post_title = current->getItem()->getTitle();
        std::string post_body = current->getItem()->getBody();
        std::string target = ".*" + phrase + ".*";
        std::regex e (target);
        
        if (std::regex_match(post_title, e) || std::regex_match(post_body, e)) {
            //std::cout << current->getItem()->getUsername() << std::endl;
            getAccountByIndex( getIndexOf(current->getItem()->getUsername()) )->removePost( current->getItem() );
            feed_.removeFromList(current->getItem());
            num_removed++;
        }
        current = current->getNext();
    }
    return num_removed;
};