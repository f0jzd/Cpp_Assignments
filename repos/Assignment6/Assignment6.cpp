#include <iostream>
#include<limits> //used to get numeric limits
int main() {

    int guessedNumber, correctNumber, numberOfAttempts;
    char playAgain;
    bool correctGuess = false;


    correctNumber = rand() % 10 + 1;//Random value between 1 and 100
    //std::cout << correctNumber << std::endl;
    std::cout << "Hello, welcome to guessing game!" << std::endl;
    std::cout << "Input your guess: ";


    while (!correctGuess)
    {
        std::cin >> guessedNumber;
        numberOfAttempts++;
        while (!std::cin >> guessedNumber)
        {
            std::cout << "Faulty input, try another" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin >> guessedNumber;
        }

        if (guessedNumber == correctNumber)
        {
            std::cout << "You won! it took you " << numberOfAttempts << " to win" << std::endl;
            std::cout << "Play again? y/n " << std::endl;
            std::cin >> playAgain;
            while (playAgain != 'y' && playAgain != 'n')
            {
                std::cout << "Faulty input, try another" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin >> playAgain;
            }
            if (playAgain == 'y')
            {
                numberOfAttempts = 0;
                correctNumber = rand() % 10 + 1;//Random value between 1 and 100
                std::cout << "Input your guess: ";
            }
            if (playAgain == 'n')
            {
                correctGuess = true;
                break;
            }
        }
        else
        {
            std::cout << "Wrong" << std::endl;
        }

    }
}
