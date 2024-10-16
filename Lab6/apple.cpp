// sorting apples
// non STL-algorithm code to be replaced by algorthms
// Anna Waltz
// 9/23/24


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>
#include <numeric>

using std::cin; using std::cout; using std::endl;
using std::string;
using std::vector; using std::deque;

struct Apples{
   double weight; // oz
   string color;  // red or green
   void print() const { cout << color << ", " <<  weight << endl; }
};



int main(){
   srand(time(nullptr));
   const double minWeight = 3.;
   const double maxWeight = 8.;

   cout << "Input crate size: ";
   int size;
   cin >> size;

   vector <Apples> crate(size);

   //generate() DONE
   std::generate(crate.begin(), crate.end(), 
   [&] {Apples temp; 
   temp.weight= minWeight + static_cast<double>(rand())/RAND_MAX*(maxWeight - minWeight);
   temp.color = rand() % 2 == 1 ? "green" : "red"; return temp;});

    // for_each() DONE
   cout << "all apples"<< endl;
   for_each(crate.begin(), crate.end(),
   [] (Apples apple) {apple.print(); });


   
   cout << "Enter weight to find: ";
   double toFind;
   cin >> toFind;


   // count_if() DONE
   auto cnt = count_if(crate.cbegin(), crate.cend(), [=](Apples apple){return apple.weight > toFind;});

   cout << "There are " << cnt << " apples heavier than " 
	<< toFind << " oz" <<  endl;

   // find_if() DONE
   cout << "at positions ";
   const auto findPos = [=] (Apples apple) {return apple.weight > toFind;};
   auto it= find_if(crate.cbegin(), crate.cend(), findPos);
   while(it != crate.cend()){
      cout << it - crate.begin() << " ";
	   it=find_if(++it, crate.cend(), findPos);
   }
   cout << endl;


   // max_element() DONE
   auto heaviest = max_element(crate.cbegin(), crate.cend(), 
   [] (const Apples &apple1, const Apples &apple2) { return apple1.weight < apple2.weight;});
   cout << "Heaviest apple weighs: " << heaviest->weight << " oz" << endl;


   // accumulate() DONE
   double sum=0;
   auto total = accumulate(crate.begin(), crate.end(), 0.0, 
   [](double sum, const Apples& apple) {return sum + apple.weight;});
   cout << "Total apple weight is: " << total << " oz" << endl;


   // transform() DONE
   cout << "How much should they grow: ";
   double toGrow;
   cin >> toGrow;
   transform(crate.begin(), crate.end(), crate.begin(), 
   [toGrow] (Apples apple){apple.weight+=toGrow; return apple;});


   // remove_if() DONE
   cout << "Input minimum acceptable weight: ";
   double minAccept;
   cin >> minAccept;

   crate.erase(remove_if(crate.begin(), crate.end(), 
   [&] (Apples apple) {return apple.weight <= minAccept;}), 
   crate.end());

   cout << "removed " << size - crate.size() << " elements" << endl;

   // bubble sort, replace with sort()
   sort( crate.begin(), crate.end(), 
   [] (Apples one, Apples two) {return one.weight < two.weight;});

   // for_each() possibly  DONE
   cout << "sorted remaining apples"<< endl;;
   for_each(crate.begin(), crate.end(),
   [] (Apples apple) {apple.print(); });

}
