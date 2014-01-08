//
//  main.cpp
//  tp2graphes
//
//  Created by Matthieu de La Roche Saint-Andre and Victor Haffreingue on 12/20/13.
//

#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

// Cell of the adjacency matrix
// This structure is used to store values in adjacency matrix
// The field "valid" is null when the value is not valid,
// and has any other value otherwise.
// The field "value" is the weight of the link.
typedef struct _adjCell {
    int value, valid;
} AdjCell;


AdjCell** parseFile(string path, int *nbNodes); // parses the file and creates the adjacency matrix
void print(AdjCell** adjMatrix, int size); // prints adjacency matrix
bool connexe(AdjCell** adjMatrix, int size); // checks connexity in adjacency matrix
bool cycle(AdjCell** adjMatrix, int size); // checks cycle presence in adjacency matrix

int main(int argc, const char * argv[]) {
    string path;
    if (argc == 2) {
        path = argv[1];
    } else {
        cout << "Which file do you want to open ? ";
        cin >> path;
        cout << endl;
    }
    //path = "/Users/matthieudelaro/Documents/classes/L3/S5/theorie_des_graphes/TP/tp2/github/tp2graphes/tp2graphes/1modified.txt";
    
    
    int size = 0; //size of adjacency matrix and of Bellman's matrix
    AdjCell **adjMatrix = parseFile(path, &size); // creates the adjacency matrix
    
    // handle reading errors
    if (!adjMatrix) {
        cout << "Error reading " << path << "." << endl;
    } else {
        // if adgency matrix was successfully created
        cout << endl;
        print(adjMatrix, size);
        cout << endl;
        
        // test connexity
        cout << endl;
        if (connexe(adjMatrix, size)) {
            cout << "The graph is connexe." << endl;
        } else {
            cout << "The graph is not connexe." << endl;
        }
        cout << endl;
        
        // test cycle presence
        cout << endl;
        if (cycle(adjMatrix, size)) {
            cout << "The graph contains cycles." << endl;
        } else {
            cout << "The graph does not contain any cycle." << endl;
        }
        cout << endl;
        
        
        // deletes adjacency matrix
        for (int i = 0; i < size; ++i) {
            delete[] adjMatrix[i];
        }
        delete[] adjMatrix;
    }
}

AdjCell** parseFile(string path, int *nbNodes) {
    cout << "Opening " << path  << "." << endl;
    FILE *file;
    int endOfFile = 0;
    file = fopen(path.c_str(), "r");
    
    AdjCell **matrix = NULL;
    
    if (file) {
        int c = 0;//current int we are parsing
        int nbLinks = 0;
        
        // Gets number of nodes
        endOfFile = fscanf(file, "%d", &c);
        if (endOfFile != EOF) {
            *nbNodes = c;
            
            // initializes the matrix
            matrix = new AdjCell*[*nbNodes];
            for (int i = 0; i < *nbNodes; ++i) {
                matrix[i] = new AdjCell[*nbNodes];
                for (int j = 0; j < *nbNodes; ++j) {
                    matrix[i][j].valid = 0;
                }
            }
        } else {
            cout << "Number of nodes is missing." << endl;
            return NULL;//number of nodes is missing
        }
        
        // Gets number of links
        // Note :
        // This is useless for the program. However, this
        // is required to comply with out teacher's
        // example of file format, so that it will make
        // verifications steps easier.
        endOfFile = fscanf(file, "%d", &c);
        if (endOfFile != EOF) {
            nbLinks = c;
        } else {
            cout << "Number of links is missing." << endl;
            return NULL;//number of links is missing
        }
        
        // read file ~line by line
        endOfFile = fscanf(file, "%d", &c);
        while (endOfFile != EOF) {
            if (c == -1) {
                // end of definition if we read -1
                return matrix;
            }
            
            //trying to get the terminal node of the link
            int line = c;
            int column = 0;
            //fflush(stdout);
            endOfFile = fscanf(file, "%d", &c);
            if (endOfFile != EOF) {
                column = c;
            } else {
                cout << "Terminal node is missing." << endl;
                return NULL;//terminal node is missing
            }
            
            //trying to get the value of the link
            endOfFile = fscanf(file, "%d", &c);
            if (endOfFile != EOF) {
                // In case a link is declared several times,
                // we keep the shortest link.
                if (matrix[line][column].valid) {
                    if (matrix[line][column].value > c) {
                        matrix[line][column].value = c;
                        matrix[line][column].valid = 1;
                        
                        
                        matrix[column][line].value = c;
                        matrix[column][line].valid = 1;
                    }
                } else {
                    matrix[line][column].value = c;
                    matrix[line][column].valid = 1;
                    
                    matrix[column][line].value = c;
                    matrix[column][line].valid = 1;
                }
            } else {
                cout << "Value is missing." << endl;
                return NULL;//value is missing
            }
            
            endOfFile = fscanf(file, "%d", &c);
        }
    } else {
        cout << "Error while opening the file." << endl;
        return NULL; // error while opening the file
    }
    
    return matrix;
}

