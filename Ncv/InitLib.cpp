#pragma once

#include <Novel-Lib\Ncpp\Common\commonLib.h>
#include <Novel-Lib\Ncv\OpenCV\CvIncludes.h>
#include <Novel-Lib\Ncv\OpenCV\Types.h>
#include <Novel-Lib\Ncv\OpenCV\PixelTypes.h>
#include <Novel-Lib\Ncv\OpenCV\error.h>
#include <Novel-Lib\Ncv\OpenCV\Channel.h>
#include <Novel-Lib\Ncv\InitLib.h>


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