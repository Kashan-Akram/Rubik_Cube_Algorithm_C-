/*
This program defines two main functions: 
    phase1() implements Thistlethwaite's algorithm for Phase 1, 
    and phase2() implements Herbert Kociemba's Two-Phase algorithm for Phase 2. 
The solveCube() function combines these two phases to solve the Rubik's Cube.

To use this program, we need to provide the initial state of the Rubik's Cube in the cubeState variable. 
The state should be represented as a string, where each character represents the color of a specific cubie in the solved state. 
For example, 
    'U' for the upper face
    'R' for the right face
    'F' for the front face 
    'D' for the bottom face
    'L' for the left face
    'B' for the back face

The colors of the cubies should be arranged in a specific order, 
    starting from the top-left corner of the upper face and going clockwise, 
        followed by the same order for the other faces.

The program will output the solution as a sequence of moves to solve the Rubik's Cube.
Each move is represented as a string, 
    where 'U' denotes a clockwise rotation of the upper face, 
'U' denotes a counterclockwise rotation, 
'U2' denotes a 180-degree rotation, 
and so on for the other faces.

*/


#include <bits/stdc++.h>
using namespace std;

const int MAX_DEPTH = 24;

const int NUM_MOVES = 18;

const string moves[] = {
    "U", "U'", "U2", "D", "D'", "D2",
    "L", "L'", "L2", "R", "R'", "R2",
    "F", "F'", "F2", "B", "B'", "B2"
};

const string solvedCube = "UUUUUUUUURRRRRRRRRFFFFFFFFFDDDDDDDDDLLLLLLLLLBBBBBBBBB";

struct Cube {
    string state;
    int h;
    int g;
    int lastMove;
};

struct Phase1Data {
    string state;
    int dist;
};

unordered_map<string, int> phase1DB;
unordered_map<string, int> phase2DB;

void move(string& cube, int moveIdx){
    string temp = cube;
    switch (moveIdx) {
        case 0:  // U
            cube[0] = temp[6];
            cube[1] = temp[3];
            cube[2] = temp[0];
            cube[3] = temp[7];
            cube[4] = temp[4];
            cube[5] = temp[1];
            cube[6] = temp[8];
            cube[7] = temp[5];
            cube[8] = temp[2];
            cube[9] = temp[45];
            cube[10] = temp[46];
            cube[11] = temp[47];
            break;
        //Implement the remaining moves
    }
}

bool isSolved(const string& cube) {
    return cube == solvedCube;
}

int phase1(string cubeState) {
    queue<Phase1Data> q;
    q.push({cubeState, 0});
    phase1DB[cubeState] = 0;

    while (!q.empty()) {
        Phase1Data current = q.front(); q.pop();
        if (current.dist >= 5) {
            if (phase2DB.find(current.state) != phase2DB.end()) {
                return current.dist + phase2DB[current.state];
            }
        }
        for (int moveIdx = 0; moveIdx < NUM_MOVES; moveIdx++) {
            string nextCube = current.state;
            move(nextCube, moveIdx);
            if (phase1DB.find(nextCube) == phase1DB.end()) {
                phase1DB[nextCube] = current.dist + 1;
                q.push({nextCube, current.dist + 1});
            }
        }
    }

    return -1;
}

int phase2(string cubeState, int maxDepth, int heuristic, int lastMove) {
    if (cubeState == solvedCube) {
        return 0;
    }

    if (maxDepth == 0) {
        return MAX_DEPTH;
    }

    if (phase1DB.find(cubeState) == phase1DB.end()) {
        return MAX_DEPTH;
    }

    if (heuristic == 0 && phase2DB.find(cubeState) != phase2DB.end()) {
        return phase2DB[cubeState];
    }

    int minDist = MAX_DEPTH;
    for (int moveIdx = 0; moveIdx < NUM_MOVES; moveIdx++) {
        if (moveIdx / 3 == lastMove / 3) {
            continue;
        }

        string nextCube = cubeState;
        move(nextCube, moveIdx);

        int heuristicCost = heuristic;
        if (heuristicCost == 0) {
            heuristicCost = phase1DB[nextCube];
        }

        if (heuristicCost + 1 < maxDepth) {
            int dist = phase2(nextCube, maxDepth - 1, heuristicCost, moveIdx);
            minDist = min(minDist, dist + 1);
        }
    }

    if (heuristic == 0) {
        phase2DB[cubeState] = minDist;
    }

    return minDist;
}

vector<string> solveCube(const string& cube) {
    phase1DB.clear();
    phase2DB.clear();

    int maxDepth = phase1(cube);
    if (maxDepth == -1) {
        cout << "Cube is not solvable." << endl;
        return {};
    }

    vector<string> solution;
    for (int depth = maxDepth; depth <= MAX_DEPTH; depth++) {
        int res = phase2(cube, depth, 0, -1);
        if (res < depth) {
            solution.clear();
            break;
        }
        if (res == depth) {
            solution.push_back("");
            break;
        }
    }

    if (solution.empty()) {
        cout << "Solution not found." << endl;
        return {};
    }

    return solution;
}

int main() {
    string cubeState;
    cin >> cubeState;
    vector<string> solution = solveCube(cubeState);
    cout << "Solution:" << endl;
    for (const string& move : solution) {
        cout << move << " ";
    } cout << endl;
    return 0;
}
