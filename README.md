🎮 Word Guessing Game (C++ OOP Project)
A console-based word puzzle game developed in C++ using Object-Oriented Programming (OOP) principles. This game challenges players to guess hidden words from a randomly generated letter grid based on difficulty level and game mode. It includes colorized terminal output, file-based score saving, and structured gameplay logic.

🧠 Features
🔠 Grid-Based Word Puzzle

Words are hidden horizontally, vertically, or diagonally.

Grid size increases with difficulty (10x10 to 20x20).

🎮 Game Modes & Levels

Easy Mode: Words of length 2–4.

Hard Mode: Words of length 5–7.

Levels: 1 (Easy) to 3 (Hardest).

📋 Word Selection

Users select characters by inputting grid coordinates.

Build words one letter at a time.

💾 Score System & High Scores

Scores are saved to a file (high_score.txt).

Automatically updates only if a higher score is achieved.

🌈 Colorful UI

Uses Windows API to apply terminal colors (Green, Red, Blue).

Improved user experience and feedback.

🧾 Instructions and About Section

Built-in game instructions and developer credits included.

🏗️ Project Structure
less
Copy
Edit
├── main.cpp              // Entry point of the game
├── oop_project.h         // Header file with class declarations
├── oop_project.cpp       // Implementation of all classes and functions
├── easy_words.txt        // Word list for Easy mode (2–4 letter words)
├── hard_words.txt        // Word list for Hard mode (5–7 letter words)
├── high_score.txt        // Automatically generated score storage
🧱 Object-Oriented Concepts Used
Classes and Inheritance

Game, GameMode (Base), EasyGame & HardGame (Derived)

Grid, Word (Template class for words)

Polymorphism

loadWords() and calculateScore() overridden in derived classes

Encapsulation

Game logic separated into modular classes

Templates

Word<T> class handles different types (currently using std::string)

📁 How to Run
Compile using any C++ compiler:

bash
Copy
Edit
g++ main.cpp oop_project.cpp -o WordGame
Make sure these files are in the same directory:

easy_words.txt

hard_words.txt

Run the game:

bash
Copy
Edit
./WordGame
If you're using Windows, open in cmd.exe for full color support.

📸 Sample Output
markdown
Copy
Edit
***************************************
*                                     *
*   Welcome to the Word Guess Game!   *
*                                     *
* 1. Start Game                       *
* 2. Instructions                     *
* 3. High Scores                      *
* 4. About Us                         *
* 5. Exit                             *
***************************************
👨‍💻 Developers
Umar Sheikh
Department of Computer Science, FAST NUCES
