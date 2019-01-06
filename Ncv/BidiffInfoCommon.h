#pragma once

//#include <NovelCVLib\Ncpp\Common\commonLib_Misc.h>
//#include <NovelCVLib\Ncpp\Math\mathLib.h>



namespace Ncv
{

	class BidiffInfoCommon
	{
	public:
		
		float LeastVal;
		int LeastValDir;

		float SecondLeastVal;
		int SecondLeastValDir;

		float NormLeastVal;
		float NormSecondLeastVal;

		//float MinVal;
		//int MinValDir;

		//float MaxVal;
		//int MaxValDir;

		//float allVals[8];
	};

}