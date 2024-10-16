// vector and list algorithms with objects in containers
// Anna Waltz

//MILESTONE 1 SECTION OF lAB 5

#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>
#include <map>

using std::ifstream;
using std::string; using std::getline;
using std::list; using std::vector;
using std::cout; using std::endl;
using std::move;
using std::map;


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
void readRoster(list<Student>& roster, string fileName);  
// printing a list out
void printRoster(const list<Student>& roster); 

int main(int argc, char* argv[]){

   if (argc <= 1){ cout << "usage: " << argv[0] 
      << " list of courses, dropouts last" << endl; exit(1);}

   // vector of courses of students
   vector <list<Student>> courseStudents; 
   for(int i=1; i < argc-1; ++i){
      list<Student> roster;
      readRoster(roster, argv[i]);  
      courseStudents.push_back(move(roster)); 
   }

   // reading in dropouts
   list<Student> dropouts; 
   readRoster(dropouts, argv[argc-1]);

   // all stidents with courses
   // map<Student, list<string>>  
   // list=courses

   map< Student, list<string> > studentMap;
   list<string> temp;
   for(int i= 1; i < argc-1; i++){
      list<Student> classRoster = courseStudents[i-1];
      string course = argv[i];
      course = course.substr(0,course.find(".txt") );
      for(auto& student : classRoster){
         //auto ret = studentMap.insert(std::make_pair(student, temp)); //redundent
         studentMap[student].push_back(course); //add course, wont overwrite
      }
   }
   for(const auto& dropped : dropouts) //dropouts removed
      studentMap.erase(dropped);

   cout << "\nall students, dropouts removed and sorted\nfirst name last name: courses enrolled" << endl;;
   for( const auto& student : studentMap){ //printing map
      cout << student.first.print() << ": ";
      for(const auto& course : student.second) //print list in map
         cout << course << " ";
      cout << endl;
   }

   

}


void readRoster(list<Student>& roster, string fileName){
   ifstream course(fileName);
   string first, last;
   while(course >> first >> last)
      roster.push_back(Student(first, last));
   course.close();
}

// printing a list out
void printRoster(const list<Student>& roster){
   for(const auto& student : roster)
      cout << student.print() << endl;
}