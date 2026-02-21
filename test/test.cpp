/*
#include "../test/catch/catch_amalgamated.hpp"
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "../src/AVLTree.h"

using namespace std;

// Helper function to capture cout output from any callable
template<typename F>
string getOutput(F func) {
    stringstream buffer;
    streambuf* old = cout.rdbuf(buffer.rdbuf());
    func();
    cout.rdbuf(old);
    return buffer.str();
}

// Test 1: invalid commands
TEST_CASE("Test invalid commands", "[invalid][validation]"){
    AVLTree tree;
    
    // invalid name
    REQUIRE(AVLTree::isValidName("A11y") == false);
    string name1 = "A11y";
    string id1 = "12345678";
    auto testInsert1 = [&]() {
        if (!AVLTree::isValidName(name1) || !AVLTree::isValidID(id1)) {
            cout << "unsuccessful" << endl;
        } else {
            tree.insert(name1, id1);
        }
    };
    REQUIRE(getOutput(testInsert1) == "unsuccessful\n");
    
    // invalid id
    REQUIRE(AVLTree::isValidID("123456789") == false);
    string name2 = "allie";
    string id2 = "123456789";
    auto testInsert2 = [&]() {
        if (!AVLTree::isValidName(name2) || !AVLTree::isValidID(id2)) {
            cout << "unsuccessful" << endl;
        } else {
            tree.insert(name2, id2);
        }
    };
    REQUIRE(getOutput(testInsert2) == "unsuccessful\n");
    
    // invalid id too short
    REQUIRE(AVLTree::isValidID("1234567") == false);
    string name3 = "bianca";
    string id3 = "1234567";
    auto testInsert3 = [&]() {
        if (!AVLTree::isValidName(name3) || !AVLTree::isValidID(id3)) {
            cout << "unsuccessful" << endl;
        } else {
            tree.insert(name3, id3);
        }
    };
    REQUIRE(getOutput(testInsert3) == "unsuccessful\n");
    
    // invalid name special characters
    REQUIRE(AVLTree::isValidName("diana!") == false);
    string name4 = "diana!";
    string id4 = "12345678";
    auto testInsert4 = [&]() {
        if (!AVLTree::isValidName(name4) || !AVLTree::isValidID(id4)) {
            cout << "unsuccessful" << endl;
        } else {
            tree.insert(name4, id4);
        }
    };
    REQUIRE(getOutput(testInsert4) == "unsuccessful\n");
    
    // invalid id letters
    REQUIRE(AVLTree::isValidID("1234567a") == false);
    string name5 = "ellie";
    string id5 = "1234567a";
    auto testInsert5 = [&]() {
        if (!AVLTree::isValidName(name5) || !AVLTree::isValidID(id5)) {
            cout << "unsuccessful" << endl;
        } else {
            tree.insert(name5, id5);
        }
    };
    REQUIRE(getOutput(testInsert5) == "unsuccessful\n");
    
    // invalid name empty string
    REQUIRE(AVLTree::isValidName("") == false);
}

// Test 2: edge cases
TEST_CASE("Test edge cases", "[edge][boundary]"){
    AVLTree tree;
    
    // remove from empty tree
    REQUIRE(getOutput([&]{ tree.remove("12345678"); }) == "unsuccessful\n");
    
    // search in empty tree
    REQUIRE(getOutput([&]{ tree.searchID("12345678"); }) == "unsuccessful\n");
    REQUIRE(getOutput([&]{ tree.searchName("allie"); }) == "unsuccessful\n");
    
    // removeInorder with negative index
    tree.insert("allie", "12345678");
    tree.insert("bianca", "23456789");
    REQUIRE(getOutput([&]{ tree.removeInorder(-1); }) == "unsuccessful\n");
    
    // removeInorder with out of bounds index
    REQUIRE(getOutput([&]{ tree.removeInorder(100); }) == "unsuccessful\n");
    
    // remove node that doesn't exist
    REQUIRE(getOutput([&]{ tree.remove("99999999"); }) == "unsuccessful\n");
}

// Test 3: rotation cases
TEST_CASE("Test four rotation cases", "[rotation][balance]"){
    // left rotation (right-right case)
    AVLTree tree1;
    tree1.insert("allie", "10000000");
    tree1.insert("bianca", "20000000");
    tree1.insert("cristine", "30000000");
    
    REQUIRE(getOutput([&]{ tree1.printPreorder(); }) == "bianca, allie, cristine\n");
    REQUIRE(getOutput([&]{ tree1.printInorder(); }) == "allie, bianca, cristine\n");
    
    // right rotation (left-left case)
    AVLTree tree2;
    tree2.insert("cristine", "30000000");
    tree2.insert("bianca", "20000000");
    tree2.insert("allie", "10000000");
    
    REQUIRE(getOutput([&]{ tree2.printPreorder(); }) == "bianca, allie, cristine\n");
    REQUIRE(getOutput([&]{ tree2.printInorder(); }) == "allie, bianca, cristine\n");
    
    // left-right rotation (left-right case)
    AVLTree tree3;
    tree3.insert("cristine", "30000000");
    tree3.insert("allie", "10000000");
    tree3.insert("bianca", "20000000");
    
    REQUIRE(getOutput([&]{ tree3.printPreorder(); }) == "bianca, allie, cristine\n");
    REQUIRE(getOutput([&]{ tree3.printInorder(); }) == "allie, bianca, cristine\n");
    
    // right-left rotation (right-left case)
    AVLTree tree4;
    tree4.insert("allie", "10000000");
    tree4.insert("cristine", "30000000");
    tree4.insert("bianca", "20000000");
    
    REQUIRE(getOutput([&]{ tree4.printPreorder(); }) == "bianca, allie, cristine\n");
    REQUIRE(getOutput([&]{ tree4.printInorder(); }) == "allie, bianca, cristine\n");
}

// Test 4: deletion cases
TEST_CASE("Test three deletion cases", "[deletion][remove]"){
    AVLTree tree;
    
    tree.insert("diana", "40000000");
    tree.insert("bianca", "20000000");
    tree.insert("frank", "60000000");
    tree.insert("allie", "10000000");
    tree.insert("cristine", "30000000");
    tree.insert("ellie", "50000000");
    tree.insert("grace", "70000000");
    
    // remove leaf node (no children)
    REQUIRE(getOutput([&]{ tree.remove("10000000"); }) == "successful\n");
    REQUIRE(getOutput([&]{ tree.searchID("10000000"); }) == "unsuccessful\n");
    REQUIRE(getOutput([&]{ tree.printInorder(); }) == "bianca, cristine, diana, ellie, frank, grace\n");
    
    // remove node with one child
    tree.remove("50000000");
    REQUIRE(getOutput([&]{ tree.remove("60000000"); }) == "successful\n");
    REQUIRE(getOutput([&]{ tree.searchID("60000000"); }) == "unsuccessful\n");
    REQUIRE(getOutput([&]{ tree.printInorder(); }) == "bianca, cristine, diana, grace\n");
    
    // remove node with two children
    AVLTree tree2;
    tree2.insert("diana", "40000000");
    tree2.insert("bianca", "20000000");
    tree2.insert("frank", "60000000");
    tree2.insert("allie", "10000000");
    tree2.insert("cristine", "30000000");
    tree2.insert("ellie", "50000000");
    tree2.insert("grace", "70000000");
    
    // remove root which has two children
    REQUIRE(getOutput([&]{ tree2.remove("40000000"); }) == "successful\n");
    REQUIRE(getOutput([&]{ tree2.searchID("40000000"); }) == "unsuccessful\n");
    string inorder = getOutput([&]{ tree2.printInorder(); });
    REQUIRE(inorder.find("diana") == string::npos);
    REQUIRE(inorder.find("allie") != string::npos);
    REQUIRE(inorder.find("bianca") != string::npos);
}

// Test 5: insert 100 nodes, remove 10, check inorder
// resource used: setup example from project instructions (OnlineGDB)
TEST_CASE("Test 100 nodes insertions and 10 removals", "[large][stress]"){
    AVLTree tree;
    vector<string> insertedIds;
    vector<string> expectedNames;
    
    for (int i = 0; i < 100; i++) {
        string id = to_string(10000000 + i);
        string name = "annie";
        
        insertedIds.push_back(id);
        expectedNames.push_back(name);
        
        string output = getOutput([&]{ tree.insert(name, id); });
        REQUIRE(output == "successful\n");
    }
    
    REQUIRE(insertedIds.size() == 100);
    REQUIRE(expectedNames.size() == 100);
    
    string inorderBefore = getOutput([&]{ tree.printInorder(); });
    
    int nodeCount = count(inorderBefore.begin(), inorderBefore.end(), ',') + 1;
    REQUIRE(nodeCount == 100);
    
    REQUIRE(getOutput([&]{ tree.searchID("10000000"); }) == "annie\n");
    REQUIRE(getOutput([&]{ tree.searchID("10000050"); }) == "annie\n");
    REQUIRE(getOutput([&]{ tree.searchID("10000099"); }) == "annie\n");
    
    vector<int> indicesToRemove = {5, 15, 25, 35, 45, 55, 65, 75, 85, 95};
    vector<string> removedIds;
    
    for (int idx : indicesToRemove) {
        string idToRemove = insertedIds[idx];
        removedIds.push_back(idToRemove);
        string output = getOutput([&]{ tree.remove(idToRemove); });
        REQUIRE(output == "successful\n");
    }
    
    REQUIRE(removedIds.size() == 10);
    
    string inorderAfter = getOutput([&]{ tree.printInorder(); });
    nodeCount = count(inorderAfter.begin(), inorderAfter.end(), ',') + 1;
    REQUIRE(nodeCount == 90);
    
    for (const string& id : removedIds) {
        string searchOutput = getOutput([&]{ tree.searchID(id); });
        REQUIRE(searchOutput == "unsuccessful\n");
    }
    
    REQUIRE(getOutput([&]{ tree.searchID("10000000"); }) == "annie\n");
    REQUIRE(getOutput([&]{ tree.searchID("10000010"); }) == "annie\n");
    REQUIRE(getOutput([&]{ tree.searchID("10000050"); }) == "annie\n");
    
    vector<string> remainingNames;
    for (int i = 0; i < 100; i++) {
        if (find(indicesToRemove.begin(), indicesToRemove.end(), i) == indicesToRemove.end()) {
            remainingNames.push_back(expectedNames[i]);
        }
    }
    
    REQUIRE(remainingNames.size() == 90);
    
    REQUIRE(getOutput([&]{ tree.removeInorder(0); }) == "successful\n");
    
    inorderAfter = getOutput([&]{ tree.printInorder(); });
    nodeCount = count(inorderAfter.begin(), inorderAfter.end(), ',') + 1;
    REQUIRE(nodeCount == 89);
    
    string heightOutput = getOutput([&]{ tree.printLevelCount(); });
    int height = stoi(heightOutput);
    REQUIRE(height <= 12);
}
*/