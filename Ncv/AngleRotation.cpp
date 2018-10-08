#include <NovelCVLib\Ncpp\Common\commonLib_Misc.h>
#include <vector>

#include <NovelCVLib\Ncv\AngleRotation.h>


#define M_PI 3.14159265358979323846
//#define M_PI 3.14159265358979323846f


namespace Ncv
{
	using namespace Ncpp;
	//using namespace Ncpp::Math;

	using namespace Ncv::ImageOperations2;

	AngleRotation::AngleRotation(float a_angDig)
	{
		// Ncpp_ASSERT(a_angDig >= 0);
		// Ncpp_ASSERT(a_angDig <= 90);


		m_angDig = a_angDig;
		m_angRad = (float)(a_angDig * M_PI / 180);

		m_nCos = ARIntScale::ScaleToI(cos(m_angRad));
		m_nSin = ARIntScale::ScaleToI(sin(m_angRad));

		m_nCos = ARIntScale::GoNearCeilByOne(m_nCos);
		m_nSin = ARIntScale::GoNearCeilByOne(m_nSin);

		const int mag1 = Sqr(m_nCos) + Sqr(m_nSin);
		Ncpp_ASSERT(mag1 >= Sqr(ARIntScale::ScaleToI(1)));

	}

}