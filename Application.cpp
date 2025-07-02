// Application.cpp

#include<iostream>
#include "Bank.h"

int main()
{
    // Create All Banks
    Banks::LoadBanks();

    // Choosing Bank... 
    int choice{};
    while (choice != 4)
    {
        std::cout << "=======================================\n";
        std::cout << "Choose Your Bank : \n";
        std::cout << "1. SBI \n";
        std::cout << "2. ICICI \n";
        std::cout << "3. HDFC \n";
        std::cout << "4. Exit\n";
        std::cout << "Enter Your Choice : ";
        std::cin >> choice;
        std::cout << "=======================================\n";

        Bank* b;
        switch (choice)
        {
        case 1: std::cout << "It's Lunch Break!! 😂\n"; break; // Just For fun !
        case 2:
                b = Banks::GetBank("ICICI"); 
                //Go to Choosen Bank's WebPage!
                b->WebPage(); break;
        case 3: 
                b = Banks::GetBank("HDFC");
                b->WebPage(); break;
        case 4: std::cout << "Bye Bye 👋"; break;
        default: std::cout << "InValid Choice \n";
        }
        std::cout << "=======================================\n";

    }


    std::cin.get();
    std::cin.get();

    return (0);

}