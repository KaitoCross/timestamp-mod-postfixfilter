//
// Created by christian on 12.04.18.
//

#include <iostream>
#include <cstdio>
#include <regex>
#include <string>
#include <iomanip>
#include <sstream>
#include <stdexcept>

using namespace std;

string sanitizeTimestamp (string sanitizeMe, bool linebreak)
{
    string toBeFound;
    if(linebreak)
    {
        toBeFound="\r";
    } else
    {
        toBeFound="  ";
    }
    unsigned long posOfUnwantedChars = sanitizeMe.find(toBeFound);
    if (posOfUnwantedChars != string::npos) {
        if(posOfUnwantedChars==4&&!linebreak) {
            sanitizeMe.replace(posOfUnwantedChars, 2, " 0"); //If a double space ruins our life, replace it with a space and leading zero if it appears before the number of the day of the month.
        }
        if (posOfUnwantedChars > 4||linebreak) {
            for (unsigned long i = posOfUnwantedChars; i + 1 < sanitizeMe.length(); i++) {
                swap(sanitizeMe[i], sanitizeMe[i + 1]); //putting unwanted in the middle linebreaks at the end of line
            }
            unsigned long oldsize = sanitizeMe.size();
            sanitizeMe.resize(oldsize-1); //resize string, removing last character -> linebreak gone!
        }
    }
    return sanitizeMe;
}

string modTimestamp(int setbackHours, string timestamp, bool needsSanitiziation, bool removeLinebreak)
{
    char tempTimestamp[26]="";
    time_t modTime;
    long int length = timestamp.length();
    tm dateMod;
    stringstream dateOfMail;
    if(needsSanitiziation) {
        dateOfMail << sanitizeTimestamp(timestamp, removeLinebreak);
    } else
    {
	 dateOfMail << sanitizeTimestamp(timestamp, false);
    }
    dateOfMail.clear();
    //if through our sanitization the string became a little smaller than usual
    //parsing it for the date and time
    if(dateOfMail.str().size() < 25)
    {
    string missingZero = dateOfMail.str();
    missingZero.replace(4,1,string("0"));
    dateOfMail.str(missingZero);
    dateOfMail>>get_time(&dateMod, "%a,%d %b %Y %H:%M:%S");
    }
    //regular string
        //Parsing it for the date and time
    else{
    	dateOfMail>>get_time(&dateMod, "%a, %d %b %Y %H:%M:%S");
	}
    dateOfMail << "";
    dateOfMail.clear();
    dateOfMail.str(string());
    modTime=mktime(&dateMod);
    modTime = modTime-setbackHours*60*60; //subtracting the time from unix timestamp
        if (removeLinebreak) {//adding size to fit everything again of linebreak was removed
            timestamp.resize((unsigned long)length, ' ');
        }

        bool tooshort = (length == 24);
        if (tooshort) { //if through our sanitization the string became a little smaller than usual
            strftime(tempTimestamp, 26, "%a,%e %b %Y %X", localtime(&modTime)); //creating new timestamp from modified time
        } else {
            strftime(tempTimestamp, 26, "%a, %d %b %Y %X", localtime(&modTime)); //the same but with a regular timestamp
        }
    timestamp = tempTimestamp;
    return timestamp;
}


