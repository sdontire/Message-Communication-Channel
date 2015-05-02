#ifndef DISPLAY_H
#define DISPLAY_H
/////////////////////////////////////////////////////////////////////////
// Display.h- Displaying messages received from clientExecutive and Server// 
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

#pragma once
#include "../ApplicationHelpers/AppHelpers.h"
#include <string>
using namespace ApplicationHelpers;
class Display
{
public:
	Display(){}
	~Display(){}
	void sendreq3(std::string pmsg);
	void recvreq5();
	void sendreq5();
	void Exeception(std::exception ex);
	void cosmtic();
	void show(std::string str);
};

#endif