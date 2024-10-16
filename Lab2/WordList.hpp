//HPP file for Lab2
//ANNA WALTZ


#ifndef WORDLIST_HPP
#define WORDLIST_HPP


#include <iostream>
#include <fstream>
#include <cassert>

using std::cout; using std::endl; using std::string;

class WordOccurrence {
public:
    WordOccurrence(): word_(""), num_(0){};
    WordOccurrence(const string& word, int num) : word_(word), num_(num) {};

    bool operator>(WordOccurrence);

    bool matchWord(const string &); // returns true if word matches stored
    void increment(); // increments number of occurrences
    string getWord() const; 
    int getNum() const;

private:
    string word_;
    int num_;
};

class WordList{
public:
     WordList() : size_(0){wordArray_ = new WordOccurrence[size_]; };

    WordList(const WordList&);//copy constructor
    ~WordList();//destructor
    WordList& operator=(WordList);//overloaded assignment

    friend bool equal(const WordList&, const WordList&);

    void addWord(const string &);

    void sortArray();
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