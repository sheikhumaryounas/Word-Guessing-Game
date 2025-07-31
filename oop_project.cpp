#include "oop_project.h"
void setColorGreen()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 2);
}

void setColorRed()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 12);
}

void setColorBlue()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 9);
}

void resetColor()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 7);
}

void clearScreen()
{
    system("CLS");
}

template <typename T>
void saveHighScore(const T& name, int score) {
    ifstream infile("high_score.txt");
    ofstream outfile("temp.txt");

    string playerName;
    int playerScore;
    bool playerFound = false;
    bool addedNewScore = false;
    while (infile >> playerName >> playerScore) 
    {
        if (playerName == name) 
        {
            if (score > playerScore) 
            {
                outfile << name << " " << score << endl;
                playerFound = true;
            }
            else 
            {
                outfile << playerName << " " << playerScore << endl;
            }
        }
        else 
        {
            outfile << playerName << " " << playerScore << endl;
        }
    }

    if (!playerFound)
    {
        outfile << name << " " << score << endl;
    }

    infile.close();
    outfile.close();
    remove("high_score.txt");
    rename("temp.txt", "high_score.txt");
}
template<typename T>
Word<T>::Word(const T& str) : text(str), length(str.size()) {}

template<typename T>
bool Word<T>::operator==(const Word<T>& other) const
{
    return text == other.text;
}

template<typename T>
void Word<T>::setWord(const T& str)
{
    text = str;
    length = str.size();
}

Grid::Grid(int size) : gridSize(size)
{
    if (size <= 0 || size > 20)
    {
        cout << "Grid size must be between 1 and 20." << endl;
        exit(1);
    }
    srand((unsigned)time(0));
    for (int i = 0; i < gridSize; i++)
    {
        for (int j = 0; j < gridSize; j++)
        {
            grid[i][j] = 'a' + rand() % 26;
        }
    }
}

void Grid::populateGrid(const Word<string> words[], int wordcount)
{
    for (int i = 0; i < wordcount; i++)
    {
        int direction = rand() % 3;
        int row, col;
        bool placed = false;
        while (!placed)
        {
            row = rand() % gridSize;
            col = rand() % gridSize;

            if (direction == 0 && col + words[i].length <= gridSize)
            {
                for (int j = 0; j < words[i].length; j++)
                {
                    grid[row][col + j] = tolower(words[i].text[j]);
                }
                placed = true;
            }
            else if (direction == 1 && row + words[i].length <= gridSize)
            {
                for (int j = 0; j < words[i].length; j++)
                {
                    grid[row + j][col] = tolower(words[i].text[j]);
                }
                placed = true;
            }
            else if (direction == 2 && row + words[i].length <= gridSize && col + words[i].length <= gridSize)
            {
                for (int j = 0; j < words[i].length; j++)
                {
                    grid[row + j][col + j] = tolower(words[i].text[j]);
                }
                placed = true;
            }
        }
    }
}

void Grid::displayGrid() const
{
    cout << "     ";
    for (int i = 0; i < gridSize; i++)
    {
        if (gridSize == 20)
        {
            cout << i << "  ";
        }
        else
        {
            cout << i << " ";
        }
        
    }
    cout << endl;
    cout << "    ";
    for (int i = 0; i < gridSize*2; i++)
    {
        if (gridSize == 20)
        {
            cout << "--";
        }
        else
        {
            cout << "-";
        }
        
    }
    cout << endl;
    for (int i = 0; i < gridSize; i++)
    {
        if (i <= 9)
        {

            cout << i << "  | ";
        }
        else
        {
            cout << i << " | ";
        }
        for (int j = 0; j < gridSize; j++)
        {
            if (gridSize == 20)
            {
                cout << grid[i][j] << "  ";
            }
            else
            {
                cout << grid[i][j] << " ";
            }
                
        }
        cout << endl;
    }
}

