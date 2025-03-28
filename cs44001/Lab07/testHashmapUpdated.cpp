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
   //cout << "result: " << result.first->first << result.first->second << endl;
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
   //cout << "result: " << result.first << " " << result.second << endl;
   assert(result.second);
   assert(result.first== nullptr);

   result = myHash.erase(90); // erased all elements in container
   //cout << "result: " << result.first << " " << result.second << endl;
   assert(result.second);
   assert(result.first == nullptr);

   result = myHash.erase(5); // erase key not in container
   //cout << "result: " << result.first << " " << result.second << endl;
   assert(!result.second);
   // first is unspecified

   cout << "og tests passed" << endl;

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

   cout << "string insert passed" << endl;
   
   // Find elements
   auto y = employees.find(1);
   assert(y != nullptr);
   assert(y->second == "Alice");

   y = employees.find(2);
   assert(y != nullptr);
   assert(y->second == "Bob");

   y = employees.find(4);
   assert(y == nullptr);

   cout << "find passed" << endl;
   
   // Erase elements
   result2 = employees.erase(1);
   assert(result2.second);
   assert(result2.first->first == 2);
   assert(result2.first->second == "Bob");

   result2 = employees.erase(3);
   assert(result2.second);
   assert(result2.first == nullptr);
   
   result2 = employees.erase(4);
   assert(!result2.second);

   result2 = employees.erase(2);
   assert(result2.second);
   assert(result2.first == nullptr);

    cout << "erase passed" << endl;

   // [] operator
   employees[4] = "Diana";
   assert(employees[4] == "Diana");

   employees[4] = "Edward";
   assert(employees[4] == "Edward"); // value should be updated - unsafe insert

   employees[5];
   assert(employees[5] == ""); // value should be default constructed

   // Rehashing test
   // Insert elements to ensure the container needs rehashing
   for (int i = 6; i <= 150; ++i) {
       employees[i] = "Employee" + std::to_string(i);
   }
   assert(employees[6] == "Employee6");
   assert(employees[15] == "Employee15");
   assert(employees[20] == "Employee20");
   assert(employees[90] == "Employee90");
   assert(employees[100] == "Employee100");
   assert(employees[120] == "Employee120");
   assert(employees[150] == "Employee150");
   std::cout << "passed pre-rehashing" << std::endl;

   // rehash the container
   employees.rehash(200);

   //push more elements to ensure rehashing is working
    for (int i = 101; i <= 300; ++i) {
         employees[i] = "Employee" + std::to_string(i);
    }
    
   assert(employees[101] == "Employee101");
   assert(employees[150] == "Employee150");
   assert(employees[180] == "Employee180");
   // check if the previous elements are still there
   assert(employees[6] == "Employee6"); 
   assert(employees[15] == "Employee15");
   assert(employees[20] == "Employee20");
   assert(employees[90] == "Employee90");
    
   // Test after rehashing
   auto z = employees.find(150);
   assert(z != nullptr);
   assert(z->second == "Employee150");

   z = employees.find(200);
   assert(z != nullptr);
   assert(z->second == "Employee200");

   z = employees.find(400);
   assert(z == nullptr);

   auto it = employees.erase(150);
   assert(it.second);
   assert(it.first->first == 151);

   employees.insert(make_pair(150, "150"));
   assert(employees[150] == "150");

   cout << "rehashing passed" << endl;

   std::cout << "Tests passed" << std::endl;
}