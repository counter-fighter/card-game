#include <string>

using namespace std;

class Card {
    string name;

    public:
        Card(string name);
        friend ostream &operator<<(ostream &out, Card c);


};
