#pragma once

#include <NovelCVLib\Ncpp\Common\commonLib_Misc.h>
#include <NovelCVLib\Ncpp\Math\mathLib.h>
#include <NovelCVLib\OpenCV\CvIncludes.h>
#include <NovelCVLib\OpenCV\Types.h>
#include <NovelCVLib\OpenCV\error.h>
#include <vector>
#include <NovelCVLib\OpenCV\Channel.h>
#include <NovelCVLib\OpenCV\Image.h>



namespace Ncv
{

	class ConflictInfo //: public Ncpp::Object
	{
	public:
		bool Exists;
		int Offset_Side_1;
		int Offset_Side_2;
	};

	class ConflictInfo_Ex : public ConflictInfo//: public Ncpp::Object
	{
	public:
		int Dir;
		//float NormVal;
	};

	//typedef Ncpp::ObjRef< ConflictInfo > ConflictInfoRef;
}