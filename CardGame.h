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
    CardGame(); // 建構子
    void startGame(); // 開始遊戲的函數

private:
    int Card[53], Card_InUsed[53], Card_Index, Desk[53], user_input; // 卡片相關陣列和變數
    int count, count2, rand_number, player_number; // 計數器和玩家號碼
    bool Check_RanCardOK = true, Desk_Check = true; // 檢查卡片和桌面狀態的布林值

    string decode(int number); // 將卡片編號解碼為字串表示的函數
};
#endif
