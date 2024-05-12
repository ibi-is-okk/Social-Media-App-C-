## **Social Network Application**
This project is a social network application developed in C++ with a graphical user interface (GUI). It allows users to interact with each other, share posts, like posts, comment on posts, view profiles, and perform various other social networking activities.

# **Table of Contents**
Project Description
Folder Structure
Installation
Usage
Dependencies
Contributing
License
Project Description
The social network application is designed to simulate a simplified version of popular social media platforms. It allows users to create accounts, add friends, like posts, comment on posts, and perform other social networking activities. Key functionalities include:

Set current user
View home of the current user
Like a post
View the list of people who liked a post
Comment on a post
View a post
View a page
Run the application
Folder Structure
The project follows a structured folder organization to maintain code readability and manageability. The folder structure is as follows:

makefile
Copy code
├── src/                    # Source files directory
│   ├── Main.cpp            # Main source file
│   ├── SocialMediaApp.cpp  # Implementation of social media application
│   └── ...                 # Other source files
├── include/                # Header files directory
│   ├── Main.h              # Main header file
│   ├── SocialMediaApp.h    # Header file for social media application
│   └── ...                 # Other header files
├── data/                   # Data files directory
│   ├── Posts.txt           # Text file for storing posts
│   ├── Comments.txt        # Text file for storing comments
│   ├── Users.txt           # Text file for storing user information
│   └── Pages.txt           # Text file for storing page information
├── build/                  # Build output directory
│   └── ...                 # Generated binaries and build artifacts
├── README.md               # This README file
└── ...                     # Other project files
Installation
To install and run the social network application, follow these steps:

Clone the repository to your local machine:

bash
Copy code
git clone <repository-url>
Navigate to the project directory:

bash
Copy code
cd social-network-application
Compile the source code using a C++ compiler (e.g., g++):

bash
Copy code
g++ -o social-network-app src/*.cpp -I include/
Run the compiled executable:

bash
Copy code
./social-network-app
Usage
Once the application is running, follow the on-screen prompts to interact with the social network application. You can set the current user, view their home feed, like posts, comment on posts, view profiles, and perform other social networking activities as described in the project description.

Dependencies
The social network application has no external dependencies beyond the standard C++ libraries.

Contributing
Contributions to the social network application are welcome. If you find any bugs or have suggestions for improvements, please open an issue or submit a pull request on the GitHub repository.

License
This project is licensed under the MIT License.
