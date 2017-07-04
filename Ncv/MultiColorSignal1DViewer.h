#pragma once

#include <Lib\Novel\Ncpp\Common\commonLib.h>
#include <Lib\Novel\Ncpp\Math\mathLib.h>
#include <Lib\Novel\Ncv\OpenCV\CvIncludes.h>
#include <Lib\Novel\Ncv\OpenCV\Types.h>
#include <Lib\Novel\Ncv\OpenCV\error.h>
#include <vector>
#include <Lib\Novel\Ncv\OpenCV\Channel.h>
#include <Lib\Novel\Ncv\OpenCV\Image.h>

//#include <Lib\Novel\Ncv\Signal1D.h>

#include <Lib\Novel\Ncv\Signal1DViewer.h>



namespace Ncv
{
	using namespace Ncpp::Math;
	using namespace std;

/*
	class Signal1DDrawing : FRM_Object
	{
	public:

		Signal1DDrawing()
		{
		}

		Signal1DDrawing( Signal1DRef a_signal, U8ColorVal a_dspColor, float a_scale )
		{
			Signal = a_signal;
			DspColor = a_dspColor;
			Scale = a_scale;
		}

	public:
		Signal1DRef Signal;
		U8ColorVal DspColor;
		float Scale;
	};

	typedef Ncpp::ObjRef< Signal1DDrawing > Signal1DDrawingRef;
*/

	class MultiColorSignal1DViewer : FRM_Object
	{
	protected :


	public:
		MultiColorSignal1DViewer( Signal1DViewerRef a_sv = NULL );

		U8ImageRef GenDisplayImage()
		{
			return m_sv->GenDisplayImage();
		}

		Signal1DViewerRef GetSignalViewer()
		{
			return m_sv;
		}

		void DrawValueSignals( FixedVector< float > & a_valArr, FixedVector< U8ColorVal > & a_colorArr );

	protected:

		Signal1DViewerRef m_sv;		
	};

	typedef Ncpp::ObjRef< MultiColorSignal1DViewer > MultiColorSignal1DViewerRef;
	

}
