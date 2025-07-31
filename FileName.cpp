#include "oop_project.h"
int main()
{
    Game game;
    game.displayMainMenu();
    int choice;
    while (true)
    {
        cout << "Enter choice: ";

        cin >> choice;
        if (!choice)
        {
            cin.clear();
            cin.ignore();
            cout << "Invalid choice. Please try again." << endl;
            continue;
        }
        cin.clear();
        cin.ignore();

        switch (choice)
        {
        case 1:
            game.startGame();
            break;
        case 2:
            cout << "Instructions:" << endl;
            cout << "1.Guess all the hidden words in the grid by selecting letters based on their row and column positions." << endl;
            cout << "2.You have a limited number of chances to guess the words correctly; make each guess count!" << endl;
            cout << "3.Enter the row and column numbers to select letters, and choose whether to continue selecting more letters." << endl;
            cout << "4.Complete all the words to win; You have given five chances but if you run out of chances, the game is over." << endl;
            cout << "5.Your score will be calculated based on the difficulty level and how quickly you guess all the words." << endl;
            break;
        case 3:
            cout << "Highest Scores:" << endl;
            Game::displayHighScores();
            break;
        case 4:
            cout << "About Us" << endl;
            cout << "Developed by Umar and Zain" << endl;
            cout << "CS-Department Fast NUCES" << endl;
            break;
        case 5:
            cout << "Exiting game. Goodbye!" << endl;
            return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
        cout << "1. Start Game\n2. Options\n3. Highest Scores\n4. About Us\n5. Exit" << endl;
    }
    return 0;
}