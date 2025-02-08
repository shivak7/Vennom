#include "tinyxml2.h"
#include <iostream>
#include <string>
using namespace	tinyxml2;

int main()
{
	XMLDocument doc;
	doc.LoadFile("template.vmdl");
	
	XMLElement* titleElement = doc.FirstChildElement( "vsys" )->FirstChildElement( "parameter" );
	
	XMLText* textNode = titleElement->FirstChild()->ToText();
	std::string title = textNode->Value();
	std::cout << "String ID:" << title << std::endl;
	
	std::string p_attr = titleElement->Attribute("name");
	std::cout << "Attr String :" << p_attr << std::endl;
	
	titleElement = titleElement->NextSiblingElement("parameter");
	
	textNode = titleElement->FirstChild()->ToText();
	title = textNode->Value();
	std::cout << "Class ID:" << title << std::endl;
	
	titleElement = titleElement->NextSiblingElement("parameter");
	
	
	if(titleElement!=NULL)
	{
		textNode = titleElement->FirstChild()->ToText();
		title = textNode->Value();
		std::cout << "Class ID:" << title << std::endl;
	}
	else
		std::cout << "No more parameter elements" << std::endl;

	return 0;
}
