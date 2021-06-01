/*
#include "ffmpegFn.h"



SDL_Renderer* renderer;
SDL_Texture* texture;
SDL_Rect r;

ffmpegFn::ffmpegFn()
{
	renderer = nullptr;
	texture = nullptr;
}
ffmpegFn::~ffmpegFn()
{
	delete renderer;
	delete texture;
}


// 함수 선언
int initSDL(AVCodecContext* codec_ctx);

void displayFrame(AVFrame* frame, AVCodecContext* dec_ctx);

void decode(AVCodecContext* dec_ctx, AVFrame* frame, AVPacket* pkt, FILE* f);

void pgm_save(unsigned char* buf, int wrap, int xsize, int ysize, FILE* f);


// 비디오 파일의 정보를 출력해주는 함수
// 배운곳 https://www.youtube.com/watch?v=qMNr1Su-nR8&t=30s
// 용도 학습용
int ffmpegFn::showInformation(std::string const& str1)
{
	AVFormatContext* fmt_ctx = NULL;
	int ret;
	const char* filename = str1.c_str();
	// av_register_all();

	//fill format context with file info
	if ((ret = avformat_open_input(&fmt_ctx, filename, NULL, NULL)))
		return ret;

	// get streams info from format context
	if ((ret = avformat_find_stream_info(fmt_ctx, NULL)) < 0) {
		av_log(NULL, AV_LOG_ERROR, "Cannot find stream information\n");
		return ret;
	}

	// loop streams and dump info
	for (int i = 0; i < fmt_ctx->nb_streams; i++)
	{
		av_dump_format(fmt_ctx, i, filename, false);
	}

	// close format context
	avformat_close_input(&fmt_ctx);

	system("PAUSE");

	return 0;
}

// 비디오 보여주는 함수
int ffmpegFn::displayVideo(std::string const& str1)
{
	AVFormatContext* fmt_ctx = NULL;
	AVCodecContext* codec_ctx = NULL;
	AVCodec* Codec = NULL;
	int ret;
	const char* filename = str1.c_str();
	std::string const &out_str = "Coffee.yuv";
	const char* outfilename = out_str.c_str();
	int VideoStreamIndex = -1;

	FILE* fin = NULL;
	FILE* fout = NULL;

	AVFrame* frame = NULL;
	AVPacket* pkt = NULL;

	// av_register_all();

	// 입력 파일 열기
	avformat_open_input(&fmt_ctx, filename, NULL, NULL);

	//get stream info
	avformat_find_stream_info(fmt_ctx, NULL);

	//alloc memory for codec context
	codec_ctx = avcodec_alloc_context3(NULL);

	// find decoding codec
	Codec = avcodec_find_decoder(codec_ctx->codec_id);

	initSDL(codec_ctx);


	// main loop
	while (1)
	{

		// read an encoded packet from file
		if (ret = av_read_frame(fmt_ctx, pkt) < 0)
		{
			av_log(NULL, AV_LOG_ERROR, "cannot read frame");
			break;
		}
		// if packet data is video data then send it to decoder
		if (pkt->stream_index == VideoStreamIndex)
		{
			decode(codec_ctx, frame, pkt, fout);
		}

		// release packet buffers to be allocated again
		av_packet_unref(pkt);
	}

	system("PAUSE");

	return 0;
}

// 비디오 함수 내부 SDL 실행 함수
// 참조 및 배운곳 https://www.youtube.com/watch?v=eWN36LfyP04&t=677s
// 용도 학습용
int initSDL(AVCodecContext* codec_ctx)
{
	SDL_Window* window = NULL;

	// init SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		fprintf(stderr, "could not init sdl %s\n", SDL_GetError());
		return -1;
	}

	//create sdl window
	window = SDL_CreateWindow("Preview", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, codec_ctx->width, codec_ctx->height, 0);
	if (!window)
	{
		fprintf(stderr, "could not create sdl window \n");
		return -1;
	}

	// specify rectangle position and scale
	r.x = 0;
	r.y = 0;
	r.w = codec_ctx->width;
	r.h = codec_ctx->height;

	// create sdl renderer
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer)
	{
		fprintf(stderr, "could not create sdl renderer \n");
		return -1;
	}

	// create texture
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_YV12, SDL_TEXTUREACCESS_STREAMING, codec_ctx->width, codec_ctx->height);
	if (!texture)
	{
		fprintf(stderr, "could not create sdl texture \n");
		return -1;
	}

	return 0;
}

void displayFrame(AVFrame* frame, AVCodecContext* dec_ctx)
{
	// pass frame data to texture then copy texture to renderer and present renderer
	SDL_UpdateYUVTexture(texture, &r, frame->data[0], frame->linesize[0], frame->data[1], frame->linesize[1], frame->data[2], frame->linesize[2]);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
}

void decode(AVCodecContext* dec_ctx, AVFrame* frame, AVPacket* pkt, FILE* f)
{
	int ret;

	//send packet to decoder
	ret = avcodec_send_packet(dec_ctx, pkt);
	if (ret < 0) {
		fprintf(stderr, "Error sending a packet for decoding\n");
		exit(1);
	}
	while (ret >= 0) {
		// receive frame from decoder
		// we may receive multiple frames or we may consume all data from decoder, then return to main loop
		ret = avcodec_receive_frame(dec_ctx, frame);
		if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
			return;
		else if (ret < 0) {
			// something wrong, quit program
			fprintf(stderr, "Error during decoding\n");
			exit(1);
		}
		printf("saving frame %3d\n", dec_ctx->frame_number);
		fflush(stdout);


		// display frame on sdl window
		displayFrame(frame, dec_ctx);

		// send frame info to writing function
		pgm_save(frame->data[0], frame->linesize[0], frame->width, frame->height, f);
	}
}

void pgm_save(unsigned char* buf, int wrap, int xsize, int ysize, FILE* f)
{
	// write header
	fprintf(f, "P5\n%d %d\n%d\n", xsize, ysize, 255);
	// loop until all rows are written to file
	for (int i = 0; i < ysize; i++)
		fwrite(buf + i * wrap, 1, xsize, f);
}

*/