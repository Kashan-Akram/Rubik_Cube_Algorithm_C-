This implementation uses the Thistlethwaite's algorithm as a preprocessor to reduce the cube to a more manageable state before applying Herbert Kociemba's algorithm.

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
Each move is represented as a string, where
    
    'U' denotes a clockwise rotation of the upper face, 
    'U' denotes a counterclockwise rotation, 
    'U2' denotes a 180-degree rotation, and so on for the other faces.
