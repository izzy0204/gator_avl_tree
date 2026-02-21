#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <regex>
using namespace std;

struct Node {
    string name;
    string id;
    int height;
    Node* left;
    Node* right;
    
    Node(string n, string i) : name(n), id(i), height(1), left(nullptr), right(nullptr) {}
};

class AVLTree {
private:
    Node* root;
    int getHeight(Node* node) {
        return node ? node->height : 0;
    }
    int getBalanceFactor(Node* node) {
        if (!node) return 0;
        return getHeight(node->left) - getHeight(node->right);
    }
    void fixHeight(Node* node) {
        if (node)
            node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    }

    Node* rotateLeft(Node* node) {
        Node* newRoot = node->right;
        node->right = newRoot->left;
        newRoot->left = node;
        fixHeight(node);
        fixHeight(newRoot);
        return newRoot;
    }

    Node* rotateRight(Node* node) {
        Node* newRoot = node->left;
        node->left = newRoot->right;
        newRoot->right = node;
        fixHeight(node);
        fixHeight(newRoot);
        return newRoot;
    }

    Node* rotateLeftRight(Node* node) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    Node* rotateRightLeft(Node* node) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    Node* balanceNode(Node* node) {
        if (!node) return node;
        fixHeight(node);
        int bf = getBalanceFactor(node);

        if (bf > 1) {
            if (getBalanceFactor(node->left) >= 0)
                return rotateRight(node);
            else
                return rotateLeftRight(node);
        }
        if (bf < -1) {
            if (getBalanceFactor(node->right) <= 0)
                return rotateLeft(node);
            else
                return rotateRightLeft(node);
        }
        return node;
    }

    Node* insertHelper(Node* node, string name, string id, bool& success) {
        if (!node) {
            success = true;
            return new Node(name, id);
        }
        if (id < node->id)
            node->left = insertHelper(node->left, name, id, success);
        else if (id > node->id)
            node->right = insertHelper(node->right, name, id, success);
        else {
            success = false;
            return node;
        }
        return balanceNode(node);
    }

    Node* getMin(Node* node) {
        while (node->left) node = node->left;
        return node;
    }

    Node* removeHelper(Node* node, string id, bool& success) {
        if (!node) {
            success = false;
            return nullptr;
        }
        if (id < node->id)
            node->left = removeHelper(node->left, id, success);
        else if (id > node->id)
            node->right = removeHelper(node->right, id, success);
        else {
            success = true;
            if (!node->left) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            else if (!node->right) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            Node* succ = getMin(node->right);
            string succID = succ->id;
            string succName = succ->name;
            node->right = removeHelper(node->right, succID, success);
            node->id = succID;
            node->name = succName;
        }
        return balanceNode(node);
    }

    void inorderHelper(Node* node, vector<string>& result) {
        if (!node) return;
        inorderHelper(node->left, result);
        result.push_back(node->name);
        inorderHelper(node->right, result);
    }

    void preorderHelper(Node* node, vector<string>& result) {
        if (!node) return;
        result.push_back(node->name);
        preorderHelper(node->left, result);
        preorderHelper(node->right, result);
    }

    void postorderHelper(Node* node, vector<string>& result) {
        if (!node) return;
        postorderHelper(node->left, result);
        postorderHelper(node->right, result);
        result.push_back(node->name);
    }

    Node* searchByIDHelper(Node* node, string id) {
        if (!node) return nullptr;
        if (id == node->id) return node;
        if (id < node->id) return searchByIDHelper(node->left, id);
        return searchByIDHelper(node->right, id);
    }

    void searchByNameHelper(Node* node, string name, vector<string>& result) {
        if (!node) return;
        if (node->name == name) result.push_back(node->id);
        searchByNameHelper(node->left, name, result);
        searchByNameHelper(node->right, name, result);
    }

    void collectInorder(Node* node, vector<string>& ids) {
        if (!node) return;
        collectInorder(node->left, ids);
        ids.push_back(node->id);
        collectInorder(node->right, ids);
    }

    void destroyTree(Node* node) {
        if (!node) return;
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }

    void printVector(const vector<string>& v) {
        for (size_t i = 0; i < v.size(); i++) {
            cout << v[i];
            if (i < v.size() - 1) cout << ", ";
        }
        cout << endl;
    }

public:
    AVLTree() : root(nullptr) {}
    ~AVLTree() { destroyTree(root); }
    AVLTree(const AVLTree&) = delete;
    AVLTree& operator=(const AVLTree&) = delete;

    static bool isValidID(const string& id) {
        regex pattern("^\\d{8}$");
        return regex_match(id, pattern);
    }

    static bool isValidName(const string& name) {
        regex pattern("^[a-zA-Z ]+$");
        return regex_match(name, pattern);
    }

    void insert(string name, string id) {
        bool success = false;
        root = insertHelper(root, name, id, success);
        cout << (success ? "successful" : "unsuccessful") << endl;
    }

    void remove(string id) {
        bool success = false;
        root = removeHelper(root, id, success);
        cout << (success ? "successful" : "unsuccessful") << endl;
    }

    void searchID(string id) {
        Node* result = searchByIDHelper(root, id);
        cout << (result ? result->name : "unsuccessful") << endl;
    }

    void searchName(string name) {
        vector<string> ids;
        searchByNameHelper(root, name, ids);
        if (ids.empty()) {
            cout << "unsuccessful" << endl;
        } else {
            for (const string& id : ids)
                cout << id << endl;
        }
    }

    void printInorder() {
        vector<string> result;
        inorderHelper(root, result);
        printVector(result);
    }

    void printPreorder() {
        vector<string> result;
        preorderHelper(root, result);
        printVector(result);
    }

    void printPostorder() {
        vector<string> result;
        postorderHelper(root, result);
        printVector(result);
    }

    void printLevelCount() {
        cout << getHeight(root) << endl;
    }

    void removeInorder(int n) {
        vector<string> ids;
        collectInorder(root, ids);
        if (n < 0 || n >= (int)ids.size()) {
            cout << "unsuccessful" << endl;
        } else {
            bool success = false;
            root = removeHelper(root, ids[n], success);
            cout << (success ? "successful" : "unsuccessful") << endl;
        }
    }
};