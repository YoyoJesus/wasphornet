/**
   * Austin  Sternberg
   * bigint
   * cs23001
   */

//This file contains all of the code needed to make bigint work correctly

#include "bigint.hpp"


//defualt constructor - sets bigint to zero overall
bigint::bigint() {
   for (int i = 0; i < CAPACITY; ++i){
      barray[i] = 0;
   }
}

//singe int constructor - cycles through int given and assigns each digit to bigint array
bigint::bigint(int num){
   for (int i = 0; i < CAPACITY; ++i){
      barray[i] = num % 10;
      num = num / 10;
   }
}

//Constant Character constructor - sets bigint to the conversion of a character as an array of integers
bigint::bigint(const char my_char[]) : bigint(){
   int array_length = 0;

   //loops through to the end of the const char to determien how many values to map
   while (my_char[array_length] != '\0'){
      ++array_length;
   }

   //maps each digit of the const char to bigint - interating from back to front
   int k = 0; //this is only used as an indexing variable
   for (int j = array_length - 1; j >= 0; j--, k++){
      barray[k] = int(my_char[j]) - int('0');
   }
}

//Printing debug function - prints each value of bigint array seperated by |
void bigint::debugPrint(std::ostream& out) const{
   for(int i = CAPACITY - 1 ; i >= 0; --i){
      out << "|" << barray[i] << "|";
   }

   out << std::endl;
}
 
//stream overload operator - prints condensed bigint when needed
std::ostream& operator<<(std::ostream& out, bigint rhs){
   int loopv = CAPACITY - 1;
   bool all_zero = true;

   //checks if bigint is zero
   for (int i = 0; i < CAPACITY; ++i){
      if (rhs.barray[i] != 0)
         all_zero = false;
   }

   //if bigint is zero, print a 0
   if (all_zero) 
      out << "0" << std::endl;
   
   //if bigint does not equal zero, interate through to get actual number
   else {
      
      //droop all leading zeros from bigint number
      while(loopv >= 0 && rhs.barray[loopv] == 0){
         --loopv;
      }

      //print the signifant digits of bigint
      while(loopv >= 0){
         //if we reach the max of 80 digits, start a new line
         if (loopv % 80 == 0)
            out << rhs.barray[loopv] << std::endl;
         else
            out << rhs.barray[loopv];

         --loopv;
      }
   }
   //drop final result onto the out stream
   return out;
}

//equal overload operator
bool bigint::operator==(bigint rhs){
   bool equal = true;

   //check if bigint lhs = bigint rhs
   for (int i = 0; i < CAPACITY; ++i){
      if (barray[i] == rhs.barray[i])
         equal = true;
      else
         return false;
   }

   //return result either way
   return equal;
}

//Input overload operator - allows us to take input and assign them to bigint arrays
std::istream& operator>>(std::istream& in, bigint& rhs) {
   char ch;
   char char_array[CAPACITY];

   //ensure the newly created array is set to zero for all values
   for (int i = 0; i < CAPACITY; ++i) {
      char_array[i] = 0;
   }

   in >> ch;
   //map the digits of what is inputed from the file to the new array, skipping any line breaks or ";"
   for (int i = 0; i < CAPACITY && ch != ';'; ++i) {
      char_array[i] = ch;
      in >> ch;
   }

   //set the object array to the new bigint value
   rhs = char_array;
   return in;
}

//addition operator - allows us to add two bigint numbers toghether
bigint bigint::operator+(bigint rhs) const {
   int num = 0;
   int temp = 0;

   //iterate through each digit of both bigints, adding their sums toghether
   for (int i = 0; i < CAPACITY; ++i) {
      num = barray[i] + rhs.barray[i] + num;
      temp = num % 10;
      num = num / 10;
      rhs.barray[i] = temp;
   }

   return rhs;
}

//subscript operator - allows us to return each individual digit of bigint as needed
int bigint::operator[](int i) const {
   return barray[i];
}

//timesDigit method - allows for a single digit integer from 0-9 to be multiplied by a stored bigint value
bigint bigint::timesDigit(int x) const {
   bigint int_product = *this; //set our temporary bigint to the current value of what this method is invoked on

   if (x == 0) // if x is zero, then our bigint value becomes zero
      return (int_product = 0);
   
   if (x == 1) // if x is one, then our bigint value stays the same
      return int_product;
  
   if( x <= 9) { //if x is anything 2-9, then the value of bigint is multiplied by that
      int remainder = 0;
      int result;
      
      //iterate through each digit of bigint
      for (int i = 0; i < CAPACITY; ++i) {
         remainder = barray[i] * x + remainder; //multiply current digit by x adding any remaining leftovers
         result = remainder % 10; //establish what the single digit answer is for current bigint index
         remainder = remainder / 10; //grab the remaining amount left over
         int_product.barray[i] = result; //set current index to resulting digit
      }
   }

   return int_product;
}

//times10 method - allows for a bigint to multiplied by a power of 10
bigint bigint::times10(int x) const {
   bigint temp;

   //if x is zero, bigint is multiplied by one, so simply return current bigint
   if (x == 0) 
      return *this;

   //if x is anything from 1 or greater, iterate through array to multiply by base10 value
   if (x > 0) {
      for (int i = CAPACITY - x - 1; i >= 0; --i)
         temp.barray[i + x] = barray[i]; //shift old array by current base10 value
   }

   return temp;
}

//multiplication operator - allows for two bigint values to be multiplied toghether
bigint bigint::operator*(bigint rhs) {
   bigint mult_product;
   bigint temp;

   //iterate through bigint
   for (int i = 0; i < CAPACITY; ++i) {
      temp = timesDigit(rhs.barray[i]); //sets temp to the current digit of rhs multiplies by lhs
      mult_product = mult_product +  temp.times10(i); //set resulting bigint to value of both lhs and rhs (raised to a power of ten) multiplied toghether
   }

   return mult_product;
}

//factorial method - allows us to use bigint to calculate the factorial of a number
bigint bigint::nfact(int num) {
   bigint result = 1;
   
   //iterate through every possible number between 1 and num, multiplying by so each time
   for (int i = 2; i <= num; ++i) {
      result = result * i;
   }
   
   return result;
}

//trailing zeros method - calculated how many trailing zeros any number may have and returns that value
int bigint::trailingZeros() const {
    int count = 0;

    // Iterate from the most significant digit to the least significant digit
    for (int i = 0; i < CAPACITY; ++i) {
        if (barray[i] != 0) 
            break; // Stop counting when a non-zero digit is encountered

        count++; // Increment count if digit is zero
    }

    return count;
}

/*
Answers to questions asked in challenge:

1. How many trailing zero's are there in 100! - 24 trailing zeros

2. Give a short write up about how one can mathematicy figure out how many trailing zeros are on a given number:

   To find the number of trailing zeros in any number the first step in figure out how many digits are in that integer.
   To do so we can take the log base 10 of the number and add one. From here we can take that number and subtract in from
   the maximun number of digits that is possible for the type of number we using, i.e. 32 or 64 bit integers. This would
   result in the number of leading zeros the number has.

   In the event that a number is a power of ten, the math becomes much easier. Such numbers will have trailing
   zero equal to the power it is raised to. For example 100 is 10^2, so it should have 2 leading zeros, and does.
*/
