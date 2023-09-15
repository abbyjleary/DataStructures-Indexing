/**
 *    @file: index-tree.h
 *  @author: Abby Leary
 *    @date: 10/9/22
 *   @brief: holds the Node and Tree functions
 *
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
 *  Function:   lower
 *              finds the lowercase version of a word
 *
 *  @param word - the word to be converted to lowercase
 *  @return - the string in lowercase
 */
string lower(string word);

struct Node
{

    /**
     *  Function:   Node
     *              default node constructor
     *
     *  @param newWord - the new word to set word as
     *  @param occur - the total times the word occurs
     *  @param newLeft - the new left pointer
     *  @param newRight - the new right pointer
     */
    Node(string newWord = "", int occur = 0, Node *newLeft = nullptr, Node *newRight = nullptr)
    {
        word = newWord;
        data = {};
        left = newLeft;
        right = newRight;
    }
    string word;
    vector<pair<int, int>> data;
    int occur;
    Node *right;
    Node *left;
};

class Tree
{
public:
    /**
     *  Function:   insert
     *              uses the private insert function to insert a new word into the tree
     *
     *  @param newWord - the new word to be added
     *  @param line - the line the word is on
     */
    void insert(string newWord, int line) { privInsert(root, newWord, line); }

    /**
     *  Function:   print
     *              uses the private print function to print the whole tree
     */
    void print()
    {
        cout << endl;
        privPrint(root);
    }

    /**
     *  Function:   search
     *              uses the private search function to search the tree
     *
     *  @param search - word being searched for
     *  @return - the node containing the word
     */
    Node search(string target);

    /**
     *  Function:   occurMost
     *              uses the private occur most function to find the word that occurs the most
     *
     *  @return - the node containing the word that occurs most
     */
    Node occurMost();

private:
    Node *root = nullptr;

    /**
     *  Function:   privInsert
     *              inserts a word into the tree
     *
     *  @param root - a pointer to the root of the tree
     *  @param newWord - the new word being added to the tree
     *  @param line - the line the new word is on
     */
    void privInsert(Node *&root, string newWord, int line);

    /**
     *  Function:   privPrint
     *              prints the entire tree in order
     *
     *  @param root - a pointer to the root of the tree
     */
    void privPrint(Node *root);

    /**
     *  Function:   privSearch
     *              searches the tree for a specified target
     *
     *  @param root - a pointer to the root of the tree
     *  @param target - the root being searched for
     *  @return - a pointer to a node containing the word
     */
    Node *privSearch(Node *&root, string target);

    /**
     *  Function:   privOccurMost
     *              finds which word occurs the most
     *
     *  @param root - a pointer to the root of the tree
     *  @param occur - how many times it occurs
     *  @return - a pointer to a node containing the word that occurs the most
     */
    Node *privOccurMost(Node *root, int &occur);
};

void Tree::privInsert(Node *&root, string newWord, int line)
{
    // create a new node with 1 occurence if it doesn't exist already
    if (root == nullptr)
    {
        root = new Node(lower(newWord));
        root->data.push_back(pair<int, int>{line, 1});
        root->occur = 1;
        return;
    }

    // add to occurrence if the word is already in the tree
    if (root->word == lower(newWord))
    {
        for (int i = 0; i < (root->data).size(); i++)
        {
            if (line == (root->data)[i].first)
            {
                ++(root->data)[i].second;
                ++(root->occur);
                return;
            }
        }
        (root->data).push_back(pair<int, int>{line, 1});
        ++(root->occur);
        return;
    }

    // insert left it is is left
    else if (lower(newWord) < root->word)
    {
        privInsert(root->left, newWord, line);
    }

    // insert right if it is more
    else if (lower(newWord) > root->word)
    {
        privInsert(root->right, newWord, line);
    }
}

void Tree::privPrint(Node *root)
{
    // stop if the root is null
    if (root == nullptr)
    {
        return;
    }

    // print the left subtree
    privPrint(root->left);

    // print everything in the node
    cout << root->word << ": [";
    for (int i = 0; i < ((root->data).size()); i++)
    {
        cout << "<" << (root->data[i]).first << "," << (root->data[i]).second << ">";
        if ((i + 1) < (root->data).size())
        {
            cout << ", ";
        }
    }
    cout << "]" << endl;

    // print the right subtree
    privPrint(root->right);
}

Node *Tree::privSearch(Node *&root, string target)
{
    // return nullptr if the root is null
    if (root == nullptr)
    {
        return root;
    }

    // if the target is on the left, search the left subtree
    else if (lower(target) < root->word)
    {
        return privSearch(root->left, target);
    }

    // if the target is on the right, search the right subtree
    else if (lower(target) > root->word)
    {
        return privSearch(root->right, target);
    }
    return root;
}

Node Tree::occurMost()
{
    // return an empty node if the node has not been found
    Node *n = privOccurMost(root, root->occur);
    if (n == nullptr)
    {
        return *(new Node);
    }

    // return a pointer to the node containing the word occuring most
    return *n;
}

Node Tree::search(string target)
{
    // return an empty node if the node is not found
    Node *n = privSearch(root, target);
    if (n == nullptr)
    {
        return *(new Node);
    }

    // return a pointer to the node containing the target word
    return *n;
}

string lower(string word)
{
    string s = word;

    // go through the word letter by letter and convert to lowercase
    for (int i = 0; i < s.length(); i++)
    {
        s[i] = tolower(s[i]);
    }
    return s;
}

Node *Tree::privOccurMost(Node *root, int &occur)
{
    if (root == nullptr)
    {
        return nullptr;
    }

    // if the children are not null, check if the occurrences are more than the current most
    if (root->left != nullptr && root->right != nullptr)
    {
        if (root->occur > occur)
        {
            occur = root->occur;
            return root;
        }
    }

    // check left and right subtrees
    return privOccurMost(root->right, occur);
    return privOccurMost(root->left, occur);
}