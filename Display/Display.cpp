
/////////////////////////////////////////////////////////////////////////
// Display.cpp- Displaying messages received from clientExecutive and Server// 
// Executive                                                           //
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
* Display package display's the messages or strings received from clientExecutive
* and serverExecutive to the console using functions.
*
* Public Interface
* ------------------
*--------------------
* void sendreq3(std::string pmsg)- Prints string passed to it
* void recvreq5()- Prints requirement 5 message of receiver
* void sendreq5()- Prints requirement 5 message of sender
* void Exeception(std::exception ex)- Prints Exception
* void cosmtic()- Prints cout messages
* void show(std::string str)- Prints the string passed to it
*
*  Required Files:
*  ---------------
*  Display.cpp,Display.h, AppHelpers.cpp, AppHelpers.h, WindowsHelpers.cpp,
*  WindowsHelpers
*
*  Build Command:
*-------------------------
* devenv Sockets.sln /rebuild debug
*
*  Maintenance History:
*  --------------------
* version 1.1- created Display Package
*/

#include "Display.h"
#include "../ApplicationHelpers/AppHelpers.h"
#include "../WindowsHelpers/WindowsHelpers.h"
#include <iostream>
#include <string>
using namespace ApplicationHelpers;

void Display::sendreq3(std::string pmsg)
{
	Verbose::show("Demonstrating Requirement 3");
	Verbose::show("************************************");
	Verbose::show("Sender Started\n");
	Verbose::show(pmsg);
}
void Display::recvreq5()
{
	Verbose::show("Demonstrating Requirement 5");
	Verbose::show("************************************");
	Verbose::show("Reciever started\n");

}
void Display::sendreq5()
{
	Verbose::show("Demonstrating Requirement 5");
	Verbose::show("************************************");
	Verbose::show("Sender started\n");

}

void Display::Exeception(std::exception ex)
{
	Verbose::show("  Exception caught:", always);
	Verbose::show(std::string("\n  ") + ex.what() + "\n\n");
}
void Display::cosmtic()
{
	std::cout << "\n  press key to exit: ";
	std::cin.get();
	std::cout << "\n\n";
}

void Display::show(std::string str)
{
	Verbose::show(str);
	std::cout << "\n";
}

#ifdef TEST_DISPLAY
int main(int argc, char *argv[])
{
	string pmsg="Client sending Message";
	sendreq3(pmsg);
	recvreq5();
	sendreq5();
	string ex="File not found";
	Exeception(ex);
	cosmtic();
	string str="File uploaded";
	show(str)
}
#endif
