//Anna Waltz
// lab one CS3 file

//testing for text differences and pointing them out via a arrow character

#include <iostream>
#include <fstream>

using std::cout; using std::endl;


int main(int argc, char* argv[]){ //needs two arguments to work
   if(argc < 2){
      std::cout << "Invalid number of arguments!"  << std::endl;
      return 0;
   }

   std::ifstream file1; //make files and open files
   std::ifstream file2;
   file1.open(argv[1]);
   file2.open(argv[2]);

   if(!file1 || !file2) {                    // Make sure file opened correctly
        std::cerr << "File not found/cannot open " << std::endl;
        exit(1);
    } //9/27/24


   std::string line1, line2;
   bool one = true, two =true;
   int lineNumber=0;

   while( one || two){//reads until longer file ends
      lineNumber++;
         if(std::getline(file1, line1)){}
         else{//in order to continue to read if other file longer
            one = false;
            line1="";
         }

         if(std::getline(file2, line2)){}
         else{//in order...
            two=false;
            line2="";
         }

         int location=-1; //finds difference between lines, if any
         if(line1.length()>line2.length())
            for(int i=0; i <line1.length(); i++){
               if(line1[i]!=line2[i] || i>+line2.length()){
                  location=i;
                  break;
               }
            }
         else{//done for out of bounds errors
            for(int i=0; i <line2.length(); i++){
               if(line1[i]!=line2[i] || i>+line1.length()){
                  location=i;
                  break;
               }
            }
         }

         if(location>=0){ //prints if theres a line difference
            std::string lengthCheck= argv[1] ;
            lengthCheck+= ": "+ std::to_string(lineNumber)+ ": ";
            cout << argv[1] << ": " << lineNumber << ": " << line1 << endl;
            cout << argv[2] << ": " << lineNumber << ": " << line2 << endl;
            for(int i=0; i <(lengthCheck.length()+location); i++)
               cout << " ";
            cout << "^" << endl;
         }

   }
}







