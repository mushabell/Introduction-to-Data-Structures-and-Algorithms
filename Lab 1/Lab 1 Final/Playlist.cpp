#include "Playlist.h"

//Definitions for the Playlist Class
// Prints the menu options for the user to choose from
void Playlist::PrintMenu(const string& title) const {
  cout << title <<" PLAYLIST MENU" << endl;
  cout << "a - Add song" << endl;
  cout << "d - Remove song" << endl;
  cout << "c - Change position of song" << endl;
  cout << "s - Output songs by specific artist"<< endl;
  cout << "t - Output total time of playlist (in seconds)" << endl;
  cout << "o - Output full playlist" << endl;
  cout << "q - Quit" << endl;
}

//Adds a song to the end of the playlist the member function is called on
void Playlist::AddSong(const string& id, const std::string& song, const std::string& artist, int length) {
  PlaylistNode* newSong = new PlaylistNode(id, song, artist, length);
  //check if list is empty
  if (head == nullptr){
    head = newSong;
    tail = head;
    return;
  }
  //If not empty, adds to end of playlist
  tail -> SetNext(newSong);
  tail = newSong;
}

//Removed a song from playlist based on unique ID  
void Playlist::RemoveSong(const string& uniqueID) {
  int count = 0;
  PlaylistNode* prev = head;
  //loop through each node until the song wanted is found
  for(PlaylistNode* curr = head; curr != nullptr; curr = curr->GetNext()) {
    if (curr->GetID() == uniqueID){
      //if wanted song is head, reassign the head
      if (count == 0){
        head = curr -> GetNext();
      }
      //if wanted song is tail, reassign the tail
      if (curr == tail){
        tail = prev;
      }
      //if wanted song is in middle, reassign the pointers around
      if (head != tail){
        curr -> InsertAfter(prev, "remove");
      }
      cout << "\"" << curr -> GetSongName() << "\" removed."<< endl;
      cout << endl;
      delete curr;
      return;
    }
    prev = curr;
    count +=1;
  } 
}
    
void Playlist::ChangePositionSong(const int currPosition, int newPosition) {
  //Checking if the inputs are valid, and chaning if not valid
  if (newPosition <= 0){
    newPosition = 1;
  }
  int maxNumNodes = 0;
  for(PlaylistNode* curr = head; curr != nullptr; curr = curr->GetNext()){
    maxNumNodes++;
  }
  if (newPosition>maxNumNodes){
    newPosition = maxNumNodes;
  }
  int currPositionCount = 1;
  PlaylistNode* prevToCurr = head;
  PlaylistNode* currentNode = head;
  //Find the current position of the song
  for(PlaylistNode* currpos = head; currpos != nullptr; currpos = currpos->GetNext()) {
    if (currPositionCount == currPosition){
      break;
    }
    prevToCurr = currpos;
    currPositionCount++;
  }
  int newPositionCount = 1;
  PlaylistNode* prevToNewPos = head;
  PlaylistNode* newposNode = head;
  //find the new position of the song
  for(PlaylistNode* newpos = head; newpos != nullptr; newpos = newpos->GetNext()) {
    if (newPositionCount == newPosition){
      break;
    }
    prevToNewPos = newpos;
    newPositionCount++;
  }
  currentNode = prevToCurr -> GetNext();
  newposNode = prevToNewPos -> GetNext();
  //Different operations based on Testcases
  //If the node is moving forward in the playlist
  if (newPosition < currPosition){
    cout << "\"" << currentNode -> GetSongName() << "\" moved to position " << newPosition << endl;
    cout << endl;
    if (newPosition != 1){
      currentNode -> InsertAfter(prevToCurr, "remove");
      currentNode -> InsertAfter(prevToNewPos, "change");
    } else {
      //movig to the first song in the playlist
      currentNode -> InsertAfter(prevToCurr, "remove");
      currentNode -> InsertAfter(head, "newHead");
      head = currentNode;
    }
  } else if (currPosition != 1){
    //moving node towards the end of playlist
    cout << "\"" << currentNode -> GetSongName() << "\" moved to position " << newPosition << endl;
    cout << endl;
    currentNode -> InsertAfter(prevToCurr, "remove");
    currentNode -> InsertAfter(newposNode, "change");
  } else if (currPosition == 1){
    //moving head node to new position
    cout << "\"" << prevToCurr -> GetSongName() << "\" moved to position " << newPosition << endl;
    cout << endl;
    head = head -> GetNext();
    prevToCurr -> InsertAfter(newposNode, "change");
  }
}

