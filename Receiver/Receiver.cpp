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

#include <fstream>
#include "Receiver.h"
#include "../ApplicationHelpers/AppHelpers.h"
#include "../FileSystem/FileSystem.h"
#include "../Message/Message.h"
#include "../Sender/Sender.h"

using namespace FileSystem;
using namespace ApplicationHelpers;

using Files = std::vector<std::string>;
using Path1 = std::string;
using Patterns = std::vector<std::string>;

class TextSearch
{
public:
	using Files = std::vector<std::string>;
	using SearchString = std::string;

	bool TextSearch::search(string sstr, string path)
	{
		//file_mutex.lock();
		std::ostringstream stext;
		std::ofstream fs;
		Path *p = new Path();
		//std::string fullfile = p->getFullFileSpec(file);

		fs.open(path, std::fstream::in);
		if (fs.good())
		{
			stext << fs.rdbuf();
			std::string text = stext.str();
			size_t pos = text.find(sstr);
			if (pos < text.size())
				return true;
		}

		//file_mutex.unlock();
		return false;
	}
private:
	mutex file_mutex;
};

Receiver::Receiver()
{

}


Receiver::~Receiver()
{
}
// Starts the receiver
string Receiver::start(string msg1,Socket &si) ////////////////////////////////////////////////////////////////////////////////
{
		try
		{
			Message *msgobj = new Message();
				msgobj->setMessage(msg1);
				string msgstr="";
				//TextSearch text_search;
				if (msg1.find("command:uploadfile") != std::string::npos)
				{
					type = true;
					msgstr=writeToFile(msg1, type,si);
				}

				if (msg1.find("command:download") != std::string::npos)
				{
					Sender sd;
					Message *m = new Message();
					string filename = m->getmsgBody(msg1);
					string sendaddres=msgobj->getsendAddr(msg1);
					string clientaddres = msgobj->getrecvAddr(msg1);
					string client_port;
					string client_addrs;
					string server_port;
					string server_addrs;
					string parsed;
					stringstream input_stringstream1(sendaddres);

					if (getline(input_stringstream1, parsed, ','))
					{
						client_addrs = parsed;
					}
					if (getline(input_stringstream1, parsed, ' '))
					{
						client_port = parsed;
					}

					string parsed1;
					stringstream input_stringstream(clientaddres);

					if (getline(input_stringstream, parsed1, ','))
					{
						server_addrs = parsed1;
					}
					if (getline(input_stringstream, parsed1, ' '))
					{
						server_port = parsed1;
					}


					/*string parsed2;
					stringstream input_stringstream2(filename);

					if (getline(input_stringstream, parsed2, '\t'))
					{
						filename = parsed2;
					}*/
					
					int clientport = atoi(client_port.c_str());
					int serverport = atoi(server_port.c_str());
					sd.sendTextFile(client_addrs, clientport, server_addrs, serverport, filename, si, true);

					Message ackmsg;
					ackmsg.setCommand("Acknowledgement");
					ackmsg.setsendAddr(msgobj->getrecvAddr(msg1));
					ackmsg.setrecAddr(msgobj->getsendAddr(msg1));
					string s = "Message :" + msgobj->getmsgBody(msg1) + "Received by client with address: " + msgobj->getrecvAddr(msg1);
					Verbose::show("************************************");
					ackmsg.setmsgBody(s);
					msgstr = ackmsg.getMessage();

				}
				else if (msg1.find("command:NormalMessage") != std::string::npos)
				{
					Display *disp = new Display();
					disp->show("Demonstrating Requirement 3");
					disp->show("************************************");
					type = true;
					string prtmsg = "Server received message: " + msgobj->getmsgBody(msg1) + " From client with address: " + msgobj->getsendAddr(msg1);
					disp->show(prtmsg);
					string pmsg = "Sending Acknowledgement to Client with address: " + msgobj->getsendAddr(msg1);
					disp->show(pmsg);
					Message ackmsg;
					ackmsg.setCommand("Acknowledgement");
					ackmsg.setsendAddr(msgobj->getrecvAddr(msg1));
					ackmsg.setrecAddr(msgobj->getsendAddr(msg1));
					string s = "Message :" + msgobj->getmsgBody(msg1) + "Received by Server with address: " + msgobj->getrecvAddr(msg1);
					Verbose::show("************************************");
					ackmsg.setmsgBody(s);
					msgstr=ackmsg.getMessage();
				}
				else if (msg1.find("command:textsearch") != std::string::npos)
				{
				    TextSearch *ts=new TextSearch();
					Message *m = new Message();
					//ts.search();
					BlockingQueue<std::string> resultfiles;
					std::vector<string> file_patterns,all_files;
					string sstr = m->getmsgBody(msg1);
					string file_path = m->getFileName(msg1);
					string filepattern = m->getPatterns(msg1);

					std::istringstream ss(filepattern);
					std::string token;

					while (std::getline(ss, token, ',')) {
						file_patterns.push_back(token);
					}

					all_files = showFiles(file_path, file_patterns);
					for each (string file in all_files)
					{
						if (ts->search(sstr, file))
							resultfiles.enQ(file);
					}
					string resultfiles1;

					for (int i = 0; i < resultfiles.size(); i++)
					{
						resultfiles1 =resultfiles1 + resultfiles.deQ();
						resultfiles1.append(";");
					}
					string setFileMessage1=setFileMessage(msg1, resultfiles1);
					si.sendString(setFileMessage1);
					//search(sstr,resultfiles);
				}
				return msgstr;
		}

		catch (std::exception& ex)
		{
			Display *disp = new Display();
			disp->Exeception(ex);
			return "";
		}
		
}

