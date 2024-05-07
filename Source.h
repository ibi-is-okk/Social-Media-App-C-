#ifndef PART1_H
#define PART1_H

#include <iostream>
#include <fstream>
#include <string>
#include "source2.h"
#include "source3.h"

using namespace std;

class BaseClass {
    char* id;
    const int maxPosts = 10;
    Post** timeline;
    int noOfPosts;
public:
    void setId(const char*);
    BaseClass(const char*);
    BaseClass(std::ifstream&);
    virtual ~BaseClass(); //child destructor called frst
    bool AddPost(Post*);
    Post* GetLatestPost();
    const char* getAccountID();
    Post* SearchPostByID(char*);
    void ViewTimeline();
    void PrintMemories();
    virtual void PrintName() = 0;
    virtual void PrintDetails();
};

class User : public BaseClass {
    char* firstName;
    char* lastName;
    static const int maxFriends = 10;
    static const int maxNoOfLikedPages = 10;

    Page** likedPages;
    int noOfLikedPages;

    User** friends;
    int noOfFriends;
public:
    User(char*, char*, char*);
    User(std::ifstream&, char**, int&, char**, int&);
    ~User();
    void ReadDataFromFile(std::ifstream&, char**, int&, char**, int&);
    bool AddFriend(User*);
    void RemoveFriend(User*);
    bool LikePage(Page*);
    void UnlikePage(Page*);
    void PrintName();
    int getFriendCount();
    int getLikedPagesCount();
    void ViewHome();
    void PrintFriendList();
    void PrintLikedPagesList();
    const char* getAccountID();
};


class Page : public BaseClass {
    static const int maxLikers = 10;
    char* title;

    int noOfLikers;
    BaseClass** likers;
public:
    void PrintName();
    Page(const char*, const char*);
    Page(std::ifstream&);
    ~Page();
    bool AddLiker(BaseClass*);
    void RemoveLiker(BaseClass*);
};



#endif