//loops through playlist and prints all songs by the sme artist   
void Playlist::OutputSongsByArtist(const string& artistName) const {
  int num = 1;
  for (const PlaylistNode* curr = head; curr != nullptr; curr = curr -> GetNext()){
    if (curr->GetArtistName() == artistName){
      cout << num << "."<< endl;
      curr -> PrintPlaylistNode();
      cout << endl;
    }
    num +=1;
  }
}

//loops through playlist and prints the total time of the playlist in seconds   
void Playlist::OutputTotalTime() const {
  cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << endl;
  int sum = 0;
  for(const PlaylistNode* curr = head; curr != nullptr; curr = curr->GetNext()) {
    sum += curr ->GetSongLength();
  }
  cout << "Total time: " << sum << " seconds" << endl;
  cout << endl;
}

//Prints out the information for each song in the playlist 
void Playlist::OutputFullPlaylist() const {
  //Checking if empty
  if (head == nullptr){
    cout << "Playlist is empty" << endl;
    cout << endl;
    return;
  }
  //loop through each node in list
  int num = 1;
  for (const PlaylistNode* curr = head; curr != nullptr; curr = curr -> GetNext()){
    cout << num << "."<< endl;
    curr -> PrintPlaylistNode();
    cout << endl;
    num +=1;
  }
}
    

// Definitions for the PlaylistNode class
const string& PlaylistNode::GetID() const { return uniqueID; }

const string& PlaylistNode::GetArtistName() const { return artistName; }

const string& PlaylistNode::GetSongName() const { return songName; }

int PlaylistNode::GetSongLength() const { return songLength; }

PlaylistNode* PlaylistNode::GetNext() { return nextNodePtr; }

const PlaylistNode* PlaylistNode::GetNext() const { return nextNodePtr; }

//Prints all the details of one song
const void PlaylistNode::PrintPlaylistNode() const{
  cout << "Unique ID: " << uniqueID << '\n';
  cout << "Song Name: " << songName << '\n';
  cout << "Artist Name: " << artistName << '\n';
  cout << "Song Length (in seconds): " << songLength << endl;
}

//Sets the song at the end of the list
void PlaylistNode::SetNext(PlaylistNode* newSong){
  this->nextNodePtr = newSong;  
}

//Based on each edge case, the function changes the position of previous and current nodes
void PlaylistNode::InsertAfter(PlaylistNode* nodeLoc, const string& functionCheck){
  if (functionCheck == "remove"){
    nodeLoc -> nextNodePtr = this -> nextNodePtr;
  }
  if (functionCheck == "change"){
    this -> nextNodePtr = nodeLoc -> nextNodePtr;
    nodeLoc -> nextNodePtr = this;
  }
  if (functionCheck == "moveToHead"){
    this -> nextNodePtr = nodeLoc -> nextNodePtr;
  }
  if (functionCheck == "newHead"){
    this -> nextNodePtr = nodeLoc;
  }
}

//Function created to insert a node after the node this function is called on
void PlaylistNode::InsertAfter(PlaylistNode* nodeLoc){
  PlaylistNode* tmpNext = nullptr;
  tmpNext = this->nextNodePtr;
  this->nextNodePtr = nodeLoc;
  nodeLoc->nextNodePtr = tmpNext;
}