// Writes to the file in the server.. downloading
string Receiver::writeToFile(std::string filemsg, bool type,Socket &si)
{
	Display *disp = new Display();
	Message *m = new Message();
	char filestart = m->getFileStart(filemsg);
	string msgbody = m->getmsgBody(filemsg),filename = m->getFileName(filemsg),fullpath = "../UploadedFolder/" + filename,msgstr="";
	std::ofstream o;
	try
	{
		if (type == true)
		{
			if (filestart == '1')
			{
				
				o.open(fullpath);
				o << msgbody << endl;

			}

			else if (filemsg.find("Body:endfile") != string::npos)
			{
				o.close();
				string uploadpath = "../UploadedFolder/" + m->getFileName(filemsg);
				string uploadstring = "\n Recieved File: " + m->getFileName(filemsg)+" And stored at path: " +uploadpath;
				disp->show(uploadstring);
				string pmsg = "Sending Acknowledgement to Client with address: " + m->getsendAddr(filemsg);
				disp->show(pmsg);
				msgstr = setMessage(filemsg);
				
			}
			else
			{
				o.open(fullpath,ios::app);
				if (o.is_open())
					o << msgbody << endl;
			}

		}
		return msgstr;
	}

	catch (exception ex)
	{
		disp->Exeception(ex);
		return "";
	}

}
string Receiver::writeToFile1(std::string filemsg, bool type, Socket &si)
{
	Display *disp = new Display();
	Message *m = new Message();
	char filestart = m->getFileStart(filemsg);
	string msgbody = m->getmsgBody(filemsg), filename = m->getFileName(filemsg), fullpath = "../UploadedFolder/" + filename, msgstr = "";
	std::ofstream o;
	try
	{
		if (type == true)
		{
			if (filestart == '1')
			{

				o.open(fullpath);
				o << msgbody << endl;

			}

			else if (filemsg.find("Body:endfile") != string::npos)
			{
				o.close();
				string uploadpath = "../UploadedFolder/" + m->getFileName(filemsg);
				string uploadstring = "\n Recieved File: " + m->getFileName(filemsg) + " And stored at path: " + uploadpath;
				disp->show(uploadstring);
				string pmsg = "Sending Acknowledgement to Client with address: " + m->getsendAddr(filemsg);
				disp->show(pmsg);
				msgstr = setMessage(filemsg);

			}
			else
			{
				o.open(fullpath, ios::app);
				if (o.is_open())
					o << msgbody << endl;
			}

		}
		return msgstr;
	}

	catch (exception ex)
	{
		disp->Exeception(ex);
		return "";
	}

}



