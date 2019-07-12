#include <NovelCVLib\Ncpp\Common\commonLib_Misc.h>
#include <NovelCVLib\OpenCV\CvIncludes.h>
#include <NovelCVLib\OpenCV\Types.h>
#include <NovelCVLib\OpenCV\error.h>
#include <vector>
#include <NovelCVLib\OpenCV\Channel.h>
#include <NovelCVLib\OpenCV\Image.h>
#include <NovelCVLib\OpenCV\funcs1.h>

#include <NovelCVLib\Ncv\Signal1DViewer.h>

namespace Ncv
{
	using namespace Ncpp;
	using namespace Ncpp::Math;


	Signal1DViewer::Signal1DViewer( int a_nScaleX ) : m_margX(40), m_margY(40)
	{
		m_nMaxSignalLength = 0;
		m_bkgColor = u8ColorVal(128, 180, 180);
		//m_bkgColor = u8ColorVal(110, 0, 0);

		m_nScaleX = a_nScaleX;
	}


	void Signal1DViewer::AddSignal( Signal1DRef a_signal, const U8ColorVal a_dspColor, 
		float a_nScale, int a_nShiftX, int a_nShiftY )
	{
		int signMax = a_signal->m_nBgn + a_signal->m_data.size();

		if( signMax > m_nMaxSignalLength )
			m_nMaxSignalLength = signMax;

		Signal1DDrawing si;

		si.Signal = a_signal;
		si.DspColor = a_dspColor;
		si.Scale = a_nScale;
		si.ShiftX = a_nShiftX;
		si.ShiftY = a_nShiftY;

		this->m_signalInfoVect.push_back(si);
	}


	void Signal1DViewer::AddSignalDrawingColl( IIterator_REF( Signal1DDrawingRef ) a_sigDrwIter )
	{
		do
		{
			this->AddSignalDrawing( a_sigDrwIter->GetCurrent() );

		}while(a_sigDrwIter->MoveNext());
	}


	U8ImageRef Signal1DViewer::GenDisplayImage()
	{
		//const int nScaleX = 1;
		//const int nScaleX = 5;
		//const int nScaleX = 10;

		const int nScaleX = m_nScaleX;

		U8ImageRef ret = U8Image::Create( cvSize( 2 * m_margX + m_nMaxSignalLength * nScaleX, 
			2 * m_margY + 256 ), 3);


		U8ChannelRef retCh0 = ret->GetAt(0);
		U8ChannelRef retCh1 = ret->GetAt(1);
		U8ChannelRef retCh2 = ret->GetAt(2);


		retCh0->SetAll( m_bkgColor.val0 );
		retCh1->SetAll( m_bkgColor.val1 );
		retCh2->SetAll( m_bkgColor.val2 );


		{
			cvLine (
				ret->GetIplImagePtr(), 
				cvPoint( 0, m_margY), 
				cvPoint( ret->GetSize().width - 1, m_margY), 
				CV_RGB(0, 0, 0),
				1 );


			cvLine (
				ret->GetIplImagePtr(), 
				cvPoint( 0, ret->GetSize().height - 1 - m_margY - 20), 
				cvPoint( ret->GetSize().width - 1, ret->GetSize().height - 1 - m_margY - 20), 
				CV_RGB(0, 0, 0),
				1 );

			cvLine (
				ret->GetIplImagePtr(), 
				cvPoint( 0, ret->GetSize().height - 1 - m_margY), 
				cvPoint( ret->GetSize().width - 1, ret->GetSize().height - 1 - m_margY), 
				CV_RGB(0, 0, 0),
				1 );
		}



		for (int j = -1; j < m_nMaxSignalLength - 1; j++)
		{
			const int x = j * m_nScaleX + m_margX;


			//const int y0 = 255 - (0 * scale) + rSD.ShiftY + m_margY;

			//retCh0->SetAt( x, y, color.val0 );
			//retCh1->SetAt( x, y, color.val1 );
			//retCh2->SetAt( x, y, color.val2 );


			cvLine(
				ret->GetIplImagePtr(),
				cvPoint(x, 0),
				cvPoint(x, ret->GetSize().height - 1),
				//CV_RGB(180, 180, 180),
				CV_RGB(120, 120, 120),
				1);


			//cvLine(
			//	ret->GetIplImagePtr(),
			//	cvPoint((x - 1) * nScaleX + m_margX, y0),
			//	//cvPoint(x * nScaleX + m_margX, y0),
			//	cvPoint(x * nScaleX + m_margX, y),
			//	CV_RGB(color.val2, color.val1, color.val0),
			//	1);
		}







		for(int i=0; i < m_signalInfoVect.size(); i++)
		{
			Signal1DDrawing & rSD = m_signalInfoVect[i];

			U8ColorVal color = rSD.DspColor;
			int x = rSD.Signal->m_nBgn + rSD.ShiftX;

			vector<float> & rData = m_signalInfoVect[i].Signal->m_data;

			const float scale = m_signalInfoVect[i].Scale;

			//for(int j = 1; j < rData.size(); j++, x++)
			for(int j = 1; j < rData.size(); j++, x++)
			{
				const int y = 255 - (rData[j] * scale) + rSD.ShiftY + m_margY;
				const int y0 = 255 - (rData[j - 1] * scale) + rSD.ShiftY + m_margY;
			
				//const int y0 = 255 - (0 * scale) + rSD.ShiftY + m_margY;

				//retCh0->SetAt( x, y, color.val0 );
				//retCh1->SetAt( x, y, color.val1 );
				//retCh2->SetAt( x, y, color.val2 );

				

				cvLine (
					ret->GetIplImagePtr(), 
					cvPoint((x - 1) * nScaleX + m_margX, y0),
					//cvPoint(x * nScaleX + m_margX, y0),
					cvPoint(x * nScaleX + m_margX , y), 
					CV_RGB(color.val2, color.val1, color.val0),
					1 );
			}
		}


		return ret;
	}



}