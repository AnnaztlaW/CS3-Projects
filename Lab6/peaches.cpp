// jamming peaches
// non STL-algorithm code to be replaced by algorthms
// Anna Waltz
// 9/30/2021


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>
#include <numeric>
#include <functional>

using std::cin; using std::cout; using std::endl;
using std::string;
using std::vector; using std::deque;
using namespace std::placeholders;

struct Peaches{
   double weight; // oz
   bool ripe;  // ripe or not
   void print() const { cout << (ripe?"ripe":"green") << ", " <<  weight << endl; }
};

double jamFunctor( double& sum, Peaches& peach, double weightToJam){
   return peach.weight < weightToJam ? sum+=peach.weight : sum ;
};


int main(){
   srand(time(nullptr));
   const double minWeight = 3.;
   const double maxWeight = 8.;

   cout << "Input basket size: ";
   int size;
   cin >> size;

   vector <Peaches> basket(size);

   // replace with generate() DONE
   generate(basket.begin(), basket.end(), [&] {Peaches peach;
      peach.weight = minWeight + static_cast<double>(rand())/RAND_MAX*(maxWeight - minWeight);
      peach.ripe = rand() % 2;
      return peach;
   });

   // for_each() DONE
   cout << "all peaches"<< endl;
   for_each(basket.begin(), basket.end(),
   [] (Peaches peach) {peach.print(); });

   // remove_copy_if() DONE
   deque<Peaches> peck;
   // make peck and copy ripe
   peck.erase( remove_copy_if(basket.begin(), basket.end(), peck.begin(),
   [](Peaches peach) {return peach.ripe==false;}),
   peck.end());
   //remove ripe from basket
   basket.erase(remove_if(basket.begin(), basket.end(), 
   [] (Peaches peach) {return peach.ripe ==true;}), 
   basket.end());


   // for_each() DONE
   cout << "\npeaches remaining in the basket"<< endl;
   for_each(basket.begin(), basket.end(),
   [] (Peaches peach) {peach.print(); });

   cout << endl;

   // for_each() DONE
   cout << "peaches moved to the peck"<< endl;
   for_each(peck.begin(), peck.end(),
   [] (Peaches peach) {peach.print(); });


   // prints every "space" peach in the peck
   const int space=3; 
   cout << "\nevery " << space << "\'d peach in the peck"<< endl;
   // replace with advance()/next()/distance(), DONE
   auto it=peck.cbegin() -1;    
   while (it + space < peck.cend()) {
      advance(it, space);
      it->print();
    }


   // putting all small ripe peaches in a jam
   // use a binder to create a functor with configurable max weight
   // accumulate() or count_if() then remove_if() DONE

   const double weightToJam = 10.0; //max weight for a peach to be turned into jam
   double jamWeight = accumulate(peck.begin(), peck.end(), 0.0, bind(jamFunctor, _1, _2, 10.0)); 
   
   cout << "Weight of jam is: " << jamWeight << endl;

}
