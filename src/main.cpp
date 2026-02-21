#include <iostream>
#include <string>
#include "AVLTree.h"
using namespace std;

static inline void trim(std::string& s) {
    while (!s.empty() && std::isspace(static_cast<unsigned char>(s.front()))) s.erase(s.begin());
    while (!s.empty() && std::isspace(static_cast<unsigned char>(s.back())))  s.pop_back();
}

string extractQuotedString(const string& str) {
    size_t a = str.find('"');
    if (a == string::npos) return "";
    size_t b = str.find('"', a + 1);
    if (b == string::npos) return "";
    return str.substr(a + 1, b - a - 1);
}

void parseCommand(AVLTree& tree, const string& line) {
    size_t spacePos = line.find(' ');
    string command = (spacePos == string::npos) ? line : line.substr(0, spacePos);
    string args = (spacePos == string::npos) ? "" : line.substr(spacePos + 1);
    trim(args);

    if (command == "insert") {
        string name = extractQuotedString(args);
        size_t firstQuote = args.find('"');
        size_t closeQuote = (firstQuote != string::npos) ? args.find('"', firstQuote + 1) : string::npos;
        string id = (closeQuote != string::npos) ? args.substr(closeQuote + 1) : "";
        trim(id);

        if (!AVLTree::isValidName(name) || !AVLTree::isValidID(id)) {
            cout << "unsuccessful" << endl;
            return;
        }
        tree.insert(name, id);
    }
    else if (command == "remove") {
        string id = args;
        trim(id);
        if (!AVLTree::isValidID(id)) {
            cout << "unsuccessful" << endl;
            return;
        }
        tree.remove(id);
    }
    else if (command == "search") {
        if (args.empty()) {
            cout << "unsuccessful" << endl;
            return;
        }
        if (args[0] == '"') {
            string name = extractQuotedString(args);
            if (!AVLTree::isValidName(name)) {
                cout << "unsuccessful" << endl;
                return;
            }
            tree.searchName(name);
        } else {
            string id = args;
            trim(id);
            if (!AVLTree::isValidID(id)) {
                cout << "unsuccessful" << endl;
                return;
            }
            tree.searchID(id);
        }
    }
    else if (command == "printInorder")   tree.printInorder();
    else if (command == "printPreorder")  tree.printPreorder();
    else if (command == "printPostorder") tree.printPostorder();
    else if (command == "printLevelCount") tree.printLevelCount();
    else if (command == "removeInorder") {
        try {
            trim(args);
            tree.removeInorder(std::stoi(args));
        } catch (const std::invalid_argument&) {
            std::cout << "unsuccessful\n";
        } catch (const std::out_of_range&) {
            std::cout << "unsuccessful\n";
        }
    }
    else {
        cout << "unsuccessful" << endl;
    }
}

int main() {
    AVLTree tree;
    int numCommands;
    cin >> numCommands;
    cin.ignore();

    for (int i = 0; i < numCommands; i++) {
        string line;
        getline(cin, line);
        parseCommand(tree, line);
    }

    return 0;
}