#pragma once

#include <NovelCVLib\Ncpp\Common\commonLib.h>
#include <NovelCVLib\OpenCV\CvIncludes.h>
#include <NovelCVLib\OpenCV\Types.h>
#include <NovelCVLib\OpenCV\PixelTypes.h>
#include <NovelCVLib\OpenCV\error.h>
#include <NovelCVLib\OpenCV\Channel.h>
#include <NovelCVLib\Ncv\InitLib.h>


namespace Ncv
{
	bool g_bDone = false;

	void InitLib(void)
	{
		if(g_bDone)
			return;

/*		std::vector<char> * pCv;

		for(int i=0; i<100; i++)
		{
			pCv = new std::vector<char>();
			pCv->resize(1000000);
		}*/

/*		std::vector<char> cv;
		cv.resize(100000000);
		cv.*/

/*		cv.resize(100000000);
		cv.resize(100000000);
		cv.clear();
		cv.resize(100000000);*/

		g_bDone = true;
	}


}