char Grid::getCharacterAt(int row, int col) const
{
    if (row < 0 || row >= gridSize || col < 0 || col >= gridSize)
    {
        cout << "Row or column index out of range." << endl;
        return '\0';
    }
    return grid[row][col];
}

int Grid::getSize() const
{
    return gridSize;
}

GameMode::GameMode(int level, Grid* gridPtr) : level(level), grid(gridPtr), wordcount(0), wordstoguess(0) {}

void GameMode::playLevel()
{
    string playerName;
    cout << "Enter your name: ";
    cin >> playerName;

    grid->displayGrid();
    int remainingWords = wordstoguess;
    int chances = 5;
    int score = 0;

    cout << "Words to guess: " << remainingWords << endl;

    try {
        while (remainingWords > 0 && chances > 0)
        {
            char guessedWord[20];
            int guessedLength = 0;

            cout << "Start guessing a word by selecting characters.\n";
            while (true)
            {
                int row = -1, col = -1;
                while (true)
                {
                    cout << "Input row (0 to " << grid->getSize() - 1 << "): ";
                    if (cin >> row)
                    {
                        if (row >= 0 && row < grid->getSize())
                        {
                            break;
                        }
                        else
                        {
                            cout << "Invalid row. Please enter a number between 0 and " << grid->getSize() - 1 << ".\n";
                        }
                    }
                    else
                    {
                        cout << "Invalid input. Please enter a number.\n";
                        cin.clear();
                        cin.ignore();
                    }
                }
                while (true)
                {
                    cout << "Input column (0 to " << grid->getSize() - 1 << "): ";
                    if (cin >> col)
                    {
                        if (col >= 0 && col < grid->getSize())
                        {
                            break;
                        }
                        else
                        {
                            cout << "Invalid column. Please enter a number between 0 and " << grid->getSize() - 1 << ".\n";
                        }
                    }
                    else
                    {
                        cout << "Invalid input. Please enter a number.\n";
                        cin.clear();
                        cin.ignore();
                    }
                }

                char letter = grid->getCharacterAt(row, col);
                if (letter == '\0') 
                {
                    cout << "Selected position is out of range." << endl;
                    continue;
                }

                guessedWord[guessedLength++] = letter;
                cout << "Selected character at position [" << row << "," << col << "] = " << letter << endl;

                char continueSelection;
                while (true)
                {
                    cout << "Do you want to select another character? (y/n): ";
                    cin >> continueSelection;
                    if (continueSelection == 'y' || continueSelection == 'Y' || continueSelection == 'n' || continueSelection == 'N') {
                        break; 
                    }
                    else
                    {
                        cout << "Invalid input. Please enter 'y' or 'n'.\n";
                    }
                }

                if (continueSelection == 'n' || continueSelection == 'N')
                {
                    guessedWord[guessedLength] = '\0';
                    break;
                }
            }

            bool found = false;
            for (int i = 0; i < wordcount; i++)
            {
                if (words[i].text == guessedWord)
                {
                    setColorGreen();
                    cout << "Word complete! You guessed: ";
                    setColorBlue();
                    cout << guessedWord << endl;
                    resetColor();
                    cout << "Remaining words to guess are " << --remainingWords << endl;
                    score += 10;

                    found = true;
                    break;
                }
            }

            if (!found)
            {
                setColorRed();
                cout << "Incorrect guess. Try again." << endl;
                resetColor();
                --chances;
            }

            std::this_thread::sleep_for(std::chrono::seconds(5));
            clearScreen();
            grid->displayGrid();
            cout << "Words to guess: " << remainingWords << endl;
        }

        saveHighScore(playerName, score);

        if (remainingWords == 0)
        {
            cout << "Congratulations! You've found all words.\n";
        }
        else
        {
            cout << "Game Over. You've run out of chances.\n";
        }
        cout << "Your final score: " << score << endl;
    }
    catch (const char* msg)
    {
        cout << msg << endl;
    }
}

