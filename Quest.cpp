#include "Quest.h"

// ================= Quest =================

Quest::Quest(int id, const string& title, const string& desc)
    : id(id), title(title), description(desc) {}

void Quest::addSubquest(Quest* q) {
    children.push_back(q);
}

void Quest::printTree(int depth) {
    for (int i = 0; i < depth; i++)
        cout << "  ";

    cout << "- [" << id << "] " << title << endl;

    for (auto c : children)
        c->printTree(depth + 1);
}

// ================= QuestManager =================

Quest* QuestManager::findQuest(Quest* node, int id) {
    if (!node) return nullptr;
    if (node->id == id) return node;

    for (auto c : node->children) {
        Quest* res = findQuest(c, id);
        if (res) return res;
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
    for (auto c : node->children)
        deleteRecursive(c);
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

    cout << "\n=== ALL QUESTS ===\n";
    for (auto r : roots)
        r->printTree();
}

// ================= TRAVERSAL =================

// Preorder: NODE -> CHILDREN
void QuestManager::preorder(Quest* node) {
    if (!node) return;

    cout << node->id << " - " << node->title << endl;

    for (auto c : node->children)
        preorder(c);
}

// Inorder (N-ary): FIRST CHILD -> NODE -> REST CHILDREN
void QuestManager::inorder(Quest* node) {
    if (!node) return;

    if (!node->children.empty())
        inorder(node->children[0]);

    cout << node->id << " - " << node->title << endl;

    for (int i = 1; i < node->children.size(); i++)
        inorder(node->children[i]);
}

// Postorder: CHILDREN -> NODE
void QuestManager::postorder(Quest* node) {
    if (!node) return;

    for (auto c : node->children)
        postorder(c);

    cout << node->id << " - " << node->title << endl;
}

void QuestManager::traversePreorder() {
    for (auto r : roots)
        preorder(r);
}

void QuestManager::traverseInorder() {
    for (auto r : roots)
        inorder(r);
}

void QuestManager::traversePostorder() {
    for (auto r : roots)
        postorder(r);
}
