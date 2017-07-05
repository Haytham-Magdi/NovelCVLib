#include <Novel-Lib\Ncpp\Common\commonLib.h>
#include <Novel-Lib\Ncv\OpenCV\CvIncludes.h>
#include <Novel-Lib\Ncv\OpenCV\Types.h>
#include <Novel-Lib\Ncv\OpenCV\error.h>
#include <vector>
#include <Novel-Lib\Ncv\OpenCV\Channel.h>
#include <Novel-Lib\Ncv\OpenCV\Image.h>
#include <Novel-Lib\Ncv\OpenCV\funcs1.h>

#include <Novel-Lib\Ncv\IOMgr.h>

namespace Ncv
{
	using namespace Ncpp;
	//using namespace Ncpp::Math;


	IOMgr::IIOMgrCore * IOMgr::m_pCore;

	char IOMgr::m_tmpBuff[];



}