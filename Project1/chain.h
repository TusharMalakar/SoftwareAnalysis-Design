//Tushar Malakar
// Create a Chain class from scratch without using the STL
//Pay special attention to Weiss's "big five", the destructor, 
//copy constructor, copy assignment operator, move constructor and 
//move assignment operator.

#ifndef CSCI335_HOMEWORK1_CHAIN_
#define CSCI335_HOMEWORK1_CHAIN_

#include <iostream>
#include <cstddef>
#include <sstream>
#include <fstream>

namespace teaching_project {
template<typename Object>
class Chain {
 public:

  // Zero-parameter constructor.
  // Initialize the size to 0 and array to null
  Chain(): size_(0){ array_ = nullptr;}

  // Copy-constructor.
  Chain(const Chain &rhs){
      size_ = rhs.size_;
      array_ = new Object[size_];
      for (int i = 0; i < rhs.size_; i++){
          array_[i] = rhs.array_[i];
      }
  }

  // Copy-assignment.
  Chain& operator=(const Chain &rhs){
      Chain lChain = rhs;
      std::swap(*this, lChain);
      return *this;
  }

  // Move-constructor.
  Chain(Chain &&rhs) : size_{rhs.size_}, array_{rhs.array_}{
      rhs.size_ = 0;
      rhs.array_ = nullptr;
  }

  // Move-assignment.
  Chain& operator=(Chain &&rhs){
      if (this == &rhs){
          return *this;
      }
      std::swap(size_, rhs.size_);
      std::swap(array_, rhs.array_);
      return *this;
  }

  ~Chain() {
      delete[] array_;
      size_ = 0;
  }

  // End of big-five.

  // One parameter constructor.
  Chain(const Object& item){
      size_ = 1;
      array_ = new Object[size_];
      array_[0] = item;
  }

  // Read a chain from standard input.
  void ReadChain(){
    std::string line;
    getline(std::cin, line);
    size_ = line[1] - '0';
    std::stringstream get(line.substr(4, line.size() - 5));
    delete [] array_;
    array_ = new Object[size_];
    for (int i = 0; i < size_; i++){
    get >> array_[i];
    }	
  }
void writeFile();

//returns the size of the chain
  size_t size() const {
      return size_;
  }

  // @location: an index to a location in the chain.
  // @returns the Object at @location.
  // const version.
  // abort() if out-of-range.
  const Object& operator[](size_t location) const {
    if (location >= size_){
        abort();
    }
      return array_[location];
  }

 // @location: an index to a location in the range.
 // @returns the Object at @location.
 // non-const version.
 // abort() if out-of-range.
 Object& operator[](size_t location){
     if (location >= size_){
         abort();
     }
     return array_[location];
 }

 //  @c1: A chain.
 //  @c2: A second chain.
 //  @return the concatenation of the two chains.
 friend Chain operator+(const Chain &c1, const Chain &c2){
     Chain chain;
     //allocating size and space for concat string
     chain.size_ = c1.size_ + c2.size_;
     chain.array_ = new Object[chain.size_];

     // first chain
     for (int i = 0; i< c1.size_; i++){
         chain.array_[i] = c1.array_[i];
     }
     // second chain
     for (int i = 0; i < c2.size_; i++){
         chain.array_[i + c1.size_] = c2.array_[i];
     }
     return chain;

 }

 // @c1: A chain
 // @append: an object that is being appended to the chain
 // This function was made to accommodate for the cout << d + "hi_there";
 // test in testPart2() since the given + overload operator function
 // only concatenated two chains and not objects
 friend Chain operator+(const Chain &c1, const Object &c2){
    Chain chain;
    chain.size_ = c1.size_+1;
    chain.array_ = new Object[chain.size_];

     for (int i = 0; i < c1.size_; i++){
         chain.array_[i] = c1.array_[i];
     }
     //appending the object to end of the chain
     chain.array_[c1.size_] = c2;

    return chain;
 }

 // Overloading the << operator.
 friend std::ostream &operator<<(std::ostream &out, const Chain &a_chain){
   // Print the chain.
   out << "[";
   if (a_chain.size_ == 0){
       out << "]" << std::endl;
       return out;
   }
   if (a_chain.size_ == 1){
       out << a_chain.array_[a_chain.size_-1] << "]" << std::endl;
       return out;
   }
   else{
   for (int i = 0; i < a_chain.size_-1; i++){
       out << a_chain.array_[i] << " ";
   }
   out << a_chain.array_[a_chain.size_-1] << "]" << std::endl;

   return out;
   }
 }

 private:
  size_t size_;
  Object *array_;
};
}  // namespace teaching_project
#endif // CSCI_335_HOMEWORK1_CHAIN_
