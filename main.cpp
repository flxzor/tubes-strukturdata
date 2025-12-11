#include "Quest.h"
#include "Player.h"
#include <iostream>
using namespace std;

int main() {
    QuestManager qm;
    PlayerManager pm;
    int choice;

    while (true) {
        cout << "\n=== MAIN MENU ===\n";
        cout << "1. Create Main Quest\n";
        cout << "2. Create Subquest\n";
        cout << "3. Update Quest\n";
        cout << "4. Delete Quest\n";
        cout << "5. Show All Quests\n";
        cout << "6. Register Player\n";
        cout << "7. Player Login\n";
        cout << "8. Assign Quest to Player\n";
        cout << "9. Remove Player Quest\n";
        cout << "10. Show All Players\n";
        cout << "0. Exit\n";
        cout << "Choose: ";
        cin >> choice;

        cin.ignore();

        if (choice == 0) break;

        if (choice == 1) {
            string title, desc;
            cout << "Title: "; getline(cin, title);
            cout << "Description: "; getline(cin, desc);
            qm.createMainQuest(title, desc);
        }

        else if (choice == 2) {
            int pid;
            string title, desc;
            cout << "Parent ID: "; cin >> pid; cin.ignore();
            cout << "Title: "; getline(cin, title);
            cout << "Description: "; getline(cin, desc);
            qm.createSubquest(pid, title, desc);
        }

        else if (choice == 3) {
            int id;
            string title, desc;
            cout << "Quest ID: "; cin >> id; cin.ignore();
            cout << "New title: "; getline(cin, title);
            cout << "New desc: "; getline(cin, desc);
            qm.updateQuest(id, title, desc);
        }

        else if (choice == 4) {
            int id;
            cout << "Quest ID: "; cin >> id;
            qm.deleteQuest(id);
        }

        else if (choice == 5) {
            qm.showAll();
        }

        else if (choice == 6) {
            string u, p;
            cout << "Username: "; cin >> u;
            cout << "Password: "; cin >> p;
            pm.registerPlayer(u, p);
        }

        else if (choice == 7) {
            string u, p;
            cout << "Username: "; cin >> u;
            cout << "Password: "; cin >> p;

            Player* pl = pm.login(u, p);
            if (!pl) {
                cout << "Login failed.\n";
                continue;
            }

            int pc;
            while (true) {
                cout << "\n=== Player Menu ===\n";
                cout << "1. View My Quests\n";
                cout << "0. Logout\n";
                cout << "Choose: ";
                cin >> pc;

                if (pc == 0) break;

                if (pc == 1) {
                    cout << "\n=== My Quests ===\n";
                    for (int qid : pl->questIds) {
                        Quest* q = qm.find(qid);
                        if (q) cout << "- [" << q->id << "] " << q->title << "\n";
                    }
                }
            }
        }

        else if (choice == 8) {
            string username;
            int qid;

            cout << "Player username: ";
            cin >> username;

            cout << "Quest ID: ";
            cin >> qid;

            Player* pl = pm.findPlayer(username);
            if (!pl) {
                cout << "Player not found.\n";
                continue;
            }

            Quest* q = qm.find(qid);
            if (!q) {
                cout << "Quest ID not found.\n";
                continue;
            }

            pm.assignQuest(pl, qid);
        }
        else if (choice == 9) {
            string username;
            int qid;

            cout << "Player username: ";
            cin >> username;

            cout << "Quest ID to remove: ";
            cin >> qid;

            Player* pl = pm.findPlayer(username);
            if (!pl) {
                cout << "Player not found.\n";
                continue;
            }

            pm.removeQuest(pl, qid);
        }
        else if (choice == 10) {
            pm.showAllPlayers();
        }
    }

    return 0;
}
