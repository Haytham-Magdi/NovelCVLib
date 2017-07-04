#pragma once


#include <Lib\Novel\Ncpp\Common\commonLib.h>
#include <Lib\Novel\Ncv\OpenCV\CvIncludes.h>
#include <Lib\Novel\Ncv\OpenCV\Types.h>
#include <Lib\Novel\Ncv\OpenCV\PixelTypes.h>
#include <Lib\Novel\Ncv\OpenCV\error.h>
#include <Lib\Novel\Ncv\OpenCV\Channel.h>
#include <Lib\Novel\Ncv\OpenCV\Image.h>



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