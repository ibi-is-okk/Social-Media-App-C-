#include <iostream>
#include <fstream>
#include <string>
#include "Source.h"
#include "Source2.h"
#include "Source3.h"

using namespace std;

void main()
{
	cout << "\n\n\tSOCIAL MEDIA APP";
	Date::CurrentDate.SetDate(15, 17, 20);

	SocialMediaApp fb;

	char*** tempFriendList = 0;
	char*** tempLikedPages = 0;

	fb.LoadData(tempFriendList, tempLikedPages);
	fb.AssociateFriends(tempFriendList);
	fb.AssociatePages(tempLikedPages);

	fb.LoadAllPosts();
	fb.LoadAllComments();
	fb.run();
	//system("pause");
}


void    run()
{
	char arr[] = "u7";
	char* x = arr;
	char arr2[] = "post5";
	char* y = arr2;
	char arr3[] = "post8";
	char* z = arr3;
	char arr4[] = "Thanks for the wishes";
	char* a = arr4;
	char arr5[] = "p1";
	char* b = arr5;
	char arr6[] = "Ali";
	char* c = arr6;
	SetCurrentUser(x);
	CurrentUser->ViewFriendList();
	CurrentUser->ViewLikedPages();
	CurrentUser->ViewHome();
	CurrentUser->ViewTimeLine();
	PrintLikedList(y);
	cout << "\n-------------------------------------------------------"
		<< "\n\t\tCommand LikePost(5)\n";
	LikePost(y);
	PrintLikedList(y);
	cout << "\n-------------------------------------------------------"
		<< "\n\t\tCommand PostComment(8)\n";
	PostComment(z, a);
	ViewPost(z);
	cout << "\n\n-------------------------------------------------\n";
	ViewPage(b);
	cout << "\n\n-------------------------------------------------\n";
	Search(c);
	cout << endl;
}

int SocialMediaApp::totalPosts = 0;
int SocialMediaApp::totalComments = 0;




