/******************************************************************
* Автор:   Сатин Владимир                                         *
* Группа:  ПИ-261                                                 *
* Задание: Лабораторная работа 5: строки, векторы и словари в C++ *
* Вариант: 10                                                     *
******************************************************************/

#include <cctype>
#include <iostream>
#include <limits>
#include <map>
#include <string>
#include <vector>

using namespace std;

int main() {
  // Limits from the general rules of the variants
  const int maxCount = 100;
  const int maxAbsValue = 1000;
  const size_t maxTextLength = 200;
  const size_t maxKeyLength = 40;
  const int maxAsciiCode = 127;

  string partLetter;
  if (!getline(cin, partLetter)) {
    cout << "INVALID\n";
    return 1;
  }

  if (partLetter == "A") {
    // Part A: convert Latin letters to lower case
    string text;
    string result;
    unsigned char symbolCode;
    if (!getline(cin, text) || text.size() > maxTextLength) {
      cout << "INVALID\n";
      return 1;
    }

    for (size_t symbolIndex = 0; symbolIndex < text.size(); ++symbolIndex) {
      symbolCode = static_cast<unsigned char>(text[symbolIndex]);
      if (symbolCode > maxAsciiCode) {
        cout << "INVALID\n";
        return 1;
      }
    }

    // A new string keeps the source text unchanged
    for (size_t symbolIndex = 0; symbolIndex < text.size(); ++symbolIndex) {
      symbolCode = static_cast<unsigned char>(text[symbolIndex]);
      result += static_cast<char>(tolower(symbolCode));
    }

    if (result.empty()) {
      cout << "EMPTY\n";
    } else {
      cout << result << "\n";
    }
  } else if (partLetter == "B") {
    // Part B: print the elements in reverse order
    int count;
    int value;
    vector<int> values;
    if (!(cin >> count) || count < 0 || count > maxCount) {
      cout << "INVALID\n";
      return 1;
    }

    for (int valueIndex = 0; valueIndex < count; ++valueIndex) {
      if (!(cin >> value) || value < -maxAbsValue || value > maxAbsValue) {
        cout << "INVALID\n";
        return 1;
      }

      values.push_back(value);
    }

    if (values.empty()) {
      cout << "EMPTY\n";
    } else {
      // The index is shifted by one: size_t cannot go below 0
      for (size_t valueIndex = values.size(); valueIndex > 0; --valueIndex) {
        if (valueIndex < values.size()) {
          cout << " ";
        }

        cout << values[valueIndex - 1];
      }

      cout << "\n";
    }
  } else if (partLetter == "C") {
    // Part C: add the increment to the value of the key
    int count;
    string key;
    int value;
    bool isValueValid;
    bool isKeyLengthValid;
    map<string, int> values;
    map<string, int>::iterator entryIterator;
    if (!(cin >> count) || count < 0 || count > maxCount) {
      cout << "INVALID\n";
      return 1;
    }

    // The pairs and then the query: count + 1 keys with numbers
    for (int pairIndex = 0; pairIndex <= count; ++pairIndex) {
      if (!(cin >> key >> value)) {
        cout << "INVALID\n";
        return 1;
      }

      isValueValid = value >= -maxAbsValue && value <= maxAbsValue;
      isKeyLengthValid = key.size() <= maxKeyLength;
      if (!isValueValid || !isKeyLengthValid) {
        cout << "INVALID\n";
        return 1;
      }

      for (size_t symbolIndex = 0; symbolIndex < key.size(); ++symbolIndex) {
        if (static_cast<unsigned char>(key[symbolIndex]) > maxAsciiCode) {
          cout << "INVALID\n";
          return 1;
        }
      }

      if (pairIndex < count) {
        // A repeated key keeps the last value
        values[key] = value;
      } else {
        // A missing key starts from 0
        values[key] += value;
      }
    }

    if (values.empty()) {
      cout << "EMPTY\n";
    } else {
      // A map has no indexes, so it is walked with an iterator in key order
      for (entryIterator = values.begin(); entryIterator != values.end(); ++entryIterator) {
        cout << entryIterator->first << " " << entryIterator->second << "\n";
      }
    }
  } else if (partLetter == "D") {
    // Part D: names of the owners of broken addresses
    int count;
    string name;
    string email;
    string field;
    vector<map<string, string>> records;
    vector<string> fields;
    vector<string> result;
    bool isValid;
    bool isEmailValid;
    bool hasSpace;
    int atSignCount;
    size_t atSignPosition;
    if (!(cin >> count) || count < 0 || count > maxCount) {
      cout << "INVALID\n";
      return 1;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    for (int recordIndex = 0; recordIndex < count; ++recordIndex) {
      if (!getline(cin, name) || !getline(cin, email)) {
        cout << "INVALID\n";
        return 1;
      }

      records.push_back({{"name", name}, {"email", email}});
    }

    // Every record is checked first, so INVALID never follows a partial answer
    isValid = true;
    for (size_t recordIndex = 0; recordIndex < records.size() && isValid; ++recordIndex) {
      fields = {records[recordIndex].at("name"), records[recordIndex].at("email")};
      for (size_t fieldIndex = 0; fieldIndex < fields.size() && isValid; ++fieldIndex) {
        field = fields[fieldIndex];
        if (field.empty() || field.size() > maxTextLength) {
          isValid = false;
        } else if (field.front() == ' ' || field.back() == ' ') {
          isValid = false;
        }

        for (size_t symbolIndex = 0; symbolIndex < field.size() && isValid; ++symbolIndex) {
          if (static_cast<unsigned char>(field[symbolIndex]) > maxAsciiCode) {
            isValid = false;
          }
        }
      }
    }

    if (!isValid) {
      cout << "INVALID\n";
      return 1;
    }

    for (size_t recordIndex = 0; recordIndex < records.size(); ++recordIndex) {
      email = records[recordIndex].at("email");
      atSignCount = 0;
      hasSpace = false;
      for (size_t symbolIndex = 0; symbolIndex < email.size(); ++symbolIndex) {
        if (email[symbolIndex] == '@') {
          ++atSignCount;
        }

        if (email[symbolIndex] == ' ') {
          hasSpace = true;
        }
      }

      // The position matters only when there is exactly one '@'
      atSignPosition = email.find('@');
      isEmailValid = atSignCount == 1 && !hasSpace;
      if (isEmailValid) {
        isEmailValid = atSignPosition > 0 && atSignPosition + 1 < email.size();
      }

      if (!isEmailValid) {
        result.push_back(records[recordIndex].at("name"));
      }
    }

    if (result.empty()) {
      cout << "EMPTY\n";
    } else {
      for (size_t nameIndex = 0; nameIndex < result.size(); ++nameIndex) {
        cout << result[nameIndex] << "\n";
      }
    }
  } else {
    cout << "INVALID\n";
    return 1;
  }

  return 0;
}
