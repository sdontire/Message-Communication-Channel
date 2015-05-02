/////////////////////////////////////////////////////////////////////////////
// 
//clientExecutive.cpp - Test passing strings, blocks, and buffers          //
// Ver 1.1                                                                 //
// Dontireddy Sneha Reddy, CSE#687 - Object Oriented Design, Spring 2015   //
// Syracuse University, 315 380-0886, sdontire@syr.edu                     //
//-------------------------------------------------------------------------//
//                                                                         //
//-------------------------------------------------------------------------//
// Application: Demo for Project #3, Communication Channel                 //
// Platform:    Dell 2720, Win Pro 8.1, Visual Studio 2013                 //
/////////////////////////////////////////////////////////////////////////////
/*
*  Package Operations:
*  -------------------
*  This package provides tests for Sockets-4.7:
*  - passing byte buffers
*  - passing strings
*  - This package passes Filename of the file to be uploaded to the server and
*    message to be sent to server using sender and receives acknowledgment from 
*    the server.
*
*  Required Files:
*  ---------------
*  clientExecutive.cpp, ServerExecutive.cpp, Message.h, Message.cpp
*  Sockets.h, Sockets.cpp, AppHelpers.h, AppHelpers.cpp, Sender.h, Sender.cpp,
*  Receiver.h, Receiver.cpp
*
*  Build Command:
*  --------------
*  devenv Sockets.sln /rebuild debug
*
*  Maintenance History:
*  --------------------
*  ver 1.2: 4/11
*  Added Additional features- Sending messages to the server
*  ver 1.1 : 30 Mar 15
*  - minor modification to comments, above
*  ver 1.0 : 30 Mar 15
*  - first release
*/

#include "../ApplicationHelpers/AppHelpers.h"
#include "../Sockets/Sockets.h"
#include "../Sender/Sender.h"
#include "../Message/Message.h"
#include "../Receiver/Receiver.h"
#include <iostream>

using namespace ApplicationHelpers;


struct Cosmetic
{
  ~Cosmetic()
  {
	  Display *disp = new Display();
	  disp->cosmtic();
  }
} aGlobalForCosmeticAction;

//----< demonstration >------------------------------------------------------


int main(int argc, char *argv[])
{
  title("Client", '=');
  Display *disp = new Display();
  try
  {
    Verbose v(true);
    SocketSystem ss;
    SocketConnecter si;
	string filename;
	string client_address;
	string client_port;
	string server_address;
	string server_port;
	int clientport;
	int serverport;
	string textsearch;
	string filepattern;
	std::vector<std::string> file_patterns;
	string type;
	if (argc > 1 && argc==7)
	{
		filename = argv[1];
		type = argv[2];
		client_address = argv[3];
		client_port = argv[4];
		server_address = argv[5];
		server_port = argv[6];
		clientport = atoi(client_port.c_str());
		serverport = atoi(server_port.c_str());
		
	}
	else
	{
		filepattern = argv[3];
		filename = argv[1];
		type = argv[2];
		client_address = argv[4];
		client_port = argv[5];
		server_address = argv[6];
		server_port = argv[7];
		textsearch = argv[8];
		clientport = atoi(client_port.c_str());
		serverport = atoi(server_port.c_str());
	}


    while (!si.connect(server_address,clientport))
    {
      Verbose::show("client waiting to connect");
      ::Sleep(100);
    } 
	Sender sd;
	if (type == "upload")
	{
		if (filename.find(".exe") != std::string::npos || filename.find(".bin") != std::string::npos)
			disp->show("Not demonstrating exe files");
		else if (filename.find(".txt") != std::string::npos)
			sd.sendTextFile(client_address, clientport, server_address, serverport, filename, si, true);
		else
			sd.sendNormalMessage(client_address, clientport, server_address, serverport, filename, si);
		Receiver *rs = new Receiver();
		rs->recvAck(si);
	}
	else if (type == "download")
	{
		if (filename.find(".txt") != std::string::npos)
			sd.sendDownloadMessage(client_address, clientport, server_address, serverport, filename, si);
		BlockingQueue<string> q_;
		while (true)
		{
			Receiver *rs = new Receiver();
			std::string command = si.recvString();
			q_.enQ(command);
			if (command.size() == 0)
				break;
			size_t size = q_.size();
			string ackmsg;
			for (size_t i = 0; i < size; i++)
			{
				command = q_.deQ();
				ackmsg = rs->start(command, si);
			}
			Sender *s = new Sender();
			if (ackmsg != "")
			{
				s->sendAck(si, ackmsg);
				break;
			}
		}
	}
	else if (type == "textsearch")
	{
		Sender s;
		s.sendTextSearchMessage(client_address, clientport, server_address, serverport,textsearch, filepattern, filename,si);
		Receiver *rs = new Receiver();
		rs->recvAck1(si);
	}
    si.shutDownSend();
  }
  catch (std::exception& ex)
  {
	  disp->Exeception(ex);
  }
}
