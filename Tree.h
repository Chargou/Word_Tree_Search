#pragma once

#include <string>
#include <unordered_map>
#include <vector>

class Tree {
    class Node {
        public:
        char data;
        bool is_valid_end = false;
        std::pmr::unordered_map<char, Node*> children = {};

        explicit Node(const char c) : data(c) {}

        Node* getNext(char) const;

        Node* addChild(char);

        ~Node();

        void saveNode(std::ostream& os) const;
        //Node*
    };

    Node* root = new Node('%'); // This char data should never be accessed so we could put whatever in there

    public:
    Tree() = default;
    ~Tree();

    bool isValidWord(const std::string &word) const;

    void addWord(const std::string &word);
    void addWords(const std::vector<std::string> &words);
    void addWordsFromFile(const std::string &filename);
};
