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
            sanitizeMe.replace(posOfUnwantedChars, 2, " 0");
        }
        if (posOfUnwantedChars > 4||linebreak) {
            for (unsigned long i = posOfUnwantedChars; i + 1 < sanitizeMe.length(); i++) {
                swap(sanitizeMe[i], sanitizeMe[i + 1]);
            }
            unsigned long oldsize = sanitizeMe.size();
            sanitizeMe.resize(oldsize-1);
        }
    }
    return sanitizeMe;
}

string modTimestamp(int setbackHours, string timestamp, bool needsSanitiziation, bool removeLinebreak)
{
    char tempTimestamp[26]="";
    time_t modTime;
    long int length = timestamp.length();
    //string temp;
    tm dateMod;
    stringstream dateOfMail;
    if(needsSanitiziation) {
        dateOfMail << sanitizeTimestamp(timestamp, removeLinebreak);
        //temp = dateOfMail.str();
    } else
    {
        dateOfMail<<timestamp;
    }
    dateOfMail.clear();
    dateOfMail>>get_time(&dateMod, "%a, %d %b %Y %H:%M:%S");
    dateOfMail << "";
    dateOfMail.clear();
    dateOfMail.str(string());
    modTime=mktime(&dateMod);
    modTime = modTime-setbackHours*60*60;
        if (removeLinebreak) {
            timestamp.resize((unsigned long)length, ' ');
        }
        bool tooshort = (length == 24);
        if (tooshort) {
            strftime(tempTimestamp, 26, "%a,%e %b %Y %X", localtime(&modTime));
        } else {
            strftime(tempTimestamp, 26, "%a, %d %b %Y %X", localtime(&modTime));
        }
    timestamp = tempTimestamp;
    return timestamp;
}


