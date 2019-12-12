#include <iostream>
#include "Game.h"
//@Author Sean Nash & Oisin Wilson
//@Login C00217019 & C00213826
//Time Taken 8 Hours.




int main(int argc, char* argv[])
{
	Client myClient("127.0.0.1", 1111); //Create client to connect to server 127.0.0.1 [localhost] on port 1111
	if (!myClient.Connect()) //If client fails to connect...
	{
		std::cout << "Failed to connect to server..." << std::endl;
		system("pause");
		return -1;
	}

	std::string whatever = "ASDABHw";
	myClient.SendConnection(whatever);

	Game game;
	game.run(myClient);

	return EXIT_SUCCESS;
};