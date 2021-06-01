#include "ffmpegFn.h"

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