#pragma once

#include <NovelCVLib\Ncpp\Common\commonLib_Misc.h>
#include <NovelCVLib\Ncpp\Math\mathLib.h>



namespace Ncv
{

	template<class T>
	class Bidiff
	{
	public:

		T Diff1_BkwdVal;
		T Diff1_FwdVal;

	};

}