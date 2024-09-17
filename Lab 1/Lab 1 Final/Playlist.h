#pragma once
#include <iostream>
using namespace std;

class PlaylistNode {

private:
  string uniqueID;
  string songName;
  string artistName;
  int songLength;
  PlaylistNode* nextNodePtr;
public:
  // PlaylistNode default constctor 
  PlaylistNode()
  :uniqueID("none"),
  songName("none"),
  artistName("none"),
  songLength(0),
  nextNodePtr(0){};
  
  // PlaylistNode constructor with parameters
  PlaylistNode (const string& uniqueID, const string& songName, const string& artistName, const int songLength)
  :uniqueID(uniqueID),
  songName(songName),
  artistName(artistName),
  songLength(songLength),
  nextNodePtr(0){};

  //PlaylistNode deconstructor 
  ~PlaylistNode(){
    delete nextNodePtr;
  }
  //copy constructor
  PlaylistNode(const PlaylistNode&) = delete;

  // copy assignment operator
  PlaylistNode& operator=(const PlaylistNode&) = delete;

  // member functions for the PlaylistNode class
  const string& GetID() const;
  const string& GetArtistName() const;
  const string& GetSongName() const;
  int GetSongLength() const;
  PlaylistNode* GetNext();
  const PlaylistNode* GetNext() const;
  const void PrintPlaylistNode() const;
  void InsertAfter(PlaylistNode* nodeLoc, const string& functionCheck);
  void InsertAfter(PlaylistNode* nodeLoc);
  void SetNext(PlaylistNode* newSong);
};

class Playlist {
  PlaylistNode* head;
  PlaylistNode* tail;
public:
  //Playlist constructor
  Playlist()
    : head(nullptr),tail(nullptr)
  {}

  //Playlist deconstrcutor
  ~Playlist() {
    if(head != nullptr){
      PlaylistNode *temp = head;
      while(temp != nullptr){
	      PlaylistNode *nodeToDelete = temp;
	      temp = temp->GetNext();
	      delete nodeToDelete;
	    }
    }
  }

  //copy constructor
  Playlist(const Playlist&) = delete;

  // copy assignment operator
  Playlist& operator=(const Playlist&) = delete;

  // member functions for Playlist class
  void PrintMenu(const string& title) const;
  void AddSong(const string& id, const std::string& song, const std::string& artist, int length);
  void RemoveSong(const string& uniqueID);
  void ChangePositionSong(const int currPosition, int newPosition);
  void OutputSongsByArtist(const string& artistName) const;
  void OutputTotalTime() const;
  void OutputFullPlaylist() const;
};

