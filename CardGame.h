#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

class CardGame {
public:
    CardGame();
    void startGame();

private:
    int Card[53], Card_InUsed[53], Card_Index, Desk[53], user_input;
    int count, count2, rand_number, player_number;
    bool Check_RanCardOK = true, Desk_Check = true;

    string decode(int number);
};
#endif
