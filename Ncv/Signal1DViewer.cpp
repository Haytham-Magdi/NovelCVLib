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


	Signal1DViewer::Signal1DViewer(int a_nScaleX, int a_nScaleY) : m_margX(40), m_margY(40)
	{
		m_nMaxSignalLength = 0;
		m_bkgColor = u8ColorVal(128, 180, 180);
		//m_bkgColor = u8ColorVal(110, 0, 0);

		m_nScaleX = a_nScaleX;
		m_nScaleY = a_nScaleY;
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
		const int nScaleY = m_nScaleY;

		U8ImageRef ret = U8Image::Create( cvSize( 2 * m_margX + m_nMaxSignalLength * nScaleX, 
			2 * m_margY + 256 * nScaleY), 3);


		U8ChannelRef retCh0 = ret->GetAt(0);
		U8ChannelRef retCh1 = ret->GetAt(1);
		U8ChannelRef retCh2 = ret->GetAt(2);


		retCh0->SetAll( m_bkgColor.val0 );
		retCh1->SetAll( m_bkgColor.val1 );
		retCh2->SetAll( m_bkgColor.val2 );


		{
			cv::line(
				ret->GetMat(), 
				cv::Point( 0, m_margY), 
				cv::Point( ret->GetSize().width - 1, m_margY), 
				CV_RGB(0, 0, 0),
				1 );

//------


			cv::line(
				ret->GetMat(),
				cv::Point(0, ret->GetSize().height - 1 - m_margY - (127 - 20) * nScaleY),
				cv::Point(ret->GetSize().width - 1, ret->GetSize().height - 1 - m_margY - (127 - 20) * nScaleY),
				CV_RGB(140, 140, 140),
				1);

			cv::line(
				ret->GetMat(),
				cv::Point(0, ret->GetSize().height - 1 - m_margY - (127 - 10) * nScaleY),
				cv::Point(ret->GetSize().width - 1, ret->GetSize().height - 1 - m_margY - (127 - 10) * nScaleY),
				CV_RGB(140, 140, 140),
				1);




			cv::line(
				ret->GetMat(),
				cv::Point(0, ret->GetSize().height - 1 - m_margY - 127 * nScaleY),
				cv::Point(ret->GetSize().width - 1, ret->GetSize().height - 1 - m_margY - 127 * nScaleY),
				CV_RGB(30, 30, 30),
				1);



			cv::line(
				ret->GetMat(),
				cv::Point(0, ret->GetSize().height - 1 - m_margY - (127 + 20) * nScaleY),
				cv::Point(ret->GetSize().width - 1, ret->GetSize().height - 1 - m_margY - (127 + 20) * nScaleY),
				CV_RGB(140, 140, 140),
				1);

			cv::line(
				ret->GetMat(),
				cv::Point(0, ret->GetSize().height - 1 - m_margY - (127 + 10) * nScaleY),
				cv::Point(ret->GetSize().width - 1, ret->GetSize().height - 1 - m_margY - (127 + 10) * nScaleY),
				CV_RGB(140, 140, 140),
				1);



//--------

			cv::line (
				ret->GetMat(),
				cv::Point(0, ret->GetSize().height - 1 - m_margY - 10 * nScaleY),
				cv::Point(ret->GetSize().width - 1, ret->GetSize().height - 1 - m_margY - 10 * nScaleY),
				CV_RGB(140, 140, 140),
				1 );

			cv::line(
				ret->GetMat(),
				cv::Point(0, ret->GetSize().height - 1 - m_margY - 20 * nScaleY),
				cv::Point(ret->GetSize().width - 1, ret->GetSize().height - 1 - m_margY - 20 * nScaleY),
				CV_RGB(30, 30, 30),
				1);





			cv::line (
				ret->GetMat(),
				cv::Point( 0, ret->GetSize().height - 1 - m_margY), 
				cv::Point( ret->GetSize().width - 1, ret->GetSize().height - 1 - m_margY), 
				CV_RGB(0, 0, 0),
				1 );
		}


		if (m_nScaleX > 1)
		{
			for (int j = -1; j < m_nMaxSignalLength - 1; j++)
			{
				const int x = j * m_nScaleX + m_margX;

				cv::line(
					ret->GetMat(),
					cv::Point(x, 0),
					cv::Point(x, ret->GetSize().height - 1),
					CV_RGB(120, 120, 120),
					1);
			}
		}



		for(int i=0; i < m_signalInfoVect.size(); i++)
		{
			Signal1DDrawing & rSD = m_signalInfoVect[i];

			U8ColorVal color = rSD.DspColor;
			int x = rSD.Signal->m_nBgn + rSD.ShiftX;

			vector<float> & rData = m_signalInfoVect[i].Signal->m_data;

			const float scale = m_signalInfoVect[i].Scale;

			for(int j = 1; j < rData.size(); j++, x++)
			{
				const int y = (255 - (rData[j] * scale) + rSD.ShiftY) * nScaleY + m_margY;
				const int y0 = (255 - (rData[j - 1] * scale) + rSD.ShiftY) * nScaleY + m_margY;
			
				cv::line (
					ret->GetMat(),
					cv::Point((x - 1) * nScaleX + m_margX, y0),
					cv::Point(x * nScaleX + m_margX , y), 
					CV_RGB(color.val2, color.val1, color.val0),
					1 );
			}
		}

		return ret;
	}

	U8ImageRef Signal1DViewer::GenColorBarsDisplayImage()
	{
		if (3 != m_signalInfoVect.size())
		{
			ThrowNcvException();
		}

		const int nScaleX = m_nScaleX;
		const int nScaleY = m_nScaleY;

		U8ImageRef ret = U8Image::Create(cvSize(2 * m_margX + m_nMaxSignalLength * nScaleX,
			2 * m_margY + 256 * nScaleY), 3);


		U8ChannelRef retCh0 = ret->GetAt(0);
		U8ChannelRef retCh1 = ret->GetAt(1);
		U8ChannelRef retCh2 = ret->GetAt(2);


		retCh0->SetAll(m_bkgColor.val0);
		retCh1->SetAll(m_bkgColor.val1);
		retCh2->SetAll(m_bkgColor.val2);



		for (int j = -1; j < m_nMaxSignalLength - 1; j++)
		{
			const int x = j * m_nScaleX + m_margX;

			cv::line(
				ret->GetMat(),
				cv::Point(x, ret->GetSize().height * 2 / 3 - 1),
				cv::Point(x, ret->GetSize().height - 1),
				CV_RGB(120, 120, 120),
				1);
		}



		{
			Signal1DDrawing & rSD0 = m_signalInfoVect[0];
			Signal1DDrawing & rSD1 = m_signalInfoVect[1];
			Signal1DDrawing & rSD2 = m_signalInfoVect[2];

			//U8ColorVal color = rSD.DspColor;
			int x = rSD0.Signal->m_nBgn + rSD0.ShiftX;

			vector<float> & rData0 = m_signalInfoVect[0].Signal->m_data;
			vector<float> & rData1 = m_signalInfoVect[1].Signal->m_data;
			vector<float> & rData2 = m_signalInfoVect[2].Signal->m_data;

			const float scale = m_signalInfoVect[0].Scale;

			for (int j = 1; j < rData0.size(); j++, x++)
			{
				const int y = (255 - (255) + rSD0.ShiftY) * nScaleY + m_margY;
				const int y0 = (255 - (0) + rSD0.ShiftY) * nScaleY + m_margY;

				const U8ColorVal color = U8ColorVal(rData2[j - 1], rData1[j - 1], rData0[j - 1]);

				cv::rectangle(
					ret->GetMat(),
					cv::Point((x - 1) * nScaleX + m_margX, y0),
					cv::Point(x * nScaleX + m_margX, y),
					CV_RGB(color.val0, color.val1, color.val2),
					-1);
			}
		}

		{
			cv::line(
				ret->GetMat(),
				cv::Point(0, m_margY),
				cv::Point(ret->GetSize().width - 1, m_margY),
				CV_RGB(0, 0, 0),
				1);


			cv::line(
				ret->GetMat(),
				cv::Point(0, ret->GetSize().height - 1 - m_margY - 20),
				cv::Point(ret->GetSize().width - 1, ret->GetSize().height - 1 - m_margY - 20),
				CV_RGB(0, 0, 0),
				1);

			cv::line(
				ret->GetMat(),
				cv::Point(0, ret->GetSize().height - 1 - m_margY),
				cv::Point(ret->GetSize().width - 1, ret->GetSize().height - 1 - m_margY),
				CV_RGB(0, 0, 0),
				1);
		}



		return ret;
	}




}