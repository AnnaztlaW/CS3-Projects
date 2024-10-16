//Anna Waltz Lab 2
//ounts how many times each word occurs in the file and outputs the words (and counts) 
//in the increasing order of occurrence, 
//i.e. the counts need to be output in sorted order: 
//rare words first. If the two words have the same number of occurences, 
//the words should be sorted in alphabetical order.


//Word is any sequence of alphanumeric characters separateed by whitespace or punctuation marks. 
//Whitespace and punctuation marks are to be discarded. 
//That is, the punctuation marks should not be counted either as a part of the word or as a separate word.


#include "WordList.hpp"


int main(int argc, char* argv[]){ //provides one file = file to be sorted
    if(argc != 2){
        std::cout << "Invalid number of arguments!"  << std::endl;
        return 0;
    }

    std::ifstream file; //make files and open files
    file.open(argv[1]);
    if(!file) {                    // Make sure file opened correctly
            std::cerr << "File not found/cannot open " << std::endl;
            exit(1);
    }

   WordList list;
   char character;
   string wordToAdd="";

    while(file.get(character)){
        if( ('A' <=character && character<='Z') || ('a' <=character && character <='z') || ('0' <=character && character <='9')){//valid character
            wordToAdd +=character;
        }
        else{ //invalid character
            if(wordToAdd.length()>0)
                list.addWord(wordToAdd);
            wordToAdd=""; //reset word for new words after invalid character
        }
    }
    if(wordToAdd.length()>0)
            list.addWord(wordToAdd);
    //print final product, prink invokes sort
    list.print();
}
