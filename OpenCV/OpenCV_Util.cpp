
#include <NovelCVLib\OpenCV\OpenCV_Util.h>


namespace Ncv
{
	namespace OpenCV_Util
	{


		//using namespace Ncv::OpenCV_Util;


		Size_2D size_2D(const cv::Size & src)
		{
			//return Size_2D(src.width, src.height);

			Size_2D ret(src.width, src.height);
			return ret;
		}

		cv::Size toCvSize(const Size_2D & src)
		{
			return cvSize(src.GetX(), src.GetY());
		}


		S32Point toS32Point(const cv::Point & src)
		{
			S32Point ret(src.x, src.y);
			return ret;
		}

		cv::Point toCvPoint(const S32Point & src)
		{
			return cv::Point(src.GetX(), src.GetY());
		}


		S64Point toS64Point(const cv::Point & src)
		{
			S64Point ret(src.x, src.y);
			return ret;
		}

		cv::Point toCvPoint(const S64Point & src)
		{
			return cv::Point(src.GetX(), src.GetY());
		}


	}
}


