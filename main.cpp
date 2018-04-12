#include <iostream>
#include <cstdio>
#include <regex>
#include <fstream>
#include <vector>
#include <exception>
#include <string>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdexcept>
#include<arpa/inet.h>
#include "func.h"
/*
Code by KaitoCross https://github.com/KaitoCross not yet published
These tools are free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version.
These tools are distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
*/
using namespace std;
int main(int argc, char* argv[]) {
    string filename = "/home/kaito/email.eml";
    string StampPat = "[MTWFS][ouehra][neduit]\\x2C(\\s+|\\S)[0-9]+\\s[A-S][a-z][a-z]((\\s)|(\\r\\s))[0-2][0-9][0-9][0-9]((\\s)|(\\r\\s))[0-2][0-9]\\x3A[0-5][0-9]\\x3A[0-5][0-9]";
    regex DatePat(StampPat,regex_constants::ECMAScript);
    if (argc == 1)
    {
        filename=argv[0];
    }
    string currentline ="Hello world";
    string previousline = "";
    string memoryForFileLines="";
    //stringstream dateOfMail;
    //char timestamp[26];
    smatch results;
    fstream email_file;
    email_file.open(filename,fstream::in | fstream::out);
    long long int oldreadpos = 0;
    long long int readpos = 0;
    long long int newWritePos = 0;
    int matches = 0;
    int setbackHours = 0;
    bool previousmatch = false;
    //time_t modTime;
    //time(&modTime);

    //datiming = localtime()(&modTime);

    //strftime(timestamp,26,"%a,%e %b %Y %X",localtime(&modTime));
    string stimestamp;
    cout << stimestamp << "\n";
    struct timeval timeout;
    timeout.tv_sec=2;
    int sockfd = socket(AF_INET,SOCK_DGRAM,0);
    struct sockaddr_in serv, client;
    serv.sin_family = AF_INET;
    serv.sin_port = htons(1337);
    serv.sin_addr.s_addr = inet_addr("127.0.0.1");
    socklen_t l = sizeof(client);
    socklen_t m = sizeof(serv);
    char buffer[10] = "REQTO";
    char buffer2[5]="0000";
    int sent = sendto(sockfd,buffer,5,0,(struct sockaddr *)&serv,m);
    recvfrom(sockfd,buffer,10,0,(struct sockaddr *)&client,&l);
    char *ptr;

    if (strncmp(buffer,"RCVTO",5) == 0)
    {
    cout << "RECEIVED OFFSET INFO\n";
        char *endOfBuffer = &buffer[10];
        setbackHours = (int)strtol(buffer+6,&endOfBuffer,10);
    }
    while (getline(email_file,currentline) /*&& currentline.find("Content-Type")*/)
    {
        //tm dateMod;
        memoryForFileLines = "";
        memoryForFileLines.append(currentline);
        bool match = regex_search(memoryForFileLines,results,DatePat,regex_constants::match_any);
        if (match) {
            cout << "Found on position " << results.position(0) << " " << memoryForFileLines << "\n";

            newWritePos = readpos + results.position(0);
            email_file.seekp(newWritePos);
            string /* temp*/ stimestamp = modTimestamp(setbackHours,results.str(),true, false); /*sanitizeTimestamp(results.str(),false);
            dateOfMail<<temp;
            dateOfMail.clear();
            //cout << dateOfMail.str() << "\n";
            dateOfMail>>get_time(&dateMod, "%a, %d %b %Y %H:%M:%S");
            dateOfMail << "";
            dateOfMail.clear();
            dateOfMail.str(string());
            modTime=mktime(&dateMod);
            modTime = modTime-setbackHours*60*60;
            bool tooshort = (temp.length()==24);
            if(tooshort)
            {
                    strftime(timestamp, 26, "%a,%e %b %Y %X", localtime(&modTime));
            }
            else {
                strftime(timestamp, 26, "%a, %d %b %Y %X", localtime(&modTime));
            }
            stimestamp=timestamp;*/
            cout <<"new timestamp: "<< stimestamp << std::endl;
            email_file << stimestamp;
            email_file.seekg(readpos+currentline.length());
            matches++;
            previousmatch = true;

        }
        else if (!previousmatch)
        {
            memoryForFileLines = "";
            memoryForFileLines.append(previousline);
            memoryForFileLines.append(currentline);
            match = regex_search(memoryForFileLines,results,DatePat);
            if(match)
            {
                cout << "Found on position " << results.position(0) << " " << memoryForFileLines << "\n";
                newWritePos = oldreadpos + results.position(0);
                email_file.seekp(newWritePos);
                unsigned long oldsize = results.str().size();
                string /*temp*/stimestamp = modTimestamp(setbackHours,results.str(),true,true);/*sanitizeTimestamp(results.str(),true);
                dateOfMail<<temp;
                dateOfMail.clear();
                dateOfMail>>get_time(&dateMod,"%a, %d %b %Y %H:%M:%S");
                dateOfMail << "";
                dateOfMail.clear();
                dateOfMail.str(string());
                //dateMod.tm_hour= dateMod.tm_hour + dateMod.tm_gmtoff/60/60;
                //dateMod.tm_gmtoff=0;
                //dateMod.tm_zone="UTC";
                modTime=mktime(&dateMod);
                modTime = modTime-setbackHours*60*60;
                temp.resize(oldsize,' ');
                bool tooshort = (temp.length()==24);
                if(tooshort)
                {
                    strftime(timestamp, 26, "%a,%e %b %Y %X", localtime(&modTime));
                    timestamp[24]= ' ';
                }
                else {
                    strftime(timestamp, 26, "%a, %d %b %Y %X", localtime(&modTime));
                    timestamp[25]= ' ';
                }
                stimestamp = timestamp; */
                cout <<"new timestamp: "<< stimestamp << std::endl;
                email_file << stimestamp;
                matches++;
            }
        } else
        {
            previousmatch=false;
        }
        previousline="";
        previousline.append(currentline);
        oldreadpos = readpos;
        readpos = email_file.tellg();
    }
    cout << matches << std::endl;
    email_file.close();
    return 0;
}