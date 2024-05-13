#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include "Main.h"
#include "SocialMediaApp.h"
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

/******************* Helper Class ****************/

	int String::strlen(char* str)
	{
		int size = 0, i = 0;
		for (i = 0;str[i] != '\0';i++)
		{
			size++;
		}
		size += 1;
		return size;
	}
	char* String::strcpy(char* str)
	{
		int i = 0, size = 0;
		size = strlen(str);
		char* temp = 0;
		if (size > 0)
		{
			temp = new char[size];
			for (i = 0;i < size - 1;i++)
			{
				if (str[i] >= 0)
					temp[i] = str[i];
			}
			temp[i] = '\0';
		}
		return temp;
	}
	bool String::strcmp(char* str1, char* str2)
	{
		if (strlen(str1) != strlen(str2))
			return false;

		for (int i = 0; i < strlen(str1); i++)
			if (str1[i] != str2[i])
				return false;

		return true;
	}


	/******************* Date Class ****************/

	//Date CurrentDate;
	void  Date::ReadFromFile(ifstream& fin, int day = 0, int month = 0, int year = 0)
	{
		fin >> day >> month >> year;
		date = day;
		Month = month;
		Year = year;
	}
	Date::Date(int D = 0, int M = 0, int Y = 0)
	{
		date = D;
		Month = M;
		Year = Y;
	}
	bool Date::IsLatestPost()
	{
		return (date == CurrentDate.date - 1 || date == CurrentDate.date) && Month == CurrentDate.Month && Year == CurrentDate.Year;
	}
	void Date::SetDate(int d, int m, int y)
	{
		date = d;
		Month = m;
		Year = y;
	}
	void Date::Print()
	{
		cout << " " << date << "/" << Month << "/" << Year  << endl;
	}

Date Date::CurrentDate(0, 0, 0); //Date intialized


/******************* BaseClass Class ****************/

	BaseClass::BaseClass()
	{
		ID = 0;
	}
	BaseClass::~BaseClass()
	{
		if (ID)
			delete[] ID;
	}
	void BaseClass::SetTotalPages(int TotalPgs)
	{
		totalPages = TotalPgs;
	}
	void BaseClass::SetTotalUsers(int TotalUsers)
	{
		totalUsers = TotalUsers;
	}

int BaseClass::totalPages = 0; //static intialized 
int BaseClass::totalUsers = 0;

/******************* Comments Class ****************/

	Comments::Comments()
	{
		Text = ID = 0;
		author = 0;
		TotalComments++;
	}
	Comments::~Comments()
	{
		if (ID != 0)
			delete[] ID;
		if (Text != 0)
			delete[] Text;
		author = NULL;
	}

	void Comments::Print()
	{
		cout << "\t~";
		author->PrintName();
		cout << "wrote: " << " \"" << Text << "\" " << endl;
	}
	void Comments::Setter(char* id, BaseClass*& commentBy, char* text)
	{
		ID = String::strcpy(id);
		author = commentBy;
		Text = String::strcpy(text);

	}

int Comments::TotalComments = 0;

