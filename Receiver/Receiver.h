#ifndef RECEIVER_H
#define RECEIVER_H
/////////////////////////////////////////////////////////////////////////
// Receiver.h- For receiving message from client ,server and interpreting them //
// ver 1.1                                                             //
// Dontireddy sneha reddy, CSE687 - Object Oriented Design, Spring 2015//
// Syracuse University, 315-380-0886, sdontire@syr.edu                 //
//---------------------------------------------------------------------//
//---------------------------------------------------------------------//
// Application: OOD Projects #3                                        //
// Platform:    Visual Studio 2013, Dell 2720, Win 8.1 pro             //
/////////////////////////////////////////////////////////////////////////
/*
*  Package Operations:
*  -------------------
*  Receiver package receives messgae from serverExecutive and interpretes the 
*  message. If message is file uploading, revceiver will write the messgae body to 
*  the file name specified in the message. At the last message, it will close the file. 
*
*
* Public Interface
* ------------------
*--------------------
*
* void start- start executition of receiver and check the command type
* void writeToFile- writes data received from the client to the newly created file
* setMessage- for setting acknowledgement to be sent to client
* recvAck- Client Waiting for the acknowledgement from the server
*
*  Required Files:
*  ---------------
*  Receiver.h, Receiver.cpp, BlockingQueue.h, BlockingQueue.cpp, Sockets.h, Sockets.cpp
*  FileSystem.h, FileSystem.cpp, AppHelpers.h, AppHelpers.cpp, Display.h, Display.cpp,
*  Message.h, Message.cpp
*
*  Build Command:
*-------------------------
* devenv Sockets.sln /rebuild debug
*
*  Maintenance History:
*  --------------------
* version 1.1- created Receiver Package
*/


#pragma once
#include "../BlockingQueue/BlockingQueue.h"
#include "../Sockets/Sockets.h"
#include "../Threads/Threads.h"
#include "../locks/locks.h"
#include <string>
#include<fstream>
#include "../Display/Display.h"
using namespace std;
using Files = std::vector<std::string>;
using Path1 = std::string;
using Patterns = std::vector<std::string>;



class Receiver
{
public:
	Receiver();
	~Receiver();
	string start(string msg, Socket &si);
	string writeToFile(std::string filemsg, bool type, Socket &si); 
	void recvAck(Socket &si);
	string setMessage(std::string filemsg);
	string ReadfromFile(std::string filemsg, bool type, Socket &si);
	Files showFiles(const Path1& path, Patterns& patts);
	string setFileMessage(std::string filemsg, string resultfiles);
	std::vector<std::string> showAllDirectories(std::string & baseDirectory, std::vector<std::string> & directories);
	void recvAck1(Socket &si);
	string writeToFile1(std::string filemsg, bool type, Socket &si);

private:
	BlockingQueue<string> q_;
	bool type=true;
	bool text=false;
};
#endif