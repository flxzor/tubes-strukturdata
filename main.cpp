// main.cpp
#include "Quest.h"

int main() {
    QuestManager qm;
    int choice;

    while (true) {
        cout << "\n=== Quest Manager ===\n";
        cout << "1. Create Main Quest\n";
        cout << "2. Create Subquest\n";
        cout << "3. Update Quest\n";
        cout << "4. Delete Quest\n";
        cout << "5. Show All Quests\n";
        cout << "0. Exit\n";
        cout << "Choose: ";
        cin >> choice;

        cin.ignore(); // buang newline

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
    }

    return 0;
}
