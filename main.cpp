#include <iostream>
#include <map>
#include <math.h>
#include <cstring>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

using namespace std;

map < string, int > numbers;

void fillMap() {
    numbers["one"] = 1;
    numbers["two"] = 2;
    numbers["three"] = 3;
    numbers["four"] = 4;
    numbers["five"] = 5;
    numbers["six"] = 6;
    numbers["seven"] = 7;
    numbers["eight"] = 8;
    numbers["nine"] = 9;
    numbers["ten"] = 10;
    numbers["eleven"] = 11;
    numbers["twelve"] = 12;
    numbers["thirteen"] = 13;
    numbers["fourteen"] = 14;
    numbers["fifeen"] = 15;
    numbers["sixteen"] = 16;
    numbers["seventeen"] = 17;
    numbers["eighteen"] = 18;
    numbers["nineteen"] = 19;
    numbers["twenty"] = 20;
    numbers["thirty"] = 30;
    numbers["forty"] = 40;
    numbers["fifty"] = 50;
    numbers["sixty"] = 60;
    numbers["seventy"] = 70;
    numbers["eighty"] = 80;
    numbers["ninety"] = 90;
    numbers["hundred"] = 100;
    numbers["thousand"] = 1000;
    numbers["million"] = pow(10, 6);
    numbers["billion"] = pow(10, 9);
}

string lowerCase(string s) {
    for (uint pos = 0; pos < s.length(); pos++)
        s[pos] = tolower(s[pos]);

    return s;
}

string getWord(string& sentence) {
    string word = "";
    for (int pos = 0; pos < sentence.length(); pos++) {
        if (sentence[pos] == ' ') {
            sentence = sentence.substr(sentence.find_first_of(" \t") + 1);
            return word;
        }

        word += sentence[pos];

    }

    sentence = sentence.substr(sentence.find_first_of(" \t") + 1);
    return word;
}

int calculateWords(string income) {
    int totalWords = 0;
    for (int pos = 0; pos < income.length(); pos++) {
        if (income[pos] == ' ' && income[pos + 1] != ' ')
            totalWords++;

    }
    totalWords++;

    return totalWords;
}

bool isMult(int currentNumber) {
    return (currentNumber == 100 || currentNumber == 1000 || currentNumber == pow(10, 6) || currentNumber == pow(10, 9));
}

bool calculate_number(int& totalWords, string& currentword, string& income, string& result) {
    string word;
    int currentNumber = 0;
    int finalNumber = 0;
    vector < int > calc;
    vector < int > temp;
    vector < int > sum;

    word = currentword;
    
    //We get all the numbers provided
    while (numbers.find(word) != numbers.end() and totalWords > 0) {
        calc.push_back(numbers.find(word) -> second);
        totalWords--;
        word = getWord(income);
    }
    
    //If there is more words that are not numbers, we return them. 
    if (totalWords > 0) 
        currentword = word;
        
    //Calculation of the number 
    for (int a = 0; a < calc.size(); a++) {
        if (isMult(calc[0]))
            return 1;
        else {
            if (isMult(calc[a])) {
                for (int p = 0; p < temp.size(); p++) 
                    currentNumber += temp[p];
                
                temp.clear();
                if (currentNumber != 0)
                    currentNumber *= calc[a];
                else
                    currentNumber = calc[a];
                    
                sum.push_back(currentNumber);
                currentNumber = 0;
            } else {
                temp.push_back(calc[a]);
            }
        }
    }

    if (temp.size() > 0) {
        for (int a = 0; a < temp.size(); a++)
            sum.push_back(temp[a]);
    }

    for (int a = 0; a < sum.size() - 1; a++) {

        if (sum[a] > sum[a + 1]) {
            finalNumber += sum[a];
        } else {
            while (sum[a] <= sum[a + 1]) {

                sum[a] = sum[a] * 10;
            }
            finalNumber += sum[a];

        }
    }
    finalNumber += sum[sum.size() - 1];
    result += to_string(finalNumber) + " ";

    return 0;
}

int main() {
    //Map filled with possible numbers up to 10^9
    fillMap();

    //Number in string format asked to the user. It is then lower cased to match the map. 
    string income;
    bool error = 0;
    cout << "Insert the sentence with a number (string)" << endl;

    std::getline(std::cin, income);

    //Calculating the number of words introduced by the user. 
    int totalWords = calculateWords(income);

    string word, nextWord;
    string lowerCaseWord, lowerCaseNextWord;
    string result = "";

    //We do not handle words that are nor numbers. 
    word = getWord(income);
    while (totalWords > 0) {

        if (numbers.find(lowerCase(word)) == numbers.end()) {
            result += word;
            result += ' ';
            totalWords--;
            word = getWord(income);
        } else {
            error = calculate_number(totalWords, word, income, result);
        }

    }

    if (error == 1) {
        result = "Wrong number provided";
        totalWords = 0;
    }
    while (totalWords > 0) {
        result += word;
        result += ' ';
        totalWords--;
    }

    cout << "RESULT: " << result << endl;

    return 0;
}
