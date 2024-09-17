#include <iostream>
#include  <bits/stdc++.h>

#include "Playlist.h"

using namespace std;

int main() {
  string title;
  cout << "Enter playlist's title:" << endl;
  getline(cin, title);
  cout << endl;

  Playlist P;

  //Continues to ask user how they want to modify a playlist until user quits
  while(true) {
    P.PrintMenu(title);


    cout << "\nChoose an option:"<< endl; 

    //checking to make sure than the input is a string
    string command;
    if (!(cin >> command)) break;

    //calls different functions based on user's input
    if (command == "a") {
      string uniqueID;
      string songName;
      string artistName;
      int songLength;
      cout<< "ADD SONG" << endl;
      cout << "Enter song's unique ID:" << endl;
      cin >> uniqueID;
      cout << "Enter song's name:" << endl;
      cin.ignore();
      getline(cin, songName);
      cout << "Enter artist's name:" << endl;
      getline(cin, artistName);
      cout << "Enter song's length (in seconds):" << endl;
      cin >> songLength;
      cout << endl;
      P.AddSong(uniqueID, songName, artistName, songLength);
    } else if (command == "d") {
      string uniqueID;
      cout << "REMOVE SONG" << endl;
      cout<<"Enter song's unique ID:"<<endl;
      cin >> uniqueID;
      P.RemoveSong(uniqueID);
    } else if (command == "c") {
      int currentPosition;
      int newPosition;
      cout << "CHANGE POSITION OF SONG"<< endl;
      cout << "Enter song's current position:" << endl;
      cin >> currentPosition;
      cout << "Enter new position for song:" << endl;
      cin >> newPosition;
      P.ChangePositionSong(currentPosition, newPosition);
    } else if (command == "s") {
      string artistName;
      cout<< "OUTPUT SONGS BY SPECIFIC ARTIST" << endl;
      cout<<"Enter artist's name:" << endl;
      cin.ignore();
      getline(cin, artistName);
      cout << endl;
      P.OutputSongsByArtist(artistName);
    } else if (command == "t") {
      P.OutputTotalTime();
    } else if (command == "o") {
      cout << title << " - OUTPUT FULL PLAYLIST" << endl;
      P.OutputFullPlaylist();
    } else if (command == "q") {
      break;
    }
  }

  // If cin is in an error state (even end-of-file), then send an error message
  if (!cin) {
    cout << "Program did not exit cleanly" << endl;
    return 1;
  }
  
  return 0;
}
