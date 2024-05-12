#ifndef SOCIALMEDIAAPP_H
#define SOCIALMEDIAAPP_H

#include "Main.h"
#include <iostream>
using namespace std;


class SocialMediaApp
{
	Users* CurrentUser;
	Users** UsersList;
	Pages** PageList;
	Posts** AllPosts;

	static  int totalPosts;
	static  int totalComments;
public:
	SocialMediaApp();
	~SocialMediaApp();
	void LoadData(char***& tempFriendList, char***& tempLikedPages);
	void AssociatePages(char***& tempLikedPages);
	void AssociateFriends(char***& tempFriendList);
	void LoadAllPosts();
	void LoadAllComments();
	BaseClass*& SearchObjectByID(char* temp);
	Pages*& SearchPageByID(char* str);
	Users*& SearchUserByID(char* str);
	Posts*& SearchPostByID(char* str);
	void LikePost(char* postID);
	void PrintLikedList(char* postID);
	void PostComment(char* postID, char* text);
	void ViewPost(char* postID);
	void ViewPage(char* pageID);
	void SetCurrentUser(char* user);
	void Printmem(char* , string);
	void run();

};

#endif // SOCIALMEDIAAPP_H
