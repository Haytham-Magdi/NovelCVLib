#include <Lib\Novel\Ncpp\Common\commonLib.h>
#include <Lib\Novel\Ncv\OpenCV\CvIncludes.h>
#include <Lib\Novel\Ncv\OpenCV\Types.h>
#include <Lib\Novel\Ncv\OpenCV\error.h>
#include <vector>
#include <Lib\Novel\Ncv\OpenCV\Channel.h>
#include <Lib\Novel\Ncv\OpenCV\Image.h>
#include <Lib\Novel\Ncv\OpenCV\funcs1.h>

#include <Lib\Novel\Ncv\ImgSizeRotationColl.h>


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

