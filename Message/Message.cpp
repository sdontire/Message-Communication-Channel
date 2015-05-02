/////////////////////////////////////////////////////////////////////////
// Message.cpp- For constructing and interpreting messages             //
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
#include "Message.h"

string Message::getGenericContents(string tag)
{
	string temp = tag, result;
	size_t index = msg.find(temp);
	index += temp.size();
	for (int i = index; msg[i] != '\n'; i++)
	{
		result.push_back(msg[i]);

	}

	return result;

}
void Message::setGenericContents(string tag, string contents)
{
	string temp = tag;
	msg.append(temp);
	msg.append(contents);
	msg.append("\n");

}


string Message::getMessage()
{
	return this->msg;

}

void Message::setMessage(string input)
{

	this->msg = input;
}


void Message::setsendAddr(string addr)
{
	string temp = "senderAddress:";
	msg.append(temp);
	msg.append(addr);
	msg.append("\n");
}

string Message::getsendAddr(string msg)
{
	string temp = "senderAddress:", result;
	size_t index = msg.find(temp);
	index += temp.size();
	for (int i = index; msg.at(i) != '\n'; i++)
	{
		result.push_back(msg[i]);
	}
	return result;
}

void Message::setrecAddr(string addr)
{
	string temp = "receiverAddress:";
	msg.append(temp);
	msg.append(addr);
	msg.append("\n");
}
string Message::getrecvAddr(string msg)
{
	string temp = "receiverAddress:", result;
	size_t index = msg.find(temp);
	index += temp.size();
	for (int i = index; msg.at(i) != '\n'; i++)
	{
		result.push_back(msg[i]);
	}
	return result;
}

void Message::setCommand(string cmd)
{
	string temp = "command:";
	msg.append(temp);
	msg.append(cmd);
	msg.append("\n");
}

void Message::setmsgLen(string len)
{
	string temp = "content-length:";
	msg.append(temp);
	msg.append(len);
	msg.append("\n");
}

string Message::getmsgBody(string msg)
{
	//msg = msg + "#";
	string temp = "Body:", result;
	size_t index = msg.find(temp);
	index += temp.size();
	for (size_t i = index;i< msg.size(); i++)
	{
		result.push_back(msg[i]);
	}
	return result;
}

void Message::setmsgBody(string body)
{
	string temp = "Body:";
	msg.append(temp);
	msg.append(body);
	msg.append("\n");
}
void Message::setPatterns(string patterns)
{
	string temp = "Patterns:";
	msg.append(temp);
	msg.append(patterns);
	msg.append("\n");
}
string Message::getPatterns(string msg)
{
	string temp = "Patterns:", result;
	size_t index = msg.find(temp);
	index += temp.size();
	for (int i = index; msg.at(i) != '\n'; i++)
	{
		result.push_back(msg[i]);
	}
	return result;
}
void Message::setmsgBody1(string body)
{
	string temp = "Body:";
	msg.append(temp);
	msg.append(body);
}
string Message::getFileName(string msg)
{
	string temp = "FileAttr:", result;
	size_t index = msg.find(temp);
	index += temp.size();
	for (int i = index; msg[i] != ';'; i++)
	{
		result.push_back(msg[i]);

	}
	return result;
}


char Message::getFileStart(string filemsg)
{
	string temp = "FileAttr:";
	char filestart;
	size_t index = filemsg.find(temp);
	index += temp.size();
	string filename = getFileName(filemsg);
	index += filename.size() + 1;

	filestart = filemsg[index];
	return filestart;
}


void Message::setFileAttrs(string fileattr)
{
	string temp = "FileAttr:";
	msg.append(temp);
	msg.append(fileattr);
	msg.append("\n");
}

//Test stub
#ifdef TEST_MESSAGE
int main(int argc, char* argv[])
{
	std::cout << "\n  Testing Message class\n ";
	try
	{
		Message m;
		m.setCommand("Normal Message");
		m.setFileAttrs("file1.txt;1");
		m.setmsgBody("test stub content");
		m.setmsgLen("17");
		m.setrecAddr("127.0.0.1,8080");
		m.setsendAddr("127.0.0.1,8080");

		string command = m.getCommand();
		cout << "\nCommand:" << command;

		string filename = m.getFileName();
		cout << "\nFilename:" << filename;

		char fstart = m.getFileStart();
		cout << "\nFilestart:" << fstart;

		string body = m.getmsgBody();
		cout << "\nBody:" << body;
	}

	catch (exception ex)
	{
		cout << "\n\n  " << ex.what();
		return 1;
	}

}
#endif