#include <NovelCVLib\Ncpp\Common\commonLib.h>
#include <NovelCVLib\Ncv\OpenCV\CvIncludes.h>
#include <NovelCVLib\Ncv\OpenCV\Types.h>
#include <NovelCVLib\Ncv\OpenCV\error.h>
#include <vector>
#include <NovelCVLib\Ncv\OpenCV\Channel.h>
#include <NovelCVLib\Ncv\OpenCV\Image.h>
#include <NovelCVLib\Ncv\OpenCV\funcs1.h>

#include <NovelCVLib\Apps\Binarization\BinarizationProcess1.h>


#define M_PI 3.14159265358979323846


namespace Ncv
{
	using namespace Ncpp;
	//using namespace Ncpp::Math;

	namespace Ns_Binarization
	{

		BinarizationProcess1::BinarizationProcess1(F32ImageRef a_srcImg)
		{
			m_srcImg = a_srcImg;

			Prepare();
		}

		void BinarizationProcess1::Prepare()
		{
		
		}



	}
}

