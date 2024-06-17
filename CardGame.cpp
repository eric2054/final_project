#include "CardGame.h"

// CardGame 類別的建構子
CardGame::CardGame() {
    // 初始化用來追蹤使用中的卡片和桌面上的卡片的陣列
    for (int count = 0; count <= 52; count++) {
        Card_InUsed[count] = 0;
        Desk[count] = 0;
    }

    // 設置隨機數生成器
    srand((unsigned)time(NULL));
    Card_Index = 1;
    Check_RanCardOK = true;

    // 生成隨機排列的卡片
    while (Check_RanCardOK) {
        rand_number = rand() % 52 + 1;
        if (Card_InUsed[rand_number] == 0) {
            Card_InUsed[rand_number] = Card_Index;
            Card[Card_Index] = rand_number;
            Card_Index++;
        }
        Check_RanCardOK = false;
        // 檢查是否還有未使用的卡片
        for (int count = 1; count <= 52; count++) {
            if (Card_InUsed[count] == 0) {
                Check_RanCardOK = true;
            }
        }
    }
}

// 開始卡片遊戲的函數
void CardGame::startGame() {
    vector<int> usedCards; // 記錄已經出過的牌
    vector<int> hiddenCards[4]; // 記錄每位玩家的蓋牌

    // 分發並顯示初始卡片給玩家
    for (int count2 = 0; count2 <= 3; count2++) {
        cout << "玩家" << (count2 + 1) << "===";
        for (int count = 1; count <= 13; count++) {
            int cardIndex = count + count2 * 13;
            if (Card[cardIndex] == 7) { // 如果是梅花七
                player_number = count2;
                Desk[Card[cardIndex]] = 1;
                usedCards.push_back(Card[cardIndex]); // 將開局出梅花七的牌加入到已使用的牌中
            }
            // 顯示未使用的牌
            if (find(usedCards.begin(), usedCards.end(), Card[cardIndex]) == usedCards.end()) {
                cout << count << "." << decode(Card[cardIndex]) << " ";
            }
            else {
                cout << "  ";
            }
        }
        cout << "\n";
    }

    cout << "梅花七在 玩家" << (player_number + 1) << "手上,已出牌\n";

    // 移動到下一位玩家
    if (player_number == 3) {
        player_number = 0;
    }
    else {
        player_number = player_number + 1;
    }

    while (Desk_Check) {
        cout << "玩家" << (player_number + 1) << "===";
        bool validMove = false;

        // 檢查玩家是否有有效的牌可出
        for (int count = 1; count <= 13; count++) {
            int cardIndex = count + player_number * 13;
            int cardValue = Card[cardIndex];
            if (Desk[cardValue] == 0 && find(usedCards.begin(), usedCards.end(), cardValue) == usedCards.end()) {
                int lowerCard = cardValue - 1;
                int upperCard = cardValue + 1;
                if ((lowerCard % 13 != 0 && Desk[lowerCard] == 1) || (upperCard % 13 != 1 && Desk[upperCard] == 1)) {
                    validMove = true;
                    break;
                }
            }
        }

        // 如果沒有有效的牌可出，請玩家選擇一張牌蓋起來
        if (!validMove) {
            cout << "沒有有效的牌可出, 請選擇一張牌蓋起:\n";
            for (int count = 1; count <= 13; count++) {
                int cardIndex = count + player_number * 13;
                if (find(usedCards.begin(), usedCards.end(), Card[cardIndex]) == usedCards.end()) {
                    cout << count << "." << decode(Card[cardIndex]) << " ";
                }
                else {
                    cout << "  ";
                }
            }
            cout << "\n 蓋牌:";
        }
        // 如果有有效的牌可出，請玩家出牌
        else {
            for (int count = 1; count <= 13; count++) {
                int cardIndex = count + player_number * 13;
                if (find(usedCards.begin(), usedCards.end(), Card[cardIndex]) == usedCards.end()) {
                    cout << count << "." << decode(Card[cardIndex]) << " ";
                }
                else {
                    cout << "  ";
                }
            }
            cout << "\n 出牌:";
        }

        string userInputStr;
        cin >> userInputStr;
        // 如果玩家輸入 "pass"，移動到下一位玩家
        if (userInputStr == "pass") {
            if (player_number == 3) {
                player_number = 0;
            }
            else {
                player_number++;
            }
            continue; // 跳到下一位玩家
        }
        user_input = stoi(userInputStr); // 將使用者輸入的字串轉換為整數

        if (validMove) {
            if (user_input <= 13 && user_input >= 1 && Desk[Card[user_input + player_number * 13]] == 0 && find(usedCards.begin(), usedCards.end(), Card[user_input + player_number * 13]) == usedCards.end()) {
                Desk[Card[user_input + player_number * 13]] = 1;
                usedCards.push_back(Card[user_input + player_number * 13]); // 將出過的牌加入到已使用的牌中
            }
        }
        else {
            if (user_input <= 13 && user_input >= 1 && Desk[Card[user_input + player_number * 13]] == 0 && find(usedCards.begin(), usedCards.end(), Card[user_input + player_number * 13]) == usedCards.end()) {
                hiddenCards[player_number].push_back(Card[user_input + player_number * 13]);
                usedCards.push_back(Card[user_input + player_number * 13]); // 將蓋起的牌加入到已使用的牌中
            }
        }

        // 顯示目前牌桌的情況
        cout << "目前牌桌的情況:\n";
        for (int i = 0; i < 4; i++) {
            switch (i) {
                case 0:
                    cout << "梅花: ";
                    break;
                case 1:
                    cout << "方塊: ";
                    break;
                case 2:
                    cout << "紅心: ";
                    break;
                case 3:
                    cout << "黑桃: ";
                    break;
            }
            for (int j = 1; j <= 13; j++) {
                int card = i * 13 + j;
                if (Desk[card] == 1) {
                    cout << decode(card) << " ";
                }
                else {
                    cout << "[ ] ";
                }
            }
            cout << "\n";
        }

        // 移動到下一位玩家
        if (player_number == 3) {
            player_number = 0;
        }
        else {
            player_number = player_number + 1;
        }

        // 檢查是否還有可以出的牌
        Check_RanCardOK = false;
        Desk_Check = false;
        for (int count = 1; count <= 52; count++) {
            if (Desk[count] == 0 && find(usedCards.begin(), usedCards.end(), count) == usedCards.end()) {
                Desk_Check = true;
                break;
            }
        }
    }

    cout << "遊戲結束\n";

    // 計算並顯示每位玩家的蓋牌點數
    int minPoints = INT_MAX;
    int winner = -1;
    for (int i = 0; i < 4; i++) {
        int points = 0;
        for (int card : hiddenCards[i]) {
            points += (card % 13 == 0) ? 13 : card % 13; // K 為 13 點
        }
        cout << "玩家" << (i + 1) << "的蓋牌點數: " << points << "\n";
        if (points < minPoints) {
            minPoints = points;
            winner = i;
        }
    }
    cout << "玩家" << (winner + 1) << "獲勝, 蓋牌點數最少\n";
}

// 將卡片編號解碼為字串表示的函數
string CardGame::decode(int number) {
    string color;
    switch ((number - 1) / 13) {
        case 0:
            color = "梅花";
            break;
        case 1:
            color = "方塊";
            break;
        case 2:
            color = "紅心";
            break;
        case 3:
            color = "黑桃";
            break;
    }
    switch (number % 13) {
        case 0:
            color = color + "K";
            break;
        case 10:
            color = color + "10";
            break;
        case 11:
            color = color + "J";
            break;
        case 12:
            color = color + "Q";
            break;
        default:
            color = color + to_string(number % 13);
            break;
    }
    return color;
}
