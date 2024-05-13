# **Social Network Application**
This project is a social network application developed in C++ . It allows users to interact with each other, share posts, like posts, comment on posts, view profiles, and perform various other social networking activities.

## **Table of Contents**
- Project Description
- Folder Structure
- Installation
- Usage
- Dependencies
- Contributing
- License

## **Project Description**
The social network application is designed to simulate a simplified version of popular social media platforms. It allows users to create accounts, add friends, like posts, comment on posts, and perform other social networking activities. Key functionalities include:
- Set current user
- View home of the current user
- Like a post
- View the list of people who liked a post
- Comment on a post
- View a post
- View a page
- View a memory
- Run the application

## **Structure**
### **Inheritance:**
- Pages and Users inherit from BaseClass
- Activity inherits from PostsMemory inherits from Posts
### **Composition:**
- SocialMediaApp has compositions of pointers to objects of type Users, Pages, and Posts
### **Aggregation:**
- Pages and Users have compositions of pointers to objects of type Posts (timeline for users and posts on the page)
### **Association:**
- Users has associations with other users (friends) and pages (liked pages)
- Posts has associations with Users (author), Comments, and BaseClass (likers)


## **Installation**
To install and run the social network application, follow these steps:

+ Clone the repository to your local machine:
git clone <repository-url>
+ Navigate to the project directory:
cd social-network-application
+ Compile the source code using a C++ compiler (e.g., g++):
g++ -o social-network-app src/*.cpp -I include/
+ Run the compiled executable:
./social-network-app

# **Usage**
Once the application is running, follow the on-screen prompts to interact with the social network application. You can set the current user, view their home feed, like posts, comment on posts, view profiles, and perform other social networking activities by hardcoding changes in the SocialMediaApp.cpp file by making changes in the Arrays in the run function.

## **Dependencies**
The social network application has no external dependencies beyond the standard C++ libraries.

## **Contributing**
Contributions to the social network application are welcome. If you find any bugs or have suggestions for improvements, please open an issue or submit a pull request on the GitHub repository.

## **License**
This project is not licensed.
