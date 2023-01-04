#include "PlayList.h"
#include <stdexcept>
#include <iostream>

using std::cout;
using std::endl;
using std::exception;
using std::out_of_range;

// Default Constructor
PlayList::PlayList() : head(nullptr), length(0) { }

// Copy Constructor
// given a playlist, copy constructor creates a deep copy of it
PlayList::PlayList(const PlayList& pl) {
    //if length == 0 -> playlist is empty -> nothing to copy
    //else
    if (pl.length != 0) {
        this->head = new PlayListNode(pl.head->song,nullptr);
        // curr is used to traverse the playlist
        // temp is used to traverse pl
        PlayListNode* curr = this->head;
        PlayListNode* temp = pl.head->next;
        this->length = 1;

        // traverse the playlist, deep copying each song from pl to the playlist
        while (temp != nullptr) {
            curr->next = new PlayListNode(temp->song,nullptr);
            curr = curr->next;
            temp = temp->next;
            this->length++;
        }
    }
}


// Destructor
PlayList::~PlayList() {
    //if head == nullptr, then there is nothing to delete
    //else
    if (this->head != nullptr) {
        PlayListNode* curr = this->head; 
        //curr starts at head and traverses until the end of the playlist  
        //delete the songs one by one during traversal
        while (curr != nullptr) {
            PlayListNode* temp = curr->next; //store next song in temp, set curr to temp after deleting
            delete curr; 
            curr = temp;
        }
    }
}


/*
    Description: given a playlist pl, operator= deallocates the playlist, deep copies pl to the platlist and returns a reference to the playlist
    PRE: pl should exist
    POST: playlist is now a deepcopy of pl
*/
PlayList& PlayList::operator=(const PlayList & pl) {
    PlayListNode* curr = this->head;

    while (curr != nullptr) {   // traverse the playlist and deallocates
        PlayListNode* temp = curr->next;
        delete curr;
        curr = temp;
    }
    
    if (pl.length == 0) {   // pl is empty LL
        return *this;
    }
    else {  // pl is not empty, deep copy it to this
        head = new PlayListNode(pl.head->song,nullptr);
        // curr is used to traverse the playlist
        // temp is used to traverse pl
        PlayListNode* curr = this->head;
        PlayListNode* temp = pl.head->next;
        this->length = 1;

        // during traversal, deepcopyfrom pl to playlist song by song
        while (temp != nullptr) {
            curr->next = new PlayListNode(temp->song,nullptr);
            curr = curr->next;
            temp = temp->next;
            this->length++;
        }
        return *this;
    }
}


/*
    Description: given a song and a position, insert() will insert the song at the given position in the playlist
    PRE: position must be in the range: [0,length] , position=length tells function to insert at the end of the playlist
    POST: playlist is updated s.t the given song is now inserted at the given positin in the playlist, length of playlist increased by 1
*/
void PlayList::insert(Song sng, unsigned int pos) {
    // empty LL, insert sng as the head
    if (this->length == 0) {  
        this->head = new PlayListNode(sng);
        this->length++;
    }
    // LL not empty
    // position = 0, sng set as head and now points to the previous head
    else if (pos == 0) {   
        PlayListNode* curr = new PlayListNode(sng, head);
        this->head = curr;
        this->length++;
    }
    // 1 <= position < length (in range, not 0)
    else {  
        PlayListNode* prev = nullptr;
        PlayListNode* curr = this->head;
        unsigned int count = 0; // used to keep track of traversal of playlist

        // traversing the playlist
        while (curr != nullptr) {
            if (count == pos) { // if count == pos, then we found the correct position to insert song
                PlayListNode* temp = curr;
                curr = new PlayListNode(sng, temp); // create new node containing the song to insert, bumping the current song behind it
                prev->next = curr;
                this->length++;
                break;
            }
            // if count != pos, then continue traversal
            prev = curr;
            curr = curr->next;
            count++;
        }
        // if traversal ended w/o count == pos, then insert at the end of the LL
        if (pos == length) { 
            prev->next = new PlayListNode(sng);
            this->length++;
        }
    }
}


