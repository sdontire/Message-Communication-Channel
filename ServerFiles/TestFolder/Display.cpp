/////////////////////////////////////////////////////////////////////
//  Display.cpp - Displays results                                 //
//  ver 1.0                                                        //
//                                                                 //
//  Language:      Visual C++ 2013                                 //
//  Platform:      Dell Precision T7400, Vista Ultimate SP1        //
//  Application:   Prototype for CSE687 Pr1, feb2014               //    
//  Author:			Siddhartha Kakarla, Fall 2013,skakarla@syr.edu //
//  Reference:      Jim Fawcett, CST 4-187, Syracuse University    //
//                 (315) 443-3948, jfawcett@twcny.rr.com           //
/////////////////////////////////////////////////////////////////////

#include "Display.h"
#include <string>
#include <vector>
#include "XmlWriter.h"
#include "MNode.h"
#include "MTree.h"

//display function scope for /b or /B option
void Display::displayFunctionNameSizeComplexity(std::string elementName,int lineCount, int complexity)
{
	std::cout << "\n \n Function " << elementName; 
	std::cout << ", Function size(line count) is:" << lineCount;
	std::cout << ", Complexity is:" << complexity;
	
}

//display funtion scope normally
void Display::displayFunctionName(std::string elementName, int startBrace, int endBrace)
{
	std::cout << "\n \n Function " << elementName;
	std::cout << "\n \t opening brace line number is:" << startBrace;
	std::cout << "\n \t closing brace line number is:" << endBrace;

}

//Display numbe of scopes for a function
void Display::displayNodesNumber(int nodesnumber)
{
	std::cout << "\n \t Number of nodes:" << nodesnumber;
}

//To display xml representation of funtion scope with highest complexity
void Display::printXml(std::vector<std::string> functionscopes)
{
	XmlWriter xwtr;
	if (functionscopes.size() > 0)
	{
		xwtr.start(functionscopes[0]);
	}
	else 
	{
		std::cout << "\n \nNo functions with complexity in this class";
		return;
	}
	for (int i = 1; i < (int)functionscopes.size() - 1; i++)
	{
		if (functionscopes[i] != "/")
		{
			xwtr.start(functionscopes[i]);
			std::cout << "\n \t";
		}
		else
		{
			xwtr.end();
		}
	}

	std::cout << "\n -----------------------\n";
	std::cout << "\nXML Representation";
	std::cout << "\n -----------------------\n";
	std::cout << xwtr.xml();
}

//To display tree representation of funtion with highest complexity
void Display::printTree(std::vector<std::string> functionscopes)
{
	if (functionscopes.size() == 0)
	{
		std::cout << "\nThere are no functions with scopes in this class to construct a tree";
		return;
	}

	typedef TMTree::MNode<std::string> Node;
	std::vector<Node *> treeVector;
	class newOper : public TMTree::Operation<Node>
	{
	public:
		bool operator()(Node* pNode)
		{
			std::cout << "\n -- " << pNode->ToString();
			return false;
		}
	};

	TMTree::MTree<Node> tree(new newOper);
	Node* pRoot = new Node(functionscopes[0]);
	tree.makeRoot(pRoot);
	treeVector.push_back(pRoot);
	for (int i = 1; i < (int)functionscopes.size() - 1; i++)
	{
		if (functionscopes[i] != "/")
		{
			Node* child = new Node(functionscopes[i]);
			treeVector[treeVector.size() - 1]->addChild(child);
			treeVector.push_back(child);
		}
		else
		{
			treeVector.pop_back();
		}
	}

	std::cout << "\n \n-----------------------";
	std::cout << "\n Tree Representation";
	std::cout << "\n -----------------------\n";
	tree.walk(pRoot);
	std::cout << std::endl;
}

//To display structure scope
void Display::displayStructName(std::string elementName, int startBrace, int endBrace)
{
	std::cout << "\n \n struct " << elementName; 
	std::cout << "\n \t opening brace line number is:" << startBrace;
	std::cout << "\n \t closing brace line number is:" << endBrace;
}

//To display enum scope
void Display::displayEnumName(std::string elementName, int startBrace, int endBrace)
{
	std::cout << "\n \n enum " << elementName; 
	std::cout << "\n \t opening brace line number is:" << startBrace;
	std::cout << "\n \t closing brace line number is:" << endBrace;
}

//to display namespace scope
void Display::displayNamespaceName(std::string elementName, int startBrace, int endBrace)
{
	std::cout << "\n \n namespace " << elementName; 
	std::cout << "\n \t opening brace line number is:" << startBrace;
	std::cout << "\n \t closing brace line number is:" << endBrace;
}

//to display class scope
void Display::displayClassName(std::string elementName, int startBrace, int endBrace)
{
	std::cout << "\n \n class " << elementName; 
	std::cout << "\n \t opening brace line number is:" << startBrace;
	std::cout << "\n \t closing brace line number is:" << endBrace;
}


//Test stub
#ifdef TEST_DISPLAY
	
int main(int argc,char *argv[])
{
	cout<<"\n Demonstarting Display.cpp";
	displayClassName("class1",6,50);
	displayNamespaceName("namespace1",5,200);
	displayEnumName("Enum1",9,5);
	displayStructName("Struct1",15,7);
	displayNodesNumber(5);
	displayFunctionName("Func1",20,40);
	displayFunctionNameSizeComplexity("Func1",30,5);

	return 1;
}


#endif