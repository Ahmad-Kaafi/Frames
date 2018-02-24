

#include "Frame.h"
#include "Animation.h"
#include <iostream>
#include <string>
#include <time.h>

using namespace std;



Animation::Animation(char * name) {
	animationName = name;
	//frames = nullptr;
	numFrames = 0;
}
/*****************************************
Function Name: ~Animation
Purpose: To cleanup all the frames in the memory of struct Animation.
Function In parameters: N/A
Function Out parameters: N/A
Version: 1.0
*****************************************/
Animation::~Animation() {
	DeleteFrames();
}

/*****************************************
Function Name: InsertFrame
Purpose: To add a new Frame to Animation at a specified position.
Function In parameters: N/A
Function Out parameters: N/A
Version: 1.0
*****************************************/
void Animation::InsertFrame() {
	char* fname;// = nullptr;
	//int counter = numFrames;
	//Frame *iterator;
	//iterator = new Frame;

	//int size = strlen(fname) + 1; // get the length of fileName
	fname = new char[100];

	cout << "Insert a Frame in the Animation\n" << endl;
	cout << "Please enter the Frame filename: ";
	cin >> fname; // catch user entered fname

	//strcpy(iterator->GetfileName(), fname); // copy user entered fname into fileName
	if (numFrames != 0)
	{
		for (unsigned int i = 0; i < numFrames; i++) //loop to check for duplicates of filenames
		{
			if (frames[i]->FindFileName(fname) == true)//compares existing filenames to the one from the user
			{
				cout << "Frame Already Exists" << endl;
				delete[] fname;
				fname = nullptr;
				return;
			}
		}
	}

	if (numFrames == 0)
	{
		 frames = new Frame*[BLOCK_SIZE];
		//frames = nullptr;// might need
	}
	//if (numFrames >= BLOCK_SIZE)
	//{
		if (numFrames % BLOCK_SIZE == 0 || numFrames == 0) //checks if a block is filled with frmaes
		{

			Frame** tempFrame = new Frame*[(numFrames + BLOCK_SIZE)];//allocates a larger block of memory for frames

			printf("frames, %p\n", frames);

			for (unsigned int i = 0; i < numFrames; i++)// loop to place the old frames to the new larger block of memory
				tempFrame[i] = frames[i];
			
			//frames = nullptr;// might need
			delete[] frames;//frees the old space of memory 

			printf("%p\n", tempFrame);
			printf("frames, %p\n", frames);

			frames = tempFrame;//places the new block of memory with the frames created, into frames

			tempFrame = nullptr;
		}
	//}
	//frames[numFrames]->Frame();
	frames[numFrames] = new Frame("");// allocates memory for the array of frames

	frames[numFrames]->ReplaceFrameName(fname);//allocates memory for filename to the size of the user inputed filename
	//places the user inputed filename into fileName
	int numBlocks = numFrames / BLOCK_SIZE + 1;

	cout <<"Number of Blocks =" << numBlocks << endl; 
	
	fname = nullptr;

	delete [] fname;
    //cout << numFrames << endl;

	++numFrames;//increments numframes 

	

}
void Animation::EditFrame()
{
	char* eframe = nullptr;

	int found = 0;

	if (numFrames == 0) {
		cout << "No frames in the animation" << endl;
		return;
	}

	eframe = new char[100];

	cout << "Please enter the name of the Frame to edit :" << endl;
	cin >> eframe;

	for (unsigned int i = 0; i < numFrames; i++) //loop to check for duplicates of filenames
	{
		if (frames[i]->FindFileName(eframe) == false && i==numFrames-1)//compares existing filenames to the one from the user
		{
			cout << "Frame Doesn't Exists" << endl;
			delete[] eframe;
			eframe = nullptr;
			return;
		}
		if (frames[i]->FindFileName(eframe) == true)
			break;
		
	}

	for (unsigned int i = 0; i < numFrames; i++) //loop to check for duplicates of filenames
	{
		if (frames[i]->FindFileName(eframe) == true)
		{
			cout << "Found at index " << i << endl;
			found = i;
			break;
		}

	}

	/*for (unsigned int i = 0; i < numFrames; i++)
	{
		if (frames[numFrames]->FindFileName(eframe) == true)
			cout << "Found at index " << i << endl;
	}*/
	
	cout << "What is the replacement name ? " << endl;
	cin >> eframe;

	for (unsigned int i = 0; i < numFrames; i++) //loop to check for duplicates of filenames
	{
		if (frames[i]->FindFileName(eframe) == true)
		{
			cout << "Frame Already Exists" << endl;
			delete[] eframe;
			eframe = nullptr;
			
			return;
		}
	}

		frames[found]->~Frame();
		
		frames[found]->ReplaceFrameName(eframe);
		
		eframe = nullptr;
		delete[] eframe;
//	frames[numFrames]->ReplaceFrameName(eframe);

}

/*****************************************
Function Name: DeleteFrames
Purpose: To delete all the frames in the Animation.
Function In parameters: N/A
Function Out parameters: N/A
Version: 1.0
*****************************************/
void Animation::DeleteFrames() {

	if (numFrames == 0) {
		cout << "No frames in the animation" << endl;
		return;
	}

	for (unsigned int i = 0; i < numFrames; i++)//loops to free each filename created and frames created
	{
		//delete frames[i]->~Frame;
		delete frames[i];
	}	
		
	delete [] frames;

	frames = nullptr;

	numFrames = 0;

	cout << "Deleted all the Frames in the Animation" << endl;

/*	if (frames != nullptr) {
		delete this->frames;
		frames = nullptr;
		cout << "Delete all the Frames from the Animation" << endl;
	}*/
}

/*****************************************
Function Name: RunFrames
Purpose: To display all the frames in the Animation to show the
list of Frame details one after another at 1 second intervals.
Function In parameters: N/A
Function Out parameters: N/A
Version: 1.0
*****************************************/
void Animation::RunFrames() {
	unsigned int counter = 0;
	time_t startsec, oldsec, newsec;

	if (numFrames == 0) {
		cout << "No frames in the animation" << endl;
		return;
	}

	cout << animationName << endl;

	startsec = oldsec = time(nullptr);

	while (counter < numFrames)
	{
		newsec = time(nullptr);
		if (newsec > oldsec)
		{
			cout << "Frame #" << counter << ", time = " << newsec - startsec << "sec" << endl;
			cout << "Image file name = " << frames[counter]->Report() << endl;
			oldsec = newsec;
			++counter;
		}
	}
}
