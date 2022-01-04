#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

std::string HelloWorld()
{
    return "Hello World!\n";
}

std::vector<int>SortedIntArray(std::vector<int> arr)
{
    std::sort(arr.begin(), arr.end());
    return arr;
}

std::vector<std::string>SortedStrArray(std::vector<std::string> arr)
{
    std::sort(arr.begin(), arr.end());
    return arr;
}

std::string PokerHand_Hexadecimal(std::string card)
{
    //Converts the cards into hexadecimal format
    std::string hexadecimal = "0x";
    if(card.substr(0, 2) == "10")
    {
        //Special case since 10 has 2 characters
        if(card.substr(3) == "Diamond")
        {
            hexadecimal += "1";
        }
        if(card.substr(3) == "Club")
        {
            hexadecimal += "2";
        }
        if(card.substr(3) == "Heart")
        {
            hexadecimal += "3";
        }
        if(card.substr(3) == "Spade")
        {
            hexadecimal += "4";
        }
        hexadecimal += "0a";
    }
    else
    {
        //Suits
        if(card.substr(2) == "Diamond")
        {
            hexadecimal += "1";
        }
        if(card.substr(2) == "Club")
        {
            hexadecimal += "2";
        }
        if(card.substr(2) == "Heart")
        {
            hexadecimal += "3";
        }
        if(card.substr(2) == "Spade")
        {
            hexadecimal += "4";
        }
        //Ranks
        if(card.substr(0, 1) == "2")
        {
            hexadecimal += "02";
        }
        if(card.substr(0, 1) == "3")
        {
            hexadecimal += "03";
        }
        if(card.substr(0, 1) == "4")
        {
            hexadecimal += "04";
        }
        if(card.substr(0, 1) == "5")
        {
            hexadecimal += "05";
        }
        if(card.substr(0, 1) == "6")
        {
            hexadecimal += "06";
        }
        if(card.substr(0, 1) == "7")
        {
            hexadecimal += "07";
        } 
        if(card.substr(0, 1) == "8")
        {
            hexadecimal += "08";
        }
        if(card.substr(0, 1) == "9")
        {
            hexadecimal += "09";
        }
        if(card.substr(0, 1) == "J")
        {
            hexadecimal += "0b";
        }
        if(card.substr(0, 1) == "Q")
        {
            hexadecimal += "0c";
        }
        if(card.substr(0, 1) == "K")
        {
            hexadecimal += "0d";
        }
        if(card.substr(0, 1) == "A")
        {
            hexadecimal += "0e";
        }
    }
    return hexadecimal;
}

std::string PokerHand_Ranking(std::vector<std::string> pokerhand_hexadecimal)
{
    std::vector<std::string> sorted_pokerhand_hexadecimal = SortedStrArray(pokerhand_hexadecimal);
    std::vector<std::string> rank, sorted_rank;
    std::vector<bool> same_rank(5, false);
    std::vector<bool> consecutive_rank(5, false);
    std::vector<bool> same_suit(5, false);
    std::string royals[5] = {"a", "b", "c", "d", "e"};
    std:vector<std::string> royal_ranks(royals, royals+5);
    int card_rank, next_card_rank, num_same_rank, num_same_suit, num_consecutive_ranks, first_four, last_four;
    for(int a = 0; a < sorted_pokerhand_hexadecimal.size(); a++)
    {
        rank.push_back(sorted_pokerhand_hexadecimal[a].substr(4));
        for(int b = 1; b < sorted_pokerhand_hexadecimal.size()-a; b++)
        {
            if(sorted_pokerhand_hexadecimal[a][2] == sorted_pokerhand_hexadecimal[a+b][2])
            {
                same_suit[a] = same_suit[a+b] = true;
            }
        }
    }
    sorted_rank = SortedStrArray(rank);
    for(int c = 0; c < sorted_rank.size()-1; c++)
    {
        card_rank = std::atoi(sorted_rank[c].c_str());
        next_card_rank = std::atoi(sorted_rank[c+1].c_str());
        if(card_rank + 1 == next_card_rank)
        {
            consecutive_rank[c] = consecutive_rank[c+1] = true;
        }
        if(card_rank == 0 || next_card_rank == 0)
        {
            for(int d = 0; d < royal_ranks.size(); d++)
            {
                if(sorted_rank[c+1] == royal_ranks[d])
                {
                    consecutive_rank[c] = consecutive_rank[c+1] = true;
                }
            }
        }
    }
    for(int e = 0; e < sorted_rank.size(); e++)
    {
        for(int f = 1; f < sorted_rank.size()-e; f++)
        {
            if(sorted_rank[e] == sorted_rank[e+f])
            {
                same_rank[e] = same_rank[e+f] = true;
            }
        }
    }
    num_same_rank = std::count(same_rank.begin(), same_rank.end(), true);
    first_four = std::count(same_rank.begin(), same_rank.end()-1, true);
    last_four = std::count(same_rank.begin()+1, same_rank.end(), true);
    num_same_suit = std::count(same_suit.begin(), same_suit.end(), true);
    num_consecutive_ranks = std::count(consecutive_rank.begin(), consecutive_rank.end(), true);
    if(num_same_rank == 2)
    {
        return "One Pair\n";
    }
    if(num_same_rank == 3)
    {
        return "Three Of A Kind\n";
    }
    if(num_same_rank == 4)
    {
        if((first_four == 4 && sorted_rank[1] == sorted_rank[2])|| (last_four == 4 && sorted_rank[2] == sorted_rank[3]))
        {
            return "Four of A Kind\n";
        }
        else
        {
            return "Two Pairs\n";
        }
    }
    if(num_same_rank == 5)
    {
        return "Full House\n";
    }
    if(num_same_suit != 5 && (num_consecutive_ranks == 5 || sorted_rank == royal_ranks))
    {
        return "Straight\n";
    }
    if(num_same_suit == 5 && num_consecutive_ranks != 5 && sorted_rank != royal_ranks)
    {
        return "Flush\n";
    }
    if(num_same_suit == 5 && num_consecutive_ranks == 5 && sorted_rank != royal_ranks)
    {
        return "Straight Flush\n";
    }
    if(num_same_suit == 5 && sorted_rank == royal_ranks)
    {
        return "Royal Flush\n";
    }
    else
    {
        return "High Card\n";
    }    
}

