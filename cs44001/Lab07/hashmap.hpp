// implementation basic hashmap (unordered container)
// Mikhail Nesterenko: adapted from Proc C++
// 4/15/2014

#include <cstddef>
#include <utility>
#include <functional>
#include <vector>
#include <list>

#include <iostream>

using std::vector;
using std::list;
using std::pair;
using std::make_pair;

using std::cout; using std::endl;

//////////////////////////////////////////
// hash function implemented as a class
//////////////////////////////////////////

// any Hash Class must provide 
// two methods: hash() and numBuckets().
template <typename T>
class DefaultHash {
public:
   DefaultHash(size_t numBuckets = defaultNumBuckets);
   size_t hash(const T& key) const;
   size_t numBuckets() const { return numBuckets_; }

private:
   // default number of buckets in the hash
   static const size_t defaultNumBuckets = 101; 
   size_t numBuckets_;
};

template <typename T>
DefaultHash<T>::DefaultHash(size_t numBuckets): numBuckets_(numBuckets) {}


// uses the division method for hashing.
// treats the key as a sequence of bytes, sums the ASCII
// values of the bytes, and mods the total by the number
// of buckets.
// note, this function does not work for C++ strings
template <typename T>
size_t DefaultHash<T>::hash(const T& key) const {
   size_t res = 0;
   for (size_t i = 0; i < sizeof(key); ++i) {
      const unsigned char b = 
      *(reinterpret_cast<const unsigned char *>(&key) + i);
      res += b;
   }
   return res % numBuckets_;
}


////////////////////////////////////////////////
// container class
////////////////////////////////////////////////

template <typename Key, typename Value, 
          typename Compare = std::equal_to<Key>,
          typename Hash = DefaultHash<Key>>
class hashmap{

public:
   typedef pair<const Key, Value> Element;

   // constructor
   // invokes constructors for comparison and hash objects
   hashmap(const Compare& comp = Compare(), 
	   const Hash& hash = Hash());

   Element* find(const Key& x);      // returns pointer to element with key x,
                                     // nullptr if not found 
   pair<const Element*, bool> insert(const Element& x); // inserts the key/value pair
   pair<const Element*, bool> erase(const Key& x); // erases element with key x, if exists
   Value& operator[] (const Key& x); // returns reference on value of
                                     // element with key, inserts if does not exist
   void rehash(size_t n); // rehashes the container to have n buckets

   size_t getSize() const { return size_; } // used for testing purposes
private:

   // helper function for various searches
   typename list<Element>::iterator findElement(const Key& x, const size_t bucket);

   size_t size_;   // number of elements in the container
   Compare comp_;  // comparison functor, equal_to by default
   Hash hash_;     // hash functor 

   // hash contents: vector of buckets
   // each bucket is a list containing key->value pairs
   vector<list<Element>> elems_;
};


////////////////////////////////////////////////
// container member functions
////////////////////////////////////////////////

// Construct elems_ with the number of buckets.
template <typename Key, typename Value, typename Compare, typename Hash>
   hashmap<Key, Value, Compare, Hash>::hashmap(
   const Compare& comp, const Hash& hash):
   size_(0), comp_(comp), hash_(hash) {
      elems_ = vector<list<Element>>(hash_.numBuckets());
}


// helper function
template <typename Key, typename Value, 
          typename Compare, typename Hash>
   typename list<pair<const Key, Value>>::iterator // return type
   hashmap<Key, Value, Compare, Hash>::findElement(const Key& x, size_t bucket){

   // look for the key in the bucket
   for (auto it =  elems_[bucket].begin(); it != elems_[bucket].end(); ++it)
      if (comp_(it->first, x))
	 return it;

   return elems_[bucket].end(); // element not found
}


// returns a pointer to the element with key x
// returns nullptr if no element with this key
template <typename Key, typename Value, typename Compare, typename Hash>
   typename hashmap<Key, Value, Compare, Hash>::Element* // return value type
   hashmap<Key, Value, Compare, Hash>::find(const Key& x) {

   size_t bucket = hash_.hash(x);
   auto it=findElement(x, bucket);    // use the findElement() helper   

   if (it != elems_[bucket].end())
      // found the element. Return a pointer to it.
      return &(*it); // dereference the iterator to list 
                     // then take the address of list element
   
   else // didn't find the element -- return nullptr
      return nullptr;
}


