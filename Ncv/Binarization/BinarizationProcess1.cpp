#include <Lib\Novel\Ncpp\Common\commonLib.h>
#include <Lib\Novel\Ncv\OpenCV\CvIncludes.h>
#include <Lib\Novel\Ncv\OpenCV\Types.h>
#include <Lib\Novel\Ncv\OpenCV\error.h>
#include <vector>
#include <Lib\Novel\Ncv\OpenCV\Channel.h>
#include <Lib\Novel\Ncv\OpenCV\Image.h>
#include <Lib\Novel\Ncv\OpenCV\funcs1.h>

#include <Lib\Novel\Ncv\Binarization\BinarizationProcess1.h>


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

