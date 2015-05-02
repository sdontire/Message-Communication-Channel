/////////////////////////////////////////////////////////////////////////
// ServerExecutive.cpp- For receiving message from client and interpreting them//
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
*  This package provides tests for Sockets-4.5:
*  - passing byte buffers
*  - passing strings
*  Receives message from the client and sends them to receiver for interpretation
*  and sends acknowledgment to the client on successful upload
*
*  Required Files:
*  ---------------
*  ClientTest.cpp, ServerTest.cpp, BlockingQueue.cpp, BlockingQueue.h,Display.cpp
*  Display.h, FileSystem.h, FileSystem.cpp, Message.h, Message.cpp,Sender.cpp
*  Sockets.h, Sockets.cpp, AppHelpers.h, AppHelpers.cpp, Sender.h
*
*  Build Command:
*  --------------
*  devenv Sockets.sln /rebuild debug
*
*  Maintenance History:
*  --------------------
* ver 1.2: 10 april 15
* uploading text files
*  ver 1.1 : 30 Mar 15
*  - minor modification to comments, above
*  ver 1.0 : 30 Mar 15
*  - first release
*/
#include "../sockets/sockets.h"
#include "../BlockingQueue/BlockingQueue.h"
#include "../ApplicationHelpers/AppHelpers.h"
#include "../Receiver/Receiver.h"
#include "../Message/Message.h"
#include "../Sender/Sender.h"
#include <iostream>
#include <thread>
#include <mutex>

using namespace ApplicationHelpers;


//----< Client Handler thread starts running this function >-----------------

/////////////////////////////////////////////////////////////////////////////
// Server's client handler class
// - must be callable object so we've built as a functor
// - passed to SocketListener::start(CallObject& co)
// - Client handling thread starts by calling operator()

class ClientHandler
{
public:
  void operator()(Socket& socket_);
  bool testStringHandling(Socket& socket_);
  bool testBufferHandling(Socket& socket_);

private:
	BlockingQueue<string> q_;
};

//----< Client Handler thread starts running this function >-----------------

void ClientHandler::operator()(Socket& socket_)
{
	Display *disp = new Display();
	BlockingQueue<string> q_;
			while (true)
			{
				Receiver *rs = new Receiver();
				std::string command = socket_.recvString();
				q_.enQ(command);
				if (command.size() == 0)
					break;
				size_t size= q_.size();
				string ackmsg;
				for (size_t i = 0; i < size; i++)
				{
					command = q_.deQ();
					ackmsg = rs->start(command, socket_);
				}
				Sender *s = new Sender();
				if (ackmsg != "")
				{
					s->sendAck(socket_, ackmsg);
				}
		}
  
  disp->show("ClientHandler socket connection closing");
  socket_.shutDown();
  socket_.close();
  disp->show("ClientHandler thread terminating");

}

//----< test stub starts here >----------------------------------------------

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
	Display *disp = new Display();
  title("Server", '=');
  try
  {
	  string client_port;
	  if (argc > 1)
	  {
		  client_port = argv[1];
	  }
	int clientport=atoi(client_port.c_str());
    Verbose v(true);
    SocketSystem ss;
    SocketListener sl(clientport,Socket::IP6);
    ClientHandler cp;
    sl.start(cp);
    Verbose::show("press key to exit: ", always);
    std::cout.flush();
    std::cin.get();
  }
  catch (std::exception& ex)
  {
	  disp->Exeception(ex);
  }
}

