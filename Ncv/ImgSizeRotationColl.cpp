#include <NovelCVLib\Ncpp\Common\commonLib.h>
#include <NovelCVLib\Ncv\OpenCV\CvIncludes.h>
#include <NovelCVLib\Ncv\OpenCV\Types.h>
#include <NovelCVLib\Ncv\OpenCV\error.h>
#include <vector>
#include <NovelCVLib\Ncv\OpenCV\Channel.h>
#include <NovelCVLib\Ncv\OpenCV\Image.h>
#include <NovelCVLib\Ncv\OpenCV\funcs1.h>

#include <NovelCVLib\Ncv\ImgSizeRotationColl.h>


#define M_PI 3.14159265358979323846


namespace Ncv
{
	using namespace Ncpp;
	//using namespace Ncpp::Math;


	//ImgSizeRotationColl::ImgSizeRotationColl(F32ImageRef a_srcImg, int a_nofRots)
	//{
	//	m_srcImg = a_srcImg;
	//	m_nofRots = a_nofRots;

	//	Prepare();
	//}

	//void ImgSizeRotationColl::Prepare()
	//{
	//
	//}

	ImgSizeRotationColl::ImgSizeRotationColl(
		CvSize a_srcSiz, int a_nofRots)
	{
		Ncpp_ASSERT(a_nofRots >= 0);

		//Ncpp_ASSERT( 0 == a_nofRots % 2 );

		m_srcSiz = a_srcSiz;

		m_nofRots = a_nofRots;

		m_rotMgrArr.SetCapacity(a_nofRots);

		float angStep = 90.0F / a_nofRots;

		for (int i = 0; i < a_nofRots; i++)
		{
			float angDig = i * angStep;

			ImgSizeRotationRef rot = new ImgSizeRotation(m_srcSiz, angDig);

			m_rotMgrArr.PushBack(rot);
		}

	}



}

