#include <NovelCVLib\Ncpp\Common\commonLib_Misc.h>
#include <NovelCVLib\OpenCV\CvIncludes.h>
#include <NovelCVLib\OpenCV\Types.h>
#include <NovelCVLib\OpenCV\error.h>
#include <vector>
#include <NovelCVLib\OpenCV\Channel.h>
#include <NovelCVLib\OpenCV\Image.h>
#include <NovelCVLib\OpenCV\funcs1.h>

#include <NovelCVLib\Ncv\ImgSizeRotationColl.h>


//#define M_PI 3.14159265358979323846
#define M_PI 3.14159265358979323846f


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
		Size_2D a_srcSiz, int a_nofRots)
	{
		Ncpp_ASSERT(a_nofRots >= 0);

		//Ncpp_ASSERT( 0 == a_nofRots % 2 );

		m_srcSiz = a_srcSiz;

		m_nofRots = a_nofRots;

		m_rotMgrArr.SetCapacity(a_nofRots);

		float angStep = 90.0F / a_nofRots;


		// to be removed
		//float angDig1 = i * angStep;
		
		//ImgSizeRotationRef rot1 = new ImgSizeRotation(m_srcSiz, 0);
		//ImgSizeRotationRef rot1 = new ImgSizeRotation(m_srcSiz, 22.5);
		//ImgSizeRotationRef rot1 = new ImgSizeRotation(m_srcSiz, 45);
		//ImgSizeRotationRef rot1 = new ImgSizeRotation(m_srcSiz, 90);

		//ImgSizeRotationRef rot1 = new ImgSizeRotation(m_srcSiz, 180);
		//ImgSizeRotationRef rot1 = new ImgSizeRotation(m_srcSiz, 225);


		for (int i = 0; i < a_nofRots; i++)
		{
			float angDig = i * angStep;

			ImgSizeRotationRef rot = new ImgSizeRotation(m_srcSiz, angDig);

			m_rotMgrArr.PushBack(rot);
		}

	}



}

