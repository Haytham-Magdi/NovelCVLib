

using namespace Ncv::OpenCV_Util;


Size_2D size_2D(const CvSize & src)
{
	return Size_2D(src.width, src.height);
}

CvSize cvSize(const Size_2D & src)
{
	return cvSize(src.GetX(), src.GetY());
}