EasyGame::EasyGame(int level, Grid* gridPtr) : GameMode(level, gridPtr)
{
    wordstoguess = (level == 1) ? 3 : (level == 2) ? 5 : 7;
}

void EasyGame::loadWords()
{
    ifstream file("easy_words.txt");
    string word;
    while (file >> word && word.size() >= 2 && word.size() <= 4)
    {
        words[wordcount++].setWord(word);
        if (wordcount == 50) break;
    }
    grid->populateGrid(words, wordcount);
}

int EasyGame::calculateScore() const
{
    return level * 10;
}

HardGame::HardGame(int level, Grid* gridPtr) : GameMode(level, gridPtr)
{
    wordstoguess = (level == 1) ? 3 : (level == 2) ? 5 : 7;
}

void HardGame::loadWords()
{
    ifstream file("hard_words.txt");
    string word;
    while (file >> word && word.size() >= 5 && word.size() <= 7)
    {
        words[wordcount++].setWord(word);
        if (wordcount == 50) break;
    }
    grid->populateGrid(words, wordcount);
}

int HardGame::calculateScore() const
{
    return level * 20; 
}

int Game::totalScore = 0;

Game::Game() : mode(nullptr), grid(nullptr) {}

Game::~Game()
{
    delete mode;
    delete grid;
}
void Game::displayMainMenu()
{
    clearScreen();
    setColorRed();
    cout << "***************************************" << endl;
    resetColor();
    cout << "*                                     *" << endl;
    setColorBlue();
    cout << "*   Welcome to the Word Guess Game!   *" << endl;
    resetColor();
    cout << "*                                     *" << endl;
    setColorGreen();
    cout << "*                                     *" << endl;
    resetColor();
    cout << "*                                     *" << endl;
    setColorGreen();
    cout << "* 1. Start Game                       *" << endl;
    resetColor();
    setColorBlue();
    cout << "* 2. Instructions                     *" << endl;
    resetColor();
    cout << "* 3. High Scores                      *" << endl;
    setColorRed();
    cout << "* 4. About Us                         *" << endl;
    resetColor();
    cout << "* 5. Exit                             *" << endl;
    setColorGreen();
    cout << "***************************************" << endl;
    resetColor();
    cout << endl;
    cout << "Please choose an option (1-5): ";
}
void Game::startGame()
{
    int modeChoice, level;
    string playerName;

    while (true)
    {
        cout << "Select mode: 1 for Easy, 2 for Hard: ";
        if (!(cin >> modeChoice) || (modeChoice != 1 && modeChoice != 2))
        {
            cout << "Invalid choice. Please enter 1 or 2.\n";
            cin.clear();
            cin.ignore();
            continue;
        }
        break;
    }

    while (true)
    {
        cout << "Select level (1, 2, or 3): ";
        if (!(cin >> level) || (level < 1 || level > 3))
        {
            cout << "Invalid level. Please select 1, 2, or 3.\n";
            cin.clear();
            cin.ignore();
            continue;
        }
        break;
    }
    if (!grid)
    {
        grid = new Grid((level == 1) ? 10 : (level == 2) ? 15 : 20);
    }
    if (!mode)
    {
        mode = (modeChoice == 1) ? static_cast<GameMode*>(new EasyGame(level, grid)) : static_cast<GameMode*>(new HardGame(level, grid));
        mode->loadWords();
    }
    mode->playLevel();
}

void Game::displayHighScores()
{
    ifstream infile("high_score.txt");
    if (!infile.is_open())
    {
        cout << "Error opening high score file!" << endl;
        return;
    }

    string playerName;
    int playerScore;
    cout << "\n--- High Scores ---" << endl;
    int rank = 1;
    while (infile >> playerName >> playerScore)
    {
        setColorBlue();
        cout << rank++ << ". " << playerName << " - " << playerScore << " points" << endl;
        resetColor();
    }
    cout << "--------------------" << endl;
    infile.close();
}