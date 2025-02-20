// object version of roster program
// Mikhail Nesterenko modified by Austin Sternberg
// 2/12/2025

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
   // default constructor
   Student(string firstName, string lastName): 
      firstName_(firstName), lastName_(lastName) {}

   // move constructor, not really needed, generated automatically
   Student(Student && org) noexcept:
      firstName_(move(org.firstName_)),
      lastName_(move(org.lastName_)),
      courses_(move(org.courses_))
   {/*cout << "move ctor" << endl;*/}

   // force generation of default copy constructor
   Student(const Student & org) = default;
   
   // print student name + all courses
   string print() const {
      string all_courses;
      // concatenate all courses
      for(const auto& course : courses_) all_courses += course + ' ';
      return firstName_ + ' ' + lastName_ + ":" + all_courses;
   }

   // add a new course
   void new_course(const string& course) {courses_.push_back(course);}

   // get the last course - accessor
   string get_course() const {return courses_.back();}

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
   list<string> courses_;
};


// reading a list from a fileName
void readRoster(list<Student>& roster, string fileName);
// remove dropouts from the main roster
void removeDropouts(list<Student>& roster, const list<Student>& dropouts);;
// merge students from different courses
void mergeStudents(list<Student>& roster);
// printing a list out
void printRoster(const list<Student>& roster);

int main(int argc, char* argv[]){

   if (argc <= 1){ cout << "usage: " << argv[0] 
      << " list of courses, dropouts last" << endl; exit(1);}

   // reading in courses
   vector<list<Student>> master_roster;
   for(int i=1; i < argc-1; ++i){
      list<Student> course_roster;
      readRoster(course_roster, argv[i]);
      master_roster.push_back(move(course_roster));
   }

   // reading in dropouts
   list<Student> dropouts;
   readRoster(dropouts, argv[argc-1]);

   // removing dropouts
   for(auto& course_roster : master_roster) removeDropouts(course_roster, dropouts);

   //splice all courses into one
   list<Student> all_students;
   for(auto& course_roster : master_roster)
      all_students.splice(all_students.end(), move(course_roster));

   // sorting the final roster
   all_students.sort();

   // merge students with the same name
   mergeStudents(all_students);

   // printing the final roster
   cout << "all students, dropouts removed and sorted\n";
   cout << "first name last name: courses enrolled\n";
   printRoster(all_students);
}


void readRoster(list<Student>& roster, string fileName){
   ifstream course(fileName);
   string first, last;
   string course_name = fileName;

   // Extract course name from filename
   int pos = course_name.find('.');
   if (pos != -1) { // If pos is -1, the file name does not contain a period
      course_name = course_name.substr(0, pos);
   }

   // Read student names from the course file
   while (course >> first >> last) {
      Student student(first, last);
      student.new_course(course_name);
      roster.push_back(move(student));
   }

   course.close();
}

void removeDropouts(list<Student>& roster, const list<Student>& dropouts){
   for (const auto& dropout_student : dropouts) {
      roster.remove(dropout_student);
   }
}

void mergeStudents(list<Student>& roster){
   for (auto it = roster.begin(); it != roster.end(); ++it){
      // set a next iterator and increment it
      auto next = it;
      ++next;

      // check if the next student is the same as the current one
      while (next != roster.end()){

         // if the students are the same, merge their courses
         if (*it == *next){
            it->new_course(next->get_course());
            next = roster.erase(next);
         } else {++next;} // move to the next student
      }
   }
}

// printing a list out
void printRoster(const list<Student>& roster){
   for (const auto& student : roster) {
      cout << student.print() << endl;
   }
}