// finds the element with key x, inserts an
// element with that key if none exists yet. Returns a reference to
// the value corresponding to that key.
// this looks really ugly with the typename stuff - I hate it
template <typename Key, typename Value, typename Compare, typename Hash>
   pair<const typename hashmap<Key, Value, Compare, Hash>::Element*, bool> 
   hashmap<Key, Value, Compare, Hash>::insert(const Element& x) {

   size_t bucket = hash_.hash(x.first);   
   auto it = findElement(x.first, bucket);    // try to find the element

   // if not found, insert a new one.
   if (it == elems_[bucket].end()) {
      ++size_;
      elems_[bucket].push_back(x);
      return make_pair(&elems_[bucket].back(), true); // return the pointer to the new element & true

   } else {
      // if found, return a pointer to the existing element & false
      return make_pair(&(*it), false);
   }
}


// removes the Element with key x, if it exists
// return a pair with a pointer to the element and a bool
// indicating if the element was removed
template <typename Key, typename Value, typename Compare, typename Hash>
   pair<const typename hashmap<Key, Value, Compare, Hash>::Element*, bool> 
   hashmap<Key, Value, Compare, Hash>::erase(const Key& x) {
      // find the element
      size_t bucket = hash_.hash(x);
      auto it = findElement(x, bucket);
   
      // if found, erase it
      if (it != elems_[bucket].end()) {
         
         // check if the element is the last in the bucket
         if (std::next(it) == elems_[bucket].end()) {
            ++bucket; // if last element, move to the next bucket
         }

         // erase the element
         elems_[bucket].erase(it);
         --size_;

         // check if there are any elements left in the bucket
         for (auto i = bucket; i < elems_.size(); ++i) {
            // if there are elements left in the bucket - return the first one
            if (!elems_[i].empty()) {
               return make_pair(&elems_[i].front(), true);
            }
         }

         // if no elements left in the bucket
         return make_pair(nullptr, true);
      }

      return make_pair(nullptr, false);  // ensure nullptr is returned if not found
}


// returns reference to value of element with key x,
// inserts if does not exist
template <typename Key, typename Value, typename Compare, typename Hash>
Value& hashmap<Key, Value, Compare, Hash>::operator[](const Key& x) {
   Element* found = find(x);

   // If key not found, insert a new element
   if (found == nullptr) {
      insert(std::make_pair(x, Value())); // insert a new element with default value
      found = find(x);  // get pointer to the new element
   }

   return found->second;
}

// rehashes the container to have n buckets
template <typename Key, typename Value, typename Compare, typename Hash>
void hashmap<Key, Value, Compare, Hash>::rehash(size_t n) {
   // If the number of buckets is greater than or equal to n, return
   if (n <= hash_.numBuckets()) { 
      cout << hash_.numBuckets() << " is less than or equal to " << n << endl;
      return; 
   } 

   // If the number of buckets is less than n, rehash the container
   // if statement for confirmation purposes mostly
   if (n > hash_.numBuckets()) {
      cout << hash_.numBuckets() << " is less than " << n <<
      " - rehashing the container" << endl;
   }

   // Create a new hash object with the specified number of buckets
   hash_ = DefaultHash<Key>(n);
   std::vector<Element> tmp;

   // Copy all elements into a temporary vector
   for (auto& elms : elems_) {
      for (auto& buckets : elms) {
         tmp.push_back(buckets);
      }
   }

   // Clear the old vector and resize it to the new size
   elems_.clear();
   elems_.resize(n);

   // Rehash all elements into the new vector
   // find index of the old bucket - then push the element into the new bucket
   for (auto& it : tmp) {
      size_t b = hash_.hash(it.first); 
      //std::cout << b << std::endl; // Testing line
      elems_[b].push_back(it);
   }
}