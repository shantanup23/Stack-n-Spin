#include "Highstakes.hpp"
#include<iostream>
#include<random>
#include<algorithm>
using namespace std;
Highstakes::Highstakes(const string& name, double balance)
    : playerName(name), initialBalance(balance) {}
string Highstakes::getName() const {
    return "Highstakes";
}
void Highstakes::printCard(const Card& card) const {
    cout << card.rank << " of " << card.suit << " (value "<< card.value<< ")" <<endl;
}
int Highstakes::cardValue(const string &rank) const {
    if(rank=="A"){
        return 14;
    }
    else if(rank=="Q"){
        return 12;
    }
    else if(rank=="K") return 13;
    else if(rank=="J") return 11;
    else return stoi(rank);
}
void Highstakes::initializeDeck() {
    static const vector<string> ranks = {
        "2","3","4","5","6","7","8","9","10","J","Q","K","A"
    };
    static const vector<string> suits = {
        "Hearts","Diamonds","Clubs","Spades"
    };
    deck.clear();
    for (const auto& suit : suits) {
        for (const auto& rank : ranks) {
            deck.push_back({rank,suit,cardValue(rank)});
        }
    }
}

void Highstakes::shuffleDeck() {
    random_device rd;
    mt19937 gen(rd());
    shuffle(deck.begin(), deck.end(), gen);
}
Card Highstakes::dealCard() {
    Card card = deck.back();
    deck.pop_back();
    return card;
}






void Highstakes::play(double& playerBalance){
    cout<<"Hey there, "<<playerName<<"! Welcome to Highstakes.."<<endl;
    cout<<"Your current balance is : $"<<playerBalance<<endl;
    double bet;
    cout<<"Enter Your bet : $";
    cin>>bet;
    if(bet<=0||bet>playerBalance) {
        cout<<"Invalid bet! Check your balance and try again."<<endl;
        return;
    }
    initializeDeck();
    shuffleDeck();
    Card playerCard=dealCard();
    Card dealerCard=dealCard();
    cout<<"Your card is : ";
    printCard(playerCard);
    cout<<endl;
    cout<<"Dealer's card is : ";
    printCard(dealerCard);
    cout<<endl;
    int playerval = playerCard.value;
    int dealerval = dealerCard.value;
    if(playerval>dealerval) {
        cout<<"Dealer: You win! You're riding high on luck today!"<<endl;
        playerBalance+=bet;
    }
    else if(playerval<dealerval) {
        cout<<"Dealer : I win!! The house always smiles.."<<endl;
        playerBalance-=bet;
    }
    else{
        cout<<"Dealer : It's a Tie!! Luck's playing fair today."<<endl;

    } 
    cout<<"Your current Balance : $"<<playerBalance<<endl;




}