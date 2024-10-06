#include <iostream>
#include <limits>
#include <optional>
#include <functional>
#include <string>
#include <sstream> 

using namespace std;

template<typename T>
T prompt_and_read(const string& prompt_message) {
    T value;
    cout << prompt_message << endl;
    cin >> value;
    return value;
}

template<typename T>
bool input_is_valid(T value, optional<T> lower_bound, optional<T> upper_bound, function<bool(T)> custom_validation) {
    if (cin.fail() || (lower_bound && value < lower_bound.value()) || (upper_bound && value > upper_bound.value()) || (custom_validation && !custom_validation(value))) {
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
    return true;
}

template<typename T>
T prompt(optional<T> lower_bound, optional<T> upper_bound, const string& prompt_message, const string& error_message, optional<T> default_value, function<bool(T)> custom_validation = nullptr) {
    T value;
    string input;
    while (true) {
        cout << prompt_message << " Enter \"default\" to use the default value of " << default_value.value_or(T()) << "." << endl;
        cin >> input;
        if (input == "default" && default_value) {
            return default_value.value();
        }
        std::stringstream ss(input);
        ss >> value;
        if (input_is_valid(value, lower_bound, upper_bound, custom_validation)) {
            break;
        } else {
            cout << error_message << endl;
        }
    }
    return value;
}

template<typename T>
T get_user_input(optional<T> lower_bound, optional<T> upper_bound, const string& prompt_message, const string& error_message, optional<T> default_value = nullopt, function<bool(T)> custom_validation = nullptr) {
    return prompt<T>(lower_bound, upper_bound, prompt_message, error_message, default_value, custom_validation);
}

// compiling the program: g++ -o main.exe main.cpp takes a bit of time to print in the console but it works
int main() {
   int value = get_user_input<int>(0, 100, "Please enter a value between 0 and 100", "Your value is invalid", 100);
   cout << "The value chosen by the user is " << value << endl;
   return 0;
}