/******************* Posts Class ****************/

	Posts::Posts()
	{
		ID = Text = 0;
		Author = 0;
		Likers = 0;
		commenters = 0;
		noOfLikers = 0;
		noOfComments = 0;
	}
	Posts::~Posts()
	{
		Author = NULL;
		if (ID != 0)
			delete[] ID;
		if (Text != 0)
			delete[] Text;
		if (Likers != 0)
			delete[] Likers;
		if (commenters)
		{
			for (int i = 0;i < noOfComments;i++)
				delete commenters[i];
			delete[] commenters;
		}
	}

	void Posts::LoadFromFile(ifstream& fin)
	{
		char tempID[20];
		char tempText[300];
		int day = 0, month = 0, year = 0;
		fin >> tempID;
		ID = String::strcpy(tempID);
		shareDate.ReadFromFile(fin, day, month, year);

		fin.ignore(1);
		fin.get(tempText, 300, '\n');
		Text = String::strcpy(tempText);
		commenters = new Comments * [10];
	}

	void Posts::Print(int check = 0) //checks if we r printing for home or timeline
	{
		if (check == 1) //for timeline
		{
			if (shareDate.IsLatestPost())
			{
				cout << "\n ->";
				Author->PrintName();
				cout << "Posted: " << " \"" << Text << "\" ";
				shareDate.Print();
				cout << "     Comments:";
				PrintComments();
			}
		}
		else
		{
			cout << "\n ->";
			Author->PrintName();
			cout << "Posted: " << " \"" << Text << "\" ";
			shareDate.Print();
			cout << "     Comments:";
			PrintComments();
		}
	}

	void Posts::AddLike(BaseClass*& currentUser)
	{
		Likers[noOfLikers] = currentUser;
		noOfLikers++;
	}
	void Posts::AddComment(Comments* Commentors)
	{
		if (!noOfComments) {
			commenters = new Comments * [10];
		}
		commenters[noOfComments] = Commentors;
		noOfComments++;
	}

	void Posts::PrintAllLikes()
	{
		cout << endl;
		for (int i = 0;i < noOfLikers;i++)
		{
			Likers[i]->Print();
			cout << endl;
		}
	}
	void Posts::PrintComments()
	{
		cout << endl;
		for (int i = 0;i < noOfComments;i++)
		{
			commenters[i]->Print();
		}
	}

	void Posts::AddComment(char* CommentID, BaseClass*& currentUser, char* text)
	{
		commenters[noOfComments] = new Comments;
		commenters[noOfComments]->Setter(CommentID, currentUser, text);
		noOfComments++;
	}

	void Posts::SetLikedBy(BaseClass**& likers)
	{
		Likers = likers;
	}
	void Posts::SetSharedBy(BaseClass* author)
	{
		Author = author;
	}

	char* Posts::GetID()
	{
		return ID;
	}
	char* Posts::GetText()
	{
		return Text;
	}
	void Posts::SetTotalLikes(int TL)
	{
		noOfLikers = TL;
	}

	/******************* Activity Class ****************/


	Activity::Activity()
	{
		typeNo = 0;
		Value = 0;
	}
	Activity::~Activity()
	{
		if (Value != 0)
			delete[] Value;
	}

	void Activity::LoadFromFile(ifstream& fin)
	{
		Posts::LoadFromFile(fin);
		fin >> typeNo;
		char temp[100];
		fin.getline(temp, 100, '\n');
		Value = String::strcpy(temp);

	}
	void Activity::Print(int check = 0)
	{
		if (check == 1) //For timeLine its checking for latest post
		{
			if (shareDate.IsLatestPost()) //for timeline
			{
				cout << "\n\n ->";
				Author->PrintName();
				if (Value)
				{
					cout << " is ";
					if (typeNo == 1)
						cout << " feeling ";
					if (typeNo == 2)
						cout << " thinking about ";
					if (typeNo == 3)
						cout << " Making ";
					if (typeNo == 4)
						cout << " celebrating ";
					cout << Value;
				}
				cout << endl;
				cout << "  \"" << Text << "\" ";
				shareDate.Print();
				PrintComments();
			}
		}
		else
		{
			cout << "\n\n ->";
			Author->PrintName();
			if (Value)
			{
				cout << " is ";
				if (typeNo == 1)
					cout << " feeling ";
				if (typeNo == 2)
					cout << " thinking about ";
				if (typeNo == 3)
					cout << " Making ";
				if (typeNo == 4)
					cout << " celebrating ";
				cout << Value;
			}
			cout << endl;
			cout << "  \"" << Text << "\" ";
			shareDate.Print();
			PrintComments();
		}
	}

	/******************* Pages Class ****************/


	Pages::Pages()
	{
		ID = Title = 0;
		totalPages = 0;
		no_of_posts = 0;
		TimeLine = NULL;
	}
	Pages::~Pages()
	{
		if (Title != 0)
			delete[] Title;
		if (TimeLine != 0)
		{
			for (int i = 0;i < no_of_posts;i++)
				delete TimeLine[i];
			delete[] TimeLine;
		}
	}
	Pages::Pages(const Pages& rhs)
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

	void   Pages::LoadPagesFromFile(ifstream& fin)
	{
		char id[4];
		char title[60];
		fin.clear(); // stream reset
		fin >> id;
		fin.ignore(1); //ignores space in file
		fin.getline(title, 60);
		ID = String::strcpy(id);
		Title = String::strcpy(title);
		totalPages++;
	}
	void  Pages::Print()
	{
		cout << endl <<"  "<< ID << " ->" << Title;
	}
	void Pages::PrintName()
	{
		cout << " "<<Title;
	}
	void Pages::PrintTimeline()
	{
		for (int i = 0;i < no_of_posts;i++)
			TimeLine[i]->Print(1);
	}
	void Pages::AddPostToTimeline(Posts* Post)
	{
		if (!no_of_posts)
			TimeLine = new Posts * [10];
		TimeLine[no_of_posts] = Post;
		no_of_posts++;
	}
	void Pages::ViewPostInLast24Hours()
	{
		for (int i = 0;i < no_of_posts;i++)
			TimeLine[i]->Print(1);
	}

	char* Pages::GetID()
	{
		return ID;
	}
	char* Pages::GetTitle()
	{
		return Title;
	}


