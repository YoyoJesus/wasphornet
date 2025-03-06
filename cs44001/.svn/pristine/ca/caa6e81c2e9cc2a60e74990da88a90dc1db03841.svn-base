// jamming peaches
// non STL-algorithm code to be replaced by algorthms
// Mikhail Nesterenko Modified by Austin Sternberg
// 9/30/2021


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>
#include <numeric>
#include <functional>

using std::cin; using std::cout; using std::endl;
using std::string;
using std::vector; using std::deque;
using std::bind;
using std::placeholders::_1;

struct Peaches{
   double weight; // oz
   bool ripe;  // ripe or not
   void print() const { cout << (ripe?"ripe":"green") << ", " <<  weight << endl; }
};


int main(){
   srand(time(nullptr));
   const double minWeight = 3.;
   const double maxWeight = 8.;

   cout << "Input basket size: ";
   int size;
   cin >> size;

   vector <Peaches> basket(size);

   // assign random weight and ripeness peaches in the basket
   // replace with generate()
   //for(auto it = basket.begin(); it != basket.end(); ++it){
   //   it->weight = minWeight + 
	//           static_cast<double>(rand())/RAND_MAX*(maxWeight - minWeight);
   //   it->ripe = rand() % 2;
   //}
   generate(basket.begin(), basket.end(), [&maxWeight, &minWeight](){
      Peaches p;
      p.weight = minWeight + static_cast<double>(rand())/RAND_MAX*(maxWeight - minWeight);
      p.ripe = rand() % 2;
      return p;
   });

   
   // for_each() possibly
   cout << "all peaches"<< endl;
   //for(const auto &e: basket) {
   //   e.print(); 
   //}

   for_each(basket.begin(), basket.end(), [](const Peaches &element){
      element.print();
   });

   // moving all the ripe peaches from basket to peck
   // remove_copy_if() with back_inserter()/front_inserter() or equivalents
   deque<Peaches> peck;
   //for(auto it=basket.begin(); it != basket.end();)
   //   if(it->ripe){
	// peck.push_front(std::move(*it));
	// it=basket.erase(it);
   //   }else
	// ++it;

   //copy all ripe peaches to peck
   remove_copy_if(basket.begin(), basket.end(), back_inserter(peck), [](const Peaches& p){
      return !p.ripe;
   });

   //remove ripe peaches from basket - remove erase idiom
   auto remove_bas = remove_if(basket.begin(), basket.end(), [](const Peaches& p){
      return p.ripe;
   });
   basket.erase(remove_bas, basket.end());

   // for_each() possibly
   cout << endl;
   cout << "peaches remainng in the basket"<< endl;
   //for(const auto &e: basket) {
   //   e.print(); 
   //}
   for_each(basket.begin(), basket.end(), [](const Peaches &element){
      element.print();
   });

   cout << endl;

   // for_each() possibly
   cout << "peaches moved to the peck"<< endl;
   //for(const auto &e: peck) {
   //   e.print();
   //}
   for_each(peck.begin(), peck.end(), [](const Peaches &element){
      element.print();
   });


   // prints every "space" peach in the peck
   const int space=3; 
   cout << "\nevery " << space << "\'d peach in the peck"<< endl;

   // replace with advance()/next()/distance()
   // no explicit iterator arithmetic
   //auto it=peck.cbegin(); int i = 1;   
   //while(it != peck.cend()){
   //   if(i == space){
	// it->print();
	// i=0;
   //   }
   //   ++i; 
   //   ++it;
   //}
   for(auto it = peck.cbegin(); it != peck.cend();){
      if (distance(peck.cbegin(), it) % space == space - 1) {
         it->print();
      }
      advance(it, 1);
   }



   // putting all small ripe peaches in a jam
   // use a binder to create a functor with configurable max weight
   // accumulate() or count_if() then remove_if()
   const double weightToJam = 10.0;
   double jamWeight = 0; 

   // create a binder for the weight comparison
   auto isLessThanWeightToJam = bind(std::less<double>(), _1, weightToJam);

   // accumulate the weight of small ripe peaches
   jamWeight = accumulate(peck.begin(), peck.end(), 0.0, [&isLessThanWeightToJam](double sum, const Peaches& p){
      // ternary operator to add weight if less than weightToJam - check if weight is less than weightToJam
      return isLessThanWeightToJam(p.weight) ? sum + p.weight : sum; 
   });

   // remove small ripe peaches from the peck - since they aew now 'jamed'
   // remove erase idiom
   auto remove_jamed = remove_if(peck.begin(), peck.end(), [&isLessThanWeightToJam](const Peaches& p){
      return isLessThanWeightToJam(p.weight);
   });
   peck.erase(remove_jamed, peck.end());
   //for(auto it=peck.begin(); it != peck.end();)
   //   if(it->weight < weightToJam){
	// jamWeight += it->weight;
	// it=peck.erase(it);
   //   }else
	// ++it;
   

   cout << "Weight of jam is: " << jamWeight << endl;

}

