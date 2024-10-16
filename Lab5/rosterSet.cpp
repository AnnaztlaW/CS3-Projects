// vector and list algorithms with objects in containers
// Anna Waltz


//MILESTONE 2 SECTION OF lAB 5

#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>
#include <set>

using std::ifstream;
using std::string; using std::getline;
using std::list; using std::vector;
using std::cout; using std::endl;
using std::move;
using std::set;


class Student{
public:
   Student(string firstName, string lastName): 
      firstName_(firstName), lastName_(lastName) {}
 
   // move constructor, not really needed, generated automatically
   Student(Student && org) noexcept:
      firstName_(move(org.firstName_)),
      lastName_(move(org.lastName_))
   {}
  
   // force generation of default copy constructor
   Student(const Student & org) = default;
   
  string print() const {return firstName_ + ' ' + lastName_;}

    // needed for unique() and for remove()
   friend bool operator== (Student left, Student right){
      return left.lastName_ == right.lastName_ &&
	     left.firstName_ == right.firstName_;
   }

   // needed for sort()
   friend bool operator< (Student left, Student right){
      return left.firstName_ < right.firstName_ ||
	     (left.firstName_ == right.firstName_ && 
	      left.lastName_ < right.lastName_);
   }
private:
   string firstName_;
   string lastName_;
};




// reading a list from a fileName
void readRoster(set<Student>& roster, string fileName);  
// printing a list out
void printRoster(const set<Student>& roster); 

int main(int argc, char* argv[]){

   if (argc <= 1){ cout << "usage: " << argv[0] 
      << " list of courses, dropouts last" << endl; exit(1);}

   // set of current students, all students but no dropouts
   set<Student> currentStudents; 

   for(int i=1; i < argc-1; ++i) // all students
      readRoster(currentStudents, argv[i]);  

   // reading in dropouts
   set<Student> dropouts; 
   readRoster(dropouts, argv[argc-1]); 
   //cout << "\n\n dropouts \n"; printRoster(dropouts);

   for(auto& dropped : dropouts) //remove dropouts
      currentStudents.erase(dropped);

   cout << "\n\nCurrently Enrolled Students" << endl;
   for(const auto& stu : currentStudents){
      cout << stu.print() << endl;
   }

}


void readRoster(set<Student>& roster, string fileName){
   ifstream course(fileName);
   string first, last;
   while(course >> first >> last)
      roster.insert(Student(first, last));
   course.close();
}

// printing a list out
void printRoster(const set<Student>& roster){
   for(const auto& student : roster)
      cout << student.print() << endl;
}