#pragma once

#include <string>
#include <vector>

class Tree {
    class Node {
        public:
        char data;
        bool is_valid_end = false;
        std::vector<Node*> children = {};

        explicit Node(const char c) : data(c) {}

        Node* getNext(char) const;

        Node* addChild(char);

        ~Node();
    };

    std::vector<Node*> starts = {};

    Node* getStart(char) const;

    public:
    Tree() = default;
    ~Tree();

    bool isValidWord(const std::string &word) const;

    void addWord(const std::string &word);
    void addWords(const std::vector<std::string> &words);
    void addWordsFromFile(const std::string &filename);
};
