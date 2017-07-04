#pragma once

#include <Lib\Novel\Ncpp\Common\commonLib.h>
#include <Lib\Novel\Ncv\OpenCV\CvIncludes.h>
#include <Lib\Novel\Ncv\OpenCV\Types.h>
#include <Lib\Novel\Ncv\OpenCV\PixelTypes.h>
#include <Lib\Novel\Ncv\OpenCV\error.h>
#include <Lib\Novel\Ncv\OpenCV\Channel.h>
#include <Lib\Novel\Ncv\InitLib.h>


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