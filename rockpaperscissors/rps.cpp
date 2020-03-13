// Rock, Paper, Scissors
// A microgame
// by Greg Anthony Ocampo

// start game with interface
// options - save and quit, play
// save and quit - saves wins, losses, and ties to rps_gamerecord file

#include <cctype>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <iostream>

void hud_stats(int w, int l, int t)
{
    std::cout << "---------------------------------------------\n"
              << "|       Wins: " << w << " | Losses: " << l << " | Ties: " << t << "       |\n"
              << "---------------------------------------------" << std::endl;
}

void interface()
{
    std::cout << "=============================================\n"
              << "|  - [1] : Play a game.                     |\n"
              << "|  - [2] : Quit.                            |\n"
              << "=============================================\n"
              << " Enter your choice here:  ";
}

void game_hud()
{
    std::cout << "---------------------------------------------\n"
              << "|    Pick rock, paper, or scissors!         |\n"
              << "|  - [R] : Rock                             |\n"
              << "|  - [P] : Paper                            |\n"
              << "|  - [S] : Scissors                         |\n"
              << "=============================================\n"
              << " Enter your choice here:  ";
}

int main()
{
    srand(time(0));
    
    std::cout << "\n           Rock, Paper, Scissors v1" << std::endl;

    // data members
    int wins = 0;
    int losses = 0;
    int ties = 0;
    char input;
    bool quit = 0;
    bool isValid = 0;
    int cpu;
    char cpu_choice;

    // open/create a savefile
    std::ifstream loadfile;
    loadfile.open("rps_gamerecord");
    loadfile >> wins;
    loadfile.ignore(1000, '\n');
    loadfile >> losses;
    loadfile.ignore(1000, '\n');
    loadfile >> ties;
    loadfile.ignore(1000, '\n');
    loadfile.close();
    
    while (!quit)
    {
        hud_stats(wins, losses, ties);
        isValid = 0;
        
        // input and validation
        while (!isValid)
        {
            interface();
            std::cin >> input;
            std::cin.ignore(1000, '\n');
            if (input == '1' || input == '2') isValid = 1;
            else
            {
                std::cout << "Please only enter [1] or [2]!\n"
                          << "Press [Enter] to continue.\n";
                std::cin.ignore();
            }           
        }
        isValid = 0;
        
        if (input == '2') quit = 1;
        else // game
        {
            while (!isValid)
            {
                // game hud
                game_hud();
                // input and validation, convert input tolower
                std::cin >> input;
                std::cin.ignore(1000, '\n');
                input = toupper(input);
                if (input == 'R' || input == 'P' || input == 'S') isValid = 1;
                else
                {
                    std::cout << "Please only enter [R], [P], or [S]!\n"
                              << "Press [Enter] to continue.\n";
                    std::cin.ignore();
                }
            }
            
            std::cout << "    You picked ";
            if (input == 'R') std::cout << "rock!" << std::endl;
            else if (input == 'P') std::cout << "paper!" << std::endl;
            else std::cout << "scissors!" <<std::endl;
            
            // computer choice
            cpu = (rand() % 100) % 3;
            if (cpu == 0) cpu_choice = 'R';
            else if (cpu == 1) cpu_choice = 'P';
            else cpu_choice = 'S';
            std::cout << "    The computer chose ";
            if (cpu_choice == 'R') std::cout << "rock!" << std::endl;
            else if (cpu_choice == 'P') std::cout << "paper!" << std::endl;
            else std::cout << "scissors!" <<std::endl;
            
            // resolve choices
            // player tie
            if (cpu_choice == input)
            {
                std::cout << "  You tied with the computer!" << std::endl;
                ++ties;
            }
            else
            {
                if (input == 'R') 
                {
                    if (cpu_choice == 'P')
                    {
                        std::cout << "  You lost to the computer!\n";
                        ++losses;
                    }
                    else
                    {
                        std::cout << "  You won against the computer!\n";
                        ++wins;
                    }
                }
                else if (input == 'P')
                {
                    if (cpu_choice == 'S')
                    {
                        std::cout << "  You lost to the computer!\n";
                        ++losses;
                    }
                    else
                    {
                        std::cout << "  You won against the computer!\n";
                        ++wins;
                    }
                }
                else
                {
                    if (cpu_choice == 'R')
                    {
                        std::cout << "  You lost to the computer!\n";
                        ++losses;
                    }
                    else
                    {
                        std::cout << "  You won against the computer!\n";
                        ++wins;
                    }
                }
                
            }
            std::cout << "  Press [Enter] to continue.\n";
            std::cin.ignore();
        } // end of game
    }
    
    std::cout << "    Quitting Rock, Paper, Scissors!\n"
              << "    Saving game record..." << std::endl;
              
    // save to file
    std::ofstream savefile;
    savefile.open("rps_gamerecord");
    savefile << wins << '\n'
             << losses << '\n'
             << ties;
    savefile.close();
    
    return 0;
}