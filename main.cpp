/**
 *
 *
 */
using namespace std;

#include <iostream>
#include <string>
#include <cstdio>

struct RomanNumeral {
    string expression;
    bool isValid() {
        bool valid = true;
        //Check if the expression is valid
        for(unsigned int i=0; i<expression.length(); i++) {
            char current = expression.at(i);
            if(current=='I'||current=='V'||current=='X'||current=='L'||current=='C'||current=='D'||current=='M') {
                //Do nothing. Characters are valid
            } else {
                cout << "Invalid character found at position: " << i << endl;
                valid = false;
            }
        }
        return valid;
    }
};



/**
 * Loop to get user input
 * @return
 */
int get_selection() {
    int selection;
    for(;;) {
        cout << "Your Options:" << endl;
        cout << "1. Roman to Base 10" << endl;
        cout << "2. Base 10 to Roman" << endl;
        cout << "3. Add 2 Roman numbers" << endl;
        cout << "4. Exit" << endl;

        cin >> selection;

        if(!cin.fail()) {
            if(selection>=1||selection<=4) {
                return selection;
            } else {
                cout << "Invalid Input Provided. Please select again";
            }
        } else {
            cout << "Invalid Input Provided. Please select again";
        }
    }
}
/**
 * Get input from user for Roman Numeral to operate on
 * @return RomanNumeral struct containing data
 */
RomanNumeral getRomanInput() {
    cout << "Input the Roman number: ";

    RomanNumeral input;

    for(;;) {
        cin >> input.expression;

        if(!cin.fail()) {
            if(input.isValid()) {
                break;
            } else {
                cout << "Invalid input, please try again" << endl;
            }
        } else {
            cout << "Invalid input, please try again" << endl;
        }
    }


    return input;
}

/**
 * Get user input in the form of a base 10 number
 * @return int Base 10 integer user has input
 */
int getBase10Input() {
    int input;
    for(;;) {
        cout << "Enter a base 10 integer";

        cin >> input;

        if(!cin.fail()) {
            if(input>0) {
                break;
            } else {
                cout << "Invalid Input, please try again" << endl;
            }
        } else {
            cout << "Invalid Input, please try again" << endl;
        }
    }

    return input;
}


/**
 * Convert roman numeral into Base 10 integer
 * I	V	X	L	C	D	M
 * 1	5	10	50	100	500	1000
 * @param input RomanNumeral
 * @return int Base 10 equivilent
 */
int RomanToBase10(RomanNumeral input) {

    int total = 0;
    for(unsigned int i=0; i<input.expression.length(); i++) {
        char current = input.expression.at(i);

        switch(current) {
            case 'I':
                total+=1;
            case 'V':
                total+=5;
            case 'X':
                total+=10;
            case 'L':
                total+=50;
            case 'C':
                total+=100;
            case 'D':
                total+=500;
            case 'M':
                total+=1000;
            default:
                cout << "Invalid Character Detected at position " << i << endl;
        }
    }

    return total;
}

/**
 * Use modulus in this to get largest possible numbers that will divide
 */
void Base10ToRoman() {

}

void RomanAddition() {

}

void RemoveSubstractives() {

}

void AddSubstractives() {

}



int main() {

    //Hardcode your first name, last name, and student number into 3 strings.
    const string FIRSTNAME = "Thomas";
    const string LASTNAME = "Herr";
    const int STUDENTNUMBER = 200325519;

    //Concatenate your first + last + (ID) to display on the output as seen in the sample
    //Gratissimum: Jason Gubbels (230333333)
    printf("Gratissimum: %s %s (%d)", FIRSTNAME.c_str(), LASTNAME.c_str(), STUDENTNUMBER);


    //Loop continuously to allow the user to make a selection (#4 exits)
    int selection = get_selection();

    //Use a switch statement to determine the user input
    switch(selection) {
        default:
            cout << "Exiting..." << endl;
        case 1:
            RomanToBase10();
        case 2:
            Base10ToRoman();
        case 3:
            RomanAddition();
    }

    //Once the user has made the selection call the respective function above to perform the below type of examples.
    //Background is provided along with working samples.

    return 0;
}