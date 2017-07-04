#pragma once

#include <Lib\Novel\Ncpp\Common\commonLib.h>
#include <Lib\Novel\Ncpp\Math\mathLib.h>
//#include <Lib\Novel\Ncv\OpenCV\CvIncludes.h>
#include <Lib\Novel\Ncv\OpenCV\Types.h>
//#include <Lib\Novel\Ncv\OpenCV\error.h>
//#include <vector>
//#include <Lib\Novel\Ncv\OpenCV\Channel.h>
//#include <Lib\Novel\Ncv\OpenCV\Image.h>

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