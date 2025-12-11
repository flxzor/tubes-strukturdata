#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Player {
public:
    string username;
    string password;
    vector<int> questIds;

    Player(const string& username, const string& password);
};

class PlayerManager {
private:
    vector<Player*> players;

public:
    Player* findPlayer(const string& username);
    void registerPlayer(const string& username, const string& password);
    Player* login(const string& username, const string& password);

    void assignQuest(Player* player, int questId);
    void removeQuest(Player* player, int questId);

    void showAllPlayers();
};

#endif
