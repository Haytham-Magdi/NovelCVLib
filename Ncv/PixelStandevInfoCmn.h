#pragma once

//#include <NovelCVLib\Ncpp\Common\commonLib_Misc.h>
//#include <NovelCVLib\Ncpp\Math\mathLib.h>
//#include <NovelCVLib\OpenCV\CvIncludes.h>
//#include <NovelCVLib\OpenCV\Types.h>
//#include <NovelCVLib\OpenCV\error.h>
//#include <vector>
//#include <NovelCVLib\OpenCV\Channel.h>
//#include <NovelCVLib\OpenCV\Image.h>



namespace Ncv
{

	class PixelStandevInfoCmn //: public Ncpp::Object
	{
	public:

		int Index;

		//int Dir;
		//float Val;
		
		float LeastVal;
		int LeastValDir;

		float SecondLeastVal;
		int SecondLeastValDir;

		float NormLeastVal1;
		float NormLeastVal2;
		float NormSecondLeastVal;

		//float MaxVal;
		//int MaxValDir;

		float allVals[8];

		bool IsDirClear() const
		{
			return this->LeastVal < 0.5 * this->NormLeastVal1;
		}
	};

	//typedef Ncpp::ObjRef< PixelStandevInfoCmn > PixelStandevInfoCmnRef;
}