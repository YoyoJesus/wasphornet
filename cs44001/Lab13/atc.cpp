// mediator-based air traffic control
// Mikhail Nesterenko
// 11/30/2022

#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <cstdio>
#include <ctime>
#include <algorithm>
#include <map>
#include <cctype>

// for timed sleep
#include <thread>
#include <chrono>


using std::cout; using std::cin; using std::endl;
using std::string;

enum class Airline {AIRFRANCE, KLM, AEROLOFT, LUFTHANSA, 
       DELTA, ALASKAN, SPIRIT};

// flyweight
class FlightLogo {
public:
   virtual string getLogo() = 0;
};

class AirFrance: public FlightLogo {
   virtual string getLogo() override {
      return std::to_string(static_cast<int>(Airline::AIRFRANCE));
   }
};

class KLM: public FlightLogo {
   virtual string getLogo() override {
      return std::to_string(static_cast<int>(Airline::KLM));
   }
};

class Aeroflot: public FlightLogo {
   virtual string getLogo() override {
      return std::to_string(static_cast<int>(Airline::AEROLOFT));
   }
};

class Lufthansa: public FlightLogo {
   virtual string getLogo() override {
      return std::to_string(static_cast<int>(Airline::LUFTHANSA));
   }
};

class Delta: public FlightLogo {
   virtual string getLogo() override {
      return std::to_string(static_cast<int>(Airline::DELTA));
   }
};

class Alaskan: public FlightLogo {
   virtual string getLogo() override {
      return std::to_string(static_cast<int>(Airline::ALASKAN));

   }
};

class Spirit: public FlightLogo {
   virtual string getLogo() override {
      return "SPRIT";
   }
};

// flyweight factory
class FlightLogoFactory {
public:
   FlightLogo* makeAirlineLogo(Airline airline) {
      if(logos_.find(airline) == logos_.end()){
         switch (airline) {
         case Airline::AIRFRANCE:
            logos_[airline] = new AirFrance();
            break;
         case Airline::KLM:
            logos_[airline] = new KLM();
            break;
         case Airline::AEROLOFT:
            logos_[airline] = new Aeroflot();
            break;
         case Airline::LUFTHANSA:
            logos_[airline] = new Lufthansa();
            break;
         case Airline::DELTA:
            logos_[airline] = new Delta();
            break;
         case Airline::ALASKAN:
            logos_[airline] = new Alaskan();
            break;
         case Airline::SPIRIT:
            logos_[airline] = new Spirit();
            break;
         default:
            cout << "Unknown airline" << endl;
            break;
         }
      }
      return logos_[airline];
   }
   
private:
   std::map<Airline, FlightLogo*> logos_;
};




// abstract mediator
class Controller{ 
public:
   virtual void join(class Flight*)=0;
   virtual void leave(class Flight*)=0;
   virtual void broadcast() = 0;
   virtual void observe() = 0;
};


// concrete mediator
// tower, runway clearance
class Tower: public Controller{
public:
   void join(class Flight*) override; 
   void leave(class Flight*) override;
   void broadcast() override;
   void observe() override;
private:
   std::set<class Flight*> waiting_;
};


// abstract colleague
class Flight {
public:
   Flight(Controller *controller):controller_(controller),
				  status_(Status::waiting){
      task_ = rand() % 2 ? Task::taxiing : Task::approaching;
      controller_->join(this);
   }
   void receive(const string &msg){
      if (msg.find(flightNo_) != string::npos || msg.find("all") != string::npos){
	 if(msg.find("clear") != string::npos){
	    cout << flightNo_ << " roger that, ";
	    cout << (task_ == Task::taxiing ? "taking off" : "landing") << endl;
	    status_ = Status::cleared;
	 } else if(msg.find("status") != string::npos) {
	    cout << flightNo_
		 << (status_ == Status::waiting ? " waiting to " : " cleared to ")   
	         << (task_ == Task::taxiing ? "take off" : "land") << endl;
	 } else
	    cout << "Tower, this is " << flightNo_ << " please repeat." << endl;
      }
   }
   bool isCleared() const {return status_ == Status::cleared;}
   void proceed(){
      std::this_thread::sleep_for(std::chrono::seconds(rand()%3+1)); // wait a while    
      // this is where the logo is used - we have to use flightNo_ to get the logo
      logo_ = logoFactory_.makeAirlineLogo(selectedAirline_);
      cout << "..." << toCaps(airlinename_) << number_
           << (task_ == Task::taxiing ? " takes off" : " lands") << "..." << endl;
      controller_->leave(this);
   };

