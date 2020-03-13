// Love Me, Love Me Not
// A fortune telling microgame
// Greg Anthony Ocampo
// 2/24/2020

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>


int main()
{
    srand(time(0));
    std::cout << "Hello, friend. Are you hoping for love?" << std::endl;
    
    std::cout << "---------------------------------------\n"
              << "|                                     |\n"
              << "|           Loving Daisy v1           |\n"
              << "|                                     |\n"
              << "---------------------------------------" << std::endl;
              
    std::cout << "You are alone, sitting on a hill at sunset.\n"
              << "Contemplating your secret love, you pick a\n"
              << "nearby flower and consider your romantic\n"
              << "fortune. Good luck, friend.\n" << std::endl;
    
    // Data Members
    int daisy = 12 + (rand() % 28);
    bool love = false;

    /* std::cout << "The daisy has: " << daisy << " petals." << std::endl; */
    
    for (int i = 0; i < daisy; i++)
    {
        std::cout << "Press [Enter] to pluck the flower petals.";
        std::cin.ignore();
        love = !love;
        if (love) std::cout << ":)" << std::endl;
        else std::cout << ":(" << std::endl;
    }
    
    std::cout << "Your love will ";
    if (love) std::cout << "be returned. Congratulations!" << std::endl;
    else std::cout << " not be returned. Sorry..." << std::endl;
        
    return 0;
}