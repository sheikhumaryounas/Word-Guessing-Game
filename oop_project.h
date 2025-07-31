#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
#include <windows.h>
#define GREEN_TEXT "\033[1;32m"
#define RED_TEXT "\033[1;31m"
#define BLUE_TEXT "\033[1;34m"
#define RESET_TEXT "\033[0m"
using namespace std;

void setColorGreen();
void setColorRed();
void setColorBlue();
void resetColor();
void clearScreen();
template<typename T>
void saveHighScore(const T& name, int score);
template<typename T>
class Word {
public:
    T text;
    int length;

    Word(const T& str = "");
    bool operator==(const Word& other) const;
    void setWord(const T& str);
};
class Grid {
private:
    char grid[20][20];
    int gridSize;

public:
    Grid(int size);
    void populateGrid(const Word<string> words[], int wordcount);
    void displayGrid() const;
    char getCharacterAt(int row, int col) const;
    int getSize() const;
};

class GameMode {
protected:
    int level;
    int wordstoguess;
    Grid* grid;
    Word<string> words[50];
    int wordcount;

public:
    GameMode(int level, Grid* gridPtr);
    virtual ~GameMode() {}
    virtual void loadWords() = 0;
    virtual int calculateScore() const = 0;
    void playLevel();
};

class EasyGame : public GameMode {
public:
    EasyGame(int level, Grid* gridPtr);
    void loadWords() override;
    int calculateScore() const override;
};

class HardGame : public GameMode {
public:
    HardGame(int level, Grid* gridPtr);
    void loadWords() override;
    int calculateScore() const override;
};

class Game {
private:
    static int totalScore;
    GameMode* mode;
    Grid* grid;

public:
    Game();
    ~Game();
    void displayMainMenu();
    void startGame();
    static void displayHighScores();
};