   void setName() {
      string temp;
      switch(selectedAirline_) {
         case Airline::AIRFRANCE: temp = "AirFrance"; break;
         case Airline::KLM: temp = "KLM"; break;
         case Airline::AEROLOFT: temp = "Aeroloft"; break;
         case Airline::LUFTHANSA: temp = "LuftHansa"; break;
         case Airline::DELTA: temp = "Delta"; break;
         case Airline::ALASKAN: temp = "Alaskan"; break;
         case Airline::SPIRIT: temp = "Spirit"; break;
         default: temp = "UNKNOWN"; break;
      }
      airlinename_ = temp;
   };

   string toCaps (const string &str) {
      string result;
      for (char c : str) {
         result += std::toupper(c);
      }
      return result;
   }

protected:
   string flightNo_;
   Controller *controller_;
   enum class Task {taxiing, approaching};  Task task_;
   enum class Status {waiting, cleared};    Status status_;
   FlightLogo *logo_;
   FlightLogoFactory logoFactory_;

   Airline selectedAirline_;
   int number_;
   string airlinename_;
};

// concrete colleagues
class Airbus: public Flight{
public:
   Airbus(Tower *tower): Flight(tower){
      static const std::vector<Airline> companies = 
         {Airline::AIRFRANCE, Airline::KLM, Airline::AEROLOFT, Airline::LUFTHANSA};
         selectedAirline_ = companies[rand() % companies.size()];
         setName();
         
         number_ = rand() % 1000;

         flightNo_ = airlinename_ + std::to_string(number_);
         cout << flightNo_ << " requesting "
         << (task_ == Task::taxiing ? "takeoff" : "landing") << endl;
   }
};

class Boeing: public Flight{
public:
   Boeing(Tower *tower): Flight(tower){
      static const std::vector<Airline> companies = 
         {Airline::DELTA, Airline::ALASKAN, Airline::SPIRIT};
      selectedAirline_ = companies[rand() % companies.size()];
      setName();
      number_ = rand() % 1000;

      flightNo_ = airlinename_ + std::to_string(number_);
      cout << flightNo_ << " requesting "
	   << (task_ == Task::taxiing ? "takeoff" : "landing") << endl;
   }
};


// member functions for Tower
void Tower::broadcast() {
   cout << "Tower: ";
   string msg;
   getline(cin,msg);
   if(!msg.empty())
      for(auto f: waiting_) f->receive(msg);
}


void Tower::observe() {
   auto findCleared = [](Flight *f){return f->isCleared();};
   
   auto toProceed = std::find_if(waiting_.begin(), waiting_.end(), findCleared);
   
   while (toProceed != waiting_.end()){ // found a cleared flight
      (*toProceed) -> proceed();
      toProceed = std::find_if(waiting_.begin(), waiting_.end(), findCleared);
      if(toProceed != waiting_.end())
	 cout << "MAYDAY! MAYDAY! MAYDAY! " << endl; // more than a single flight cleared
   }
}


void Tower::join(Flight *f) {
   waiting_.insert(f);
}


void Tower::leave(Flight *f) {
   waiting_.erase(f);
   delete f;
}

int main(){
   srand(time(nullptr));
   Tower jfk;

   new Boeing(&jfk);
   new Airbus(&jfk);
   new Boeing(&jfk);
   new Airbus(&jfk);

   while(true){
      jfk.broadcast();
      jfk.observe();
      if(rand() % 2){
	 if (rand() % 2)
	    new Boeing(&jfk);
	 else
	    new Airbus(&jfk);
      }
   }
}
