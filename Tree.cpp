#include "Tree.h"

#include <filesystem>
#include <fstream>

Tree::Node* Tree::Node::getNext(const char c) const {
    for (Node *s : children)
        if (s->data == c) return s;
    return nullptr;
}

Tree::Node* Tree::Node::addChild(const char c) {
    Node* temp = getNext(std::tolower(c));
    if (temp != nullptr) return temp;
    temp = new Node(c);
    children.push_back(temp);
    return temp;
}

Tree::Node::~Node() {
    for (Node *s : children)
        delete s;
}

void Tree::Node::saveNode(std::ostream &os) const {
    os << data
       << static_cast<char>(is_valid_end)
       << static_cast<uint16_t>(children.size());
    for (Node *s : children)
        s->saveNode(os);
}


Tree::~Tree() {
    delete root;
}

bool Tree::isValidWord(const std::string &word) const {
    const Node* temp = root; // The const here doesn't make the variable itself const, but it makes what's on the end of the pointer const
    for (char c : word) {
        temp = temp->getNext(std::tolower(c));
        if (temp == nullptr) return false;
    }
    return temp->is_valid_end;
}

void Tree::addWord(const std::string &word) {
    Node* temp = root;
    for (char c : word)
        temp = temp->addChild(c);
    temp->is_valid_end = true;
}

void Tree::addWords(const std::vector<std::string> &words) {
    for (const std::string &word : words)
        addWord(word);
}

void Tree::addWordsFromFile(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) throw std::invalid_argument("File not found");
    std::string word;
    while (std::getline(file, word))
        addWord(word);
}

