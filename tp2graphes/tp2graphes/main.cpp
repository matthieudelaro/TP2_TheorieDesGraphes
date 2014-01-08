//
//  main.cpp
//  tp2graphes
//
//  Created by Matthieu de La Roche Saint-Andre and Victor Haffreingue on 12/20/13.
//

#include <iostream>
#include <cstdio>
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
//    if (argc == 2) {
//        path = argv[1];
//    } else {
//        cout << "Which file do you want to open ? ";
//        cin >> path;
//        cout << endl;
    //    }
    //    MODIFY ME !!!!!!!!!!!!!!!!!!
    //    MODIFY ME !!!!!!!!!!!!!!!!!!
    //    MODIFY ME !!!!!!!!!!!!!!!!!!
    //    MODIFY ME !!!!!!!!!!!!!!!!!!
    //    MODIFY ME !!!!!!!!!!!!!!!!!!
    //    MODIFY ME !!!!!!!!!!!!!!!!!!
    //    MODIFY ME !!!!!!!!!!!!!!!!!!
    //    MODIFY ME !!!!!!!!!!!!!!!!!!
    path = "/Users/matthieudelaro/Documents/classes/L3/S5/theorie_des_graphes/TP/tp2/github/tp2graphes/tp2graphes/1.txt";
    
    
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
    return false;
}

// checks cycle presence in adjacency matrix
bool cycle(AdjCell** adjMatrix, int size) {
    return false;
}

