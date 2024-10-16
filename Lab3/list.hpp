// node class tempate used to contruct lists

//Anna Waltz Collection class template
//9/9/24

#ifndef LIST_HPP_
#define LIST_HPP_

#include <iostream>
using std::cout; 
using std ::endl;
using std:: string;


// the pointer part of every list is the same
// lists differ by data part
template <typename T>
class node{
  public:

  node(): next_(nullptr) {}

  // functions can be inlined
  T getData() const {return data_;}
  void setData(const T& data){data_=data;}

  // or can be defined outside
  node<T>* getNext() const;
  void setNext(node<T> *const);

  private:
  T data_;
  node<T> *next_;
};

//
// member functions for node
//
template <typename T>
node<T>* node<T>::getNext() const {
  return next_;
}

template<typename T>
void node<T>::setNext(node<T> *const next){
   next_=next;
}

// i.e, the list contains a pointer to the first element.
//You are not allowed to use double-linked list. 
//Anna Waltz 
//Lab3 collection class
//9/4/24


// forward class declaration
template<typename T>
class Collection;
// forward function declaration
template<typename T>
bool equal(const Collection<T>&, const Collection<T>&);


template <typename T>
class Collection{

  public:
  Collection(): tos(nullptr) {};
  bool isEmpty() const {
    return tos==nullptr;
  };
  bool isFull()const ;
  void add( const T& item); //adds to beginning of end of list
  void remove( const T& item); // removes ALL occurrences of item, deallocate items
  T last(); //returns last element
  void print(); //pring all items
  friend bool equal<T>(const Collection<T>&, const Collection<T>&);

  private:
  node <T> *tos; //top of collection/stack

};
//
// member functions for collection
//

template <typename T>
bool Collection<T>:: isFull()const{
    node<T>* temp = new(std:: nothrow) node<T>(); //tries to define temp
    if(temp==0) //no memory remaining
        return true;
    delete temp;
    return false;
}

template <typename T>
void Collection<T>::add( const T& item){ //adds new item
  if(!isFull()){
    node<T> *temp= new node<T>();
    temp->setData(item); 
    temp->setNext(tos); 
    tos=temp;//puts temp at beginning
  }
  else
    cout << "cannot add no room, is full" << endl;

}

template <typename T>
void  Collection<T>::remove( const T& item){ // removes ALL occurrences of item, deallocate items
  if(isEmpty())
    return;
  
  node<T> *temp ;
  while(tos->getData() ==item){ //checks first item
    temp=tos;
    tos=tos->getNext();
    delete temp;
    if(isEmpty())
    return;
  }
  
  
  temp= tos->getNext(); //current
  node<T> *prev= tos; //previous

  while(temp!=nullptr){ //checks all but first
    if(temp->getData()== item){
      prev->setNext(temp->getNext()); //change prev next
      delete temp;
      temp = prev->getNext();
    }
    else{
      temp = temp->getNext();
      prev= prev->getNext();
    }
  }

}

template <typename T>
T  Collection<T>::last(){ //returns last added element
  return tos->getData();
}

template <typename T>
void Collection<T>:: print(){ //pring all items
if(isEmpty())
  return;
  node<T> *temp = tos;
  while(temp->getNext()!=nullptr){ //prints all but last
    cout << temp->getData() << " " ;
    temp=temp->getNext();
  }
  if(!isEmpty()) //prints last
    cout << temp->getData();
    cout << endl;
}
template <typename T>
bool equal(const Collection<T>& list1, const Collection<T>&list2){
  if(list1.isEmpty() && list2.isEmpty()) //both empty
    return true;
  if(list1.isEmpty() || list2.isEmpty()) //one empty
    return false;
  node<T> *temp1 = list1.tos;
  node<T> *temp2 = list2.tos;
  do{ 
    if(temp1->getData() != temp2->getData())
      return false;
    temp1 = temp1->getNext();
    temp2 = temp2->getNext();
  }while(temp1->getNext()!=nullptr && temp1->getNext()!=nullptr);//will check all 
  return true;
}

#endif // LIST_HPP_