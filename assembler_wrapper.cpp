#include <iostream>
//#include <algorithm>
//#include <iterator>
#include <fstream>
#include <string.h>
using namespace std;
#define Size 10

template<typename K, typename V> class HTWrapper;
template <typename K, typename V>
class node {   // To be inserted in hash table
public:
  K key; V value;
  node *next;
  node(K key, V value) {
    this->key = key;
    this->value = value;
    this->next = nullptr;
  }
  //friend class HTWrapper;
};

template<typename K, typename V>
class Hash {

public:
  node<K,V> **bucket_arr;

  Hash() {
    bucket_arr = new node<K,V>*[Size];
    for(int i=0;i<Size;i++) {
      bucket_arr[i] = NULL;
    }
  }

  int HashFunction(K key) {
    return int(key) % 10;
  }

  void insertHashValue(K key, V value) {       //INBUILT COLLISION HANDLING
    int index = HashFunction(key);
    node<K,V> *ptr1 = nullptr;

    // traversing through the array
    node<K,V> *ptr2= bucket_arr[index];
    while(ptr2 != nullptr) {
      ptr1 = ptr2;
      ptr2 = ptr2->next; // traversing in the chain
    }
    if(ptr2 == nullptr) {
      // store the node here .
      ptr2 = new node<K,V>(key, value);  // has a key value pair to be stored

      if(ptr1 == nullptr) {
        // i.e. no value initially in the chain
        bucket_arr[index] = ptr2;
      }else {
        // i.e. chain is initally filled with some elements
        // so ptr1 traverses
        ptr1 -> next = ptr2;
      }
    }
    else {
      ptr2->value = value;
    }
  }

  void deleteHashValue(K key) {
    int index = HashFunction(key);
    node<K,V> *ptr1 = bucket_arr[index];
    node<K,V> *ptr2 = nullptr;

    if(ptr1 == nullptr || ptr1 -> key != key) {
      cout<<"\nElement not found\n";
      return;
    }else {
      while(ptr1->next != nullptr) {
        ptr2 = ptr1;
        ptr1 = ptr1 -> next;
      } // checking for last element in the chain
      if(ptr2 != nullptr) {
        ptr2->next = ptr1->next;
      }delete ptr1;
      cout<<"Element Deleted !.\n";
    }
  }

    // DISPLAY FUNCTION
    void returnRecord(K key) {
      int flag = 0; // NOT Found
      int index = HashFunction(key);
      node<K,V> *ptr = bucket_arr[index];
      while(ptr != nullptr) {

        if(ptr -> key == key) {
          cout<<"Found! Value - "<<ptr->value<<"\n";
          flag = 1;
          //return 1;
        }
        ptr = ptr -> next;
      }
      if(flag == 0) { return;  } // NOT Found.
    }


    // bool hasKey(K key) {
    //   bool flag = false;
    //   int index = HashFunction(key);
    //   node<K,V> *ptr = bucket_arr[index];
    //   while(ptr != nullptr) {
    //     if(ptr->key == key) {
    //       cout<<"Key Found!\n";
    //       flag = true;
    //     }
    //     ptr = ptr -> next;
    //   }
    //   return flag;
    // }

    void replaceRecord(K key) {
      V replace; int flag = 0;
      int index = HashFunction(key);
      node<K,V> *ptr = bucket_arr[index];
      while(ptr != nullptr) {
        if(ptr -> key == key) {
          cout<<"Element found !!. enter the value by which it is to be replaced ! : ";
          cin>>replace;
          ptr -> value = replace;
          flag = 1;
        }
        ptr = ptr -> next;
      }
      if(flag == 0) {
        cout<<"Element not found , Try again.!\n";
      }
    }


    void printHashTable() {
      cout<<"index    -- >     ( key , Value )   \n";
      int i=0;
      node<K,V> *ptr;
      for(i=0;i<Size;i++) {
        cout<<i<<" - > ";
        ptr = bucket_arr[i];
        while(ptr != nullptr) {
          if(isalpha(ptr->key)) {
            cout<<"   [key : "<<char(ptr->key)<<" Value : "<<ptr->value<<"]\t -> ";
          }else {
            cout<<"   [key : "<<ptr->key<<" Value : "<<ptr->value<<"]\t -> ";
          }

          ptr = ptr -> next;
        }
        cout<<"\n";
      }
    }



    // node<* retPtr(int i) {
    //   return bucket_arr[i];
    // }

 friend class HTWrapper<K,V>;
};

template<typename K, typename V>
class HTWrapper {
  fstream file;
public:
  void storehash(Hash<K,V> H) {
      file.open("hashTableStore.txt");

      for(int i=0;i<Size;i++) {
        file<<i<<" : ";
        node<K,V> *ptr = H.bucket_arr[i];
        while(ptr != nullptr) {
            file<<" ["<<ptr->value<<"] -> ";
          ptr = ptr -> next;
        }
        file<<"\n";
      }
      file.close();
  }



  void checkFromFile(Hash<K,V> H) {
    cout<<"\nChecking From File ! : \n";
    file.open("hashTableStore.txt");
string line;
  cout<<"HASH TABLE : \n\n";
    while(file) {
      getline(file,line);
      cout<<line<<"\n";
    }
    file.close();
  }
};

int main() {
  Hash<int,int> H;
  H.insertHashValue(4,16);
  H.insertHashValue(5,25);
  H.insertHashValue(3,9);
  H.insertHashValue(2,4);
  H.insertHashValue(1,1);
  H.insertHashValue(25,242);
  H.insertHashValue(22,222);
  H.insertHashValue(24, 0);
  H.insertHashValue(27,10000);
  H.insertHashValue(227, 11111);
  // H.insertHashValue('a', 20);
  // H.insertHashValue('k', 255);
  H.printHashTable();
  //H.replaceRecord(4);
  //H.printHashTable();

  HTWrapper<int,int> htw;
  htw.storehash(H);
  htw.checkFromFile(H);

  return 0;
}
