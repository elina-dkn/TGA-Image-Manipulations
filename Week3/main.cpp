// Week3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Level.h"



int main()
{
	Level* level = new Level();
	level->AssignNonDefaultValues();
	level->ToString();
	string i = "";
	do {
		cout << endl;
		cout << "[Q]uit	[S]ave Level	[L]oad Level [Z] Undo	[Y] Redo" << endl;
		cout << "[C]reate Image buffer	[D]elete Image buffer	[A]dd chunk	[R]emove chunk" << endl;
		cout << endl;
		cin >> i;
		if (i == "s" || i == "S") {
			ofstream writeStream("level.bin", ios::out | ios::binary);
			level->Serialize(writeStream);
			writeStream.close();
			cout << "Level Saved: ";
			level->ToString();
		}
		else if (i == "l" || i == "L") {
			delete level;
			level = new Level();
			ifstream readStream("level.bin", ios::in | ios::binary);
			level->Deserialize(readStream);
			readStream.close();
			cout << "Loaded Level: ";
			level->ToString();
		}
		else if (i == "c" || i == "C") {
			level->CreateImageBuffer();
		}
		else if (i == "d" || i == "D") {
			level->DeleteImageBuffer();
		}
		else if (i == "a" || i == "A") {
			level->AddChunk(0);
			level->WriteImage();
		}
	} while (i != "Q" && i != "q");


	


	
}
