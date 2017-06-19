/**
 *
 *
 */
using namespace std;

#include <iostream>
#include <string>
#include <cstdio>

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

void RomanToBase10() {

}

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