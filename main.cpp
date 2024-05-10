#include <iostream>
#include <fstream>
#include <string>
#include "Source.h"
#include "Source2.h"
#include "Source3.h"

using namespace std;


int main() {
    SocialMediaApp app;
    app.Run();
    return 0;
}

void SocialMediaApp::Run() {
    bool isLoggedIn = false;
    while (!isLoggedIn) {
        // Ask the user to login
        std::cout << "Enter your user ID to login: ";
        char userId[10];
        std::cin >> userId;
        SetCurrentUser(userId);
        if (currentUser != nullptr) {
            isLoggedIn = true;
        }
        else {
            std::cout << "Invalid user ID. Please try again.\n";
        }
    }

    int option;
    while (isLoggedIn) {
        // Display options for the user
        std::cout << "\nSelect an option:\n";
        std::cout << "1. Set Current User\n";
        std::cout << "2. View Home of Current User\n";
        std::cout << "3. Like a Post\n";
        std::cout << "4. View People who Liked a Post\n";
        std::cout << "5. Comment on a Post\n";
        std::cout << "6. View a Post\n";
        std::cout << "7. Share a Memory\n";
        std::cout << "8. View User's Profile\n";
        std::cout << "9. View Friend List\n";
        std::cout << "10. View Page\n";
        std::cout << "11. View Timeline\n";
        std::cout << "12. Logout\n";
        std::cout << "Enter your choice: ";
        std::cin >> option;

        switch (option) {
        case 1: {
            std::cout << "Enter your user ID: ";
            char userId[10];
            std::cin >> userId;
            SetCurrentUser(userId);
            break;
        }
        case 2:
            ViewHome();
            break;
        case 3: {
            std::cout << "Enter the ID of the post you want to like: ";
            char postId[10];
            std::cin >> postId;
            LikePost(postId);
            break;
        }
        case 4: {
            std::cout << "Enter the ID of the post: ";
            char postId[10];
            std::cin >> postId;
            ViewPostLikedList(postId);
            break;
        }
        case 5: {
            std::cout << "Enter the ID of the post you want to comment on: ";
            char postId[10];
            std::cin >> postId;
            std::cout << "Enter your comment: ";
            char comment[100];
            std::cin.ignore();
            std::cin.getline(comment, 100);
            PostComment(postId, comment);
            break;
        }
        case 6: {
            std::cout << "Enter the ID of the post you want to view: ";
            char postId[10];
            std::cin >> postId;
            ViewPost(postId);
            break;
        }
        case 7: {
            std::cout << "Enter the ID of the post you want to share as a memory: ";
            char postId[10];
            std::cin >> postId;
            std::cout << "Enter the memory text: ";
            char memoryText[100];
            std::cin.ignore();
            std::cin.getline(memoryText, 100);
            ShareMemory(postId, memoryText);
            break;
        }
        case 8:
            /*currentUser->ViewProfile();*/
            break;
        case 9:
            ViewFriendList();
            break;
        case 10: {
            std::cout << "Enter the ID of the page you want to view: ";
            char pageId[10];
            std::cin >> pageId;
            ViewPage(pageId);
            break;
        }
        case 11:
            ViewTimeline();
            break;
        case 12:
            isLoggedIn = false;
            break;
        default:
            std::cout << "Invalid option!\n";
        }
    }
}
