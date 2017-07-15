#pragma once

#include <NovelCVLib\Ncpp\Common\commonLib.h>
#include <NovelCVLib\Ncpp\Math\mathLib.h>
#include <NovelCVLib\Ncv\OpenCV\CvIncludes.h>
#include <NovelCVLib\Ncv\OpenCV\Types.h>
#include <NovelCVLib\Ncv\OpenCV\error.h>
#include <vector>
#include <NovelCVLib\Ncv\OpenCV\Channel.h>
#include <NovelCVLib\Ncv\OpenCV\Image.h>



namespace Ncv
{

	class ConflictInfo //: FRM_Object()
	{
	public:
		bool Exists;
		int Offset_Side_1;
		int Offset_Side_2;
	};

	class ConflictInfo_Ex : public ConflictInfo//: FRM_Object()
	{
	public:
		int Dir;
		//float NormVal;
	};

	//typedef Ncpp::ObjRef< ConflictInfo > ConflictInfoRef;
}