// Sets the message for the acknowledgement
string Receiver::setMessage(std::string filemsg)
{
	Message *msg = new Message();
	Message m;
	m.setMessage(filemsg);
	msg->setCommand("Acknowledgement");
	msg->setFileAttrs(m.getFileName(filemsg));
	msg->setsendAddr(m.getrecvAddr(filemsg));
	msg->setrecAddr(m.getsendAddr(filemsg));
	msg->setmsgBody("File Uploaded Successfully");
	string msgstr = msg->getMessage();
	return msgstr;
}
string Receiver::setFileMessage(std::string filemsg,string resultfiles)
{
	Message *msg = new Message();
	Message m;
	m.setMessage(filemsg);
	msg->setCommand("textsearch");
	msg->setFileAttrs(m.getFileName(filemsg));
	msg->setsendAddr(m.getrecvAddr(filemsg));
	msg->setrecAddr(m.getsendAddr(filemsg));
	msg->setmsgBody(resultfiles);
	string msgstr = msg->getMessage();
	return msgstr;
}

// Waits for acknowledgment from the server
void Receiver::recvAck(Socket &si)
{
	Display *disp = new Display();
	if (si.waitForData(10000, 10))
	{
		string ack;
		while (ack.length() == 0)
		{
			ack = si.recvString();
			Message *m1 = new Message();
			m1->setMessage(ack);
			string result=m1->getmsgBody(ack);

			if (ack.size() == 0 || ack.find("TEST_END") < std::string::npos)
				break;
			string msgdisp = "Acknowledgment: " + result;
			disp->show(msgdisp);
		}
	}
	else
	{
		disp->show("client wait for server timed-out");
	}

}

void Receiver::recvAck1(Socket &si)
{
	Display *disp = new Display();
	if (si.waitForData(10000, 10))
	{
		string ack;
		std::vector<string> file_patterns;
		while (ack.length() == 0)
		{
			ack = si.recvString();
			Message *m1 = new Message();
			m1->setMessage(ack);
			string result = m1->getmsgBody(ack);
			if (ack.size() == 0 || ack.find("TEST_END") < std::string::npos)
				break;

			std::istringstream ss(result);
			std::string token;

			while (std::getline(ss, token, ',')) {
				file_patterns.push_back(token);
			}
			for (int i = 0; i < file_patterns.size(); i++)
			{
				string msgdisp = "Files: " + file_patterns.at(i);
				disp->show(msgdisp);
			}
		}
	}
	else
	{
		disp->show("client wait for server timed-out");
	}

}

std::vector<std::string> Receiver::showAllDirectories(std::string & baseDirectory, std::vector<std::string> & directories)
{
	std::vector<std::string> temp_directories = FileSystem::Directory::getDirectories(baseDirectory);
	if (temp_directories.size() < 2){
		return directories;
	}
	else{
		directories.insert(directories.end(), temp_directories.begin() + 2, temp_directories.end());
		int count = 2;                                                                //recursive method to retrieve all directories
		while (count < temp_directories.size()){
			temp_directories[count] = baseDirectory+"\\"+temp_directories[count];
			showAllDirectories(temp_directories[count], directories);
			count++;
		}
	}
	return directories;

}

Files Receiver::showFiles(const Path1& path, Patterns& patts)
{
	Files files;
	if (!FileSystem::Directory::exists(path))
	{
		std::ostringstream out;
		out << "path " << path << "does not exist";
		throw std::exception(out.str().c_str());
	}
	std::cout << "path is :" << path;
	if (patts.size() == 0)
		patts.push_back("*.*");
	std::vector<std::string> directories;
	directories.push_back(std::string(path));

	showAllDirectories(std::string(path), directories);

	for (auto direc : directories){
		FileSystem::Directory::setCurrentDirectory(direc);
		for (auto patt : patts)
		{
			std::string fp = FileSystem::Directory::getCurrentDirectory();
			std::vector<std::string> temp = FileSystem::Directory::getFiles(FileSystem::Directory::getCurrentDirectory(), patt);
			for (int i = 0; i < temp.size(); i++){
				temp[i] = fp + "\\" + temp[i];                                    //retrieving files
			}
			files.insert(files.end(), temp.begin(), temp.end());
		}
	}
	return files;
}

#ifdef TEST_RECEIVER
int main(int argc, char *argv[])
{
	string msg1="command:fileupload;\n;FileName:test.txt;\n;body:sneha;"
	start(msg1);
	writeToFile(msg1,true);
	string body=getmsgBody(msg1);
	string body1=getbinarymsgBody(msg1);
	char c=getFileStart(msg1);
	string filename=getFileName(msg1);

}
#endif