#include "Source.h"
#include "Source2.h"
#include "Source3.h"

/***************** Date Class Methods ******************/

Date::Date() {}

Date::Date(int d, int m, int y) : date(d), month(m), year(y) {}

void Date::ReadDataFromFile(ifstream& inFile) {
    inFile >> date >> month >> year;
}

bool Date::operator<(const Date& d) {
    if (year < d.year)
        return true;
    else if (year > d.year)
        return false;
    else {
        if (month < d.month)
            return true;
        else if (month > d.month)
            return false;
        else {
            if (date < d.date)
                return true;
            else
                return false;
        }
    }
}

bool Date::operator>(const Date& d) {
    if (year > d.year)
        return true;
    else if (year < d.year)
        return false;
    else {
        if (month > d.month)
            return true;
        else if (month < d.month)
            return false;
        else {
            if (date > d.date)
                return true;
            else
                return false;
        }
    }
}

bool Date::operator>=(const Date& d) {
    return (*this > d) || (*this == d);
}

bool Date::operator<=(const Date& d) {
    return (*this < d) || (*this == d);
}

bool Date::operator==(const Date& d) {
    return (year == d.year) && (month == d.month) && (date == d.date);
}

void Date::Print() {
    cout << date << "-" << month << "-" << year << endl;
}

int Date::getDate() {
    return date;
}

int Date::getMonth() {
    return month;
}

int Date::getYear() {
    return year;
}

/***************** SocialMediaApp Class Methods ******************/

SocialMediaApp::SocialMediaApp() : userFile("Users.txt"), pageFile("Pages.txt"), postFile("Posts.txt"), commentFile("Comments.txt"),
currentUser(nullptr), noOfUsers(0), noOfPages(0), noOfPosts(0), totalNoOfComments(0),
user(nullptr), page(nullptr), post(nullptr) {}

SocialMediaApp::~SocialMediaApp() {
    if (currentUser != nullptr) {
        delete currentUser;
    }
    if (user != nullptr) {
        for (int i = 0; i < noOfUsers; ++i) {
            delete user[i];
        }
        delete[] user;
    }
    if (page != nullptr) {
        for (int i = 0; i < noOfPages; ++i) {
            delete page[i];
        }
        delete[] page;
    }
    if (post != nullptr) {
        for (int i = 0; i < noOfPosts; ++i) {
            delete post[i];
        }
        delete[] post;
    }
}

void SocialMediaApp::ReadDataFromFile() {
    ifstream userInFile(userFile);
    ifstream pageInFile(pageFile);
    ifstream postInFile(postFile);
    ifstream commentInFile(commentFile);
    if (userInFile && pageInFile && postInFile && commentInFile) {
        char** friendIds = new char* [maxFriends];
        char** pageIds = new char* [maxLikedPages];
        ReadUsersFromFile(userInFile, &friendIds, &noOfUsers, &pageIds, &noOfPages);
        ReadPagesFromFile(pageInFile);
        ReadPostsFromFile(postInFile);
        ReadCommentsFromFile(commentInFile);
        SetupUsersFriends(&friendIds, &noOfUsers);
        SetupUsersLikedPages(&pageIds, &noOfPages);
        delete[] friendIds;
        delete[] pageIds;
    }
    else {
        cout << "Error: Unable to open file(s)!" << endl;
    }

}

void SocialMediaApp::ReadUsersFromFile(ifstream& inFile, char*** friendIds, int* userCount, char*** pageIds, int* pageCount) {
    inFile >> *userCount;
    *friendIds = new char* [*userCount];
    *pageIds = new char* [*userCount];
    for (int i = 0; i < *userCount; ++i) {
        char id[10];
        inFile >> id;
        (*friendIds)[i] = id;
        (*pageIds)[i] = id;
    }
}

void SocialMediaApp::ReadPagesFromFile(ifstream& inFile) {
    inFile >> noOfPages;
    page = new Page * [noOfPages];
    for (int i = 0; i < noOfPages; ++i) {
        page[i] = new Page(inFile);
    }
}

void SocialMediaApp::ReadPostsFromFile(ifstream& inFile) {
    inFile >> noOfPosts;
    post = new Post * [noOfPosts];
    char** pageIds = new char* [noOfPosts];
    for (int i = 0; i < noOfPosts; ++i) {
        post[i] = new Post(inFile, nullptr, pageIds, noOfPages);
    }
    delete[] pageIds;
}

void SocialMediaApp::ReadCommentsFromFile(ifstream& inFile) {
    inFile >> totalNoOfComments;
    for (int i = 0; i < totalNoOfComments; ++i) {
        char postID[10];
        char owner[10];
        Comment* newComment = new Comment(inFile, postID, owner);
        Post* currentPost = SearchPostByID(postID);
        currentPost->AddComment(newComment);
    }
}

