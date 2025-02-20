#ifndef WORDLIST_HPP
#define WORDLIST_HPP

#include <string>
#include <iostream>
#include <cstring>
#include <algorithm>

class WordOccurrence {
public:
    WordOccurrence(const std::string& word="", int num=0) : word_(word), num_(num) {};
    bool matchWord(const std::string &); // returns true if word matches stored
    friend bool equal(const WordOccurrence&, const WordOccurrence&);
    friend bool operator<(const WordOccurrence&, const WordOccurrence&);
    void increment(); // increments number of occurrences
    std::string getWord() const; 
    int getNum() const;

private:
    std::string word_;
    int num_;
};

class WordList{
    public:
        // add copy constructor, destructor, overloaded assignment
        WordList() : size_(0), wordArray_(new WordOccurrence[size_]) {};
        WordList(const WordList&);
        ~WordList() {delete[] wordArray_;};

        WordList& operator=(WordList rhs) {swap(rhs); return *this;};
        
        // implement comparison as friend
        friend bool equal(const WordList&, const WordList&);

        void swap(WordList&);
        void addWord(const std::string &); // returns true if word is already in list
        void print();

        // Only use for testing purposes
        WordOccurrence * getWords() const {return wordArray_;};
        int getSize() const {return size_;};
    private:
        WordOccurrence *wordArray_; // a dynamically allocated array of WordOccurrences
                                    // may or may not be sorted
        int size_;
};

#endif