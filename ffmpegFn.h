#pragma once
#include <stdio.h>
#include <tchar.h>
#include <string>

extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libswresample/swresample.h>
#include <libswscale/swscale.h>
#include <libavutil/avutil.h>
}

#pragma comment(lib, "avformat.lib")
#pragma comment(lib, "avcodec.lib")
#pragma comment(lib, "swresample.lib")
#pragma comment(lib, "swscale.lib")
#pragma comment(lib, "avutil.lib")

class ffmpegFn
{
public:
	int showInformation(std::string const& str1);
};

