/*
List class implementation for term projects
CSCI 235 Fall 2022
Hunter College
*/

#include <iostream>

template<typename ItemType>
LinkedList<ItemType>::LinkedList() {
    head_ = nullptr;
    size_ = 0;
};

/*
    A copy constructor
    @param            :   Another LinkedList passed by reference

    Initializes this LinkedList with the same items as the provided LinkedList
*/
template<typename ItemType>
LinkedList<ItemType>::LinkedList(const LinkedList &list) {
    head_ = nullptr;
    size_ = 0;
    if (!list.isEmpty()) {
        Node<ItemType> *copyHead = list.getHeadPtr();
        int counter = 0;

        while (counter < list.getSize()) {
            insert(*(copyHead->getItem()), counter);
            counter++;
            copyHead = copyHead->getNext();
        }
    }
}

template<typename ItemType>
Node<ItemType>* LinkedList<ItemType>::getHeadPtr() const {
    return head_;
}


template<typename ItemType>
void LinkedList<ItemType>::clear() {
    Node<ItemType>* curr_item = head_;
    Node<ItemType>* temp = curr_item;
    for(int i = 0; i<size_; i++) {
        temp = curr_item;
        curr_item = curr_item->getNext();
        delete temp;
    }
    temp = nullptr;
    size_ = 0;
}



template<typename ItemType>
LinkedList<ItemType>::~LinkedList() {
    clear();
}

template<typename ItemType>
bool LinkedList<ItemType>::insert(ItemType& item, const int &position){
    if((position < 0 || position > size_)){
        return false;
    }

    Node<ItemType> *node = new Node<ItemType>();
    node->setItem(item);

    if(size_ == 0){
        head_ = node;
    }
    else {
        Node<ItemType> *iterator;

        if(position == 0){
            node->setNext(head_);
            head_ = node;
        }

        else if (position == size_){
            iterator = getAtPos(size_-1);
            iterator->setNext(node);
        }
        else {
            iterator = getAtPos(position-1);
            node->setNext(iterator->getNext());
            iterator->setNext(node);
        }
    }
    size_++;
    return true;
}

template <typename ItemType>
bool LinkedList<ItemType>::remove(const int&position) {
    if (position < 0 || position >= size_) {
        return false;
    }

    Node<ItemType> *iterator;

    if (position == 0){
        iterator = head_;
        head_ = head_->getNext();
    }
    else {
        iterator = getAtPos(position-1);
        iterator->setNext(iterator->getNext()->getNext());
        iterator = iterator->getNext();
    }

    size_--;
    return true;

}

/*
    A reversed copy function
    @param            :   Another LinkedList passed by reference

    Sets the current LinkedList with the same items as the provided LinkedList
    but in reverse order
*/
template <typename ItemType>
void LinkedList<ItemType>::reverseCopy(const LinkedList<ItemType> &a_list) {
    LinkedList<ItemType> newList(a_list);

    Node<ItemType> *current = newList.getHeadPtr();
    // Node<ItemType> *prev = nullptr;
    // Node<ItemType> *next = nullptr;
    const int START = 0;
    const int END = newList.getSize();

    while (current != nullptr){
        insert(*(current->getItem()), START);
        current = current->getNext();
        remove(END);
        // next = current->getNext();
        // current->setNext(prev);
        // prev = current;
        // current = next;
    }
    // head_ = prev;
}

template<typename ItemType>
int LinkedList<ItemType>::getIndexOf(const ItemType &item) const {
    Node<ItemType>* curr_item = head_;
    int counter = 0;
    while(curr_item != nullptr) {
        if((curr_item->getItem()) == &item) {
            return counter;
        }
        counter++;
        curr_item = curr_item->getNext();
    }
    return -1;
}

template<typename ItemType>
Node<ItemType>* LinkedList<ItemType>::getAtPos(const int &pos) const {

    if(pos < 0 || pos >= size_) {
        return nullptr;
    }

    Node<ItemType>* curr_item = head_;
    int counter = 0;
    while(counter < pos && curr_item != nullptr) {
        counter++;
        curr_item = curr_item->getNext();
    }
    return curr_item;
}

template<typename ItemType>
int LinkedList<ItemType>::getSize() const {
    return size_;
}

template<typename ItemType>
bool LinkedList<ItemType>::isEmpty() const {
    return size_ == 0 ? true : false;
}

template <typename ItemType>
bool LinkedList<ItemType>::moveItem(int &current_position, int &new_position) {
    if(
        (current_position > -1 && current_position < size_) &&
        (new_position > -1 && new_position < size_)
    ) {
        if(new_position != current_position) {
            if(new_position < current_position) {
                ItemType temp = *(this->getAtPos(current_position)->getItem());
                this->getAtPos(current_position)->setItem(this->getAtPos(current_position - 1)->getItem());
                this->getAtPos(current_position - 1)->setItem(temp);
                current_position--;
            }
            else {
                ItemType temp = *(this->getAtPos(current_position)->getItem());
                this->getAtPos(current_position)->setItem(this->getAtPos(current_position + 1)->getItem());
                this->getAtPos(current_position + 1)->setItem(temp);
                current_position++;
            }

            return moveItem(current_position, new_position);
        }
        else {
            return true;
        }
    }
    else {
        return false;
    }
}



/*
    @param            :   A reference to an item
    @return           :   Return true if item was moved to top, false otherwise
    @post             :   Will move the item from its current position to the front
                          of the list.
                          For example, given the list 1 -> 3 -> 5 -> 6, moving 5 to the
                          top of the list would result in 5 -> 1 -> 3 -> 6
                          (recall that positions start at 0 and end at n-1).

    You are encouraged to create your own helper functions for this endeavour.
*/
template<typename ItemType>
bool LinkedList<ItemType>::moveItemToTop(ItemType &item)
{
if (getIndexOf(item) < 1) //If the item does not exist or it is already on top, return false
    return false;
else
    {
    Node<ItemType>* new_head = new Node<ItemType>(); //Create a new head Node
    new_head->setItem(item); //Set the value of the new head Node to the item you want to move
    remove(getIndexOf(item)); //Remove the item you want to move from the List
    new_head->setNext(head_); //Set the new head pointer's next value to the current head pointer
    head_ = new_head; //Set the List's head to the new head pointer
    return true;
    }
}

template<typename ItemType>
void LinkedList<ItemType>::viewNodes() const {
    Node<ItemType>* current = head_;
    while (current != nullptr) {
        current->getItem()->displayPost();
        current = current->getNext();
    }
};

template<typename ItemType>
void LinkedList<ItemType>::updateList(Post* target_post, const std::string new_title, const std::string new_body) {
    Node<ItemType>* current = head_;
    bool finished = true;
    while ((current != nullptr) && finished) {
        if (target_post == current->getItem()) {
            current->getItem()->setTitle(new_title);
            current->getItem()->setBody(new_body);
            moveItemToTop(*target_post);
            finished = false;
        }
        current = current->getNext();
    }
};

template<typename ItemType>
bool LinkedList<ItemType>::removeFromList(ItemType* target_post) {
    Node<ItemType>* current = head_;
    int count = 0;
    while (current != nullptr) {
        if (target_post == current->getItem()) {
            Node<ItemType>* temp = current->getNext();
            remove(1);
            return true;
        }
        count++;
        current = current->getNext();
    }
    return false;
};
