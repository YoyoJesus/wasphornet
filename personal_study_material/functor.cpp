#include <iostream>
#include <functional>
#include <string>
#include <vector>
#include <algorithm>

using std::cout; using std::endl;
using std::string; using std::vector;

class MyFunctor{
    public:
       MyFunctor(int x = 0, string name = " ") : x_(x), name(name) {}
       // overloading function operator
         int operator()(int y) {
              return x_ + y;
         }
         string operator()(string s) {
              return name + s;
         }
      MyFunctor operator()(int i, string s) {
            return MyFunctor(x_ + i, name + s);
      }

      void print() const {
           cout << x_ << " " << name << endl;
      }
    private:
       int x_;
       string name;
    };
     
    int main(){
       
       MyFunctor addThem(4, ""); // creating a functor object
       cout << addThem(5) << endl; // calling the functor object

       int num = 10;
       cout << addThem(num) << endl; // calling the functor object
       cout << "\n";

       MyFunctor stringConcat(0, "Hello"); // creating a functor object
       cout << stringConcat(" World") << endl; // calling the functor object

       string str = " Dr. Nesterenko";
       cout << stringConcat(str) << endl; // calling the functor object
       cout << "\n";
       
       // THIS VEXES ME
       MyFunctor strNumCon(0, "Hello");
       cout << strNumCon(5, " World")("!!!") << endl;
       cout << strNumCon(5, " World")(" No") << endl;
       cout << strNumCon(20, " World")(1) << endl;

       // this is the way to get the number and string to print
       strNumCon(100, " Dr. Nesterenko").print();

      //populating a vector with MyFunctor objects - THIS VEXES ME
      vector<MyFunctor> v;
      generate_n(std::back_inserter(v), 10, [n = 1, &strNumCon]() mutable {
          return strNumCon(n++, " World!");
      });
      for (auto& element : v) {
          element.print();
      }
    }