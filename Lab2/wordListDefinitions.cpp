//ANNA WALTZ
//DEFINITIONS FOR HPP


#include "WordList.hpp"


bool WordOccurrence::operator>(WordOccurrence rhs){ //used for sort
    if(num_ > rhs.num_) //first sort by num occurences
        return true;
    if (num_ < rhs.num_)
        return false;
    //occurrences are equal then sort by alph
    if(word_.compare(rhs.word_) > 0) //this before word
        return true;
    return false; //word before this
}
bool WordOccurrence::matchWord(const std::string &word){ // returns true if word matches stored
        if(word == word_) //CASE SENSITIVE
            return true;
        return false;
}

void WordOccurrence::increment(){num_++;} // increments number of occurrences
string WordOccurrence::getWord() const{ return word_;}
int WordOccurrence::getNum() const{return num_;}


WordList::WordList(const WordList& rhs){
    size_=rhs.size_; //copy size
    wordArray_ = new WordOccurrence[size_];//copy array
    for(int i=0; i < size_; i++){ 
        wordArray_[i]=rhs.wordArray_[i];
    }
}

WordList::~WordList(){
    delete[] wordArray_;
    wordArray_=nullptr;
}


WordList& WordList:: operator=(WordList rhs){
    if(this!= &rhs){
        delete[] wordArray_;
        size_=rhs.size_;
        wordArray_=new WordOccurrence[size_];
        for(int i=0;i<size_;i++)
            wordArray_[i]=rhs.wordArray_[i];
    }
    return *this;
}


    // implement comparison as friend
bool equal(const WordList& lhs, const WordList& rhs){ //true if equal
    if(lhs.size_ !=rhs.size_) // if size not same
        return false;
    for(int i=0; i < rhs.size_ ; i++) {//assumes size is same, check if element is not match
        if(!(lhs.wordArray_[i].getWord()==rhs.wordArray_[i].getWord() && lhs.wordArray_[i].getNum()==rhs.wordArray_[i].getNum() ))
            return false;
    }
    return true;
}

void WordList::addWord(const std::string& word){
        //make temp, increase size, create array of new size
    bool inList=false;
    for(int i = 0; i < size_; i++){ // if in list, add to occurences
        if(wordArray_[i].matchWord(word)){
            wordArray_[i].increment();
            inList=true;
        }
    }
    if(!inList){ //not already in list, need to adjust size for new word
        WordOccurrence *temp = wordArray_;
        wordArray_ = new WordOccurrence[++size_];
             
        for(int i = 0; i < size_-1; i++)
            wordArray_[i] = temp[i]; //copy from temp
        WordOccurrence newWord(word, 1); //make new word
        wordArray_[size_-1] =  newWord; //add new word to end
    }
}

void WordList::sortArray(){ // call in print
    //add basic sort, and make comparison overloaded operators in WordOccurence
    for (int i = 1; i < size_; ++i) {
        WordOccurrence key = wordArray_[i];
        int j = i - 1;
        while (j >= 0 && wordArray_[j] > key) {
            wordArray_[j + 1] = wordArray_[j];
            j = j - 1;
        }
        wordArray_[j + 1] = key;
    }
}
void WordList::print(){
    sortArray();
    for(int i = 0; i < size_; i++){
        cout << wordArray_[i].getWord() << " " << wordArray_[i].getNum() ;
        if(i!=size_-1)cout << endl;
    }

}