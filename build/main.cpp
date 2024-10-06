#include <iostream>
#include <limits>
#include <optional>
#include <functional>

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
T prompt(optional<T> lower_bound, optional<T> upper_bound, const string& prompt_message, const string& error_message, function<bool(T)> custom_validation = nullptr) {
    T value;
    while (true) {
        value = prompt_and_read<T>(prompt_message);
        if (input_is_valid(value, lower_bound, upper_bound, custom_validation)) {
            break;
        } else {
            cout << error_message << endl;
        }
    }
    return value;
}

template<typename T>
T get_user_input(optional<T> lower_bound, optional<T> upper_bound, const string& prompt_message, const string& error_message, function<bool(T)> custom_validation = nullptr) {
    return prompt<T>(lower_bound, upper_bound, prompt_message, error_message, custom_validation);
}
// compiling the program: g++ -o main.exe main.cpp takes a bit of time to print in the console but it works
int main() {
   int value = get_user_input<int>(0, 100, "Please enter a value between 0 and 100", "Your value is invalid");
   cout << "The value chosen by the user is " << value << endl;
   return 0;
}