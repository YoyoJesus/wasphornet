// Lab 3: Collection Template
// Template class for a collection of elements of any type
// Austin Sternberg
// 2/2/2025

#ifndef COLLECTION_HPP_
#define COLLECTION_HPP_

#include <iostream>
#include <vector> // For temporary storage

// Forward class definition
template <typename T>
class Collection;

// Forward function definition  
template <typename T>
bool equal(const Collection<T>&, const Collection<T>&);

// Node class template
template <typename T>
class node {
public:
    node() : next_(nullptr) {}
    T getData() const { return data_; }
    void setData(const T& data) { data_ = data; }
    node<T>* getNext() const { return next_; }
    void setNext(node<T>* const next) { next_ = next; }

private:
    T data_;
    node<T>* next_;
};

// Collection class template
template <typename T>
class Collection {
public:
    Collection() : head(nullptr) {};
    Collection(const Collection&);
    ~Collection();
    Collection<T>& operator=(const Collection&);
    void add(const T& item);
    void remove(const T& item);
    T last() const;
    void print() const;
    friend bool equal<T>(const Collection<T>&, const Collection<T>&);

private:
    node<T>* head;
};

// Destructor: deletes all nodes
template <typename T>
Collection<T>::~Collection() {
    node<T>* current = head;

    while (current != nullptr) {
        node<T>* temp = current;
        current = current->getNext(); // Move to the next node
        delete temp; // Delete the current node
    }
}

template <typename T>
Collection<T>::Collection(const Collection<T>& other) {
    head = nullptr; // Initialize the head pointer
    std::vector<T> tempStorage; // Temporary storage for elements
    
    node<T>* temp = other.head;

    // Copy all elements from the other list
    while (temp != nullptr) {
        tempStorage.push_back(temp->getData());
        temp = temp->getNext();
    }

    // Add elements in correct order
    for (auto it = tempStorage.rbegin(); it != tempStorage.rend(); ++it) {
        add(*it);
    }
}

// Assignment operator: deep copy
template <typename T>
Collection<T>& Collection<T>::operator=(const Collection& other) {
    if (this == &other) return *this; // Self-assignment check
    
    // Delete all nodes in the current list
    node<T>* current = head;
    while (current != nullptr) {
        node<T>* temp = current;
        current = current->getNext();
        delete temp;
    }
    
    // Copy all nodes from the other list
    head = nullptr;
    if (other.head == nullptr) return *this;

    // Use a temporary array to store the elements
    std::vector<T> elements;
    current = other.head;

    // Copy all elements from the other list
    while (current != nullptr) {
        elements.push_back(current->getData());
        current = current->getNext();
    }

    // Add elements in the correct order
    for (auto it = elements.rbegin(); it != elements.rend(); ++it) {
        add(*it);
    }

    return *this;
}

template<typename T>
void Collection<T>::add(const T& item){
    node<T> *newnode; //creating a pointer to newnode
    newnode = new node<T>; //setting that pointer to a new node
    newnode->setData(item); //putting the item into that node
    newnode->setNext(head);
    head = newnode;

}

// Remove all occurrences of an item
template <typename T>
void Collection<T>::remove(const T& item) {
    // Remove matching nodes at the head
    while (head != nullptr && head->getData() == item) {
        node<T>* temp = head;
        head = head->getNext();
        delete temp;
    }
    
    if (head == nullptr) return; // If the list is empty, stop.

    // Remove occurrences in the middle
    node<T>* current = head;
    while (current->getNext() != nullptr) {
        if (current->getNext()->getData() == item) {
            node<T>* temp = current->getNext();
            current->setNext(temp->getNext());
            delete temp;

        } else {
            current = current->getNext();
        }
    }
}

// Return the first element (if exists)
template <typename T>
T Collection<T>::last() const {
    return head->getData();
}

// Print all elements in the list
template <typename T>
void Collection<T>::print() const {
    node<T>* current = head;

    // Print all elements in the list
    while (current != nullptr) {
        std::cout << current->getData() << " ";
        current = current->getNext();
    }

    std::cout << std::endl;
}

// Compare two collections for equality
template <typename T>
bool equal(const Collection<T>& l1, const Collection<T>& l2) {
    node<T>* list1 = l1.head;
    node<T>* list2 = l2.head;
    
    // Compare all elements in the two lists
    while (list1 != nullptr && list2 != nullptr) {
        if (list1->getData() != list2->getData()) {
            return false;
        }

        // Move to the next nodes
        list1 = list1->getNext();
        list2 = list2->getNext();
    }
    
    return list1 == nullptr && list2 == nullptr;
}


#endif /* COLLECTION_HPP_ */
