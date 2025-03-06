// sorting apples
// non STL-algorithm code to be replaced by algorthms
// Mikhail Nesterenko
// 02/19/2025

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>
#include <numeric>

using std::cin; using std::cout; using std::endl;
using std::string;
using std::vector; using std::deque;

struct Apples{
   double weight; // oz
   string color;  // red or green
   void print() const { cout << color << ", " <<  weight << endl; }
};


int main(){
   srand(time(nullptr));
   const double minWeight = 3.;
   const double maxWeight = 8.;

   cout << "Input crate size: ";
   int size;
   cin >> size;

   vector <Apples> crate(size);

   // assign random weight and color to apples in the crate
   // replace with generate()
   //for(auto it = crate.begin(); it != crate.end(); ++it){
   //   static_cast<double>(rand())/RAND_MAX*(maxWeight - minWeight);
   //   it->color = rand() % 2 == 1 ? "green" : "red";
   //   it->weight = minWeight + 
   //}

   //passing maxWeight and minWeight by reference - needed for lambda
   generate(crate.begin(), crate.end(), [&maxWeight, &minWeight](){
      Apples a;
      // pick a random number between minWeight and maxWeight - type casting
      a.weight = minWeight + static_cast<double>(rand())/RAND_MAX*(maxWeight - minWeight);
      a.color = rand() % 2 == 1 ? "green" : "red";
      return a;
   });


   // // for_each() possibly
   //cout << "all appleas"<< endl;
   //for(const auto &e: crate) {
   //   e.print();
   //}
   cout << "all apples" << endl;
   for_each(crate.begin(), crate.end(), [](const Apples &element){
      element.print();
   });

   
   cout << "Enter weight to find: ";
   double toFind;
   cin >> toFind;

   //// count_if()
   //int cnt = 0;
   //for(auto it = crate.cbegin(); it != crate.cend(); ++it) 
   //   if(it->weight > toFind) ++cnt;
   int cnt = 0;
   cnt = count_if(crate.begin(), crate.end(), [&toFind](const Apples &element){
      return element.weight > toFind;
   });

   cout << "There are " << cnt << " apples heavier than " 
	<< toFind << " oz" <<  endl;

   // find_if()
   cout << "at positions ";
   //for(int i=0; i < size; ++i)
   //   if(crate[i].weight > toFind)
	// cout << i << ", ";

   // iterate through the crate and find all apples heavier than toFind
   // have to use iterators in the for loop so we can pass the iterator to find_if()
   for (auto it = crate.begin(); it != crate.end();) {
      // call find_if() to find the next apple heavier than toFind
      it = find_if(it, crate.end(), [&toFind](const Apples &element){
         return element.weight > toFind;
      });

      // if an apple heavier than toFind is found, print its position
      if (it != crate.end()) {
         cout << it - crate.begin() << ", ";
         ++it;
      }
   }
   cout << endl;
    


   // max_element()
   //double heaviest = crate[0].weight;
   //for(int i=1; i < size; ++i)
   //   if(crate[i].weight > heaviest) heaviest = crate[i].weight; 
   //cout << "Heaviest apple weighs: " << heaviest << " oz" << endl;
   auto max = max_element(crate.begin(), crate.end(), [](const Apples &a, const Apples &b){
      return a.weight < b.weight;
   });
   cout << "Heaviest apple weighs: " << max->weight << " oz" << endl;

   //// for_each() or accumulate()
   double sum = 0;
   //for(int i=0; i < size; ++i)
   //   sum += crate[i].weight;
   //cout << "Total apple weight is: " << sum << " oz" << endl;
   sum = accumulate(crate.begin(), crate.end(), 0.0, [](double a, const Apples &b){
      return a + b.weight;
   });
   cout << "Total apple weight is: " << sum << " oz" << endl;

   // transform();
   cout << "How much should they grow: ";
   double toGrow;
   cin >> toGrow;
   //for(int i=0; i < crate.size(); ++i)
   //   crate[i].weight += toGrow;
   transform(crate.begin(), crate.end(), crate.begin(), [&toGrow](Apples &element){
      element.weight += toGrow;
      return element;
   });

   cout << "Input minimum acceptable weight: ";
   double minAccept;
   cin >> minAccept;


   // removing small apples
   // nested loops, replace with a single loop modification idiom
   //bool removed;
   //do{
   //   removed = false;
   //   for(auto it = crate.begin(); it != crate.end(); ++it)
	// if(it->weight < minAccept){
	//    crate.erase(it);
	//    removed = true;
	//    break;
   //    }
   //}while(removed);
   crate.erase(remove_if(crate.begin(), crate.end(), [&minAccept](const Apples &element){
      return element.weight < minAccept;
   }), crate.end());

   cout << "removed " << size - crate.size() << " elements" << endl;


   //// bubble sort, replace with sort()
   //bool swapped;
   //do{
   //   swapped = false;
   //   for(int i=0; i < crate.size()-1; ++i)
	// if(crate[i].weight > crate[i+1].weight){
	//    std::swap(crate[i], crate[i+1]);
	//    swapped = true;
	// }
   //}while(swapped);
   sort(crate.begin(), crate.end(), [](const Apples &a, const Apples &b){
      return a.weight < b.weight;
   });


   //// for_each() possibly
   //cout << "sorted remaining apples"<< endl;
   //for(const auto &e: crate) {
   //   e.print();
   //}
   cout << "sorted remaining apples" << endl;
   for_each(crate.begin(), crate.end(), [](const Apples &element){
      element.print();
   });

}