/******************* Users Class ****************/


	Users::Users()
	{
		ID = firstName = lastName = 0;
		friends = 0;
		LikedPages = 0;
		totalUsers = totalPages = noOfFriends = noOfLikedPages = no_of_posts = 0;
		Timeline = 0;
	}
	Users::~Users()
	{

		if (firstName != 0)
			delete[] firstName;
		if (lastName != 0)
			delete[] lastName;
		if (friends != 0)
			delete[] friends;
		if (LikedPages != 0)
			delete[] LikedPages;
		if (Timeline != 0)
		{
			for (int i = 0;i < no_of_posts;i++)
				delete Timeline[i];
			delete[] Timeline;
		}
	}
	Users::Users(const Users& rhs)
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
	

	void Users::ReadDataFromFile(ifstream& fin, char***& tempFriendList, char***& tempLikedPages, const int a)
	{
		char id[4];
		char fName[20];
		char lName[20];

		fin >> id;
		fin >> fName;
		fin >> lName;

		ID = String::strcpy(id);
		firstName = String::strcpy(fName);
		lastName = String::strcpy(lName);

		//storing friends in ***tempFriendList
		int i, j;
		for (i = 0;i < 10;i++)
		{
			char b = 0, c = 0, d = 0;
			tempFriendList[a][i] = new char[4]; //user
			for (j = 0;j < 4;j++)
			{
				b = fin.peek();//peek checks for nxt charachter in file without removing frm stream
				if (b == '\t' && j == 2 || j == 3) // j helps check to see if user Ids all charachters read
					break;
				fin >> tempFriendList[a][i][j]; //read characheter of ID
				c = tempFriendList[a][i][j]; // to move on to frm frnd list to like list
				d = fin.peek();
				if (c == '-' && d == '1')
				{
					break;
				}
			}
			tempFriendList[a][i][j] = '\0';
			if (c == '-')
				fin >> d;
			if (c == '-' && d == '1')
				break;
		}
		*tempFriendList[a][i] = '\0';

		//storing Likedpages in ***tempPagesList
		i = 0, j = 0;
		for (i = 0;i < 10;i++)
		{
			char b = 0, c = 0, d = 0;
			tempLikedPages[a][i] = new char[4];
			for (j = 0;j < 4;j++)
			{
				b = fin.peek();
				if (b == '\t' && j == 2)
					break;
				fin >> tempLikedPages[a][i][j];
				c = tempLikedPages[a][i][j];
				d = fin.peek();
				if (c == '-' && d == '1')
				{
					break;
				}
			}
			tempLikedPages[a][i][j] = '\0';
			if (c == '-')
				fin >> d;
			if (c == '-' && d == '1')
				break;
		}
		*tempLikedPages[a][i] = '\0';

		totalUsers++;
	}

	void  Users::Print()
	{
		cout  << firstName << " " << lastName<<":"<<endl;
	}
	void  Users::PrintName()
	{
		cout << " " << firstName << " " << lastName << " ";
	}

	void  Users::ViewFriendList()
	{
		cout << CYAN<<"\n\n-------------------------------------------------\n";
		cout << "|\t\tFollowed Friends:\t\t|";
		cout << "\t\t\t\t\t\n-------------------------------------------------\n\n"<<RESET;

		for (int i = 0;i < noOfFriends;i++)
		{
			friends[i]->Print();
		}
	}
	void  Users::ViewLikedPages()
	{
		cout <<CYAN<< "\n\n-------------------------------------------------\n";
		cout << "|\t\tLiked Pages:\t\t\t|";
		cout << "\t\t\t\t\t\n-------------------------------------------------\n\n"<<RESET;

		for (int i = 0;i < noOfLikedPages;i++)
		{
			LikedPages[i]->Print();
		}
	}

	void  Users::ViewHome()
	{
		cout <<CYAN<< "\n\n-------------------------------------------------\n";
		cout << "|\t\tHome:\t\t\t\t|";
		cout << "\t\t\t\t\t\n-------------------------------------------------\n\n"<<RESET;
		for (int i = 0;i < noOfFriends;i++)
		{
			friends[i]->PrintLatestPosts();
		}
		for (int i = 0;i < noOfLikedPages;i++)
		{
			LikedPages[i]->ViewPostInLast24Hours();
		}
	}
	void  Users::ViewTimeLine()
	{
		cout <<CYAN<< "\n\n-------------------------------------------------\n";
		cout << "|\t\tTimeLine:\t\t\t|";
		cout << "\t\t\t\t\t\n-------------------------------------------------\n"<<RESET;
		for (int i = 0;i < no_of_posts;i++)
		{
			Timeline[i]->Print(1);
		}
	}
	void  Users::PrintLatestPosts()
	{
		for (int i = 0;i < no_of_posts;i++)
		{
			Timeline[i]->Print(1);
		}
	}

	void  Users::AddPage(Pages*& PagePtr)
	{
		if (LikedPages == 0)
		{
			LikedPages = new Pages * [10];
		}
		LikedPages[noOfLikedPages] = PagePtr;
		noOfLikedPages++;
	}
	void  Users::AddFriend(Users*& Frndptr)
	{
		if (friends == 0)
		{
			friends = new Users * [10];
		}
		friends[noOfFriends] = Frndptr;
		noOfFriends++;
	}
	void  Users::AddPostToTimeline(Posts* Post)
	{
		if (!no_of_posts)
			Timeline = new Posts * [10];
		Timeline[no_of_posts] = Post;
		no_of_posts++;
	}

	char* Users::GetID()
	{
		return ID;
	}
	char* Users::GetfName()
	{
		return firstName;
	}
	char* Users::GetlName()
	{
		return lastName;
	}
	int  Users::GetTotalUsers()
	{
		return totalUsers;
	}



	


	/******************* Pretty ****************/

