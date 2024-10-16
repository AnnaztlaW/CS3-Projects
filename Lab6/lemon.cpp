// picking the best quality lemons
// converting vectors to priority queue
// Anna Waltz
// 9/24/24


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <queue>

using std::cin; using std::cout; using std::endl;
using std::string;
using std::vector;

struct Lemon {
    double quality;
    friend bool operator<(const Lemon& left, const Lemon& right) {
        return left.quality < right.quality;
    }
};

const int maxBoxSize = 30;
const int highestQuality = 10;

int main() {
    srand(time(nullptr));
    std::priority_queue<Lemon> box;
    int boxSize = rand() % maxBoxSize + 1; // random box size

    for (int i = 0 ; i < boxSize ; i++){
        Lemon temp;
        temp.quality = static_cast<double>(rand()) / RAND_MAX * highestQuality;// random quality assingment
        box.push(temp);
    }

    cout << "Here are the lemons (best first): ";
    while(!box.empty()){
        cout << box.top().quality << ", " ;
        box.pop();
    }

    cout << endl;
}