#include <iostream>
#include "SocialMediaApp.h"
//#include "Main.h"
#include <fstream>
#include <string>
using namespace std;

#define BG_RESET "\033[49m"
#define BG_RED     "\033[41m"
#define BG_GREEN   "\033[42m"
#define BG_YELLOW  "\033[43m"
#define BG_BLUE    "\033[44m"
#define BG_MAGENTA "\033[45m"
#define BG_CYAN    "\033[46m"
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#include <conio.h>


/************* SocialMediaApp class **************/

    SocialMediaApp::SocialMediaApp()
	{
		CurrentUser = 0;
		UsersList = 0;
		PageList = 0;
		AllPosts = 0;
	}
	SocialMediaApp::~SocialMediaApp()
	{
		if (CurrentUser != 0)
			CurrentUser = NULL;

		if (PageList != 0)
		{
			for (int i = 0;i < 12;i++)
				delete PageList[i];
			delete[] PageList;
		}


		if (UsersList != 0)
		{
			for (int i = 0;i < 20;i++)
				delete UsersList[i];
			delete[] UsersList;
		}



		if (AllPosts)
			delete[] AllPosts;
	}

	void SocialMediaApp::LoadData(char***& tempFriendList, char***& tempLikedPages)
	{

		int x = 0, noUsers = 0, noPages = 0;
		ifstream fin;

		fin.open("Users.txt");
		if (fin.is_open() == false)	
		{
			cout << "File not opening!";
			return;
		}
		fin >> noUsers;
		BaseClass::SetTotalUsers(noUsers);  
		UsersList = new Users * [noUsers];	//initialising  **UsersList
		for (int i = 0;i < noUsers;i++)
		{
			UsersList[i] = new Users();
		}

		tempFriendList = new char** [noUsers];   //intialising tempFriendList and tempPagesList 
		tempLikedPages = new char** [noUsers];
		for (int i = 0;i < noUsers;i++)
		{
			tempFriendList[i] = new char* [10];
			tempLikedPages[i] = new char* [10];
		}

		while (x < 20)	//reading Users 
		{
			UsersList[x]->ReadDataFromFile(fin, tempFriendList, tempLikedPages, x);
			x++;
		}
		fin.close();

		x = 0;
		fin.open("Pages.txt");
		fin >> noPages;
		Pages::SetTotalPages(noPages);

		if (fin.is_open() == false)		
		{
			cout << "File not opening";
			return;
		}

		PageList = new Pages * [noPages];	//intialising **PagesList 
		for (int i = 0;i < noPages;i++)
		{
			PageList[i] = new Pages();
		}

		while (x < noPages)	//reading Pages 
		{
			PageList[x]->LoadPagesFromFile(fin);
			x++;
		}
		fin.close();

	}
	void SocialMediaApp::AssociatePages(char***& tempLikedPages)
	{
		int x = 0;
		int noPages = 12;
		while (x != noPages)
		{
			for (int y = 0;*tempLikedPages[x][y] != '\0';y++)
			{
				UsersList[x]->AddPage(SearchPageByID(tempLikedPages[x][y]));
			}
			x++;
		}
		
		if (tempLikedPages)  //dlt temp
		{
			for (int i = 0;i < 20;i++)
			{
				for (int j = 0;*tempLikedPages[i][j] != '\0';j++)
				{
					if (tempLikedPages[i][j] != NULL)
						delete[]tempLikedPages[i][j];
				}
				delete[] tempLikedPages[i];
			}
			delete[] tempLikedPages;
		}
	}
	void SocialMediaApp::AssociateFriends(char***& tempFriendList)
	{
		int x = 0;
		int noFrnds = 20;
		while (x != noFrnds)
		{
			for (int y = 0;*tempFriendList[x][y] != '\0';y++)
			{
				UsersList[x]->AddFriend(SearchUserByID(tempFriendList[x][y]));
			}
			x++;
		}
		
		if (tempFriendList) //dlt temp
		{
			for (int i = 0;i < 20;i++)
			{
				for (int j = 0;*tempFriendList[i][j] != '\0';j++)
				{
					if (tempFriendList[i][j] != NULL)
						delete[] tempFriendList[i][j];
				}
				delete[] tempFriendList[i];
			}
			delete[] tempFriendList;
		}
	}

	void SocialMediaApp::LoadAllPosts()
	{
		ifstream fin("Posts.txt");
		if (fin.is_open())
		{
			char tempSharedBy[10];
			fin >> totalPosts;
			AllPosts = new Posts * [totalPosts];

			int CheckPostType = 0;
			for (int i = 0;i < totalPosts;i++)
			{
				fin >> CheckPostType;
				if (CheckPostType == 1)
				{
					AllPosts[i] = new Posts();			
				}

				else if (CheckPostType == 2)
				{
					AllPosts[i] = new Activity();
				}
				AllPosts[i]->LoadFromFile(fin);
				
				fin >> tempSharedBy; //reading info for SharedBy and LikedBY baki alrdy done
				BaseClass* Author = {};
				if (tempSharedBy[0] == 'u')
					Author = SearchUserByID(tempSharedBy);
				else if (tempSharedBy[0] == 'p')
					Author = SearchPageByID(tempSharedBy);

				AllPosts[i]->SetSharedBy(Author); //Assosciation
				Author->AddPostToTimeline(AllPosts[i]);

				char tempLikedBy[10][10];

				int totalLikes = 0;
				for (; ; totalLikes++)
				{
					fin >> tempLikedBy[totalLikes];
					if (tempLikedBy[totalLikes][0] == '-')
						break;
				}
				tempLikedBy[totalLikes][0] = '\0';

				AllPosts[i]->SetTotalLikes(totalLikes);

				BaseClass** LikedBy = new BaseClass * [10];
				for (int j = 0, c = 0; j < totalLikes; j++)
				{
					if (tempLikedBy[j][0] == 'u') 
					{
						LikedBy[c] = SearchUserByID(tempLikedBy[j]);
						c++;
					}
					else if (tempLikedBy[j][0] == 'p')
					{
						LikedBy[c] = SearchPageByID(tempLikedBy[j]);
						c++;
					}
				}

				AllPosts[i]->SetLikedBy(LikedBy);
			}
			fin.close();
		}
		else
			cout << "\nFile not opening\n";


	}
	void SocialMediaApp::LoadAllComments()
	{
		char	tempCommentID[10],
			tempPostID[10],
			tempAuthor[10],
			tempComment[300];

		ifstream fin("Comments.txt");
		if (fin.is_open())
		{
			fin >> totalComments;
			Comments** CommentsList = new Comments * [totalComments];

			for (int i = 0;i < totalComments;i++)
			{
				CommentsList[i] = new Comments();
				fin >> tempCommentID
					>> tempPostID
					>> tempAuthor;
				fin.ignore(1);
				fin.getline(tempComment, 300, '\n');

				BaseClass* Author = SearchObjectByID(tempAuthor);
				Posts* post = SearchPostByID(tempPostID);
				CommentsList[i]->Setter(tempCommentID, Author, tempComment);
				post->AddComment(CommentsList[i]);

			}
			if (CommentsList)
				delete[] CommentsList;
		}
		else
			cout << "\nFile not opening \n";


	}


	BaseClass*& SocialMediaApp::SearchObjectByID(char* temp)
	{
		int total = 0;
		total = Users::GetTotalUsers();
		total = 20;

		BaseClass* ANS;

		for (int i = 0; i < total; i++)
		{
			if (temp[0] == 'u')
			{
				ANS = SearchUserByID(temp);
				break;
			}
			else if (temp[0] == 'p')
			{
				ANS = SearchPageByID(temp);
				break;
			}
		}

		return ANS;
	}
	Pages*& SocialMediaApp::SearchPageByID(char* str)
	{
		int length = String::strlen(str);
		int z = 0, total = 0;

		total = Users::GetTotalUsers();
		total = 20;

		for (int y = 0;y < 20;y++)	//pages
		{
			char* str2 = PageList[y]->GetID();	
			if (String::strcmp(str2, str) == true)  
				return PageList[y];
		}
	}
	Users*& SocialMediaApp::SearchUserByID(char* arr)
	{
		int length = String::strlen(arr);
		int z = 0, total = 0;

		total = Users::GetTotalUsers();
		total = 20;

		for (int y = 0;y < 20;y++)	//users
		{
			char* str2 = UsersList[y]->GetID();
			if (String::strcmp(str2, arr) == true) 
				return UsersList[y];
		}

	}
	Posts*& SocialMediaApp::SearchPostByID(char* str)
	{

		for (int y = 0;y < totalPosts;y++)	//posts
		{
			char* str2 = AllPosts[y]->GetID();	
			if (String::strcmp(str2, str) == true)	
				return AllPosts[y];
		}

	}

	void SocialMediaApp::LikePost(char* postID)
	{
		Posts* post = SearchPostByID(postID);
		BaseClass* author = CurrentUser;
		post->AddLike(author);
		cout << "-> " << postID << " Liked: " ;
	}
	void SocialMediaApp::PrintLikedList(char* postID)
	{
		cout << "\n\n-------------------------------------------------\n";
		cout << "|\t\t Liked List : \t\t\t | ";
		cout << "\t\t\t\t\t\n-------------------------------------------------\n";
		Posts* post = SearchPostByID(postID);
		post->PrintAllLikes();
	}

	void SocialMediaApp::PostComment(char* postID, char* text)
	{
		Posts* post = SearchPostByID(postID);
		string CommentID = "c" + std::to_string(++totalComments);
		BaseClass* Author = CurrentUser;
		char* char_arr = &CommentID[0];
		post->AddComment(char_arr, Author, text);
	}

	void SocialMediaApp::ViewPost(char* postID)
	{
		cout << "\n-> Viewing Post: "<<postID;
		Posts* post = SearchPostByID(postID);
		post->Print(0);
	}
	void SocialMediaApp::ViewPage(char* pageID)
	{
		Pages* page = SearchPageByID(pageID);
		page->PrintTimeline();
	}

	void SocialMediaApp::Printmem(char* po, string text)
	{
		cout << "\n  Throw Back: " << text ;
		Posts* p = SearchPostByID(po);
		p->Print(0);

	}

	void SocialMediaApp::SetCurrentUser(char* user)
	{
		if (user != 0)
		{
			CurrentUser = SearchUserByID(user);
			cout << "\n -) Welcome ";
			CurrentUser->Print();
			cout <<"\n";
		}
		else
			cout << "\nNo User available\n";
		return;
	}


	void SocialMediaApp::run()
	{
		cout << CYAN;
		char c = 'o'; //extra
		char arr[] = "u7";
		char* x = arr;
		char arr2[] = "post5";
		char* y = arr2;
		char arr3[] = "post8";
		char* z = arr3;
		char arr4[] = "Meri Birthday pe toh wish ni kia tha";
		char* a = arr4;
		char arr5[] = "p1";
		char* b = arr5;
		string d = "What a Great Day";
		SetCurrentUser(x);
		cout << MAGENTA;
		c=_getch();
		CurrentUser->ViewFriendList();
		c=_getch();
		CurrentUser->ViewLikedPages();
		c=_getch();
		CurrentUser->ViewHome();
		c=_getch();
		CurrentUser->ViewTimeLine();
		c=_getch();
		PrintLikedList(y);
		c=_getch();
		cout << "\n-------------------------------------------------\n";
		cout << "|\t\tLike Post: "<<y<<"\t\t | ";
		cout << "\t\t\t\t\t\n-------------------------------------------------\n\n";
		LikePost(y);
		c=_getch();
		PrintLikedList(y);
		c=_getch();
		cout << "\n\n-------------------------------------------------\n";
		cout << "|\t\tView " << z<<":\t\t\t | ";
		cout << "\t\t\t\t\t\n-------------------------------------------------\n";
		ViewPost(z);  //POST BFR
		c=_getch();
		cout << "\n-------------------------------------------------\n";
		cout << "|\t\tPost Comment:\t\t\t|";
		cout << "\t\t\t\t\t\n-------------------------------------------------\n";
		PostComment(z, a);
		
		ViewPost(z); //POST AFTR
		c=_getch();
		cout << "\n\n-------------------------------------------------\n";
		cout << "|\t\tView Page:\t\t\t|";
		cout << "\t\t\t\t\t\n-------------------------------------------------\n";
		ViewPage(b);
		c=_getch();
		cout << "\n\n-------------------------------------------------\n";
		cout << "|\t\tShare Memory:\t\t\t|";
		cout << "\t\t\t\t\t\n-------------------------------------------------\n";
		Printmem(z, d);
		c=_getch();
		cout << "\n\n-------------------------------------------------\n";

		cout << endl;
	}


int SocialMediaApp::totalPosts = 0;
int SocialMediaApp::totalComments = 0;
