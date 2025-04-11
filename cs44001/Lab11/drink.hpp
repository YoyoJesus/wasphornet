// drink class to be used in Coffee Shack lab
// Mikhail Nesterenko
// 11/7/2022

#include <string>

enum class DrinkType {small, medium, large};
//prices large=10, medium=7, small=5

class Drink{
public:
   Drink(DrinkType type=DrinkType::small) {
      type_ = type;
      switch (type_) {
         case DrinkType::large: price_ = 10; break;
         case DrinkType::medium: price_ = 7; break;
         case DrinkType::small: default: price_ = 5; break;
      }
   }

   virtual int getPrice() const {
      return price_;
   };

   virtual std::string getName() const {
      switch (type_) {
         case DrinkType::medium: return "medium coffee with";
         case DrinkType::large: return "large coffee with";
         default: return "small coffee with"; // default parameter is small
      }
   };

   virtual ~Drink() {}

private: 
   int price_;
   DrinkType type_;
};

class Honey : public Drink{
public:
   Honey(const Drink *coffee): coffee_(coffee) {}

   int getPrice() const override {
      return coffee_->getPrice() + honeyPrice_;
   };

   std::string getName() const override {
      return coffee_->getName() + " honey,";
   };

   ~Honey() override {
      delete coffee_;
   };

private:
   const int honeyPrice_ = 3;
   const Drink *coffee_;
};

class Cream : public Drink{
public:
   Cream(const Drink *coffee): coffee_(coffee) {}

   int getPrice() const override {
      return coffee_->getPrice() + creamPrice_;
   };

   std::string getName() const override {
      return coffee_->getName() + " cream,";
   };

   ~Cream() override {
      delete coffee_;
   };

private:
   const int creamPrice_ = 2;
   const Drink *coffee_;
};

class Sugar : public Drink{
public:
   Sugar(const Drink *coffee): coffee_(coffee) {}

   int getPrice() const override {
      return coffee_->getPrice() + sugarPrice_;
   };

   std::string getName() const  {
      return coffee_->getName() + " sugar,";
   };

   ~Sugar() override {
      delete coffee_;
   };

private:
   const int sugarPrice_ = 1;
   const Drink *coffee_;
};
