#include <cmath>
#include <string>
#include <iostream>
#include "Function.h"

void FindDerivative(Function& funct);
void FindAntiderivative(Function& funct);

int main()
{
    bool runProgram = true;
    int input;
    while (runProgram)
    {
        std::cout << "Select an Operation" << std::endl;
        std::cout << "--------------------" << std::endl;
        std::cout << "1. Find the Derivative" << std::endl;
        std::cout << "2. Find the Antiderivative" << std::endl;
        std::cout << "3. Exit" << std::endl;
        std::cin >> input;
        std::cin.get();

        std::string mathInput;
        if (input == 1)
        {
            std::cout << "Enter equation: " << std::endl;
            std::getline(std::cin, mathInput);
            Function funct(mathInput);
            FindDerivative(funct);
            std::cout << funct.function << std::endl;
            std::cout << std::endl;
        }
        else if (input == 2)
        {
            std::cout << "Enter equation: " << std::endl;
            std::getline(std::cin, mathInput);
            Function funct(mathInput);
            FindAntiderivative(funct);
            std::cout << funct.function << std::endl;
            std::cout << std::endl;
        }
        else if (input == 3)
        {
            runProgram = false;
            std::cout << "Thanks for using the Calc Calculator!" << std::endl;
        }
        else
            std::cout << "Invalid menu selection!" << std::endl;
    }
    return 0;
}

void FindDerivative(Function& funct)
{
    // Check each term
    for (int i = 0; i < funct.numTerms; i++)
    {
        // If term is a constant, remove
        if (funct.terms[i].hasVariable == false)
            funct.terms[i].term.clear();
        else // Otherwise, bring the power of variable to its coefficient and minus one from its power
        {
            funct.terms[i].coefficient *= funct.terms[i].power;
            funct.terms[i].power--;
        }
    }
    funct.UpdateFunction();
}

void FindAntiderivative(Function& funct)
{
    // Check each term
    for (int i = 0; i < funct.numTerms; i++)
    {
        // If term is a constant, add variable
        if (funct.terms[i].hasVariable == false)
        {
            funct.terms[i].term.append(1, funct.variable);
            funct.terms[i].hasVariable = true;
        }
        else
        {
            funct.terms[i].coefficient /= (funct.terms[i].power + 1);
            funct.terms[i].power++;
        }
    }
    funct.UpdateFunction();
    funct.function.append(" + C");
}