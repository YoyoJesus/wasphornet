// hashmap test file
// Mikhail Nesterenko,  Tsung-Heng Wu
// 3/6/2024

#include "hashmap.hpp"
#include <iostream>
#include <string>
#include <cassert>

using std::string; using std::cout; using std::endl;

int main() {

   //
   // <int, int> hashmap test
   //
   hashmap<int, int> myHash;
   
   // test inserts
   pair<const pair<const int, int>*, bool> result;

   result = myHash.insert(make_pair(4, 40));
   assert(result.second);
   assert(result.first->first == 4);
   assert(result.first->second == 40);

   result = myHash.insert(make_pair(105, 1050));
   assert(result.second);
   assert(result.first->first == 105);
   assert(result.first->second == 1050);

   result = myHash.insert(make_pair(6, 60));
   assert(result.second);
   assert(result.first->first == 6);
   assert(result.first->second == 60);

   result = myHash.insert(make_pair(107, 1070));
   assert(result.second);
   assert(result.first->first == 107);
   assert(result.first->second == 1070);

   result = myHash.insert(make_pair(90, 900));
   assert(result.second);
   assert(result.first->first == 90);
   assert(result.first->second == 900);

   result = myHash.insert(make_pair(95, 950));
   assert(result.second);
   assert(result.first->first == 95);
   assert(result.first->second == 950);

   result = myHash.insert(make_pair(6, 70)); // insert with a duplicate key
   assert(!result.second);
   assert(result.first->first == 6);
   assert(result.first->second == 60);


   // searching map
   // x will have type hashmap<int, int>::value_type*
   auto x = myHash.find(4);
   assert(x != nullptr);
   assert(x->second == 40);

   x = myHash.find(5);
   assert(x == nullptr);

   // test deletes
   result = myHash.erase(4); // delete with next element in same bucket
   cout << "result: " << result.first->first << result.first->second << endl;
   assert(result.second);
   assert(result.first->first == 105);
   assert(result.first->second == 1050);

   result = myHash.erase(107); // delete the last element in a bucket
   assert(result.second);
   assert(result.first->first == 90);
   assert(result.first->second == 900);

   result = myHash.erase(6);
   assert(result.second);
   assert(result.first->first == 90);
   assert(result.first->second == 900);

   result = myHash.erase(105);
   assert(result.second);
   assert(result.first->first == 90);
   assert(result.first->second == 900);

   result = myHash.erase(95); // erase the last element in the container
   cout << "result: " << result.first << " " << result.second << endl;
   assert(result.second);
   assert(result.first== nullptr);

   result = myHash.erase(90); // erased all elements in container
   cout << "result: " << result.first << " " << result.second << endl;
   assert(result.second);
   assert(result.first == nullptr);

   result = myHash.erase(5); // erase key not in container
   cout << "result: " << result.first << " " << result.second << endl;
   assert(!result.second);
   // first is unspecified

   //
   //<integer, string> hashmap test
   //
   hashmap<int, string> employees;
   pair<const pair<const int, string>*, bool> result2;
   
   // add tests for insert using the <integer, string> hashmap
   result2 = employees.insert(make_pair(1, "Alice"));
   assert(result2.second);
   assert(result2.first->first == 1);
   assert(result2.first->second == "Alice");

   result2 = employees.insert(make_pair(2, "Bob"));
   assert(result2.second);
   assert(result2.first->first == 2);
   assert(result2.first->second == "Bob");

   result2 = employees.insert(make_pair(3, "Charlie"));
   assert(result2.second);
   assert(result2.first->first == 3);
   assert(result2.first->second == "Charlie");

   result2 = employees.insert(make_pair(2, "David"));
   assert(!result2.second);
   assert(result2.first->first == 2);
   assert(result2.first->second == "Bob");

   // Find elements
   auto y = employees.find(1);
   assert(y != nullptr);
   assert(y->second == "Alice");

   y = employees.find(2);
   assert(y != nullptr);
   assert(y->second == "Bob");

   y = employees.find(4);
   assert(y == nullptr);

   // Erase elements
   result2 = employees.erase(1);
   assert(result2.second);
   assert(result2.first->first == 2);
   assert(result2.first->second == "Bob");

   result2 = employees.erase(3);
   assert(result2.second);
   assert(result2.first->first == 2);
   assert(result2.first->second == "Bob");

   result2 = employees.erase(2);
   assert(result2.second);
   assert(result2.first == nullptr);

   result2 = employees.erase(5);
   assert(!result2.second);

   // [] operator
   employees[4] = "Diana";
   assert(employees[4] == "Diana");

   employees[4] = "Edward";
   assert(employees[4] != "Edward"); // value should not be updated - hashmaps are immutable

   employees[5];
   assert(employees[5] == "");

   // Rehashing test
   // Insert elements to ensure the container needs rehashing
   for (int i = 6; i <= 20; ++i) {
       employees[i] = "Employee" + std::to_string(i);
   }

   std::cout << "After inserting elements, before rehashing:" << std::endl;
   assert(employees[6] == "Employee6");
   assert(employees[15] == "Employee15");
   assert(employees[20] == "Employee20");

   // Perform rehashing (resize the bucket size to a larger number, e.g., 50)
   employees.rehash(50);

   std::cout << "After rehashing:" << std::endl;
   assert(employees[6] == "Employee6");
   assert(employees[15] == "Employee15");
   assert(employees[20] == "Employee20");

   // Test after rehashing
   auto z = employees.find(10);
   assert(z != nullptr);
   assert(z->second == "Employee10");

   result2 = employees.erase(10);
   assert(result2.second);
   assert(result2.first->first == 11);

   result2 = employees.insert(make_pair(10, "Reinserted"));
   assert(result2.second);
   assert(result2.first->first == 10);
   assert(result2.first->second == "Reinserted");

   std::cout << "Tests passed" << std::endl;
}