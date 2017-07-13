#pragma once

#include <NovelCVLib\Ncpp\Common\commonLib.h>
#include <NovelCVLib\Ncpp\Math\mathLib.h>
#include <NovelCVLib\Ncv\OpenCV\CvIncludes.h>
#include <NovelCVLib\Ncv\OpenCV\Types.h>
#include <NovelCVLib\Ncv\OpenCV\error.h>
#include <vector>
#include <NovelCVLib\Ncv\OpenCV\Channel.h>
#include <NovelCVLib\Ncv\OpenCV\Image.h>

namespace Ncv
{
	//using namespace Ncpp::Math;


	class LinePath : public IIterator< F32Point >
	{
	public:

		LinePath( int a_x1, int a_y1, int a_x2, int a_y2 );

		F32Point GetCurrent()
		{
			return m_curPnt.Round();
			//return m_curPnt;
		}

		bool MoveNext();




	protected:


		const F32Point m_bgnPnt;
		const F32Point m_endPnt;

		int m_nReqSteps;
		int m_nDoneSteps;

		F32Point m_curPnt;

		F32Point m_stepPnt;
	};


	typedef Ncpp::ObjRef< LinePath > LinePathRef;

}