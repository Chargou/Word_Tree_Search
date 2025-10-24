#include "Tree.h"
#include <fstream>

Tree::Node* Tree::getStart(const char c) const {
    for (Node *s : starts)
        if (s->data == c) return s;
    return nullptr;
}

Tree::Node* Tree::Node::getNext(const char c) const {
    for (Node *s : children)
        if (s->data == c) return s;
    return nullptr;
}

Tree::Node* Tree::Node::addChild(const char c) {
    Node* temp = getNext(c);
    if (temp != nullptr) return temp;
    temp = new Node(c);
    children.push_back(temp);
    return temp;
}

Tree::Node::~Node() {
    for (Node *s : children)
        delete s;
}


Tree::~Tree() {
    for (Node *s : starts)
        delete s;
}

bool Tree::isValidWord(const std::string &word) const {
    const Node* temp = getStart(word[0]); // The const here doesn't make the variable itself const, but it makes what's on the end of the pointer const
    if (temp == nullptr) return false;
    for (int i = 1; i < word.size(); i++) {
        temp = temp->getNext(word[i]);
        if (temp == nullptr) return false;
    }
    return temp->is_valid_end;
}

void Tree::addWord(const std::string &word) {
    Node* temp = getStart(word[0]);
    if (temp == nullptr) {
        temp = new Node(word[0]);
        starts.push_back(temp);
    }
    for (int i = 1; i < word.size(); i++)
        temp = temp->addChild(word[i]);
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

