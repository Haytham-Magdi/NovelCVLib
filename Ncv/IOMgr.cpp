#include <NovelCVLib\Ncpp\Common\commonLib.h>
#include <NovelCVLib\Ncv\OpenCV\CvIncludes.h>
#include <NovelCVLib\Ncv\OpenCV\Types.h>
#include <NovelCVLib\Ncv\OpenCV\error.h>
#include <vector>
#include <NovelCVLib\Ncv\OpenCV\Channel.h>
#include <NovelCVLib\Ncv\OpenCV\Image.h>
#include <NovelCVLib\Ncv\OpenCV\funcs1.h>

#include <NovelCVLib\Ncv\IOMgr.h>

namespace Ncv
{
	using namespace Ncpp;
	//using namespace Ncpp::Math;


	IOMgr::IIOMgrCore * IOMgr::m_pCore;

	char IOMgr::m_tmpBuff[];



}