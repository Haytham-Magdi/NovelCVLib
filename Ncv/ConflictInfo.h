#pragma once

#include <Novel-Lib\Ncpp\Common\commonLib.h>
#include <Novel-Lib\Ncpp\Math\mathLib.h>
#include <Novel-Lib\Ncv\OpenCV\CvIncludes.h>
#include <Novel-Lib\Ncv\OpenCV\Types.h>
#include <Novel-Lib\Ncv\OpenCV\error.h>
#include <vector>
#include <Novel-Lib\Ncv\OpenCV\Channel.h>
#include <Novel-Lib\Ncv\OpenCV\Image.h>



namespace Ncv
{

	class ConflictInfo //: FRM_Object
	{
	public:
		bool Exists;
		int Offset_Side_1;
		int Offset_Side_2;
	};

	class ConflictInfo_Ex : public ConflictInfo//: FRM_Object
	{
	public:
		int Dir;
		//float NormVal;
	};

	//typedef Ncpp::ObjRef< ConflictInfo > ConflictInfoRef;
}