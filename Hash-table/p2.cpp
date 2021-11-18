#include "hashtable.hpp"
#include <iostream>
using namespace std;

int main()
{
    HashTable<int, int, hash<int>, equal_to<>> ht;
     ht.insert(850, 694);
     ht[727] = 549;
     ht[175] = 636;
     ht[175] = 553;
     ht.insert(174,57);
     ht.insert(173,57);
     ht.insert(172,57);
     ht.insert(171,57);
     ht.insert(170,57);
     ht[746] = 847;
     ht[438] = 489;
    HashTable<int, int, std::hash<int>, std::equal_to<>> ht2(ht);
     ht.insert(175,56);
     HashTable<int, int, std::hash<int>, std::equal_to<>> ht3(ht);
     ht = ht;
     ht.insert(175,55);
     cout << ht.contains(175) << endl;
     ht.erase(175);
     cout << ht.contains(175) << endl;
     ht.printTable();
     cout << "\n";
     ht2.printTable();
     cout << "\n";
     ht3.printTable();
     return 0;
}

//// TO-DO: add this to the end of "hashtable.hpp"
//  void printTable(){
//   for (auto& bucketIt : buckets){
//   for (auto& [key, value] : bucketIt){
//   std::cout << key << ": " << value << "\n";
//   }
//   }
//  }

// TO-DO: add #include <iostream>
