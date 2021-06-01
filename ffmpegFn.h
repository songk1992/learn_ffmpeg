/*

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
#include <sdl2/SDL.h>
}

#undef main

#pragma comment(lib, "avformat.lib")
#pragma comment(lib, "avcodec.lib")
#pragma comment(lib, "swresample.lib")
#pragma comment(lib, "swscale.lib")
#pragma comment(lib, "avutil.lib")

class ffmpegFn
{
public:
	
	SDL_Renderer* renderer;
	SDL_Texture* texture;
	SDL_Rect r;

	ffmpegFn();
	~ffmpegFn();

	int showInformation(std::string const& str1);
	int displayVideo(std::string const& str1);
};

*/