#include <Novel-Lib\Ncpp\Common\commonLib.h>
#include <Novel-Lib\Ncv\OpenCV\CvIncludes.h>
#include <Novel-Lib\Ncv\OpenCV\Types.h>
#include <Novel-Lib\Ncv\OpenCV\error.h>
#include <vector>
#include <Novel-Lib\Ncv\OpenCV\Channel.h>
#include <Novel-Lib\Ncv\OpenCV\Image.h>
#include <Novel-Lib\Ncv\OpenCV\funcs1.h>

#include <Novel-Lib\Ncv\Binarization\BinarizationProcess1.h>


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

