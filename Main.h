
#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <fstream>
//using namespace std;

class Posts;
class Date;
class Comments;
class Pages;


class String
{
public:
	static int   strlen(char* str);
	static char* strcpy(char* str);
	static bool  strcmp(char* str1, char* str2);
	
};

class BaseClass {
protected:
    char* ID; //Pages and Users ID
    static int totalPages; // set bfr calling constructor
    static int totalUsers;
public:
    BaseClass();
    virtual ~BaseClass();
    virtual void Print() {};
    virtual void PrintName() {};
    virtual void AddPostToTimeline(Posts*) {};

    static void SetTotalPages(int TP);
    static void SetTotalUsers(int TU);
};

class Date {
	int date;
	int Month;
	int Year;
public:
	static Date CurrentDate;
	void ReadFromFile(std::ifstream& fin, int, int, int);
	Date(int, int, int);
	bool IsLatestPost();
	void SetDate(int, int, int);
	void Print();
};



class Posts {

protected:
	char* ID;
	char* Text;
	BaseClass* Author;
	BaseClass** Likers;
	Comments** commenters;
	Date shareDate;
	int	noOfLikers;
	int	noOfComments;

public:
	Posts();
	virtual ~Posts();
	virtual void LoadFromFile(std::ifstream& fin);
	virtual void Print(int);
	void AddLike(BaseClass*& currentUser);
	void AddComment(Comments* Commentors);
	void PrintAllLikes();
	void PrintComments();
	void AddComment(char* CommentID, BaseClass*& currentUser, char* text);
	void SetLikedBy(BaseClass**& likers);
	void SetSharedBy(BaseClass* author);
	char* GetID();
	char* GetText();
	void SetTotalLikes(int TL);
};

class Pages : public BaseClass
{
private:
	char* Title;
	Posts** TimeLine;
	int	no_of_posts;
public:
	Pages();
	~Pages();
	Pages(const Pages& rhs);
	const Pages& operator=(const Pages& rhs)
	{
		if (&rhs != this)
		{
			ID = String::strcpy(rhs.ID);
			Title = String::strcpy(rhs.Title);
			totalPages = rhs.totalPages;
			TimeLine = new Posts * [no_of_posts];
			for (int i = 0;i < no_of_posts;i++)
			{
				TimeLine[i] = new Posts;
				TimeLine[i] = rhs.TimeLine[i];
			}
		}
		return *this;
	}
	void LoadPagesFromFile(std::ifstream&);
	void Print();
	void PrintName();
	void PrintTimeline();
	void AddPostToTimeline(Posts* Post);
	void ViewPostInLast24Hours();
	char* GetID();
	char* GetTitle();
};

class Users :public BaseClass
{
private:
	char* firstName;
	char* lastName;
	Posts** Timeline;
	Users** friends;
	Pages** LikedPages;
	int		no_of_posts;
	int     noOfFriends;
	int     noOfLikedPages;
public:
	Users();
	~Users();
	Users(const Users& rhs);
	const Users& operator=(const Users& rhs) //copy constructor deep copy
	{
		if (&rhs != this)
		{
			ID = String::strcpy(rhs.ID);
			firstName = String::strcpy(rhs.firstName);
			lastName = String::strcpy(rhs.lastName);
			totalUsers = rhs.totalUsers;
			noOfFriends = rhs.noOfFriends;
			noOfLikedPages = rhs.noOfLikedPages;

			friends = new Users * [noOfFriends];
			for (int i = 0;i < noOfFriends;i++)
			{
				friends[i] = new Users();
				friends[i] = rhs.friends[i];
			}

			LikedPages = new Pages * [noOfLikedPages];
			for (int i = 0;i < noOfLikedPages;i++)
			{
				LikedPages[i] = new Pages();
				LikedPages[i] = rhs.LikedPages[i];
			}

			Timeline = new Posts * [no_of_posts];
			for (int i = 0;i < no_of_posts;i++)
			{
				Timeline[i] = new Posts;
				Timeline[i] = rhs.Timeline[i];
			}
		}
		return *this;

	}

	void ReadDataFromFile(std::ifstream& fin, char***& tempFriendList, char***& tempLikedPages, const int a); //called frm social media app
	void Print();
	void PrintName();
	void ViewFriendList();
	void ViewLikedPages();
	void ViewHome();
	void ViewTimeLine();
	void PrintLatestPosts();
	void AddPage(Pages*& PagePtr);
	void AddFriend(Users*& Frndptr);
	void AddPostToTimeline(Posts* Post);
	char* GetID();
	char* GetfName();
	char* GetlName();
	static int  GetTotalUsers();
};




class Comments {
private:
	BaseClass* author;
	char* Text;
	char* ID;
	static int TotalComments;
public:
	Comments();
	~Comments();
	void Print();
	void Setter(char* id, BaseClass*& commentBy, char* text); //Aggregation with BaseClass
};

class Activity : public Posts
{
private:
	int typeNo;
	char* Value;
public:
	Activity();
	~Activity();
	void LoadFromFile(std::ifstream& fin);
	void Print(int);
};



#endif // MAIN_H
