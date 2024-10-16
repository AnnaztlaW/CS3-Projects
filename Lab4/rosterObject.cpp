// vector and list algorithms with objects in containers
// Anna Waltz

#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>

using std::ifstream;
using std::string; using std::getline;
using std::list; using std::vector;
using std::cout; using std::endl;
using std::move;


class Student{
public:
   Student(string firstName, string lastName): firstName_(firstName), lastName_(lastName) {}
 
   // move constructor, not really needed, generated automatically
   Student(Student && org) noexcept: firstName_(move(org.firstName_)), lastName_(move(org.lastName_)), classes_(move(org.classes_)) {}
  
   // force generation of default copy constructor
   Student(const Student & org) = default;

   
  string print() const {return firstName_ + ' ' + lastName_;}

  void addClass(string class_){classes_.push_back(class_);}

  string printClasses() const {
   string temp = "";
   for(const auto& class_ : classes_){
      temp+=class_ + " ";
   }
   return temp; 
  }

    // needed for unique() and for remove()
   friend bool operator== (Student left, Student right){
      return left.lastName_ == right.lastName_ &&
	     left.firstName_ == right.firstName_;
   }

   // needed for sort()
   friend bool operator< (Student left, Student right){
      return left.lastName_ < right.lastName_ ||
	     (left.lastName_ == right.lastName_ && 
	      left.firstName_ < right.firstName_);
   }

private:
   string firstName_;
   string lastName_;
   vector<string> classes_;
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
      cout << "\n\n" << argv[i] << "\n";  
      printRoster(roster);
      courseStudents.push_back(move(roster)); 
   }


   // reading in dropouts
   list<Student> dropouts; 
   readRoster(dropouts, argv[argc-1]); 
   cout << "\n\n dropouts \n"; printRoster(dropouts);

   list<Student> allStudents;  // master list of students
 
   for(auto& lst : courseStudents) 
     allStudents.splice(allStudents.end(),lst);

   cout << "\n\n all students unsorted \n"; 
           printRoster(allStudents);

   allStudents.sort(); // sorting master list
   cout << "\n\n all students sorted \n"; printRoster(allStudents);

   allStudents.unique(); // eliminating duplicates
   cout << "\n\n all students, duplicates removed \n"; printRoster(allStudents);
   
   for (const auto& str : dropouts)  // removing individual dropouts
      allStudents.remove(str);
   cout << "\n\n all students, dropouts removed \n"; printRoster(allStudents);

//milestone 2 for lab 4
   list<Student> studentCourse;
   for(const auto& stu : allStudents){
      studentCourse.push_back(move(stu));
   }
   for(int i= 1 ; i < argc-1; i++){
      list<Student> roster;
      readRoster(roster, argv[i]); 
      string course = argv[i];
      course = course.substr(0,course.find(".txt") );
      for(auto& studentInClass : roster) //each student in class i
         for(auto& stu : studentCourse){ //check if stu in roster
            if(stu == studentInClass){
               stu.addClass(course);
               break;
            }
         }
   }
   cout << "\n\n all students, with courses\n";
   for(const auto& student : studentCourse)
      cout << student.print() << ": "  << student.printClasses()<< endl;

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