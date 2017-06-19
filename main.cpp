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
                cout << "Valid character found at position: " << i << endl;
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
        cout << "Input the base 10 number (< 9999 and > 0): ";

        cin >> input;

        if(!cin.fail()) {
            if(input>0&&input<9999) {
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
 *
 * M CM XC IV = 1000 + 100 + 1000 + 10 + 100 + 1 + 5 = 2216
 *
 * Simply add up the values of the Roman symbols. Of course, if a subtractive appears with a I, X, or C to the left
 * of a "larger" symbol, we need to substitute the pair for the correct numeric value.
 *
 * @param input RomanNumeral
 */
void RomanToBase10(RomanNumeral input) {

    int total = 0;
    for(unsigned int i=0; i<input.expression.length(); i++) {
        char current = input.expression.at(i);
        char next = input.expression.at(i+1);

        switch(current) {
            case 'I':
                //Check if the next character is V or X (Warning about indexes)
                if(next=='V') {
                    //This is actually 4, so add that and skip a character position
                    total+=4;
                    i++;
                } else if(next=='X') {
                    //This is actually 9, so add that and skip a character position
                    total+=9;
                    i++;
                } else {
                    total+=1;
                }
                break;
            case 'V':
                cout << "Adding 5" << endl;
                total+=5;
                break;
            case 'X':
                //Check if the next character is an L or C

                if(next=='L') {
                    //This is actually 40, so add that and skip a character position
                    total+=40;
                    i++;
                } else if(next=='C') {
                    //This is actually 90, so add that and skip a character position
                    total+=90;
                    i++;
                } else {
                    total+=10;
                }

                break;
            case 'L':
                cout << "Adding 50" << endl;
                total+=50;
                break;
            case 'C':
                //Check if the next character is an D or M

                if(next=='D') {
                    //This is actually 400, so add that and skip a character position
                    total+=400;
                    i++;
                } else if(next=='M') {
                    //This is actually 90, so add that and skip a character position
                    total+=900;
                    i++;
                } else {
                    total+=100;
                }

                break;
            case 'D':
                cout << "Adding 500" << endl;
                total+=500;
                break;
            case 'M':
                cout << "Adding 1000" << endl;
                total+=1000;
                break;
            default:
                cout << "Invalid Character Detected at position " << i << endl;
                break;
        }
    }

    cout << "In Base 10 this is: " << total << endl;
}

/**
 * 1.	Substitute for any subtractives in both values; that is; "uncompact" the Roman values.
 * 2.	Put the two values together—catenate them.
 * 3.	Sort the symbols in order from left-to-right with the "largest" symbols on the left.
 * 4.	Starting with the right end, combine groups of the same symbols that can make a "larger" one and substitute the single larger one.
 * 5.	Compact the result by substituting subtractives where possible.
 *
 * @param first
 * @param second
 */
void RomanAddition(RomanNumeral first, RomanNumeral second) {
    cout << "Adding: " << first.expression << " to " << second.expression << endl;



}

/**
 * Look for repeat of symbols (Groups of 4)
 * To do this we proceed right-to-left and look for four of the same symbol.
 *
 * @param input
 */
void RemoveSubstractives(RomanNumeral &input) {
    //MMCCCXXXXVIIII
    char prev;
    int streak = 0;

    for(unsigned int i=0; i<input.expression.length(); i++) {
        char current = input.expression.at(i);
        cout << "Current Character: " << current << endl;
        //cout << "Current Streak: " << streak << endl;

        if(i==0) {
            prev=current;
        } else {
            cout << "Previous Character: " << prev << endl;
            //Check if our current symbol matches our previous one
            if(current==prev) {
                streak++;
                cout << "Matches Previous Character. Adding to streak " << streak << endl;
            } else {
                //cout << "No Match. Resettting Streak Counter" << endl;
                streak=0;
            }

            prev=current;
        }

        if(streak==3) {
            cout << "Viable Substitution found" << endl;

            if(current=='X') {
                cout << "Replacing " << input.expression.substr(i-3,i) << endl;
                input.expression.replace(i-3,i,"XL");
            }

            if(current=='I') {
                cout << "Replacing: " << input.expression.substr(i-3,i) << endl;
                input.expression.replace(i-3,i,"IV");
            }

            if(current=='C') {
                cout << "Replacing: " << input.expression.substr(i-3,i) << endl;
                input.expression.replace(i-3,i,"CD");
            }

        }
    }

    cout << "Final Result: " << input.expression << endl;
}

/**
 * Find any shortforms and unexpand them
 *
 * @param input
 */
void AddSubstractives(RomanNumeral &input) {

    //If we have any of the follwing patterns:

    //IV = IIII
    //IX = VIIII
    //XL = XXXX
    //XC = LXXXX
    //CD = CCCC
    //CM = DCCCC

    size_t ivmatch = input.expression.find("IV");
    size_t ixmatch = input.expression.find("IX");
    size_t xlmatch = input.expression.find("XL");
    size_t xcmatch = input.expression.find("XC");
    size_t cdmatch = input.expression.find("CD");
    size_t cmmatch = input.expression.find("CM");


    if(ivmatch!=string::npos) {
        std::cout << "Found IV at position: " << ivmatch << endl;
        input.expression.replace(ivmatch, ivmatch+2, "IIII");
    }


    if(ixmatch!=string::npos) {
        std::cout << "Found IX at position: " << ixmatch << endl;
        input.expression.replace(ixmatch, ixmatch+2, "VIIII");
    }

    if(xlmatch!=string::npos) {
        std::cout << "Found XL at position: " << xlmatch << endl;
        input.expression.replace(xlmatch, xlmatch+2, "XXXX");
    }

    if(xcmatch!=string::npos) {
        std::cout << "Found XC at position: " << xcmatch << endl;
        input.expression.replace(xcmatch, xcmatch+2, "LXXXX");
    }

    if(cdmatch!=string::npos) {
        std::cout << "Found CD at position: " << cdmatch << endl;
        input.expression.replace(cdmatch, cdmatch+2, "CCCC");
    }

    if(cmmatch!=string::npos) {
        std::cout << "Found CM at position: " << cmmatch << endl;
        input.expression.replace(cmmatch, cmmatch+2, "DCCCC");
    }

    cout << "Fully Expanded Form: " << input.expression << endl;
}

/**
 * Given a base 10 number return a RomanNumeral equivilent
 *
 * @param input int Base 10 user number
 * //2349
 */
void Base10ToRoman(int input) {

    RomanNumeral result;
    int value_left = input;

    //Want to keep going until value left is zero

    do  {
        cout << "Value Left: " << value_left << endl;
        if(value_left-1000>0) {
            cout << "Number is divisible by 1000, add an M" << endl;
            result.expression+='M';
            value_left = value_left - 1000;
        } else if(value_left-500>0) {
            cout << "Number is divisible by 500, add a D" << endl;
            result.expression+='D';
            value_left = value_left - 500;
        } else if(value_left-100>0) {
            cout << "Number is divisible by 100, add a C" << endl;
            result.expression+='C';
            value_left = value_left - 100;
        } else if(value_left-50>0) {
            cout << "Number is divisible by 50, add an L" << endl;
            result.expression+='L';
            value_left = value_left - 50;
        } else if(value_left-10>0) {
            cout << "Number is divisible by 10, add an X" << endl;
            result.expression+='X';
            value_left = value_left - 10;
        } else if(value_left-5>0) {
            cout << "Number is divisible by 5, add an V" << endl;
            result.expression+='V';
            value_left = value_left - 5;
        } else if(value_left-1>0) {
            cout << "Number is divisible by 1, add an I" << endl;
            result.expression+='I';
            value_left = value_left - 1;
        } else {
            result.expression+='I';
            value_left=0;
        }
    } while(value_left>0);


    cout << "Result before substituting subtractives: " << result.expression << endl;
    RemoveSubstractives(result);
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
        case 1:;
            RomanToBase10(getRomanInput());
            break;
        case 2:
            Base10ToRoman(getBase10Input());
            break;
        case 3:
            RomanAddition(getRomanInput(), getRomanInput());
            break;
        default:
            cout << "Exiting..." << endl;
            break;
    }

    //Once the user has made the selection call the respective function above to perform the below type of examples.
    //Background is provided along with working samples.

    return 0;
}