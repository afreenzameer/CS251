#include <algorithm>
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <sstream>
#include <ctype.h>
#include "helpers.cpp"

using namespace std;

// Author: Afreen Zameer
// Project overview: This program creates a music library which takes in several commands. The first command “load” loads in the album, artist(s) and songs in each text file. The command “stat” prints out the number of records, artists and songs in the music library at that particular moment. Adding “-d” to the end of the stats command results in the printing of the entire music library. There is also the export command, which writes the contents of the library into a separate text file, either provided by the user or created if there is no user input. The clear function, as its name suggests, clears the contents of the music library to empty. The search function allows for searching for any artist, album, or song and returns the album(s) which that search term belongs to. The modifiers + and - are also allowed to take the intersection or difference of the search terms respectfully.

// turns any string into lowercase
string lowerCase(string str)
{
    for (int i = 0; i < str.length(); i++)
    {
        str[i] = tolower(str[i]);
    }
    return str;
}

// serves as the value of the map musicLib
struct songInfo
{
    set<string> artist;
    set<string> song;
};

// loads in the file name provided, taking in the parameters remains, the map musicLib, and the variable album which sttores the album name.
void load(string remains, std::map<string, songInfo> &musicLib, string album)
{
    if (remains == "")
    {
        remains = "musicdatabase.txt";
    }

    string artist;
    string line;
    string song;
    char firstChar;

    ifstream infile(remains);

    if (infile)
    {
        while (!infile.eof())
        {

            getline(infile, album);
            if (album != "")
            {

                songInfo temp;
                while (getline(infile, line))
                {
                    if (line == album)
                    {
                        break;
                    }

                    if (isdigit(line.at(0)))
                    {
                        temp.song.insert(line);
                    }
                    else
                    {

                        temp.artist.insert(line);
                    }
                }

                musicLib[album] = temp;
            }
        }
    }
    else if (infile.fail())
    {
        cout << "Error: Could not open music library file - " << remains << endl;
    }
}

// prints out the entire contents of the music library, taking in the musicLib as a parameter
void statd(std::map<string, songInfo> &musicLib)
{
    cout << "Your Current Music Library Includes" << endl
         << "===================================" << endl;

    for (auto &p : musicLib)
    {
        cout << p.first << endl;
        for (auto &f : p.second.artist)
        {
            cout << " " << f << endl;
        }
        for (auto &s : p.second.song)
        {
            cout << "   " << s << endl;
        }
    }
    cout << endl;
}

// prints out the contents of the musicLib. If no user input is given, musicdatabase.txt is used. Takes in remains and musicLib as parameters.
void stat(string remains, std::map<string, songInfo> &musicLib)
{
    if (remains == "")
    {
        remains = "musicdatabase.txt";
    }

    set<string> uniqueArtist;
    int i = 0;
    // inserts artists into a set, to ensure only unique artists are printed
    for (auto &a : musicLib)
    {
        for (auto &b : a.second.artist)
        {
            uniqueArtist.insert(b);
        }
        i = a.second.song.size() + i;
    }
    cout << "Overall Music Library Stats" << endl
         << "===========================" << endl;
    cout << "Total Records: " << musicLib.size() << endl;
    cout << "Total Unique Artists: " << uniqueArtist.size() << endl;
    cout << "Total Songs: " << i << endl
         << endl;
    if (remains == "-d")
    {
        statd(musicLib);
    }
}

// exports contents of musicLib into a file, taking in the parameters remains and musicLib
void exportFile(string remains, std::map<string, songInfo> &musicLib)
{
    if (remains == "")
    {
        remains = "musicdatabase.txt";
    }

    ofstream outfile;

    outfile.open(remains);

    for (auto &p : musicLib)
    {
        outfile << p.first << endl;
        for (auto &f : p.second.artist)
        {
            outfile << f << endl;
        }
        for (auto &s : p.second.song)
        {
            outfile << s << endl;
        }
        outfile << p.first << endl;
    }

    outfile.close();
}

