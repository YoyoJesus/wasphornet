// procedural version of roster program
// Mikhail Nesterenko - Modified by Austin Sternberg
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

// reading a list from a file name
void readRoster(list<list<string>>& roster, string fileName);

// printing a list
void printRoster(list<list<string>>& roster);

// remove dropouts from the main roster
void removeDropouts(list<list<string>>& roster, const list<list<string>>& dropouts);

int main(int argc, char* argv[]) {
   if (argc <= 1) {
      cout << "usage: " << argv[0] << " list of courses, dropouts last" << endl;
      exit(1);
   }

   list<list<string>> student_roster;

   // Read all course rosters
   for (int i = 1; i < argc - 1; ++i) {
      readRoster(student_roster, argv[i]);
   }

   // Process dropouts from the last file argument
   list<list<string>> dropouts;
   readRoster(dropouts, argv[argc - 1]);

   // Remove students who are in the dropout list
   removeDropouts(student_roster, dropouts);

   // Sort the final roster
   student_roster.sort();

   // Print the final roster
   cout << "all students, dropouts removed and sorted\n";
   cout << "first name last name: courses enrolled\n";
   printRoster(student_roster);
}

// Read a course roster from a file and add it to the main roster
void readRoster(list<list<string>>& roster, string file_name) {
   ifstream course(file_name);
   string first, last;
   string course_name = file_name;

    // Extract course name from filename
   int pos = course_name.find('.');
   if (pos != -1) { // If pos is -1, the file name does not contain a period
      course_name = course_name.substr(0, pos);
   }

    // Read student names from the course file
   while (course >> first >> last) {
      string full_name = first + ' ' + last;
      bool studentFound = false; // Flag to check if the student is already in the roster - default to false

      // Check if the student is already in the roster
      for (auto& lst : roster) {

         // If the student is in the roster, add the course to their list of courses
         if (lst.front() == full_name) {
            lst.push_back(course_name);
            studentFound = true;
            break;
         }
      }

         // If the student is not in the roster, add them
         if (!studentFound) {
            list<string> new_student = { full_name, course_name };
            roster.push_back(new_student);
         }
      }

   course.close();
}

// Remove dropouts from the main roster
void removeDropouts(list<list<string>>& roster, const list<list<string>>& dropouts) {

   // Iterate through the roster and remove students who are in the dropout list
   for (auto it = roster.begin(); it != roster.end(); ) {
      string student_name = it->front();
      bool is_dropout = false;

      // Check if the student is in the dropout list
      for (const auto& dropout : dropouts) {
         if (dropout.front() == student_name) {
            is_dropout = true;
            break;
         }
      }

      // Remove the student if they are in the dropout list, otherwise move to the next student
      if (is_dropout) {
         it = roster.erase(it); // Remove the student and get the next iterator
      } else {
         ++it; // Move to the next student
      }
   }
}

void printRoster(list<list<string>>& roster) {
   // Print each student and their courses
   for (const auto& student : roster) {
      auto it = student.begin();
      cout << *it << ":";  // Print student name
      ++it;

      // Print each course the student is enrolled in
      while (it != student.end()) {
         cout << *it << " ";  // Print courses
         ++it;
      }

      cout << endl;
   }
}
