//
// An example of implementing map data structure.
// It's not complete, but it's a start showing how
// the basic abstractions work.
// 
// Prof. Joe Hummel
// Northwestern University
// CS 211
// 

#include <iostream>
#include <map>
#include <string>
#include <utility>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::pair;

//
// class map:
//
template<typename KeyT, typename ValueT>
class map {
private:
  //
  // we start by implementing a map as a linked-list of nodes:
  //
  struct NODE {
    pair<KeyT, ValueT> KeyValuePair;
    NODE* Next;

    NODE(KeyT key)
      : KeyValuePair(make_pair(key, ValueT() /*defalt value*/)), 
        Next(nullptr)
    { }
  };

  //
  // data members:
  //
  NODE* Root;  // pointer to first node in linked-list
  int   Size;  // size of the linked-list

public:
  // 
  // constructor:
  //
  map()
  {
    Root = nullptr;
    Size = 0;    
  }

  //
  // size:
  //
  int size() {
    return Size;
  }

  //
  // []:
  //
  ValueT& operator[](KeyT key)
  {
    //
    // first we search to see if the given key is
    // already in the list, and if so, we return
    // the VALUE as a reference (C++ handles the 
    // reference part, we just return the value):
    //

    NODE* cur = Root;

    while(cur != nullptr) {
      if (cur->KeyValuePair.first == key) {
        return cur->KeyValuePair.second;
      }
      cur = cur->Next;
    }

    // TODO: do this SECOND

    //
    // not found, we have to insert at the 
    // front of the list and return the VALUE
    // as a reference (C++ handles the reference
    // part, we just return the value):
    //
    NODE* newnode = new NODE(key);

    newnode->Next = Root;    
    Root = newnode;

    Size = Size + 1;

    // TODO: do this FIRST


    return newnode->KeyValuePair.second;
  }



  class iterator
  {
  private:
    NODE* Ptr;

  public:
    iterator(NODE* ptr) // constructor:
      : Ptr(ptr)
    { }

    bool operator==(iterator other) //for comparing to == end()
    {
      if (this->Ptr == other.Ptr)
        return true;
      else
        return false;
    }
    pair<KeyT, ValueT>* operator->()//for accessing the <key, value>
    {
      if (this->Ptr == nullptr)
        return nullptr;
      else
        return &(this->Ptr->KeyValuePair);
    }
  };

  //
  // end()
  //
  iterator end()
  {
    return iterator(nullptr);
  }

  //
  // find()
  //
  iterator find(KeyT key) 
  {
    //
    // Search for node that contains key:
    //
    NODE* cur = Root;

    while (cur != nullptr) {

      if (cur->KeyValuePair.first == key) {
        return iterator(cur);
      }

      cur = cur->Next;
    }

    // if get here, not found:
    return iterator(nullptr);
  }


};

//
// main:
//
int main() {
  map<string, int> animals;

  animals["elephant"] = 1;
  animals["cat"] = 3;
  animals["owl"] = 1;
  animals["dog"] = 2;
  animals["bear"] = 1;
  animals["moth"] = 9;
  animals["pig"] = 4;
  animals["ferret"] = 6;
  animals["zebra"] = 1;

  while (true) {

    string type;

    cout << "Enter a type of animal> ";
    cin >> type;

    if (type == "$") {
      break;
    }
    else if (type == "#") {
      cout << "# of animals: " << animals.size() << endl;
    }
    else {
      //cout << "I own " << animals[type] << " " << type << endl;

      auto iter = animals.find(type);

      if (iter == animals.end()) //not found
        cout << "I don't own any " << type << endl;
      else
        cout << "I own " << iter->second << " " << type << endl;
    }

  }//while

  return 0;
}
