//
//  main.cpp
//  Memory
//
//  Created by Jay Mishra on 9/20/18.
//  Copyright © 2018 Jay Mishra. All rights reserved.
//

#include <iostream>     //Needed to print to the command line
#include <vector>       //Needed to use the STL vector data structure
#include <algorithm>    //Needed to be able to call shuffle()
#include <random>       //Needed to be able to create a random engine
#include <chrono>       //Needed to be able to create the seed for the random engine

using namespace std;

struct card {
    char m_face;
    char m_value;
    bool m_revealed;
};
card cards[20];
vector<int> cardNums;

char assignValue(int i) {
    if (i == 1 || i == 2)
        return '!';
    if (i == 3 || i == 4)
        return '@';
    if (i == 5 || i == 6)
        return '&';
    if (i == 7 || i == 8)
        return '#';
    if (i == 9 || i == 10)
        return '$';
    if (i == 11 || i == 12)
        return '*';
    if (i == 13 || i == 14)
        return '+';
    if (i == 15 || i == 16)
        return '~';
    if (i == 17 || i == 18)
        return '%';
    if (i == 19 || i == 20)
        return '^';
    return 'a';
}

bool allRevealed() {
    for(int i = 0; i < 20; i++) {
        if(cards[i].m_revealed == false)
            return false;
    }
    return true;
}

bool validInput(string input) {
    return !(input.size() != 3 || input[0] < 'A' || input[0] > 'T' || input[1] != ':' || input[2] < 'A' || input[2] > 'T');
}

void render(char first, char second) {
    for(int i = 0; i < 20; i++) {
        if(cards[i].m_revealed == true)
            cout << "    ";
        else if(first == cards[i].m_face || second == cards[i].m_face)
            cout << '[' << cards[i].m_value << "] ";
        else
            cout << '[' << cards[i].m_face << "] ";
        if((i + 1) % 5 == 0)
            cout << endl;
    }
    cout << endl << endl;
}

int main(int argc, const char * argv[]) {
    
    for (int i=1; i<21; ++i)
        cardNums.push_back(i);
    
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    
    auto rng = std::default_random_engine(seed);
    
    std::shuffle(cardNums.begin(), cardNums.end(), rng);
    
    for(int i = 0; i < 20; i++) {
        cards[i].m_revealed = false;
        cards[i].m_face = 'A' + i;
        cards[i].m_value = assignValue(cardNums[i]);
    }
    
    cout << " __  __ ______ __  __  ____  _______     __      _____ _      _____" << endl;
    cout << "|  \\/  |  ____|  \\/  |/ __ \\|  __ \\ \\   / /     / ____| |    |_   _|" << endl;
    cout << "| \\  / | |__  | \\  / | |  | | |__) \\ \\_/ /_____| |    | |      | |" << endl;
    cout << "| |\\/| |  __| | |\\/| | |  | |  _  / \\   /______| |    | |      | |" << endl;
    cout << "| |  | | |____| |  | | |__| | | \\ \\  | |       | |____| |____ _| |_" << endl;
    cout << "|_|  |_|______|_|  |_|\\____/|_|  \\_\\ |_|        \\_____|______|_____|" << endl << endl;
    
    cout << "Welcome to Memory-CLI, a memory game that you can play in your terminal! \n\nThere are 10 pairs of cards for you to match, each with a cardback \nranging from A-T and a concealed symbol (the symbols used are !, @, #, $, %, ^, &, *, ~, and +). \n\nSpecify which two cards you want to match by typing in your choices like this: \nfirst_cardback:second_cardback (i.e. A:B, D:R, etc.). \n\nYour score will be given to you at the end of the game. \n\nPress q at any time to quit. Enjoy!" << endl;
    
    int turns = 0;
    
    while(allRevealed() == false) {
        render('Z', 'Z');
        cout << "Enter your match selection using the format first_cardback:second_cardback or enter q to quit.";
        string choice;
        if(!std::getline(cin, choice)) { /* I/O error! */ return -1; }
        string formattedChoice = "";
        for(int i = 0; i < choice.size(); i++)
            formattedChoice += toupper(choice[i]);
        if(formattedChoice == "Q") {
            cout << endl << "Thanks for playing Memory-CLI! Bye!" << endl;
            return 0;
        } else if(!validInput(formattedChoice)) {
            cout << "Sorry, the input you entered is invalid. Please use the format first_cardback:second_cardback. \nPress ENTER to continue.";
            string enter;
            if(!std::getline(cin, enter)) { /* I/O error! */ return -1; }
            cout << "\033[2J\033[1;1H" << endl;
            continue;
        } else {
            turns++;
            cout << "\033[2J\033[1;1H" << endl;
            render(formattedChoice[0], formattedChoice[2]);
            int num1, num2;
            char val1, val2;
            for(int i = 0; i < 20; i++) {
                if(cards[i].m_face == formattedChoice[0]) {
                    val1 = cards[i].m_value;
                    num1 = i;
                } else if(cards[i].m_face == formattedChoice[2]) {
                    val2 = cards[i].m_value;
                    num2 = i;
                }
            }
            if(val1 == val2) {
                cout << "Congrats! You got a match!" << endl;
                cards[num1].m_revealed = true;
                cards[num2].m_revealed = true;
            } else {
                cout << "Sorry, your selected cards don't match." << endl;
            }
            cout << "Press ENTER to continue." << endl;
            string enter;
            if(!std::getline(cin, enter)) { /* I/O error! */ return -1; }
            cout << "\033[2J\033[1;1H" << endl;
        }
    }
    
    cout << "Congratulations! You finished the game in " << turns << " turns! \n\nThanks for playing Memory-CLI! Bye!" << endl;
}
