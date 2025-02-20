// roster that works with map<Student, list<string>> - way more efficient
// Mikhail Nesterenko - Modified by: Austin Sternberg
// 2/14/2025

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
using std::move; using std::set;
using std::string;


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



// reading a set from a fileName
void readRoster(set<Student>& courseStudents, string fileName);
// Remove Dropouts
void removeDropouts(set<Student>& courseStudents, const set<Student>& dropouts);
// printing a list out
void printRoster(const set<Student>& courseStudents); 

int main(int argc, char* argv[]){

   if (argc <= 1){ cout << "usage: " << argv[0] 
      << " list of courses, dropouts last" << endl; exit(1);}

   set<Student> courseStudents; 

   // reading in courses
   for(int i=1; i < argc-1; ++i){
      readRoster(courseStudents, argv[i]); 
   }

   // removing dropouts
   set<Student> dropouts; 
   readRoster(dropouts, argv[argc-1]); 
   removeDropouts(courseStudents, dropouts); // removing dropouts
   
   // printing the final roster
   cout << "Currently Enrolled Students\n";
   printRoster(courseStudents);

}

// reading a set from a fileName
void readRoster(set<Student>& roster, string fileName){
   ifstream course(fileName);
   string first, last;

   // reading in courses
   while(course >> first >> last)
      roster.insert(Student(first, last));
   
   course.close();
}

// Remove Dropouts
void removeDropouts(set<Student>& courseStudents, const set<Student>& dropouts){
   for(const auto& student : dropouts) courseStudents.erase(student);
}

// printing a list out
void printRoster(const set<Student>& roster){
   for(const auto& student : roster)
      cout << student.print() << endl;
}