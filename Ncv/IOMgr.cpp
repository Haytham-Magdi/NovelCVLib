#include <NovelCVLib\Ncpp\Common\commonLib_Misc.h>
#include <NovelCVLib\OpenCV\CvIncludes.h>
#include <NovelCVLib\OpenCV\Types.h>
#include <NovelCVLib\OpenCV\error.h>
#include <vector>
#include <NovelCVLib\OpenCV\Channel.h>
#include <NovelCVLib\OpenCV\Image.h>
#include <NovelCVLib\OpenCV\funcs1.h>

#include <NovelCVLib\Ncv\IOMgr.h>

namespace Ncv
{
	using namespace Ncpp;
	//using namespace Ncpp::Math;


	IOMgr::IIOMgrCore * IOMgr::m_pCore;

	char IOMgr::m_tmpBuff[];



}