void print(AdjCell** adjMatrix, int size) {
    for (int j = 0; j < size; ++j) {
        cout << "\t" << j;
    }
    for (int i = 0; i < size; ++i) {
        cout << endl << i << "\t";
        for (int j = 0; j < size; ++j) {
            if (adjMatrix[i][j].valid) {
                cout << adjMatrix[i][j].value << "\t";
            } else {
                cout << ".\t";
            }
        }
    }
    cout << endl;
}

// checks connexity in adjacency matrix
bool connexe(AdjCell** adjMatrix, int size) {
    vector<bool> found(size, false);
    vector<bool> used(size, false);
    
    int previousFoundQuantity = 1;
    int foundQuantity = 1;
    int usedQuantity = 0;
    found[0] = true;
    
    int current = 0;
    bool goOn = true;
    while (foundQuantity < size && usedQuantity < size && goOn) {
        if (used[current] == false && found[current]) {
            
            used[current] = true;
            usedQuantity++;
            
            cout << endl;
            cout << endl;
            cout << "Newly found with " << current << " : ";
            
            for (int destination = 0; destination < size; ++destination) {
                if (adjMatrix[current][destination].valid) {
                    if (found[destination] == false) {
                        found[destination] = true;
                        foundQuantity++;
                        
                        cout << destination << " ";
                    }
                }
            }
            
            cout << endl;
            cout << "foundQuantity : " << foundQuantity << endl;
            cout << "usedQuantity : " << usedQuantity << endl;
            
            cout << "found : ";
            for (int i = 0; i < size; ++i) {
                if (found[i]) {
                    cout << i << " ";
                }
            }
            cout << endl;
            
            cout << "used : ";
            for (int i = 0; i < size; ++i) {
                if (used[i]) {
                    cout << i << " ";
                }
            }
            cout << endl;
        }
        
        if (current == size - 1) {
            if (foundQuantity == previousFoundQuantity) {
                goOn = false;
            } else {
                previousFoundQuantity = foundQuantity;
                current = 0;
            }
        } else {
            current++;
        }
    }
    
    cout << endl;
    cout << endl;
    if (foundQuantity == size) {
        cout << "Each node has been found." << endl;
        return true;
    } else {
        cout << "Some node(s) has not been found." << endl;
        return false;
    }
}

// checks cycle presence in adjacency matrix
bool cycle(AdjCell** adjMatrix, int size) {
    vector<bool> deleted(size, false);
    
    int deletedQuantity = 0;
    int previousDeletedQuantity = 0;
    
    int current = 0;
    bool goOn = true;
    while (deletedQuantity < size && goOn) {
        if (deleted[current] == false) {
            
            int destinationQuantity = 0;
            for (int destination = 0; destination < size && destinationQuantity < 2; ++destination) {
                if (adjMatrix[current][destination].valid && !deleted[destination]) {
                    destinationQuantity++;
                }
            }
            
            // if the node is an entry point in the graph,
            // we delete this node
            if (destinationQuantity < 2) {
                deleted[current] = true;
                deletedQuantity++;
                cout << current << " has " << destinationQuantity << " neighbour. We delete it." << endl;
            }
        }
        
        if (current == size - 1) {
            if (deletedQuantity == previousDeletedQuantity) {
                goOn = false;
            } else {
                previousDeletedQuantity = deletedQuantity;
                current = 0;
            }
        } else {
            current++;
        }
    }
    
    cout << endl;
    cout << endl;
    if (deletedQuantity == size) {
        cout << "Each node has been deleted." << endl;
        return false;
    } else {
        cout << "Some node(s) has not been deleted." << endl;
        return true;
    }
}

