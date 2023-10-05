

/* Note: 
	1. You will have to comment main() when unit testing your code because catch uses its own main().
	2. You will submit this main.cpp file and any header files you have on Gradescope. 
*/

#include <iostream>
#include <sstream>
#include "AVL.h"
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;
int main(int argc, char* argv[]){
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " input_file output_file" << endl;
        return 1;
    }

    ifstream inputFile(argv[1]);
    if (!inputFile) {
        cerr << "Error opening input file." << endl;
        return 1;
    }

    ofstream outputFile(argv[2]);
    if (!outputFile) {
        cerr << "Error opening output file." << endl;
        return 1;
    }

    int totalCommands;
    if (!(inputFile >> totalCommands)) {
        cerr << "Error reading the total number of commands." << endl;
        return 1;
    }
    AVLTree avlTree;

    for (int i = 0; i < totalCommands; i++) {
        string commandLine;
        getline(inputFile, commandLine);

        stringstream ss(commandLine);
        string command;
        ss >> command;

        if (command == "insert") {
            string name;
            ss.ignore();
            getline(ss, name, '"');
            string id;
            ss >> id;
            if (id.length() != 8 || !all_of(id.begin(), id.end(), ::isdigit)) {
                outputFile << "unsuccessful" << endl;
                continue;
            }

            if (!all_of(name.begin(), name.end(), [](char c) {
                return isalpha(c) || isspace(c);
            })) {
                outputFile << "unsuccessful" << endl;
                continue; // Move to the next command
            }

            if (avlTree.searchID(id) != "nullptr") {
                outputFile << "unsuccessful" << endl;
                continue; // Move to the next command
            }

            avlTree.insert(name, id);

            outputFile << "successful" << endl;

        } else if (command == "remove") {
            // Read and store id
            string id;
            ss >> id;
            if (id.length() != 8 || !all_of(id.begin(), id.end(), ::isdigit)) {
                outputFile << "unsuccessful" << endl;
                continue;
            }
            if (avlTree.searchID(id) != "nullptr") {
                outputFile << "unsuccessful" << endl;
                continue;
            }
            avlTree.removeNode(id);
            outputFile << "successful" << endl;
        } else if (command == "search") {

            string argument;
            ss >> argument;

            if (argument[0] == '"') {
                // Read and store "name"
                string name;
                ss.ignore(); // Ignore the space after "search"
                getline(ss, name, '"'); // Read up to the next "
                if (!all_of(name.begin(), name.end(), [](char c) {
                    return isalpha(c) || isspace(c);
                })) {
                    outputFile << "unsuccessful" << endl;
                    continue; // Move to the next command
                }
                avlTree.searchName(name);

            } else {
                if (argument.length() != 8 || !all_of(argument.begin(), argument.end(), ::isdigit)) {
                    outputFile << "unsuccessful" << endl;
                    continue;
                }
                string name = avlTree.searchID(argument);
                if (name == "null"){
                    outputFile << "unsuccessful" << endl;
                }
                else{
                    outputFile << name << endl;
                }
            }
        } else if (command == "printInorder") {
            // Implement printInorder logic here
        } else if (command == "printPreorder") {
            // Implement printPreorder logic here
        } else if (command == "printPostorder") {
            // Implement printPostorder logic here
        } else if (command == "printLevelCount") {
            // Implement printLevelCount logic here
        } else if (command == "removeInorder") {
            // Read and store N
            string N;
            ss >> N;


        } else {
            outputFile << "unsuccessful" << endl;

        }
    }

    return 0;
}

