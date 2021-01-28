#include <iostream>

#include <map>

#include <math.h>

#include <cstring>

#include <string>

#include <stdlib.h>

#include <stdio.h>

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

string whatsNext(string sentence) {
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

string getWord(string & sentence) {
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

bool isNotMult(int currentNumber) {
  return (currentNumber != 100 && currentNumber != 1000 && currentNumber != pow(10, 6) && currentNumber != pow(10, 9));
}

bool isMult(int currentNumber) {
  return (currentNumber == 100 || currentNumber == 1000 || currentNumber == pow(10, 6) || currentNumber == pow(10, 9));
}

bool calcular_numero(int & totalWords, string currentword, string & income, string & result) {
  string word, nextWord;
  int currentNumber = 0;
  int multiplied = 1;
  int finalNumber = 0;
  if (totalWords == 1) {
    word = getWord(income);
    if (isMult(numbers.find(lowerCase(word)) -> second)) // to avoid things like "hundred" in the income. It must be "one hundred"
      return 1;
    finalNumber += numbers.find(lowerCase(word)) -> second;
    result += to_string(finalNumber);
    totalWords--;
  } else if (totalWords == 2) {
    word = currentword;
    nextWord = getWord(income);

    currentNumber = numbers.find(lowerCase(word)) -> second;
    multiplied = numbers.find(lowerCase(nextWord)) -> second;

    if (numbers.find(lowerCase(nextWord)) == numbers.end()) // Cases like "I have one pizza". Pizza is not a number and should not be handled.
    {
      finalNumber += numbers.find(lowerCase(word)) -> second;
      result += to_string(finalNumber);
      result += " " + nextWord;
    } else //If both are numbers but it makes no sense (ike "one two" in the income)
    {
      if (isNotMult(multiplied))
        return 1;
    }
    finalNumber += currentNumber * multiplied;

    totalWords -= 2;
  } else {
    word = currentword;
    nextWord = getWord(income);
    cout << "Word: " << word << endl;
    cout << "nextWord: " << nextWord << endl;
    cout << "totalWords: " << totalWords << endl;

    while (totalWords / 2 > 0 && numbers.find(lowerCase(word)) -> second && numbers.find(lowerCase(nextWord)) -> second) //both are numbers. 
    {
      cout << "@@@1" << endl;
      currentNumber = numbers.find(lowerCase(word)) -> second;
      multiplied = numbers.find(lowerCase(nextWord)) -> second;

      cout << "currentNumber " << currentNumber << endl;
      cout << "multiplied " << multiplied << endl;

      if (isNotMult(multiplied)) // Cases like twenty five
      {
        finalNumber += currentNumber;
        finalNumber += multiplied;
        cout << "Entro por el notmult -> Result: " << finalNumber << endl << endl;

      } else {
        finalNumber += currentNumber * multiplied;
        cout << "Entro por el mult -> Result: " << finalNumber << endl << endl;
      }
      totalWords -= 2;

      word = getWord(income);
      nextWord = getWord(income);
      cout << "Word: " << word << endl;
      cout << "nextWord: " << nextWord << endl;

      if (totalWords == 0)
        result += to_string(finalNumber);

      if (numbers.find(lowerCase(word)) == numbers.end()) {
        finalNumber += numbers.find(lowerCase(word)) -> second;
        result += to_string(finalNumber) +" ";
      }
      
      if(numbers.find(lowerCase(word)) != numbers.end() && isMult(numbers.find(lowerCase(word))->second)) // one hundred thousand one
      {
          finalNumber = finalNumber*numbers.find(lowerCase(word))->second;
          word=nextWord;
          nextWord = getWord(income);
          totalWords --;
      }
    }
    if (numbers.find(lowerCase(word)) -> second && numbers.find(lowerCase(nextWord)) == numbers.end()) {
      cout << "@@@2" << endl;
      finalNumber += numbers.find(lowerCase(word)) -> second;
      result += to_string(finalNumber);
      result += " " + nextWord;
      cout << "result parcial: " << result << endl;
      totalWords -= 2;
    }
    
    if (numbers.find(lowerCase(word)) == numbers.end() && numbers.find(lowerCase(nextWord)) == numbers.end() && totalWords > 1)
    {
        cout<<"@@@5" <<endl;
        result += word +" " + nextWord+" ";
        totalWords -= 2;
    }

    if (totalWords == 1) {
      word = getWord(income);
      cout << "@@@3 " << word << endl;

      if (numbers.find(word) == numbers.end()) //Case: I have one peperonni pizza
      {
        cout << "@@@4" << endl;
        result += " " + word;
        totalWords--;
      } else {

        if (isMult(numbers.find(lowerCase(word)) -> second)) //"One hundred thousand" situation
        {
          finalNumber *= numbers.find(lowerCase(word)) -> second;
          totalWords--;
          result += to_string(finalNumber);
        } else {
          finalNumber += numbers.find(lowerCase(word)) -> second;
          totalWords--;
          result += to_string(finalNumber);
        }
      }
    }

  }

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
  while (totalWords > 0) {
    word = getWord(income);
    if (numbers.find(lowerCase(word)) == numbers.end()) {
      result += word;
      result += ' ';
      totalWords--;
    } else {
      error = calcular_numero(totalWords, word, income, result);
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