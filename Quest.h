#ifndef QUEST_H
#define QUEST_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Quest {
public:
    int id;
    string title;
    string description;
    vector<Quest*> children;

    Quest(int id, const string& title, const string& desc);

    void addSubquest(Quest* q);
    void printTree(int depth = 0);
};

class QuestManager {
private:
    vector<Quest*> roots;
    int nextId = 1;

    Quest* findQuest(Quest* node, int id);
    void deleteRecursive(Quest* node);

    // traversal helper (DFS)
    void preorder(Quest* node);
    void inorder(Quest* node);
    void postorder(Quest* node);

public:
    Quest* find(int id);

    void createMainQuest(const string& title, const string& desc);
    void createSubquest(int parentId, const string& title, const string& desc);
    void updateQuest(int id, const string& newTitle, const string& newDesc);
    void deleteQuest(int id);

    void showAll();

    void traversePreorder();
    void traverseInorder();
    void traversePostorder();
};

#endif