#include <Windows.h>

	void setBackgroundColor(int color) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
		GetConsoleScreenBufferInfo(hConsole, &bufferInfo);

		WORD newAttributes = (bufferInfo.wAttributes & 0xFFF0) | color;
		SetConsoleTextAttribute(hConsole, newAttributes);
	}



#include <conio.h>

	void sleep() {
		int x = 0;
		while (x < 599999999) {
			x++;
		}
	}
	void sleep2() {
		int x = 0;
		while (x < 169999999) {
			x++;
		}
	}
	void pretty() {

		cout <<YELLOW<< "Loading.";
		sleep2();
		system("cls");
		cout << "Loading..";
		sleep2();
		system("cls");
		cout << "Loading...";
		sleep2();
		system("cls");
		cout << "Loading.";
		sleep2();
		system("cls");
		cout << "Loading..";
		sleep2();
		system("cls");
		cout << "Loading...";
		sleep2();
		system("cls");



		cout <<CYAN<< "\n\n\t\t~THE IBI APP~\n\n"<<RESET;
		cout <<MAGENTA<< "\tLogin:";
		cout << "\n\tPassword:";
		sleep2();
		system("cls");
		cout << CYAN << "\n\n\t\t~THE IBI APP~\n\n" << RESET;
		cout << MAGENTA << "\tLogin:I";
		cout << "\n\tPassword:";
		sleep2();
		system("cls");
		cout << CYAN << "\n\n\t\t~THE IBI APP~\n\n" << RESET;
		cout << MAGENTA << "\tLogin:Ib";
		cout << "\n\tPassword:";
		sleep2();
		system("cls");
		cout << CYAN << "\n\n\t\t~THE IBI APP~\n\n" << RESET;
		cout << MAGENTA << "\tLogin:Ibi";
		cout << "\n\tPassword:";
		sleep2();
		system("cls");
		cout << CYAN << "\n\n\t\t~THE IBI APP~\n\n" << RESET;
		cout << MAGENTA << "\tLogin:Ibi_";
		cout << "\n\tPassword:";
		sleep2();
		system("cls");
		cout << CYAN << "\n\n\t\t~THE IBI APP~\n\n" << RESET;
		cout << MAGENTA << "\tLogin:Ibi_i";
		cout << "\n\tPassword:";
		sleep2();
		system("cls");
		cout << CYAN << "\n\n\t\t~THE IBI APP~\n\n" << RESET;
		cout << MAGENTA << "\tLogin:Ibi_is";
		cout << "\n\tPassword:";
		sleep2();
		system("cls");
		cout << CYAN << "\n\n\t\t~THE IBI APP~\n\n" << RESET;
		cout << MAGENTA << "\tLogin:Ibi_is_";
		cout << "\n\tPassword:";
		sleep2();
		system("cls");
		cout << CYAN << "\n\n\t\t~THE IBI APP~\n\n" << RESET;
		cout << MAGENTA << "\tLogin:Ibi_is_D";
		cout << "\n\tPassword:";
		sleep2();
		system("cls");
		cout << CYAN << "\n\n\t\t~THE IBI APP~\n\n" << RESET;
		cout << MAGENTA << "\tLogin:Ibi_is_Dy";
		cout << "\n\tPassword:";
		sleep2();
		system("cls");
		cout << CYAN << "\n\n\t\t~THE IBI APP~\n\n" << RESET;
		cout << MAGENTA << "\tLogin:Ibi_is_Dyi";
		cout << "\n\tPassword:";
		sleep2();
		system("cls");
		cout << CYAN << "\n\n\t\t~THE IBI APP~\n\n" << RESET;
		cout << MAGENTA << "\tLogin:Ibi_is_Dyin";
		cout << "\n\tPassword:";
		sleep2();
		system("cls");
		cout << CYAN << "\n\n\t\t~THE IBI APP~\n\n" << RESET;
		cout << MAGENTA << "\tLogin:Ibi_is_Dying";
		cout << "\n\tPassword:";
		sleep2();
		system("cls");
		cout << CYAN << "\n\n\t\t~THE IBI APP~\n\n" << RESET;
		cout << MAGENTA << "\tLogin:Ibi_is_Dying";
		cout << "\n\tPassword:*";
		sleep2();
		system("cls");
		cout << CYAN << "\n\n\t\t~THE IBI APP~\n\n" << RESET;
		cout << MAGENTA << "\tLogin:Ibi_is_Dying";
		cout << "\n\tPassword:**";
		sleep2();
		system("cls");
		cout << CYAN << "\n\n\t\t~THE IBI APP~\n\n" << RESET;
		cout << MAGENTA << "\tLogin:Ibi_is_Dying";
		cout << "\n\tPassword:***";
		sleep2();
		system("cls");
		cout << CYAN << "\n\n\t\t~THE IBI APP~\n\n" << RESET;
		cout << MAGENTA << "\tLogin:Ibi_is_Dying";
		cout << "\n\tPassword:****";
		sleep2();
		system("cls");
		cout << "Logging In." ;
		sleep2();
		system("cls");
		cout << "Logging In.." ;
		sleep2();
		system("cls");
		cout << "Logging In..."<<MAGENTA;
		sleep2();
		system("cls");


		cout <<RED<< R"(
    W   W  EEEEE  L      CCCC  OOO  M   M  EEEEE)";
		sleep();
		cout << R"(
    W   W  E      L     C     O   O MM MM  E  )";
		sleep();
		cout << R"(
    W W W  EEEE   L     C     O   O M M M  EEEE)";
		sleep();
		cout << R"(
    WW WW  E      L     C     O   O M   M  E)";
		sleep();
		cout << R"(
    W   W  EEEEE  LLLLL  CCCC  OOO  M   M  EEEEE)" << RESET ;
		sleep();
		system("cls");


	}

	/******************* Int Main ****************/

int main()
{
	
	pretty();
	cout  <<CYAN<< "\n\n\t\t~THE IBI APP~\n\n"<<RESET;
	sleep();

	Date::CurrentDate.SetDate(14, 11, 2017);
	cout << GREEN<<"\nSyestem Date: ";
	Date::CurrentDate.Print();

	SocialMediaApp ibi;
	char*** tempFriendList = 0; //frnds of each user
	char*** tempLikedPages = 0; //liked pages by each user
	ibi.LoadData(tempFriendList, tempLikedPages); // constructors called for all here with users / page being read
	ibi.AssociateFriends(tempFriendList);
	ibi.AssociatePages(tempLikedPages); //class ki attributes k liay

	ibi.LoadAllPosts(); //read posts
	ibi.LoadAllComments(); //read comments
	ibi.run();
	return 0;
}








