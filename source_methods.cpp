#include "Source.h"
#include "Source2.h"
#include "Source3.h"

/*******************BAseClass Methods*******************/

class BaseClass {
protected:
    char* id;
public:
    BaseClass(const char* id) {
        setId(id);
    }

    ~BaseClass() {
        delete[] id;
    }

    void setId(const char* newId) {
        if (id != nullptr) {
            delete[] id;
        }
        id = new char[strlen(newId) + 1];
        strcpy(id, newId);
    }

    const char* getAccountID() const {
        return id;
    }
    void setAccountID(const char* newId) {
        setId(newId);
    }
};


/***************** User Class Methods ******************/

User::User(char* id, char* fName, char* lName) : BaseClass(id) {
    firstName = new char[strlen(fName) + 1];
    strcpy(firstName, fName);
    lastName = new char[strlen(lName) + 1];
    strcpy(lastName, lName);
    friends = new User * [maxFriends];
    noOfFriends = 0;
    likedPages = new Page * [maxNoOfLikedPages];
    noOfLikedPages = 0;
}

User::User(ifstream& inFile, char** friendIds, int& friendCount, char** pageIds, int& pageCount) : BaseClass("") {
    ReadDataFromFile(inFile, friendIds, friendCount, pageIds, pageCount);
}

User::~User() {
    delete[] firstName;
    delete[] lastName;
    if (friends != nullptr) {
        for (int i = 0; i < noOfFriends; ++i) {
            delete friends[i];
        }
        delete[] friends;
    }
    if (likedPages != nullptr) {
        delete[] likedPages;
    }
}

void User::ReadDataFromFile(ifstream& inFile, char** friendIds, int& friendCount, char** pageIds, int& pageCount) {
    char id[10];
    inFile >> id >> firstName >> lastName;
    setAccountID(id);
    inFile >> friendCount;
    for (int i = 0; i < friendCount; ++i) {
        friends[i] = new User(inFile, friendIds, friendCount, pageIds, pageCount);
    }
    inFile >> pageCount;
    for (int i = 0; i < pageCount; ++i) {
        likedPages[i] = new Page(inFile);
    }
}

bool User::AddFriend(User* friendToAdd) {
    if (noOfFriends >= maxFriends) {
        cout << "Friend limit reached!" << endl;
        return false;
    }
    friends[noOfFriends++] = friendToAdd;
    return true;
}

bool User::LikePage(Page* pageToLike) {
    if (noOfLikedPages >= maxNoOfLikedPages) {
        cout << "Page like limit reached!" << endl;
        return false;
    }
    likedPages[noOfLikedPages++] = pageToLike;
    return true;
}

void User::PrintName() {
    cout << "User: " << firstName << " " << lastName << endl;
}

int User::getFriendCount() {
    return noOfFriends;
}

int User::getLikedPagesCount() {
    return noOfLikedPages;
}

//void User::ViewHome() {
//    cout << "Home Page for User: "  << endl;
//    cout << "-------------------------" << endl;
//    cout << "Posts shared by friends in the last 24 hours:" << endl;
//    for (int i = 0; i < getFriendCount(); ++i) {
//        User* friendUser = friends[i];
//        if (friendUser != nullptr) {
//            friendUser->ViewPostsInLast24Hours();
//        }
//    }
//    cout << endl << "Posts shared by liked pages in the last 24 hours:" << endl;
//    for (int i = 0; i < getLikedPagesCount(); ++i) {
//        Page* likedPage = likedPages[i];
//        if (likedPage != nullptr) {
//            likedPage->ViewPostsInLast24Hours();
//        }
//    }
//}

void User::PrintFriendList() {
    cout << "Friend List of " << firstName << " " << lastName << ":" << endl;
    for (int i = 0; i < noOfFriends; ++i) {
        cout << i + 1 << ". ";
        friends[i]->PrintName();
    }
}

void User::PrintLikedPagesList() {
    cout << "Liked Pages List of " << firstName << " " << lastName << ":" << endl;
    for (int i = 0; i < noOfLikedPages; ++i) {
        cout << i + 1 << ". ";
        likedPages[i]->PrintName();
    }
}
//
//void User::ViewPostsInLast24Hours() {
//    Date currentDate = Date::getTodaysDate();
//    for (int i = 0; i < 12; ++i) {
//        if (currentDate - posts[i]->getShareDate() <= 1) { // Assuming operator- returns the difference in days
//            posts[i]->Print(true, true); // Assuming Print function prints the post along with its comments
//        }
//    }
//}




/***************** Page Class Methods ******************/

Page::Page(const char* id, const char* pgTitle) : BaseClass(id) {
    title = new char[strlen(pgTitle) + 1];
    strcpy(title, pgTitle);
    likers = new BaseClass * [maxLikers];
    noOfLikers = 0;

}

Page::Page(ifstream& inFile) : BaseClass("") {
    char id[10];
    inFile >> id >> title;
    setAccountID(id);
}

Page::~Page() {
    delete[] title;
    if (likers != nullptr) {
        delete[] likers;
    }
}

bool Page::AddLiker(BaseClass* liker) {
    if (noOfLikers >= maxLikers) {
        cout << "Liker limit reached!" << endl;
        return false;
    }
    likers[noOfLikers++] = liker;
    return true;
}

void Page::PrintName() {
    cout << "Page: " << title << endl;
}


//void Page::ViewPostsInLast24Hours() {
//    Date currentDate = Date::getTodaysDate();
//    for (int i = 0; i < 12; ++i) {
//        if (currentDate - posts[i]->getShareDate() <= 1) { // Assuming operator- returns the difference in days
//            posts[i]->Print(true, true); // Assuming Print function prints the post along with its comments
//        }
//    }
//}
