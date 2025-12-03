// Quest.cpp
#include "Quest.h"

// ======================== Quest =========================

Quest::Quest(int id, const string& title, const string& desc)
    : id(id), title(title), description(desc) {}

void Quest::addSubquest(Quest* q) {
    children.push_back(q);
}

void Quest::printTree(int depth) {
    for (int i = 0; i < depth; i++) cout << "  ";
    cout << "- [" << id << "] " << title << "\n";

    for (auto c : children) c->printTree(depth + 1);
}

// ==================== QuestManager ======================

Quest* QuestManager::findQuest(Quest* node, int id) {
    if (!node) return nullptr;
    if (node->id == id) return node;

    for (auto c : node->children) {
        Quest* result = findQuest(c, id);
        if (result) return result;
    }
    return nullptr;
}

Quest* QuestManager::find(int id) {
    for (auto r : roots) {
        Quest* q = findQuest(r, id);
        if (q) return q;
    }
    return nullptr;
}

void QuestManager::createMainQuest(const string& title, const string& desc) {
    roots.push_back(new Quest(nextId++, title, desc));
}

void QuestManager::createSubquest(int parentId, const string& title, const string& desc) {
    Quest* parent = find(parentId);
    if (!parent) {
        cout << "Parent quest not found.\n";
        return;
    }
    parent->addSubquest(new Quest(nextId++, title, desc));
}

void QuestManager::updateQuest(int id, const string& newTitle, const string& newDesc) {
    Quest* q = find(id);
    if (!q) {
        cout << "Quest not found.\n";
        return;
    }
    q->title = newTitle;
    q->description = newDesc;
}

void QuestManager::deleteRecursive(Quest* node) {
    for (auto c : node->children) deleteRecursive(c);
    delete node;
}

void QuestManager::deleteQuest(int id) {
    for (int i = 0; i < roots.size(); i++) {
        if (roots[i]->id == id) {
            deleteRecursive(roots[i]);
            roots.erase(roots.begin() + i);
            return;
        }
    }

    for (auto r : roots) {
        for (int i = 0; i < r->children.size(); i++) {
            if (r->children[i]->id == id) {
                deleteRecursive(r->children[i]);
                r->children.erase(r->children.begin() + i);
                return;
            }
        }
    }

    cout << "Quest not found.\n";
}

void QuestManager::showAll() {
    if (roots.empty()) {
        cout << "No quests available.\n";
        return;
    }
    for (auto r : roots) r->printTree();
}
