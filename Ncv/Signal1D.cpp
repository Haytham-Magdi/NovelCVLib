#include <NovelCVLib\Ncpp\Common\commonLib_Misc.h>
#include <NovelCVLib\OpenCV\CvIncludes.h>
#include <NovelCVLib\OpenCV\Types.h>
#include <NovelCVLib\OpenCV\error.h>
#include <vector>
#include <NovelCVLib\OpenCV\Channel.h>
#include <NovelCVLib\OpenCV\Image.h>
#include <NovelCVLib\OpenCV\funcs1.h>

#include <NovelCVLib\Ncv\Signal1D.h>

namespace Ncv
{
	using namespace Ncpp;
	using namespace Ncpp::Math;


	void Signal1DBuilder::Init(int a_capacity, int a_nBgn)
	{
		m_sig = new Signal1D();

		m_sig->m_data.resize( a_capacity );
		m_sig->m_data.resize( 0 );

		m_sig->m_nBgn = a_nBgn;
	}

	void Signal1DBuilder::AddValue(const float a_value)
	{
		if( true == m_bDone )
		{
			Ncpp::Debug::Assert( false );
			return;
		}

		m_sig->m_data.push_back( a_value );
	}

	void Signal1DBuilder::AddData( float * a_dataBuf, const int a_nSize )
	{
		for( int i=0; i < a_nSize; i++ )
			AddValue( a_dataBuf[ i ] );
	}

	void Signal1DBuilder::AddConstArr( float a_val, const int a_nSize )
	{
		for( int i=0; i < a_nSize; i++ )
			AddValue( a_val );
	}

	void Signal1DBuilder::Build( )
	{
		m_bDone = true;
	}

	Signal1DRef Signal1DBuilder::GetResult()
	{
		Build();

		if( false == m_bDone )
		{
			Ncpp::Debug::Assert( false );
			return nullptr;
		}

		return m_sig;
	}

}