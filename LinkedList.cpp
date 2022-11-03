/*
List class implementation for term projects
CSCI 235 Fall 2022
Hunter College
*/


#include <iostream>


/* Default constructor*/
template<typename ItemType>
LinkedList<ItemType>::LinkedList() {
    head_ = nullptr; 
    size_ = 0;
}



/* Destructor */
template<typename ItemType>
LinkedList<ItemType>::~LinkedList() {
    clear();
}



/* @return  : the head pointer
This function is for grading purposes*/
template<typename ItemType>
Node<ItemType>* LinkedList<ItemType>::getHeadPtr() const {
    return head_;
}




/*
    @post   : removes all items from the caller list
**/
template<typename ItemType>
void LinkedList<ItemType>::clear() {

    Node<ItemType>* curr_item = head_;
    while(curr_item != nullptr) {
        Node<ItemType>* temp = curr_item;
        curr_item = curr_item->getNext();
        // delete temp->getItem();
        // temp->setItem(NULL);
        // temp->setNext(nullptr);
        delete temp;
        temp = nullptr;
    }

}



/*
    @param  item: the item to insert in the list
    @param  position: the position where to inserted
    @pre position is a valid place within the list, otherwise false will be returned
    @return   :  true if the item has been inserted in the caller list,
                false otherwise
    @post     : Inserts item in  list at  position

**/
template<typename ItemType>
bool LinkedList<ItemType>::insert(ItemType* item, const int &position){
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




/*
    @param  position:  the position where to remove
    @pre position is a valid place within the list, otherwise false will be returned
    @pre      : returns true if the item at position has been removed from the list,
                false otherwise
    @post     : removes node at  position
**/
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

    return true;

}



/*
    @param   item : the item to find in the list
    @pre      : takes item object and checks if exist in list and return
    @return   : returns the position (index) of object in the list

**/
template<typename ItemType>
int LinkedList<ItemType>::getIndexOf(const ItemType &item) const {
    Node<ItemType>* curr_item = head_;
    int counter = 0;
    while(curr_item != nullptr) {
        if(curr_item->getItem() == item) {
            return counter;
        }
        counter++;
        curr_item = curr_item->getNext();
    }
    return -1;
}




/* @return  : the size of the list */
template<typename ItemType>
int LinkedList<ItemType>::getSize() const {
    return size_;
}


  /* @return  : true if the list is empty, false otherwise */
template<typename ItemType>
bool LinkedList<ItemType>::isEmpty() const {
    return size_ == 0 ? true : false;
}

template<typename ItemType>
void LinkedList<ItemType>::viewNodes() const {
    Node<ItemType>* current = head_;
    while (current != nullptr) {
        current->getItem()->displayPost();
        current = current->getNext();
    }
};


// PRIVATE METHODS

/*
    @param   pos : the position of the item
    @pre     : pos is a valid place in the list
    @return  : a pointer to the node at pos, if pos is invalid, returns nullptr
**/
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
