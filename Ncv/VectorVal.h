#pragma once

#include <NovelCVLib\Ncpp\Common\commonLib.h>
#include <NovelCVLib\Ncpp\Math\mathLib.h>
//#include <NovelCVLib\Ncv\OpenCV\CvIncludes.h>
#include <NovelCVLib\Ncv\OpenCV\Types.h>
//#include <NovelCVLib\Ncv\OpenCV\error.h>
//#include <vector>
//#include <NovelCVLib\Ncv\OpenCV\Channel.h>
//#include <NovelCVLib\Ncv\OpenCV\Image.h>

namespace Ncv
{
	template<class T, const int N>
	class VectorVal
	{
	public:
		const int GetNofDims()
		{
			return N;
		}

	public:
		T Vals[N];

	};

	template<int const N>
	using F32VectorVal = VectorVal<float, N>;

}