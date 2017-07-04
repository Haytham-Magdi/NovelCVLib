#pragma once

#include <Lib\Novel\Ncpp\Common\commonLib.h>
#include <Lib\Novel\Ncpp\Math\mathLib.h>
#include <Lib\Novel\Ncv\OpenCV\CvIncludes.h>
#include <Lib\Novel\Ncv\OpenCV\Types.h>
#include <Lib\Novel\Ncv\OpenCV\error.h>
#include <vector>
#include <Lib\Novel\Ncv\OpenCV\Channel.h>
#include <Lib\Novel\Ncv\OpenCV\Image.h>



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