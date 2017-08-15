#pragma once

#include <NovelCVLib\Ncpp\Common\commonLib.h>
#include <NovelCVLib\Ncpp\Math\mathLib.h>
//#include <NovelCVLib\OpenCV\CvIncludes.h>
#include <NovelCVLib\OpenCV\Types.h>
//#include <NovelCVLib\OpenCV\error.h>
//#include <vector>
//#include <NovelCVLib\OpenCV\Channel.h>
//#include <NovelCVLib\OpenCV\Image.h>

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