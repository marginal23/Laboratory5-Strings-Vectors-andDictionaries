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
  // Limits from the general rules of the variants.
  const int maxCount = 100;
  const int maxAbsValue = 1000;
  const size_t maxTextLength = 200;
  const size_t maxKeyLength = 40;
  const int maxAsciiCode = 127;

  string part;
  if (!getline(cin, part)) {
    cout << "INVALID\n";
    return 1;
  }

  if (part == "A") {
    // Part A: convert Latin letters to lower case.
    string text;
    string result;
    if (!getline(cin, text) || text.size() > maxTextLength) {
      cout << "INVALID\n";
      return 1;
    }
    for (size_t symbolIndex = 0; symbolIndex < text.size(); ++symbolIndex) {
      if (static_cast<unsigned char>(text[symbolIndex]) > maxAsciiCode) {
        cout << "INVALID\n";
        return 1;
      }
    }

    // A new string keeps the source text unchanged.
    for (size_t symbolIndex = 0; symbolIndex < text.size(); ++symbolIndex) {
      result += static_cast<char>(
          tolower(static_cast<unsigned char>(text[symbolIndex])));
    }

    if (result.empty()) {
      cout << "EMPTY\n";
    } else {
      cout << result << "\n";
    }
  } else if (part == "B") {
    // Part B: print the elements in reverse order.
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
      // The index is shifted by one: size_t cannot go below 0.
      for (size_t valueIndex = values.size(); valueIndex > 0; --valueIndex) {
        if (valueIndex < values.size()) {
          cout << " ";
        }
        cout << values[valueIndex - 1];
      }
      cout << "\n";
    }
  } else if (part == "C") {
    // Part C: add the increment to the value of the key.
    int count;
    string key;
    int value;
    map<string, int> values;
    if (!(cin >> count) || count < 0 || count > maxCount) {
      cout << "INVALID\n";
      return 1;
    }

    // The pairs and then the query: count + 1 keys with numbers.
    for (int pairIndex = 0; pairIndex <= count; ++pairIndex) {
      if (!(cin >> key >> value) || key.size() > maxKeyLength ||
          value < -maxAbsValue || value > maxAbsValue) {
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
        // A repeated key keeps the last value.
        values[key] = value;
      } else {
        // A missing key starts from 0.
        values[key] += value;
      }
    }

    if (values.empty()) {
      cout << "EMPTY\n";
    } else {
      // A map has no indexes, so it is walked with an iterator in key order.
      for (auto entryIterator = values.begin(); entryIterator != values.end();
           ++entryIterator) {
        cout << entryIterator->first << " " << entryIterator->second << "\n";
      }
    }
  } else if (part == "D") {
    // Part D: names of the owners of broken addresses.
    int count;
    string name;
    string email;
    vector<map<string, string>> records;
    vector<string> fields;
    vector<string> result;
    bool valid;
    int atCount;
    bool hasSpace;
    size_t atPosition;
    bool suitable;
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

    // Every record is checked first, so INVALID never follows a partial answer.
    valid = true;
    for (size_t recordIndex = 0; recordIndex < records.size() && valid;
         ++recordIndex) {
      const map<string, string>& record = records[recordIndex];
      if (record.find("name") == record.end() ||
          record.find("email") == record.end()) {
        valid = false;
      } else {
        fields = {record.at("name"), record.at("email")};
        for (size_t fieldIndex = 0; fieldIndex < fields.size() && valid;
             ++fieldIndex) {
          const string& field = fields[fieldIndex];
          if (field.empty() || field.size() > maxTextLength ||
              field.front() == ' ' || field.back() == ' ') {
            valid = false;
          }
          for (size_t symbolIndex = 0; symbolIndex < field.size() && valid;
               ++symbolIndex) {
            if (static_cast<unsigned char>(field[symbolIndex]) > maxAsciiCode) {
              valid = false;
            }
          }
        }
      }
    }
    if (!valid) {
      cout << "INVALID\n";
      return 1;
    }

    for (size_t recordIndex = 0; recordIndex < records.size(); ++recordIndex) {
      email = records[recordIndex].at("email");
      atCount = 0;
      hasSpace = false;
      for (size_t symbolIndex = 0; symbolIndex < email.size(); ++symbolIndex) {
        if (email[symbolIndex] == '@') {
          ++atCount;
        }
        if (email[symbolIndex] == ' ') {
          hasSpace = true;
        }
      }
      atPosition = email.find('@');
      suitable = atCount == 1 && !hasSpace && atPosition > 0 &&
                 atPosition + 1 < email.size();
      if (!suitable) {
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
