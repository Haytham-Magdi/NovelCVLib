#include <NovelCVLib\Ncpp\Common\commonLib_Misc.h>
#include <NovelCVLib\OpenCV\CvIncludes.h>
#include <NovelCVLib\OpenCV\Types.h>
#include <NovelCVLib\OpenCV\error.h>
#include <vector>
#include <NovelCVLib\OpenCV\Channel.h>
#include <NovelCVLib\OpenCV\Image.h>
#include <NovelCVLib\OpenCV\funcs1.h>

#include <NovelCVLib\Ncv\MultiColorSignal1DViewer.h>

namespace Ncv
{
	using namespace Ncpp;
	using namespace Ncpp::Math;


	MultiColorSignal1DViewer::MultiColorSignal1DViewer( Signal1DViewerRef a_sv )
	{
		m_sv = a_sv;

		if( nullptr == a_sv )
			m_sv = new Signal1DViewer();
	}


	void MultiColorSignal1DViewer::DrawValueSignals( 
		FixedVector< float > & a_valArr, FixedVector< U8ColorVal > & a_colorArr )
	{
		Ncpp::Debug::Assert( a_valArr.GetSize() == a_colorArr.GetSize() );

		FixedVector< float > & valArr = a_valArr;

		{				
			const int nScaleW = 800 / valArr.GetSize() + 1;

			//Signal1DViewerRef a_sv1 = new Signal1DViewer();
			int i;

			for( int i=0; i < valArr.GetSize(); i++ )
			{
				Signal1DBuilder sb1( 1000, i * nScaleW );

				float val = valArr[i];

				for( int k=0; k < nScaleW; k++ )
				{
					sb1.AddValue( val );
				}

				//U8ColorVal color1 = u8ColorVal( val, val, val );
				U8ColorVal color1 = a_colorArr[ i ];				

				m_sv->AddSignal( sb1.GetResult(), color1 );
			}


		}



	}


}