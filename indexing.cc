/**
 *    @file: indexing.cc
 *  @author: Abby Leary
 *    @date: 10/9/22
 *   @brief: main program for showing and traversing the tree
 *
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include "index-tree.h"

using namespace std;

/**
 *  Function:   menu
 *              prints the menu of options
 */
void menu();

/**
 *  Function:   noPunct
 *              takes the outside punctuation out of a word
 *
 *  @param word - word for punctuation to be taken out of
 *  @return - the word with no punctuation at the beginning or end
 */
string noPunct(string word);

/**
 *  Function:   search
 *              finds if a node is in the vector
 *
 *  @param v - vector to be parsed
 *  @param target - word being looked for
 *  @return - true if the word is there, and false if it isn't
 */
bool search(vector<string> v, string target);

int main()
{
    // load ignore file
    ifstream in;
    in.open("ignore.txt");

    // load the text into a string stream
    string text;
    getline(in, text);
    stringstream ss;
    ss << text;

    // load separate words into a vector
    vector<string> ignore;
    while (!ss.eof())
    {
        ss >> text;
        text = noPunct(text);
        ignore.push_back(text);
    }
    in.close();

    // load main text file
    in.open("Alan-Turing.txt");

    // check to see if file opened
    if (in.fail())
    {
        cout << "File was unable to be opened." << endl;
        return 0;
    }
    Tree tree;
    int line = 0;

    // load main text into a binary tree
    while (!in.eof())
    {
        getline(in, text);
        if (text != "")
        {
            stringstream sstream;
            sstream << text;
            line++;
            while (!sstream.eof())
            {
                sstream >> text;
                text = noPunct(text);
                if (text != "")
                {
                    // only insert it if it isn't an ignore word
                    if (!search(ignore, lower(text)))
                    {
                        tree.insert(text, line);
                    }
                }
            }
        }
    }

    in.close();

    // print the menu and get the choice
    cout << endl
         << "Choose an option:" << endl
         << endl;
    menu();
    int choice;
    cin >> choice;

    while (choice != 4)
    {
        // make sure the choice is valid
        while (choice < 1 || choice > 4)
        {
            cout << endl
                 << "Option invalid. Please choose a valid option:" << endl
                 << endl;
            menu();
            cin >> choice;
        }

        if (choice == 1)
        {
            tree.print();
        }

        if (choice == 2)
        {
            // asking for the word to search for
            string searchWord;
            Node n;
            cout << endl
                 << "Enter the word you want to search for: ";
            cin >> searchWord;
            n = tree.search(lower((searchWord)));

            // if the word is not found
            if (n.word == "")
            {
                cout << endl
                     << lower(searchWord) << " was not found." << endl;
            }

            // if the word is found, print the data
            else
            {
                cout << endl
                     << lower(searchWord) << ": [";
                for (int i = 0; i < (n.data).size(); i++)
                {
                    {
                        cout << "<" << (n.data[i]).first << "," << (n.data[i]).second << ">";
                        if ((i + 1) < (n.data).size())
                        {
                            cout << ", ";
                        }
                    }
                }
                cout << "]" << endl;
            }
        }

        if (choice == 3)
        {
            // find the node with the most occurrences
            Node n = tree.occurMost();
            cout << endl
                 << "The word " << n.word << " occurs " << n.occur << " times." << endl;
        }

        // choose again
        cout << endl
             << endl;
        cout << "Choose another option: " << endl
             << endl;
        menu();
        cin >> choice;
    }
}

void menu()
{

    cout << "1. Display occurrences of words in order" << endl;
    cout << "2. Search for a word" << endl;
    cout << "3. Display the most common word" << endl;
    cout << "4. Quit" << endl
         << endl;
}

string noPunct(string word)
{
    // when the first character in the string is a symbol
    while (!isalpha(word[0]) && !isdigit(word[0]) && word.size() > 0)
    {
        word.erase(0, 1);
        // for single symbol characters return empty string
        if (word.size() == 0)
        {
            return word;
        }
    }

    // when the last character in the string is a symbol
    while (!isalpha(word[word.length() - 1]) && !isdigit(word[word.length() - 1]))
    {
        word.erase(word.length() - 1, 1);
    }

    // takes the "'s" off the end
    if (word[word.length() - 1] == 's' && word[word.length() - 2] == '\'')
    {
        word.erase(word.length() - 2, 2);
    }

    return word;
}

bool search(vector<string> v, string target)
{
    // parse through the vector
    for (int i = 0; i < v.size(); i++)
    {
        if (v[i] == target)
        {
            // return true if the target is found
            return true;
        }
    }
    return false;
}