// filled/hollow figures demonstrates Bridge Design Pattern,
// square is either hollow or square and is painted with a particular character,
// it is bridged over Figure --> Fill abstract body/handle
// Mikhail Nesterenko
// 2/12/2014

#include <iostream>
#include <cstdlib>

using std::cout; using std::endl; using std::cin;

// abstract body 
class Fill{
public:
   Fill(char fillChar, char borderChar): fillChar_(fillChar), 
                                    borderChar_(borderChar){}
   virtual char getBorder() { return borderChar_;};
   virtual char getInternal() { return fillChar_;};
   virtual ~Fill() {}
protected:
   char fillChar_;
   char borderChar_;
};

// concrete body
class Hollow: public Fill{
public:
   //basically forcing binding of fillChar_ to ' '
   // even though I am not using std::bind directly
   Hollow(char borderChar):Fill(' ', borderChar){}
   ~Hollow() override {}
};


// another concrete body
class Filled: public Fill {
public:
   // fillChar_ is the same as borderChar_
   Filled(char fillChar):Fill(fillChar, fillChar){}
   ~Filled() override {}
};

//concrete body that uses different fill & border
class FullyFilled: public Fill {
public:
   FullyFilled(char fillChar, char borderChar):Fill(fillChar, borderChar){}
   ~FullyFilled() override {}
};

//last concrete body - random fill & border
class RandomFilled: public Fill {
public:
   RandomFilled(char fillChar, char borderChar):Fill(fillChar, borderChar){}

   // returns either fillChar_ or borderChar_ randomly
   char getBorder() override {return rand() % 2 == 0 ? 
                                 borderChar_ : fillChar_;}
   char getInternal() override {return rand() % 2 == 0 ? 
                                 fillChar_ : borderChar_;}

   ~RandomFilled() override {}
};

// abstract handle
class Figure {
public:
   Figure(int size, Fill* fill): size_(size), fill_(fill){}
   virtual void draw() =0;
   virtual ~Figure(){}
protected:
   int size_;
   Fill *fill_;
};

// concrete handle
class Square: public Figure{
public:
   Square(int size, Fill* fill): Figure(size, fill){}
   void draw() override;

};

void Square::draw(){
   for(int i=0; i < size_; ++i){
      for(int j=0; j < size_; ++j)
	 if(i==0 || j==0 || i==size_-1 || j==size_-1 )
	    cout << fill_ -> getBorder();
	 else
	    cout << fill_ -> getInternal();
      cout << endl;
   }
}

int main(){
   srand(time(nullptr));
  
   Fill* hollowPaintJ = new Hollow('&');
   Fill* filledPaintStar = new Filled('@');

   //These are based on the above two - passing & and @ to the constructor
   Fill* fullyFilled = new FullyFilled(hollowPaintJ->getBorder(), 
                                       filledPaintStar->getBorder());
   Fill* randomPaint = new RandomFilled(hollowPaintJ->getBorder(), 
                                       filledPaintStar->getBorder());

   
   Figure *smallBox = new Square(6, hollowPaintJ);
   Figure *bigBox = new Square(15, filledPaintStar);
   Figure *filedBox = new Square(10, fullyFilled);
   Figure *randomBox = new Square(9, randomPaint);
   
   smallBox->draw();
   cout << endl;
   bigBox -> draw();
   cout << endl;
   filedBox -> draw();
   cout << endl;
   randomBox -> draw();
   
}
