#include <iostream>
#include <windows.h>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

// print elemnt of vector in one line
void printVector(const vector<string>& vec) {
    for (size_t i = 0; i < vec.size(); ++i) {
        cout << vec[i];

        // if size of vec is equal to 1 don't print "Q+ key is pressed" 
        if (i < vec.size() - 1) {
            cout << "+";
        }
    }
}

// Returns the key that is in vec1 but not in vec2 (i.e., the key that was released)
// Returns Which Key is Released
// - vec1 : currently pressed key
// - vec2 : prev pressed Key
string UpKey(const vector<string>& vec1, const  vector<string>& vec2) {
    // compare two vector in foreach
    for (const auto& element : vec1) {
        if (find(vec2.begin(), vec2.end(), element) == vec2.end()) {
            // different key
            return element;
        }
    }
    
    // return Null if hit Exception
    return "";
}

// Converts a numeric key code to its string representation
// - Key code : signal of Key in Keyboard
// - return name of key in keyboard Based on Signal
string convert_key_number_to_key_value (int keyCode){

    // Map of key codes to their respective string names
    // Reference : https://cherrytree.at/misc/vk.htm
    map<int, string> keyNames = {
        {1, "Left Mouse Button"},
        {2, "Right Mouse Button"},
        {3, "Control Break"},
        {4, "Middle Mouse Button"},
        {8, "Backspace"},
        {9, "Tab"},
        /*Reserved*/
        {12, "Clear"},
        {13, "Enter"},
        /*Undefined*/
        {19, "Pause Break"},
        {20, "Caps Lock"},
        {27, "Esc"},
        /*IME Key*/
        {32, "Spacebar"},
        {33, "Page Up"},
        {34, "Page Down"},
        {35, "End"},
        {36, "Home"},
        {37, "Left Arrow"},
        {38, "Up Arrow"},
        {39, "Right Arrow"},
        {40, "Down Arrow"},
        {41, "Select"},
        {42, "Print"},
        {43, "Excecute"},
        {44, "Print Screen"},
        {45, "Insert"},
        {46, "Delete"},
        {47, "Help"},
        {48, "0"},
        {49, "1"},
        {50, "2"},
        {51, "3"},
        {52, "4"},
        {53, "5"},
        {54, "6"},
        {55, "7"},
        {56, "8"},
        {57, "9"},
        /*Undefined*/
        /*Alphabet key*/
        {91, "Left Windows"},
        {92, "Right Windows"},
        {93, "Option"},
        /*Reserved*/
        {95, "Sleep"},
        {96, "Numpad 0"},
        {97, "Numpad 1"},
        {98, "Numpad 2"},
        {99, "Numpad 3"},
        {100, "Numpad 4"},
        {101, "Numpad 5"},
        {102, "Numpad 6"},
        {103, "Numpad 7"},
        {104, "Numpad 8"},
        {105, "Numpad 9"},
        {106, "num *"},
        {107, "num +"},
        {108, "Seperator"},
        {109, "num -"},
        {110, "Decimal"},
        {111, "num /"},
        {112, "F1"},
        {113, "F2"},
        {114, "F3"},
        {115, "F4"},
        {116, "F5"},
        {117, "F6"},
        {118, "F7"},
        {119, "F8"},
        {120, "F9"},
        {121, "F10"},
        {122, "F11"},
        {123, "F12"},
        {124, "F13"},
        {125, "F14"},
        {126, "F15"},
        {127, "F16"},
        {144, "NUM Lock"},
        {145, "Scroll Lock"},
        {160, "Left Shift"},
        {161, "Right Shift"},
        {162, "Left ctrl"},
        {163, "Right ctrl"},
        {164, "Left Alt"},
        {165, "Right Alt"},
        {186, ";"},
        {187, "="},
        {188, ","},
        {189, "-"},
        {190, "."},
        {191, "/"},
        {192, "`"},
        /*Reserved*/
        {219, "["},
        {220, "\\"},
        {221, "]"},
        {222, "'"},
        {246, "Attn"},
        {247, "CrSel"},
        {248, "ExSel"},
        {249, "Erase EOF"},
        {250, "Play"},
        {251, "Zoom"},
        /*Reserved*/
        {253, "PA1"},
        {254, "Clear"},
    };

    // Search for the keyCode in the map and return its string name
    auto it = keyNames.find(keyCode);
    if (it != keyNames.end()) {
        return it->second;
    } else { // if Doesn't match print Signal
        return "Unknown Key (" + to_string(keyCode) + ")";
    }
}

int main() {

    // Tracks the previous state of each key
    bool prevKeyState[256] = {false}; 

    // Stores the currently pressed keys as a string in vector
    vector<string> currentPressedKeys;        

    // Stores the previously pressed keys for comparison
    vector<string> prevPressedKeys;           

    // Infinite loop to continuously check the state of the keys
    while (true) { 

        // reinitialize
        currentPressedKeys.clear();

        // Iterate over all key (Polling Method)
        for (int key = 0; key < 256; key++) {

            /// GetAsyncKeyState is detect Key is Up or Down
            /// - 0x8000 = is down
            /// - 0x0001 = is recently used
            // Check if the key is currently pressed
            bool keyIsPressed = (GetAsyncKeyState(key) & 0x8000) != 0;

            if (keyIsPressed) {
                
                // Specified Key on Keyboard
                string keyName;

                // Convert alphabet keys directly to characters
                if(key >= 65 && key <= 90){
                    keyName = char(key);
                } else if (key == 16 || key == 17 || key == 18){ // skip ctrl+shift+alt keys
                    continue;
                } else { // convert signal of key to his names
                    keyName = convert_key_number_to_key_value(key);
                }

                // push new pressed key to currentPressedKeys
                currentPressedKeys.push_back(keyName);
            }

            // Update the previous key state
            prevKeyState[key] = keyIsPressed;
        }

        // Check if the current pressed keys are different from the previous iteration
        if (currentPressedKeys != prevPressedKeys) {

            cout << "\n";

            // If no keys are currently pressed, display the key that was released
            if(currentPressedKeys.empty()){
                printVector(prevPressedKeys);
                std::cout << " is Up" << std::endl;
                prevPressedKeys = currentPressedKeys;
                continue;
            }

            // if recently one key is Released
            if (prevPressedKeys.size() > currentPressedKeys.size()) {

                // Detect Which Key And Display
                std::string ReleasedKey = UpKey(prevPressedKeys, currentPressedKeys);
                std::cout << ReleasedKey <<  " is Up" << std::endl;
            }

            // Display the currently pressed keys
            printVector(currentPressedKeys);
            cout << " is Pressed!" << endl;
            prevPressedKeys = currentPressedKeys;
        }

        Sleep(50); // Small delay to reduce CPU usage
    }

    return 0;
}