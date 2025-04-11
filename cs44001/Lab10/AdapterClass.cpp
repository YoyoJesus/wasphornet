// figures: class adapter pattern
// Mikhail Nesterenko
// 11/7/2022

#include <iostream>

using std::cout; using std::endl; using std::cin;

// adaptee/implementer
class LegacyRectangle{
public:
   LegacyRectangle(int topLeftX, 
		   int topLeftY, 
		   int bottomRightX, 
		   int bottomRightY): 
      topLeftX_(topLeftX), 
      topLeftY_(topLeftY), 
      bottomRightX_(bottomRightX), 
      bottomRightY_(bottomRightY){}

   void move(int topLeftX, 
         int topLeftY, 
         int bottomRightX, 
         int bottomRightY) {
            topLeftX_ = topLeftX;
            topLeftY_ = topLeftY;
            bottomRightX_ = bottomRightX;
            bottomRightY_ = bottomRightY;
         }

   int getTopLeftX() const { return topLeftX_; }
   int getTopLeftY() const { return topLeftY_; }
   int getBottomRightX() const { return bottomRightX_; }
   int getBottomRightY() const { return bottomRightY_; }

   void oldDraw() const {
      for(int i=0; i < bottomRightY_; ++i){
	 for(int j=0; j < bottomRightX_; ++j)
	    if(i >= topLeftY_  && j >= topLeftX_ )
	       cout << '*';
	    else
	       cout << ' ';
	 cout << endl;
      }
   }
// defining top/left and bottom/right coordinates 
private: 
   int topLeftX_;
   int topLeftY_;
   int bottomRightX_;
   int bottomRightY_;
};

// target interface
class Square {
public:
   virtual void draw() const =0;
   virtual int size() const =0; // needed for returning size
   virtual ~Square(){}
};


// adapter uses multiple inheritance to inherit
// interface and implementation
class SquareAdapter: public Square, 
		     private LegacyRectangle {
public:
   SquareAdapter(int size): LegacyRectangle(0,0,size,size){};
   void draw() const override {
      oldDraw();
   }
   int size() const override { // Override size() from the interface
      return getBottomRightX()-getTopLeftX();
   }

   void resize(int newSize) {
      // resize the square
      // by moving the bottom right corner
      // 'resizing' the square to the new size
      move(getTopLeftX(), getTopLeftY(), newSize, newSize);
   }
};


int main(){
   int sizeInput;
   cout << "Enter the size of the square: ";
   cin >> sizeInput;

   // create a square using the adapter
   Square* square;
   square = new SquareAdapter(sizeInput);
   cout << "Creating a square of size " << square->size() << endl;
   square->draw();


   cout << "Enter the new size of the square: ";
   cin >> sizeInput;
   // resize the square using the adapter
   static_cast<SquareAdapter*>(square)->resize(sizeInput);
   cout << "Resizing the square to size " << square->size() << endl;
   square->draw();
}
