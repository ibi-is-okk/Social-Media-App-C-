#ifndef PART3_H
#define PART3_H

#include <iostream>
#include <fstream>
#include <string>
#include "source.h"
#include "source2.h"

using namespace std;

class Date {
    int date;
    int month;
    int year;
    static Date Today;
public:
    static void setTodaysDate(int, int, int);
    static void setTodaysDate(const Date&);
    static Date getTodaysDate();
    void setDate(int, int, int);
    Date();
    Date(int, int, int);

    void ReadDataFromFile(std::ifstream&);

    bool operator<(const Date& date);
    bool operator>(const Date& date);
    bool operator>=(const Date& D);
    bool operator<=(const Date& D);
    bool operator==(const Date& D);

    void Print();

    int getDate();
    int getMonth();
    int getYear();

    friend std::istream& operator>>(std::istream&, Date&);
};

class SocialMediaApp {
    const int maxFriends = 10;
    const int maxLikedPages = 10;
    const int maxIDLength = 10;
    const char* userFile;
    const char* pageFile;
    const char* postFile;
    const char* commentFile;

    User* currentUser;
    int noOfUsers;
    int noOfPages;
    int noOfPosts;
    int totalNoOfComments;

    User** user;
    Page** page;
    Post** post;
public:
    void ReadUsersFromFile(std::ifstream&, char***, int*, char***, int*);
    void ReadPagesFromFile(std::ifstream&);
    void ReadPostsFromFile(std::ifstream&);
    void ReadCommentsFromFile(std::ifstream&);

    void SetupUsersFriends(char***, int*);
    void SetupUsersLikedPages(char***, int*);
    User* SearchUserByID(const char*);
    Page* SearchPageByID(const char*);
    Post* SearchPostByID(const char*);

    void DeleteUser(User*&);
    void DeletePage(Page*&);
    void DeletePostsOfAuthor(BaseClass*);

    SocialMediaApp();
    static SocialMediaApp* instance;

    SocialMediaApp(const SocialMediaApp&) = delete;
    static SocialMediaApp* getInstance() {
        if (!instance)
            instance = new SocialMediaApp;

        return instance;
    }
    void ReadDataFromFile();

    void ViewPostLikedList(const char*);
    void ViewFriendList();
    void ViewLikedPagesList();
    void ViewHome();
    void ViewTimeline();
    void ViewPage(const char*);
    void ViewPost(const char*);
    void PrintMemories();

    void SetCurrentUser(const char*);

    bool LikePost(const char*);
    bool PostComment(const char*, const char*);
    bool ShareMemory(const char*, const char*);
    ~SocialMediaApp();

};

#endif




