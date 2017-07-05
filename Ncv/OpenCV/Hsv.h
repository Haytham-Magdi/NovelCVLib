#pragma once


#include <Novel-Lib\Ncpp\Common\commonLib.h>
#include <Novel-Lib\Ncv\OpenCV\CvIncludes.h>
#include <Novel-Lib\Ncv\OpenCV\Types.h>
#include <Novel-Lib\Ncv\OpenCV\PixelTypes.h>
#include <Novel-Lib\Ncv\OpenCV\error.h>
#include <Novel-Lib\Ncv\OpenCV\Channel.h>
#include <Novel-Lib\Ncv\OpenCV\Image.h>



namespace Ncv
{
	using namespace Ncpp;

	class Hsv
	{
	public :

		static void GetHsvOfRgb(Uint8 a_nRed, Uint8 a_nGrn, Uint8 a_nBlu,
			Uint8 * a_pHue, Uint8 * a_pSat, Uint8 * a_pVal);

		static void CalcHsvDiff(S16ImageRef a_srcP, 
			Ncv::S16ImageRef a_srcAN, S16ImageRef a_dst);
	};


}