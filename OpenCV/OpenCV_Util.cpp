
#include <NovelCVLib\OpenCV\OpenCV_Util.h>


using namespace Ncv::OpenCV_Util;


Size_2D size_2D(const CvSize & src)
{
	return Size_2D(src.width, src.height);
}

CvSize toCvSize(const Size_2D & src)
{
	return cvSize(src.GetX(), src.GetY());
}
