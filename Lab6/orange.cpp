// selecting oranges
// converting vectors to multimaps
// Anna Waltz
// 9/26/2022


//use a multimap instead of vector to store fruit 
//as well as upper_bound(), lower_bound() functions and emplace() to populate the multimap.


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <string>
#include <map>

using std::cin; using std::cout; using std::endl;
using std::string;
using std::vector;

enum class Variety {orange, pear, apple};
vector<string> colors = {"red", "green", "yellow"};


const int maxTreeSize = 100;
int main(){
   srand(time(nullptr));
   int treeSize = rand()%maxTreeSize+1;

   std::multimap<Variety, string> tree; //make map
   for(int i= 0; i < treeSize; i++){ //populate map
      Variety v = static_cast<Variety>(rand() % 3);//create random fruit 
      string color = colors[rand()%3]; //identify random color
      tree.emplace(v, color);
   }

   // printing colors of oranges
   cout << "Colors of the oranges: ";
   for(auto fruit=tree.begin(); fruit!=tree.end(); ++fruit)
      if(fruit->first == Variety::orange) 
         cout << fruit->second << ", ";
   cout << endl;

}