int main()
{
    std::cout << HelloWorld();

    int s;
    std::string input;
    std::vector<int> arr;
    std::vector<int> sorted_arr;
    std::cout << "List of numbers (Max = 5) to be sorted: ";
    std::getline(std::cin, input);
    std::istringstream input_string(input);
    while(input_string >> s)
    {
        arr.push_back(s);
    }
    sorted_arr = SortedIntArray(arr);
    for(int i = 0; i < sorted_arr.size(); i++)
    {
        std::cout << sorted_arr[i] << ' ';
    }
    std::cout << '\n';
    
    std::string card1, card2, card3, card4, card5;
    std::vector<std::string> pokerhand;
    std::vector<std::string> pokerhand_hexadecimal, sorted_pokerhand_hexadecimal;
    std::string pokerhand_ranking;
    std::cout << "First Card: ";
    std::getline(std::cin, card1);
    pokerhand.push_back(card1);
    pokerhand_hexadecimal.push_back(PokerHand_Hexadecimal(card1));
    std::cout << "Second Card: ";
    std::getline(std::cin, card2);
    pokerhand.push_back(card2);
    pokerhand_hexadecimal.push_back(PokerHand_Hexadecimal(card2));
    std::cout << "Third Card: ";
    std::getline(std::cin, card3);
    pokerhand.push_back(card3);
    pokerhand_hexadecimal.push_back(PokerHand_Hexadecimal(card3));
    std::cout << "Fourth Card: ";
    std::getline(std::cin, card4);
    pokerhand.push_back(card4);
    pokerhand_hexadecimal.push_back(PokerHand_Hexadecimal(card4));
    std::cout << "Fifth Card: ";
    std::getline(std::cin, card5);
    pokerhand.push_back(card5);
    pokerhand_hexadecimal.push_back(PokerHand_Hexadecimal(card5));
    std::cout << "Poker hand in hexadecimal format: ";
    for(int j = 0; j < pokerhand_hexadecimal.size(); j++)
    {
        std::cout << pokerhand_hexadecimal[j] << " ";
    }
    std::cout << "\n";
    sorted_pokerhand_hexadecimal = SortedStrArray(pokerhand_hexadecimal);
    std::cout << "Poker hand in hexadecimal format (sorted): ";
    for(int k = 0; k < sorted_pokerhand_hexadecimal.size(); k++)
    {
        std::cout << sorted_pokerhand_hexadecimal[k] << " ";
    }
    std::cout << "\n";
    pokerhand_ranking = PokerHand_Ranking(pokerhand_hexadecimal);
    std::cout << pokerhand_ranking;
}
