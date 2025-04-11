// needed for lab
// Mikhail Nesterenko
// 3/18/2022

#include <iostream>
#include <vector>
#include <cstdlib>
#include "CarFactory.hpp"
#include <array>

using std::vector;
using std::cout; using std::endl;

const int NUM_CARS = 8; // number of cars in the lot

class CarLot{
public:
   CarLot();

   Car *testDriveCar(){
      carIndex_ = 0; // using to reset the index to 0
      return car4sale_[carIndex_];
   }

   // if a car is bought, requests a new one
   Car *buyCar(){ 
      Car *bought = 
      car4sale_[carIndex_] = 
        factories_[rand()%factories_.size()]->requestCar();
      return bought;
   }

   int lotSize() const {return car4sale_.size();}

   Car *nextCar() {
      if (carIndex_ < car4sale_.size())
         return car4sale_[carIndex_++]; // postfix increment operator
      else {
         carIndex_ = 0; // reset index to 0
         return nullptr; // no more cars to test drive
      }
   }
		     
private:
   int carIndex_; // index of the car in the lot
   vector<Car *> car4sale_; // changed to vector<Car*> from Car*
   vector<CarFactory *> factories_;
};


CarLot::CarLot(){
   // creates 2 Ford factories and 2 Toyota factories 
   factories_.push_back(new FordFactory());   
   factories_.push_back(new ToyotaFactory());
   factories_.push_back(new FordFactory());
   factories_.push_back(new ToyotaFactory());

   // gets the first car for sale
   //car4sale_ = factories_[rand() % factories_.size()] -> requestCar();
   for(int i=0; i < NUM_CARS; ++i){
      Car *car = factories_[rand() % factories_.size()] -> requestCar();
      car4sale_.push_back(car);
   }

}



CarLot *carLotPtr = nullptr; // global pointer instantiation

// test-drives a car
// buys it if Toyota
void toyotaLover(int id){
   if (carLotPtr == nullptr)
      carLotPtr = new CarLot();

   Car *toBuy = carLotPtr -> testDriveCar(); 

   for (int i=0; i < carLotPtr->lotSize(); ++i){
      Car *toBuy = carLotPtr -> nextCar();

      // select a preferred model that this buyer likes
      static const std::array<std::string, 5> 
         models = {"Corolla", "Camry", "Prius", "4Runner", "Yaris"};
      std::string Pmodel = models[rand() % models.size()];

      // if no more cars to test drive, leave the lot
      if (toBuy == nullptr) {
         cout << "Buyer is leaving the lot!" << endl;
         break;
      }

      cout << "Jill Toyoter " << id + 1 << endl;
      // I am doing it this way to ensure that the id starts at 1
      // I do not like id starting at 0 in the output
      // 0 is not a good id number based on my experience in DB
      cout << "test driving " 
	   << toBuy->getMake() << " "
	   << toBuy->getModel();

      if (toBuy->getMake() == "Toyota" && 
          toBuy->getModel() == Pmodel){
         cout << " love it! buying it!" << endl;
         carLotPtr -> buyCar();
         break;
      } else
         cout << " did not like it!" << endl;
   }
}

// test-drives a car
// buys it if Ford
void fordLover(int id){
   if (carLotPtr == nullptr)
      carLotPtr = new CarLot();

   Car *toBuy = carLotPtr -> testDriveCar();

   for (int i = 0; i < carLotPtr->lotSize(); ++i) {
      Car *toBuy = carLotPtr -> nextCar();

      // select a preferred model that this buyer likes
      static const std::array<std::string, 4>
      models = {"Focus", "Mustang", "Explorer", "F-150"};
      std::string Pmodel = models[rand() % models.size()];

      // if no more cars to test drive, leave the lot
      if (toBuy == nullptr) {
         cout << "Buyer is leaving the lot!" << endl;
         break;
      }
   
      cout << "Jack Fordman " << id + 1  << endl;
      // I am doing it this way to ensure that the id starts at 1
      // I do not like id starting at 0 in the output
      // 0 is not a good id number based on my experience in DB
      cout << " test driving "
	   << toBuy->getMake() << " "
        << toBuy->getModel();
   
      if (toBuy->getMake() == "Ford" && 
          toBuy->getModel() == Pmodel){
         cout << " love it! buying it!" << endl;
         carLotPtr -> buyCar();
         break;
      } else
         cout << " did not like it!" << endl;
   }
}



int main() {
   srand(time(nullptr));

   const int numBuyers=20;
   for(int i=0; i < numBuyers; ++i)
      if(rand()% 2 == 0)
	      toyotaLover(i);
      else
	      fordLover(i);
  
}
