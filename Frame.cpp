

#include "Frame.h"
#include "string.h"
using namespace std;

/*****************************************
Function Name: Frame
Purpose: To initialize the variables in the struct Frame.
Function In parameters: N/A
Function Out parameters: N/A
Version: 1.0
*****************************************/
Frame::Frame(char* fName) {
	frameName = nullptr;
	//frameName = new char[50]; might need delete
	frameName = fName;
}

/*****************************************
Function Name: ~Frame
Purpose: To cleanup the variables in the struct Frame.
Function In parameters: N/A
Function Out parameters: N/A
Version: 1.0
*****************************************/
Frame::~Frame() {
	delete frameName;
	frameName = nullptr; 
}
bool Frame::FindFileName(char* newfilename) 
{
	if (strcmp(frameName, newfilename) == 0)//compares existing filenames to the one from the user
		return true;

	else
		return false;
}
void Frame::ReplaceFrameName(char* replaceName) {
	
	frameName = replaceName;

}
char* Frame::Report()
{
	return frameName;
}
