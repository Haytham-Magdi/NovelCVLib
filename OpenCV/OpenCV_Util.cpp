
#include <NovelCVLib\OpenCV\OpenCV_Util.h>


namespace Ncv
{
	namespace OpenCV_Util
	{


		//using namespace Ncv::OpenCV_Util;


		Size_2D size_2D(const CvSize & src)
		{
			//return Size_2D(src.width, src.height);

			Size_2D ret(src.width, src.height);
			return ret;
		}

		CvSize toCvSize(const Size_2D & src)
		{
			return cvSize(src.GetX(), src.GetY());
		}


		S32Point toS32Point(const CvPoint & src)
		{
			S32Point ret(src.x, src.y);
			return ret;
		}

		CvPoint toCvPoint(const S32Point & src)
		{
			return cvPoint(src.GetX(), src.GetY());
		}



	}
}


