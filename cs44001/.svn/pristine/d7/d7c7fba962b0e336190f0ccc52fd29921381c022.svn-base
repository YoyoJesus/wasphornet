// selecting oranges
// converting vectors to multimaps
// Mikhail Nesterenko
// 9/26/2022


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <string>
#include <map>

using std::cin; using std::cout; using std::endl;
using std::string;
using std::vector;
using std::multimap;

enum class Variety {orange, pear, apple};
vector<string> colors =  {"red", "green", "yellow"};

int main(){
   srand(time(nullptr));
   multimap<Variety, vector<string>> tree;

   // random fruit and color selection using emplace
   int treeSize = rand() % 100 + 1;
   for (int i = 0; i < treeSize; ++i) {
      Variety fruit = static_cast<Variety>(rand() % 3);
      vector<string> color;
      color.push_back(colors[rand() % 3]);
      tree.emplace(fruit, color);
   }

   // using lower_bound and upper_bound to print colors of oranges
   cout << "Colors of the oranges: ";
   auto lower = tree.lower_bound(Variety::orange);
   auto upper = tree.upper_bound(Variety::orange);
   for (auto it = lower; it != upper; ++it) {
      for (auto &color : it->second)
         cout << color << " ";
   }
   cout << endl;
}

