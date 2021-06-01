


#include "ffmpegFn.h"

int main()
{
	std::string path = "Coffee.mp4";
	ffmpegFn myFn = ffmpegFn();

	myFn.showInformation(path);

	return 0;
}


