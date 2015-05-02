
/////////////////////////////////////////////////////////////////////////
// Sender.cpp- For receiving message from client and interpreting them //
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
*  Sender Packages sends the constructed messages to the server and also
* sendes the acknowledegement after the server receives the messages to the client.
*
*
* Public Interface
* ------------------
*--------------------
*
* void sendTextFile- Sends the constructed message for text file to server.
* void sendBinarytFile- Sends the constructed message for binary file to server.
* Message getFileFirstMessage- Constructs the first message to be sent.
* Message getOtherMessage- Constructs the messages other than first message to be sent.
* Message getEndMessage- Constructs the last message and sends to the server
* void sendNormalMessage- Constructs simple messages.
* void sendAck- Sends Acknowledgement to the server from client
*
*  Required Files:
*  ---------------
*  Sender.h, Sender.cpp, BlockingQueue.h, BlockingQueue.cpp, Sockets.h, Sockets.cpp
*  FileSystem.h, FileSystem.cpp
*
*  Build Command:
*-------------------------
* Sockets.sln
*
*  Maintenance History:
*  --------------------
* version 1.1- created Sender Package
*/
#include "Sender.h"
#include "../Message/Message.h"
#include "../FileSystem/FileSystem.h"
#include "../ApplicationHelpers/AppHelpers.h"
#include "../locks/locks.h"
#include "../Threads/Threads.h"
#include "../Display/Display.h"
using namespace ApplicationHelpers;
using namespace FileSystem;
using namespace std;

//sending text file to the server
void Sender::sendTextFile(std::string clientip, int clientport, std::string serverip, int serverport, string filename, Socket& si, bool textfile1)
{
	Display *disp = new Display();
	disp->sendreq5();
	textfile = textfile1;
	Path *p = new Path;
	string path = p->getName(filename, true);
	string printmsg = "Uploading File " + path + " to Server with address: " + serverip + "," + std::to_string(serverport);
	disp->show(printmsg);
	File::direction dir;
	File::type type;
	File f(filename);
	string line;

	dir = File::direction::in;
	type = File::type::text;
	f.open(dir, type);
	line = f.getLine();

	Message msg2 = getFileFirstMessage(clientip, clientport,serverip,serverport,line, path);
	q_.enQ(msg2.getMessage());
	string sendstring = q_.deQ();
	si.sendString(sendstring);
	int j = 0;
	while (f.getEof() == false && f.isGood())
	{
		Message msg;
		string line;
		line = f.getLine();

		msg = getOtherMessage(clientip, clientport,serverip,serverport, line, path);
		q_.enQ(msg.getMessage());
		sendstring = q_.deQ();
		si.sendString(sendstring);
	}
	string endline = "endfile";
	Message msg1;
	msg1 = getOtherMessage(clientip, clientport,serverip,serverport, endline, path);
	q_.enQ(msg1.getMessage());
	sendstring = q_.deQ();
	si.sendString(sendstring);
	size_t size = q_.size();
	return;
}

//Construct text file's first message
Message Sender::getFileFirstMessage(string clientip, int clientport, string serverip, int serverport, string line, string path)
{
	Message msg;
	msg.setCommand("uploadfile");
	string messagebody = line + '\0';
	msg.setsendAddr(clientip + "," + std::to_string(clientport));
	msg.setrecAddr(serverip + "," + std::to_string(serverport));
	msg.setmsgLen(std::to_string(sizeof(string)*messagebody.size()));
	msg.setFileAttrs(path + ";1");
	msg.setmsgBody(messagebody);
	return msg;
}

//Construct Text file's other messages
Message Sender::getOtherMessage(string clientip, int clientport, string serverip, int serverport, string line, string path)
{
	Message msg;
	msg.setCommand("uploadfile");
	string messagebody = line + '\0';
	msg.setsendAddr(clientip + "," + std::to_string(clientport));
	msg.setrecAddr(serverip + "," + std::to_string(serverport));
	msg.setmsgLen(std::to_string(sizeof(string)*messagebody.size()));
	msg.setFileAttrs(path + ";0");
	msg.setmsgBody(messagebody);
	return msg;
}

//Construct the last message
Message Sender::getEndMessage(string ip, int port)
{
	Message msg;
	msg.setCommand("EndMessage");
	string messagebody = "LastMessage\t";
	msg.setsendAddr(ip + "," + std::to_string(port));
	msg.setrecAddr(ip + "," + std::to_string(port));
	msg.setmsgLen(std::to_string(sizeof(string)*messagebody.size()));
	msg.setmsgBody(messagebody);
	return msg;

}
//Constructing and Sending normal message
void Sender::sendNormalMessage(string clientip, int clientport, string serverip, int serverport, string arg, Socket& si)
{
	Display *d = new Display();
	string pmsg = "Sending Message: " + arg;
	d->sendreq3(pmsg);
	Message msg;
	msg.setCommand("NormalMessage");
	string messagebody = arg + '\t';
	msg.setsendAddr(clientip + "," + std::to_string(clientport));
	msg.setrecAddr(serverip + "," + std::to_string(serverport));
	msg.setmsgLen(std::to_string(sizeof(string)*messagebody.size()));
	msg.setmsgBody(messagebody);
	string msg1 = msg.getMessage();
	si.sendString(msg1);
}

//Constructing and Sending download message
void Sender::sendDownloadMessage(string clientip, int clientport, string serverip, int serverport, string arg, Socket& si)
{
	Display *d = new Display();
	string pmsg = "Sending Message: " + arg;
	d->sendreq3(pmsg);
	Message msg;
	msg.setCommand("download");
	string messagebody = arg;
	msg.setsendAddr(clientip + "," + std::to_string(clientport));
	msg.setrecAddr(serverip + "," + std::to_string(serverport));
	msg.setmsgLen(std::to_string(sizeof(string)*messagebody.size()));
	msg.setmsgBody1(messagebody);
	string msg1 = msg.getMessage();
	si.sendString(msg1);
}

//Constructing and Sending textsearch message
void Sender::sendTextSearchMessage(string clientip, int clientport, string serverip, int serverport, string arg,string patterns,string filepath,Socket& si)
{
	Display *d = new Display();
	string pmsg = "Sending Message: " + arg;
	d->sendreq3(pmsg);
	Message msg;
	msg.setCommand("textsearch");
	string messagebody = arg;
	msg.setsendAddr(clientip + "," + std::to_string(clientport));
	msg.setrecAddr(serverip + "," + std::to_string(serverport));
	msg.setmsgLen(std::to_string(sizeof(string)*messagebody.size()));
	msg.setFileAttrs(filepath + ";");
	msg.setPatterns(patterns);
	msg.setmsgBody(messagebody);
	string msg1 = msg.getMessage();
	si.sendString(msg1);
}
//Sending Acknowledgement to client
void Sender::sendAck(Socket& si,string ack)
{
	si.sendString(ack);
}


#ifdef TEST_SENDER

int main(int argc, char *argv[])
{
	string ip="localhost";
	int port=9080;
	filename= "../TestFolder/Test.txt";
	Socket si;
	sendBinarytFile(ip,port,filename,si)
		path="..TestFolder/Test.txt";
	string line="Project 3 OOd"
	Message msg= getFileFirstMessage(ip,port,line,path);
	Message msg1=getOtherMessage(ip,port,line,path);
	Message endmsg=getEndMessage(ip,port);
	string ack="File uploaded successfully";
	sendAck(si,ack);
	string arg=1;
	sendNormalMessage(ip,port,arg);
	string ack="File uploaded successfully";
	sendAck(si,ack);
}
#endif