void SocialMediaApp::SetupUsersFriends(char*** friendIds, int* userCount) {
    for (int i = 0; i < *userCount; ++i) {
        User* currentUser = SearchUserByID((*friendIds)[i]);
        if (currentUser) {
            for (int j = 0; j < currentUser->getFriendCount(); ++j) {
                User* friendToAdd = SearchUserByID(currentUser->friends[j]->getAccountID());
                if (friendToAdd) {
                    currentUser->AddFriend(friendToAdd);
                }
            }
        }
    }
}


void SocialMediaApp::SetupUsersLikedPages(char*** pageIds, int* pageCount) {
    for (int i = 0; i < *pageCount; ++i) {
        User* currentUser = SearchUserByID((*pageIds)[i]);
        if (currentUser) {
            for (int j = 0; j < currentUser->getLikedPagesCount(); ++j) {
                Page* pageToLike = dynamic_cast<Page*>(SearchPageByID(currentUser->likedPages[j]->getAccountID()));
                if (pageToLike) {
                    currentUser->LikePage(pageToLike);
                }
            }
        }
    }
}


User* SocialMediaApp::SearchUserByID(const char* id) {
    for (int i = 0; i < noOfUsers; ++i) {
        if (strcmp(user[i]->getAccountID(), id) == 0) {
            return dynamic_cast<User*>(user[i]);
        }
    }
    return nullptr;
}

Page* SocialMediaApp::SearchPageByID(const char* id) {
    for (int i = 0; i < noOfPages; ++i) {
        if (strcmp(page[i]->getAccountID(), id) == 0) {
            return dynamic_cast<Page*>(page[i]);
        }
    }
    return nullptr;
}

Post* SocialMediaApp::SearchPostByID(const char* id) {
    for (int i = 0; i < noOfPosts; ++i) {
        if (strcmp(post[i]->getAccountID(), id) == 0) {
            return post[i];
        }
    }
    return nullptr;
}

void SocialMediaApp::SetCurrentUser(const char* id) {
    currentUser = SearchUserByID(id);
}

void SocialMediaApp::ViewPostLikedList(const char* postId) {
    Post* currentPost = SearchPostByID(postId);
    currentPost->PrintLikedList();
}

void SocialMediaApp::ViewFriendList() {
    if (currentUser != nullptr) {
        currentUser->PrintFriendList();
    }
    else {
        cout << "No current user set!" << endl;
    }
}

void SocialMediaApp::ViewLikedPagesList() {
    if (currentUser != nullptr) {
        currentUser->PrintLikedPagesList();
    }
    else {
        cout << "No current user set!" << endl;
    }
}

void SocialMediaApp::ViewHome() {
    if (currentUser != nullptr) {
        currentUser->ViewHome();
    }
    else {
        cout << "No current user set!" << endl;
    }
}

void SocialMediaApp::ViewTimeline() {
    // Implement according to requirements
}

void SocialMediaApp::ViewPage(const char* pageId) {
    Page* currentPage = SearchPageByID(pageId);
    // Implement according to requirements
}

void SocialMediaApp::ViewPost(const char* postId) {
    Post* currentPost = SearchPostByID(postId);
    currentPost->Print(true, true);
}

void SocialMediaApp::PrintMemories() {
    if (currentUser != nullptr) {
        currentUser->PrintMemories();
    }
    else {
        cout << "No current user set!" << endl;
    }
}

bool SocialMediaApp::LikePost(const char* postId) {
    if (currentUser != nullptr) {
        Post* postToLike = SearchPostByID(postId);
        if (postToLike != nullptr) {
            return postToLike->AddLiker(currentUser);
        }
        else {
            cout << "Post not found!" << endl;
        }
    }
    else {
        cout << "No current user set!" << endl;
    }
    return false;
}

bool SocialMediaApp::PostComment(const char* postId, const char* commentText) {
    if (currentUser != nullptr) {
        Post* postToAddComment = SearchPostByID(postId);
        if (postToAddComment != nullptr) {
            Comment* newComment = new Comment(postId, commentText, currentUser);
            return postToAddComment->AddComment(newComment);
        }
        else {
            cout << "Post not found!" << endl;
        }
    }
    else {
        cout << "No current user set!" << endl;
    }
    return false;
}

bool SocialMediaApp::ShareMemory(const char* postId, const char* memoryText) {
    if (currentUser != nullptr) {
        Post* originalPost = SearchPostByID(postId);
        if (originalPost != nullptr) {
            Memory* newMemory = new Memory(postId, memoryText, Date::getTodaysDate(), currentUser, originalPost);
            return true; // Implement as required
        }
        else {
            cout << "Post not found!" << endl;
        }
    }
    else {
        cout << "No current user set!" << endl;
    }
    return false;
}

SocialMediaApp* SocialMediaApp::instance = nullptr;






