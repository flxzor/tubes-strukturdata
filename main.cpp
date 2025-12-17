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
        cout << "11. Traverse Preorder\n";
        cout << "12. Traverse Inorder\n";
        cout << "13. Traverse Postorder\n";
        cout << "0. Exit\n";
        cout << "Choose: ";
        cin >> choice;
        cin.ignore();

        if (choice == 0) break;

        if (choice == 1) {
            string t, d;
            cout << "Title: "; getline(cin, t);
            cout << "Description: "; getline(cin, d);
            qm.createMainQuest(t, d);
        }
        else if (choice == 2) {
            int pid;
            string t, d;
            cout << "Parent ID: "; cin >> pid; cin.ignore();
            cout << "Title: "; getline(cin, t);
            cout << "Description: "; getline(cin, d);
            qm.createSubquest(pid, t, d);
        }
        else if (choice == 3) {
            int id;
            string t, d;
            cout << "Quest ID: "; cin >> id; cin.ignore();
            cout << "New Title: "; getline(cin, t);
            cout << "New Description: "; getline(cin, d);
            qm.updateQuest(id, t, d);
        }
        else if (choice == 4) {
            int id;
            cout << "Quest ID: ";
            cin >> id;
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

            cout << "\nMy Quests:\n";
            for (int qid : pl->questIds) {
                Quest* q = qm.find(qid);
                if (q)
                    cout << "- [" << q->id << "] " << q->title << endl;
            }
        }
        else if (choice == 8) {
            string u;
            int qid;
            cout << "Username: "; cin >> u;
            cout << "Quest ID: "; cin >> qid;

            Player* pl = pm.findPlayer(u);
            if (!pl) {
                cout << "Player not found.\n";
                continue;
            }
            if (!qm.find(qid)) {
                cout << "Quest not found.\n";
                continue;
            }
            pm.assignQuest(pl, qid);
        }
        else if (choice == 9) {
            string u;
            int qid;
            cout << "Username: "; cin >> u;
            cout << "Quest ID to remove: "; cin >> qid;

            Player* pl = pm.findPlayer(u);
            if (!pl) {
                cout << "Player not found.\n";
                continue;
            }
            pm.removeQuest(pl, qid);
        }
        else if (choice == 10) {
            pm.showAllPlayers();
        }
        else if (choice == 11) {
            qm.traversePreorder();
        }
        else if (choice == 12) {
            qm.traverseInorder();
        }
        else if (choice == 13) {
            qm.traversePostorder();
        }
    }

    return 0;
}
