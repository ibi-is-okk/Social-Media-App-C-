#ifndef PART2_H
#define PART2_H

#include <iostream>
#include <fstream>
#include <string>
#include "source.h"
#include "source3.h"

using namespace std;

class Activity {
    static const int noOfTypes = 4;
    static const int noOfSubtypes = 3;
    static const char* types[noOfTypes];
    int typeNo;
    char* subtype;
public:
    Activity(int, const char*);
    Activity(std::ifstream&);
    ~Activity();
    void Print();
};

class Comment : public SocialMediaApp{
    char* id;
    char* text;
    BaseClass* author;
public:
    Comment(const char*, const char*, BaseClass*);
    Comment(std::ifstream&, char* postID, char* owner);
    ~Comment();
    void setAuthor(BaseClass* acc);
    const BaseClass* getAuthor();
    void Print();
};

class Post :public BaseClass {  
    static const int maxComments = 10;
    static const int maxLikers = 10;
    char* id;
    char* text;

    int noOfLikers;
    BaseClass** likers;

    Date shareDate;

    Comment** comments;
    int noOfComments;

    Activity* activity;

protected:
    void PrintComments();
    void PrintText();
    BaseClass* owner;

public:
    Post(const char*, const char*, int, int, int, BaseClass*, int = -1, char* = nullptr);
    Post(const char*, const char*, const Date&, BaseClass*, int = -1, char* = nullptr);
    Post(std::ifstream&, char*, char**, int&);
    void ReadDataFromFile(std::ifstream&, char*, char**, int&);
    virtual ~Post();
    Date getShareDate();
    bool AddLiker(BaseClass*);
    void RemoveLiker(BaseClass*);
    bool AddComment(Comment*);
    void RemoveCommentsOfAccount(BaseClass*);
    virtual void Print(bool = false, bool = true);
    void SetOwner(BaseClass*);
    const BaseClass* getOwner();
    const char* getID();
    void PrintLikedList();
    const char* getAccountID();
    void PrintName() override;
};

class Memory : public Post {
    Post* origPost;
public:
    Memory(const char* id, const char* text, int dd, int mm, int yyyy, BaseClass* author, Post* orig);
    Memory(const char* id, const char* text, const Date& currDate, BaseClass* author, Post* orig);
    void Print(bool, bool);
};


#endif