/*
    Description: given a position, remove() removes the song at that position in the playlist and returns it
    PRE: position must be in the range: [0,length-1]
    POST: song has been removed from playlist and length decreased by 1
*/
Song PlayList::remove(unsigned int pos) {
    // playlist with one song
    // delete the song, head now points to null (empty playlist)
    if (this->length == 1) {  
        Song ret = this->head->song;
        PlayListNode* temp = this->head;
        delete temp;
        this->head = nullptr;
        this->length--;
        return ret;
    }
    // playlist has at least 2 songs
    else {
        Song ret = this->get(pos);  // use get() to retrieve the removed song at given position

        // pos = 0, remove the song at the front of the playlist
        if (pos == 0) { 
            PlayListNode* temp = this->head->next;
            delete this->head;
            head = temp; // new head is the 2nd song in the playlist
            return ret;
        }
        // pos in the range [1,length-1]
        else {  
            PlayListNode* prev = nullptr;
            PlayListNode* curr = this->head;
            unsigned int count = 0; // used to keep track of traversal

            // traverse the playlist
            while (curr!=nullptr) {
                if (count == pos) { // when count=pos, then remove then position to remove has been found
                    PlayListNode* temp = curr->next;
                    delete curr;
                    prev->next = temp;
                    this->length--;
                }
                // count != pos, continute traversal
                prev = curr;
                curr = curr->next;
                count++;
            }
            return ret;
        }
    }
}


/*
    Description: given 2 positions in the playlist, swap the songs so they take each others spots in the playlist
    PRE: positions must be within the range [0,length-1]
    POST: playlist is updated s.t the songs in the 2 positions have swapped places
*/
void PlayList::swap(unsigned int pos1, unsigned int pos2) {
    // if pos1 == pos2, nothing happeens (swap the same song)
    if (pos1 == pos2) {
        return;
    }
    PlayListNode* curr1;
    PlayListNode* prev1;
    PlayListNode* curr2;
    PlayListNode* prev2;
    // initializing previous and current nodes
    // if pos1=0 or pos2=0, then prev has to be set to nullptr (nothing points to the head)
    if (pos1 == 0) {
        prev1 = nullptr;
        curr1 = this->head;
    }
    if (pos2 == 0) {
        prev2 = nullptr;
        curr2 = this->head;
    }

    PlayListNode* trav = this->head;
    unsigned int count = 0;
    // traverse the playlist
    // pos1/pos2 != 0
    while (trav != nullptr) {
        if (count == pos1-1) { // if count = (pos1)-1, then set prev1 as the current node, curr1 as the next node
            prev1 = trav;
            curr1 = trav->next;
            count++;
            trav = trav->next;
        }
        else if (count == pos2-1) { // if count = (pos2)-1, then set prev2 as the current curr2 as the next node
            prev2 = trav;
            curr2 = trav->next;
            count++;
            trav = trav->next;
        }
        else { // continue traversal
            count++;
            trav = trav->next;
        }
    }

    // determine whether pos1,pos2 are adjacent
    bool adjacent = false;
    if (pos1 > pos2) {
        if (pos1 - pos2 == 1) {
            adjacent = true;
        }
    }
    if (pos2 > pos1) {
        if (pos2 - pos1 == 1) {
            adjacent = true;
        }
    }
    // nodes & previous nodes have now been set

    // swapping the next nodes
    PlayListNode* temp = curr1->next;
    curr1->next = curr2->next;
    curr2->next = temp;

    if (adjacent == false) {    // pos1,pos2 are not adjacent
        if (pos1 == 0) {    // pos1 is the head
            this->head = curr2;
            prev2->next = curr1;
        }
        else if (pos2 == 0) {   // pos2 is the head
            this->head = curr1;
            prev1->next = curr2;
        }
        else {  // pos1,2 are not the heads
            prev1->next = curr2;
            prev2->next = curr1;
        }
    }
    else {  // pos1,pos2 are adjacent
        if (pos1 == 0) {    // pos1 is the head, pos2=1 is implied
            this->head = curr2;
            head->next = curr1;
        }
        else if (pos2 == 0) {   // pos2 is the head, pos1=1 is implied
            this->head = curr1;
            head->next = curr2;
        }
        else {  //pos1,2 are not the heads
            if (pos1 < pos2) {
                prev1->next = curr2;
                curr2->next = curr1;
                prev2 = nullptr;
            }
            else {  //pos1 > pos2
                prev2->next = curr1;
                curr1->next = curr2;
                prev1 = nullptr;
            }
        }
    }
}

/*
    DESCRIPTION: given a position in the playlist, get() returns the Song at that position
    PRE: position in the playlist must be valid, range: [0,length-1]
    POST:  nothing has changed in the playlist
*/
Song PlayList::get(unsigned int pos) const {
    PlayListNode* curr = this->head;
    unsigned int count = 0; // used to keep track of traversal
    
    // traversing the playlist
    while (curr != nullptr) {
        if (count == pos) { // if count == pos, then song is found. stop traversal
            break;
        }
        curr = curr->next;
        count++;
    }
    return curr->song;
}

/*  
    DESCRIPTION: given a playlist, size() returns the length of the playlist
    PRE: no parameters/preconditions
    POST: nothing has changed in the playlist
*/
unsigned int PlayList::size() const { return this->length; }