// takes the set difference, intersection, or union depending on what (if any) modifier is used. Takes in the parameters term, musicLib, sttoreAlbum, result, and difference. These are all different sets used to store the different modified sets.
void modifiers(string term, std::map<string, songInfo> &musicLib, set<string> &storeAlbum, set<string> &result, set<string> &difference)
{
    if (term.at(0) == '+')
    {
        set_intersection(storeAlbum.begin(), storeAlbum.end(), result.begin(), result.end(), inserter(difference, difference.begin()));
        result = difference;
    }
    else if (term.at(0) == '-')
    {

        set_difference(result.begin(), result.end(), storeAlbum.begin(), storeAlbum.end(), inserter(difference, difference.begin()));
        result = difference;
    }
    else
    {

        set_union(storeAlbum.begin(), storeAlbum.end(), result.begin(), result.end(), inserter(difference, difference.begin()));
        result = difference;
    }
}

// searches through the terms given a category of artist song or album. Returns an album which the term is in. If a modifier is used, it can take the intersection or difference of the terms. Takes in remains and musicLib as parameters.
void search(string remains, std::map<string, songInfo> &musicLib)
{
    // case for if there is no user input
    if (remains == "")
    {

        cout << "Error: Search terms cannot be empty." << endl
             << "No results found." << endl
             << endl;
    }
    else
    {
        // stringstream in first the category (album, artist, or song), then the term, for example Taylor and Swift.
        stringstream ss(remains);
        string category;
        ss >> category;
        string term;
        set<string> storeAlbum;
        set<string> difference;
        set<string> result;

        while (ss >> term)
        {
            storeAlbum.clear();
            difference.clear();

            string lc;
            lc = lowerCase(term);
            string lcNew;
            // removes the modifier at the begining of the term
            if (lc.at(0) == '+' || lc.at(0) == '-')
            {
                lcNew = lc.substr(1);
            }
            else
            {
                lcNew = lc;
            }

            if (category == "album")
            {
                // if in all the albums it finds the term given, it will store it into the set storeAlbum
                for (auto &p : musicLib)
                {

                    string key = lowerCase(p.first);

                    if (key.find(lcNew) != string::npos)
                    {
                        storeAlbum.insert(p.first);
                    }
                }

                modifiers(term, musicLib, storeAlbum, result, difference);
            }
            if (category == "artist")
            {
                // if in all the artists it finds the term given, it will store it into the set storeAlbum
                for (auto &p : musicLib)
                {
                    for (auto r : p.second.artist)
                    {
                        string key2 = lowerCase(r);
                        if (key2.find(lcNew) != string::npos)
                        {
                            storeAlbum.insert(p.first);
                        }
                    }
                }

                modifiers(term, musicLib, storeAlbum, result, difference);
            }
            else if (category == "song")
            {
                //if in all the songs it finds the term given, it will store it into the set storeAlbum
                for (auto &p : musicLib)
                {
                    for (auto r : p.second.song)
                    {

                        string key3 = lowerCase(r);

                        if (key3.find(lcNew) != string::npos)
                        {
                            storeAlbum.insert(p.first);
                        }
                    }
                }
                modifiers(term, musicLib, storeAlbum, result, difference);
            }
        }
        //prints out the result found in modifiers function
        cout << "Your search results exist in the following albums: ";
        for (auto &p : result)
        {
            cout << endl
                 << p;
        }
        cout << endl
             << endl;
    }
}

int main()
{
    string userEntry;
    string command, remains;
    map<string, songInfo> musicLib;
    string album;

    // Display welcome message once per program execution
    cout << "Welcome to the Music Library App" << endl;
    cout << "--------------------------------" << endl;

    // Stay in menu until exit command
    do
    {
        cout << endl;
        cout << "Enter a command (help for help): " << endl;
        getline(cin, userEntry);
        cout << endl;

        // Split the user entry into two pieces
        splitFirstWord(userEntry, command, remains);

        // make all the commands lowercase
        lowerCase(command);

        // take an action, one per iteration, based on the command
        if (command == "help")
        {
            helpCommand();
        }
        // clears the contents of the musicLibrary
        else if (command == "clear")
        {
            musicLib.clear();
        }
        // exports contents of musicLib into another file
        else if (command == "export")
        {
            exportFile(remains, musicLib);
        }
        // loads in contents of whatever file the user provides
        else if (command == "load")
        {
            load(remains, musicLib, album);
        }
        // prints out the number of records, unique artists, and songs in the musicLib
        else if (command == "stats")
        {
            stat(remains, musicLib);
        }
        // searches the musicLib for a song, artist, or album
        else if (command == "search")
        {
            search(remains, musicLib);
        }

    } while (command != "exit");

    cout << "Thank you for using the Music Library App" << endl;
    return 0;
}
