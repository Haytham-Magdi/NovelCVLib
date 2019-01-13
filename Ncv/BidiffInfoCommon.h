#pragma once

//#include <NovelCVLib\Ncpp\Common\commonLib_Misc.h>
//#include <NovelCVLib\Ncpp\Math\mathLib.h>



namespace Ncv
{

	class BidiffInfoCommon
	{
	public:
		
		int Index;

		//float LeastVal;
		float LeastValDirMaxVal;
		float LeastValDirMinVal;
		int LeastValDir;

		float SecondLeastVal;
		int SecondLeastValDir;

		float NormLeastVal;
		float NormDiff2LeastVal;
		float NormSecondLeastVal;

		bool IsEdge;

		//float MinVal;
		//int MinValDir;

		//float MaxVal;
		//int MaxValDir;

		//float allVals[8];
	};

}