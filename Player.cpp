#include "Player.h"

Player::Player(const string& username, const string& password)
    : username(username), password(password) {}

Player* PlayerManager::findPlayer(const string& username) {
    for (auto p : players)
        if (p->username == username)
            return p;
    return nullptr;
}

void PlayerManager::registerPlayer(const string& username, const string& password) {
    if (findPlayer(username)) {
        cout << "Username already exists.\n";
        return;
    }
    players.push_back(new Player(username, password));
    cout << "Player registered.\n";
}

Player* PlayerManager::login(const string& username, const string& password) {
    for (auto p : players)
        if (p->username == username && p->password == password)
            return p;
    return nullptr;
}

void PlayerManager::assignQuest(Player* player, int questId) {
    for (int id : player->questIds)
        if (id == questId) {
            cout << "Player already has this quest.\n";
            return;
        }
    player->questIds.push_back(questId);
    cout << "Quest assigned.\n";
}

void PlayerManager::removeQuest(Player* player, int questId) {
    for (int i = 0; i < player->questIds.size(); i++) {
        if (player->questIds[i] == questId) {
            player->questIds.erase(player->questIds.begin() + i);
            cout << "Quest removed.\n";
            return;
        }
    }
    cout << "Quest not found on player.\n";
}

void PlayerManager::showAllPlayers() {
    if (players.empty()) {
        cout << "No players registered.\n";
        return;
    }

    cout << "\n=== ALL PLAYERS ===\n";
    for (auto p : players) {
        cout << "- " << p->username << " | Quests: ";
        if (p->questIds.empty()) cout << "(none)";
        for (int id : p->questIds)
            cout << id << " ";
        cout << endl;
    }
}
