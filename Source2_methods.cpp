#include "Source.h"
#include "Source2.h"
#include "Source3.h"
using namespace std;

/***************** Post Class Methods ******************/

Post::Post(const char* id, const char* txt, int dd, int mm, int yyyy, BaseClass* own, int actType, char* actVal)
    : BaseClass(id), owner(own), activity(nullptr), noOfLikers(0), noOfComments(0), likers(nullptr), comments(nullptr) {
    text = new char[strlen(txt) + 1];
    strcpy(text, txt);
    shareDate.setDate(dd, mm, yyyy);
    if (actType != -1) {
        activity = new Activity(actType, actVal);
    }
}

Post::Post(const char* id, const char* txt, const Date& currDate, BaseClass* own, int actType, char* actVal)
    : owner(own), activity(nullptr), noOfLikers(0), noOfComments(0), likers(nullptr), comments(nullptr), BaseClass(id) {
    text = new char[strlen(txt) + 1];
    strcpy(text, txt);
    shareDate = currDate;
    if (actType != -1) {
        activity = new Activity(actType, actVal);
    }
}

Post::Post(ifstream& inFile, char* id, char** pageIds, int& pageCount) : owner(nullptr), activity(nullptr), noOfLikers(0), noOfComments(0), likers(nullptr), comments(nullptr), BaseClass(id) {
    ReadDataFromFile(inFile, id, pageIds, pageCount);
}


Post::~Post() {
    delete[] text;
    if (likers != nullptr) {
        delete[] likers;
    }
    if (comments != nullptr) {
        for (int i = 0; i < noOfComments; ++i) {
            delete comments[i];
        }
        delete[] comments;
    }
    delete activity;
}

void Post::ReadDataFromFile(ifstream& inFile, char* id, char** pageIds, int& pageCount) {
    inFile.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore the dashed line
    inFile.getline(text, 256); // read post text
    char ownerId[10];
    int actType;
    inFile >> actType;
    if (actType != -1) {
        char actVal[100];
        inFile.ignore(std::numeric_limits<streamsize>::max(), '\n'); // ignore newline
        inFile.getline(actVal, 100);
        activity = new Activity(actType, actVal);
    }
    char likedList[256];
    inFile.getline(likedList, 256); // read liked list
    char* token = strtok(likedList, " ");
    while (token != NULL) {
        if (token[0] == 'u') { // liked by user
            BaseClass* liker = SearchUserByID(token);
            AddLiker(liker);
        }
        else if (token[0] == 'p') { // liked by page
            BaseClass* liker = SearchPageByID(token);
            AddLiker(liker);
        }
        token = strtok(NULL, " ");
    }
}

bool Post::AddLiker(BaseClass* liker) {
    if (noOfLikers >= maxLikers) {
        cout << "Liker limit reached!" << endl;
        return false;
    }
    likers[noOfLikers++] = liker;
    return true;
}

void Post::RemoveLiker(BaseClass* liker) {
    for (int i = 0; i < noOfLikers; ++i) {
        if (likers[i] == liker) {
            // shift elements to fill gap
            for (int j = i; j < noOfLikers - 1; ++j) {
                likers[j] = likers[j + 1];
            }
            noOfLikers--;
            return;
        }
    }
}

bool Post::AddComment(Comment* newComment) {
    if (noOfComments >= maxComments) {
        cout << "Comment limit reached!" << endl;
        return false;
    }
    comments[noOfComments++] = newComment;
    return true;
}

void Post::RemoveCommentsOfAccount(BaseClass* account) {
    for (int i = 0; i < noOfComments; ++i) {
        if (comments[i]->getAuthor() == account) {
            delete comments[i];
            // shift elements to fill gap
            for (int j = i; j < noOfComments - 1; ++j) {
                comments[j] = comments[j + 1];
            }
            noOfComments--;
            i--; // after deletion
        }
    }
}

void Post::Print(bool showLikes, bool showComments) {
    cout << "Post ID: " << getAccountID() << endl;
    cout << "Text: " << text << endl;
    cout << "Shared Date: ";
    shareDate.Print();
    cout << "Owner: ";
    owner->PrintName();
    if (activity != nullptr) {
        cout << "Activity: ";
        activity->Print();
    }
    if (showLikes) {
        cout << "Likes: ";
        PrintLikedList();
    }
    if (showComments) {
        cout << "Comments: " << endl;
        PrintComments();
    }
}

void Post::SetOwner(BaseClass* own) {
    owner = own;
}

const BaseClass* Post::getOwner() {
    return owner;
}

const char* Post::getID() {
    return getAccountID();
}

Date Post::getShareDate() {
    return shareDate;
}

void Post::PrintLikedList() {
    for (int i = 0; i < noOfLikers; ++i) {
        likers[i]->PrintName();
    }
}

void Post::PrintComments() {
    for (int i = 0; i < noOfComments; ++i) {
        comments[i]->Print();
    }
}

/***************** Memory Class Methods ******************/

Memory::Memory(const char* id, const char* txt, int dd, int mm, int yyyy, BaseClass* author, Post* orig) : Post(id, txt, dd, mm, yyyy, author) {
    origPost = orig;
}

Memory::Memory(const char* id, const char* txt, const Date& currDate, BaseClass* author, Post* orig) : Post(id, txt, currDate, author) {
    origPost = orig;
}

void Memory::Print(bool showLikes, bool showComments) {
    cout << "Memory: ";
    Post::Print(showLikes, showComments);
}

/***************** Activity Class Methods ******************/

Activity::Activity(int t, const char* val) : typeNo(t), subtype(val) {}

Activity::Activity(ifstream& inFile) {
    inFile >> typeNo;
    char val[100];
    inFile.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore newline
    inFile.getline(val, 100);
    subtype = val;
}

Activity::~Activity() {}

void Activity::Print() {
    cout << "Type: " << typeNo << ", Subtype: " << subtype << endl;
}

/***************** Comment Class Methods ******************/

Comment::Comment(const char* cid, const char* txt, BaseClass* owner) : author(owner) {
    id = new char[strlen(cid) + 1];
    strcpy(id, cid);
    text = new char[strlen(txt) + 1];
    strcpy(text, txt);
}

Comment::Comment(ifstream& inFile, char* postID, char* owner) {
    inFile >> id >> text;
    setAuthor(SearchUserByID(owner));
}

Comment::~Comment() {
    delete[] id;
    delete[] text;
}

void Comment::setAuthor(BaseClass* acc) {
    author = acc;
}

const BaseClass* Comment::getAuthor() {
    return author;
}

void Comment::Print() {
    cout << "Comment ID: " << id << ", Text: " << text << ", Author: ";
    author->PrintName();
}



