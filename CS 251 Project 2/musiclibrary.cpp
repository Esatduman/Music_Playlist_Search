// Name: Esat Duman 
// UIN: 662726641
// System: Windows
// IDE: Visual Studios
// Date: 2/14/2023
// Program Overview: This program will load music files into a map and utilize sets. 
// the program will function as a music library as the user searches through the maps container for songs, albums and artists.
// code will consist vasrious amount of functions for each command. Thanks!
//_________________________________________________________

/// Assignment details and provided code are created and
/// owned by Adam T Koehler, PhD - Copyright 2023.
/// University of Illinois Chicago - CS 251 Spring 2023

#include <algorithm>
#include <locale>
#include <map>
#include <set>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

// INSERTS GIVEN HELPERS CODE BELOW - DO NOT REMOVE
#include "helpers.cpp"
// INSERTS GIVEN HELPERS CODE ABOVE - DO NOT REMOVE

//
// NOTE TO STUDENTS:
// You may use the functions in the helpers file,
// but you may not modify the file or its contents in any way whatsoever.
//

//
// STUDENT CODE MAY GO BELOW THIS LINE
//


struct Album {          // struct for Album and songs. 
    set<string> artist;
    set<string> songs;
    string albumTitle;

    
};

void loadFile(string filename, map<string, int>& musicLibrary)  // this function loads the user input file into a map
{
     if (filename.empty())
        return;
    // TODO: Load data from file into the map
    ifstream infile(filename);
    if (!infile.is_open()) {     // check to see if file can be opened. 
        cout << "Error: Could not open music library file - " << filename << endl;
        return;
    }
    string albumName;  
    string artist;
    string songName;
    while (getline(infile, albumName)) {     // getline for file 
        if (!musicLibrary.count(albumName)) {
            Album album;
            infile >> artist;
            album.artist.insert(artist);
            set<string> songs;
            while (getline(infile, songName) && songName != albumName) {
                songs.insert(songName);
            }
            album.songs = songs;
           musicLibrary[albumName] = album;
        }
    }
    
}

void toLower(string &str)   // toloWer so I can use thus function inside searchAlbum which makes it easier
{
    transform(str.begin(), str.end(), str.begin(),
        [](unsigned char c){ return tolower(c); });
}

// searchAlbum function searches through the map by using a for loop to iterate
void searchAlbum(const string &searchTerm, map<string, Album> &musicLibrary)
{
    string searchTermLower = searchTerm;
    toLower(searchTermLower);
    bool found = false;
    for (const auto &album : musicLibrary)
    {
        string albumTitleLower = album.first;
        toLower(albumTitleLower);
        string artistLower;
for (const auto &artist : album.second.artist) {
    artistLower = artist;
    break;
}
        toLower(artistLower);
        if (albumTitleLower.find(searchTermLower) != string::npos || artistLower.find(searchTermLower) != string::npos)  // finds the album title through out the file and prints it 
        {
            
            found = true;
            cout <<"Your search results exist in the following albums:" << endl;
            cout << album.first << endl;
            cout << endl;
            cout << endl;
        }
        else
        {
            for (const auto &song : album.second.songs)
            {
                string songTitleLower = song;
                toLower(songTitleLower);
                if (songTitleLower.find(searchTermLower) != string::npos)
                {
                    found = true;
                    cout << album.first << endl;
                    break;
                }
            }
        }
    }
    if (!found)
    {
        cout << " Your search results exist in the following albums: "  << endl;
    }
}

// Searches the song instead of the album title 
void searchSong(const string &searchTerm, map<string, Album> &musicLibrary)
{
    string searchTermLower = searchTerm;
    toLower(searchTermLower);
    bool found = false;
    for (const auto &album : musicLibrary)
    {
        for (const auto &song : album.second.songs)
        {
            string songTitleLower = song;
            toLower(songTitleLower);
            if (songTitleLower.find(searchTermLower) != string::npos)
            {
                found = true;
                cout << song << endl;
            }
        }
    }
    
}

// stats functions also iterates through the map and counts the number of songs,albums, and artists
void statsCommand(const map<string, Album> &musicLibrary) {
    int total_records = 0;
    int total_artists = 0;
    int total_songs = 0;
    set<string> unique_artists;
    set<string> unique_songs;
    string last_artist_name = "";

    for (const auto &album : musicLibrary) {
        ++total_records;
        string albumTitle = album.first;
        string artistName;
        istringstream iss(albumTitle);
        iss >> artistName;
        while (iss >> artistName) {
            // Check if the artist name has only two words
            if (artistName.find(' ') == string::npos) {
                break;
            }
        }
        // Only count the artist if the name has only two words
        if (artistName.find(' ') == string::npos) {
            if (last_artist_name != artistName && unique_artists.count(artistName) == 0) {
                ++total_artists;
                unique_artists.insert(artistName);
            }
            last_artist_name = artistName;
        }
        for (const auto &song : album.second.songs) {
            if (song.size() >= 2 && isdigit(song[0]) && isdigit(song[1])) {
                ++total_songs;
            }
            unique_songs.insert(song);
        }
    }

    cout << "Overall Music Library Stats" << endl;
    cout << "===========================" << endl;
    cout << "Total Records: " << total_records << endl;
    cout << "Total Unique Artists: " << unique_artists.size() << endl;
    cout << "Total Songs: " << total_songs << endl;
    cout << endl;
}

// couldn't get the export to successfully to work. 
void exportFile(string filename, map<string, Album>& musicLibrary) {
    if (filename.empty())
        return;

    ofstream outfile(filename);
    if (!outfile.is_open()) {
        cout << "Error: Could not open file for writing - " << filename << endl;
        return;
    }

    
}

// One map with two sets.

//Notes to self: makes functions for each command. should use maps and sets for the project.

int main()
{
    string input;
    string userEntry;
    string command, remains;
    string filename1;
    // TODO: Declare any necessary variables for the music libary
    map<string, Album> musicLibrary;
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
        tolower(command);

        // take an action, one per iteration, based on the command
        if (command == "help")
        {
            helpCommand();
        }
        else if (command == "clear")
        {
            musicLibrary.clear();
        }
        else if (command == "export")
        {
            exportFile(remains, musicLibrary);
        }
        else if (command == "load")
        {
            loadFile(remains, musicLibrary);
        }
        else if (command == "stats")
        {
           statsCommand(musicLibrary);
        }          
        else if (command == "search")
        {
           searchAlbum(remains, musicLibrary);
           searchSong(remains, musicLibrary);
        }
        else
        {
        // If the searchType is not "album", display an error message
        if (userEntry != "load" && userEntry != "exit") {
        cout << "Error: invalid command" << endl;
             }
        }
        
    }while(command != "exit");    

    cout << "Thank you for using the Music Library App" << endl;
    return 0;
}
