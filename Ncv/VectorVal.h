#pragma once

#include <Novel-Lib\Ncpp\Common\commonLib.h>
#include <Novel-Lib\Ncpp\Math\mathLib.h>
//#include <Novel-Lib\Ncv\OpenCV\CvIncludes.h>
#include <Novel-Lib\Ncv\OpenCV\Types.h>
//#include <Novel-Lib\Ncv\OpenCV\error.h>
//#include <vector>
//#include <Novel-Lib\Ncv\OpenCV\Channel.h>
//#include <Novel-Lib\Ncv\OpenCV\Image.h>

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