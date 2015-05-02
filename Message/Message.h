#ifndef MESSAGE_H
#define MESSAGE_H

/////////////////////////////////////////////////////////////////////////
// Message.h- For constructing and interpreting message                //
// ver 1.1                                                             //
// Dontireddy sneha reddy, CSE687 - Object Oriented Design, Spring 2015//
// CST 4-187, Syracuse University, 315-380-0886, sdontire@syr.edu      //
//---------------------------------------------------------------------//
//---------------------------------------------------------------------//
// Application: OOD Projects #3                                        //
// Platform:    Visual Studio 2013, Dell 2720, Win 8.1 pro             //
/////////////////////////////////////////////////////////////////////////
/*
*  Package Operations:
*  -------------------
* Provides one class Message for constructing messages and interpreting.
* Messages are constructed on basis of http messages. Message contains Headers:
* Command, Senders address, Receiver's address, content-length and
* body of the message.
*
* Public Interface
* ------------------
*--------------------
*
* string getCommand -function for getting command
* void setCommand - function for setting command
* void setsendAddr - function for setting sender address
* void setrecAddr - function for setting receiver address
* void setmsgLen -  function for setting message length
* string getmsgBody - function for getting message body
* void setmsgBody - function for setting message body
* string getMessage-  function for getting message
* void setMessage- function for seeting message
* string getFileName- function for getting filename
* char getFileStart- function for setting file start attribute, 
* if 0 first msg or middle message
* void setFileAttrs- for setting filename
* string getGenericContents- for getting contents
* void setGenericContents- for setting contents
*
*  Required Files:
*  ---------------
*  Message.h, Message.cpp
*
*  Build Command:
*-------------------------
* devenv Sockets.sln /rebuild debug
*
*  Maintenance History:
*  --------------------
* version 1.1- created Message Package
*/

#pragma once
#include <string>
using namespace std;

class Message
{
public:
	string getCommand();
	void setCommand(string);

	//string getsendAddr();
	void setsendAddr(string);

	//tring getrecseAddr();
	void setrecAddr(string);

	//string getmsgLen();
	void setmsgLen(string);

	string getmsgBody(string msg);
	void setmsgBody(string);
	void setmsgBody1(string body);

	string getMessage();
	void setMessage(string);

	string getsendAddr(string msg);
	string getrecvAddr(string msg);

	void setPatterns(string patterns);
	string getPatterns(string msg);

	string getFileName(string msg);
	char getFileStart(string filemsg);
	void setFileAttrs(string);

	string getGenericContents(string tag);
	void setGenericContents(string tag, string contents);


	private:
	string msg;
};
#endif