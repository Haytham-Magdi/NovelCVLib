#pragma once

#include <Lib\Novel\Ncpp\Common\commonLib.h>
#include <Lib\Novel\Ncpp\Math\mathLib.h>
#include <Lib\Novel\Ncv\OpenCV\CvIncludes.h>
#include <Lib\Novel\Ncv\OpenCV\Types.h>
#include <Lib\Novel\Ncv\OpenCV\error.h>
#include <vector>
#include <Lib\Novel\Ncv\OpenCV\Channel.h>
#include <Lib\Novel\Ncv\OpenCV\Image.h>

#include <Lib\Novel\Ncv\OpenCV\funcs1.h>

#include <Lib\Novel\Ncv\LinePath.h>
//#include <Lib\Novel\Ncv\ColorFilter1DSystem.h>



namespace Hcv
{
	//using namespace Hcpl::Math;


	class ImageLineViewer2 : public IColorFilter1DSystemConsumer
	{


	protected:

		class RgnInfo
		{
		public:

			RgnInfo()
			{
			}


		public:

			int IndexOnLine;
			F32ColorVal * pImgPix;
			F32ColorVal * pShowPix;
			F32Point pos;

		protected:

		};

		class IFilterOutputMgr : FRM_Object
		{
		public:
			virtual void ProcessOutput( int a_nFilterID, F32ColorVal a_outVal, int a_nBackShift ) = 0;
			virtual void ProcessOutput( int a_nFilterID, float a_outVal, int a_nBackShift ) = 0;
			virtual void ProvideSignal( Signal1DViewerRef a_sv ) = 0;
		};

		typedef Hcpl::ObjRef< IFilterOutputMgr > IFilterOutputMgrRef;

		class FilterOutputMgrBase : public IFilterOutputMgr
		{
		public:
			FilterOutputMgrBase( ImageLineViewer2 * a_pIlv, IFilterOutputMgrRef a_inner = NULL ) : 
			  m_pIlv( a_pIlv ), m_inner( a_inner ) {}

			virtual void ProcessOutput( int a_nFilterID, F32ColorVal a_outVal, int a_nBackShift )
			{ ThrowHcvException(); }

			virtual void ProcessOutput( int a_nFilterID, float a_outVal, int a_nBackShift )
			{ ThrowHcvException(); }

			virtual void ProvideSignal( Signal1DViewerRef a_sv )
			{ ProvideInnerSignal( a_sv ); }

		protected:

			void ProcessInner( int a_nFilterID, F32ColorVal a_outVal, int a_nBackShift )
			{
				if( NULL != m_inner )
					m_inner->ProcessOutput( a_nFilterID, a_outVal, a_nBackShift );
			}

			void ProcessInner( int a_nFilterID, float a_outVal, int a_nBackShift )
			{
				if( NULL != m_inner )
					m_inner->ProcessOutput( a_nFilterID, a_outVal, a_nBackShift );
			}

			void ProvideInnerSignal( Signal1DViewerRef a_sv )
			{
				if( NULL != m_inner )
					m_inner->ProvideSignal( a_sv );
			}

		protected:
			ImageLineViewer2 * m_pIlv;

		private:
			IFilterOutputMgrRef m_inner;
		};

		class DummyOutputMgr : public FilterOutputMgrBase
		{
		public:
			DummyOutputMgr( ImageLineViewer2 * a_pIlv ) : FilterOutputMgrBase( a_pIlv ) {}

			virtual void ProcessOutput( int a_nFilterID, F32ColorVal a_outVal, int a_nBackShift ) { }
			virtual void ProcessOutput( int a_nFilterID, float a_outVal, int a_nBackShift ) { }
			virtual void ProvideSignal( Signal1DViewerRef a_sv ) { }
		};

		class ColorOutputMgr : public FilterOutputMgrBase
		{
		public:
			ColorOutputMgr( ImageLineViewer2 * a_pIlv,
				U8ColorVal a_valColor0, U8ColorVal a_valColor1, U8ColorVal a_valColor2 ) 
				: FilterOutputMgrBase( a_pIlv ), m_sb0( NULL ), m_sb1( NULL ), m_sb2( NULL ), 
				m_valColor0(a_valColor0), m_valColor1(a_valColor1), m_valColor2(a_valColor2) {}

			virtual void ProcessOutput( int a_nFilterID, F32ColorVal a_outVal, int a_nBackShift );
			virtual void ProvideSignal( Signal1DViewerRef a_sv );

		protected:
			Signal1DBuilderRef m_sb0;
			Signal1DBuilderRef m_sb1;
			Signal1DBuilderRef m_sb2;

			U8ColorVal m_valColor0;
			U8ColorVal m_valColor1;
			U8ColorVal m_valColor2;
		};


		class AvgOutputMgr : public ColorOutputMgr
		{
		public:
			AvgOutputMgr( ImageLineViewer2 * a_pIlv ) : ColorOutputMgr( a_pIlv,
				u8ColorVal(200, 0, 0), u8ColorVal(0, 180, 0), u8ColorVal(0, 0, 255) ) {}

			//virtual void ProcessOutput( int a_nFilterID, F32ColorVal a_outVal, int a_nBackShift );
			//virtual void ProvideSignal( Signal1DViewerRef a_sv );
		};


		class SingleOutputMgr : public FilterOutputMgrBase
		{
		public:
			SingleOutputMgr( ImageLineViewer2 * a_pIlv, U8ColorVal a_color ) 
				: FilterOutputMgrBase( a_pIlv ), m_color(a_color), m_sb( NULL ) {}

			virtual void ProcessOutput( int a_nFilterID, float a_outVal, int a_nBackShift );
			virtual void ProvideSignal( Signal1DViewerRef a_sv );

		protected:
			U8ColorVal m_color;
			Signal1DBuilderRef m_sb;
		};


/*
		class Diff1MarkerOutputMgr : public SingleOutputMgr
		{
		public:
			Diff1MarkerOutputMgr( ImageLineViewer2 * a_pIlv, U8ColorVal a_color ) 
				: SingleOutputMgr( a_pIlv, a_color ) {}

			virtual void ProcessOutput( int a_nFilterID, float a_outVal, int a_nBackShift );
		};
*/

		class Diff1MarkerOutputMgr : public FilterOutputMgrBase
		{
		public:
			Diff1MarkerOutputMgr( ImageLineViewer2 * a_pIlv, IFilterOutputMgrRef a_inner = NULL ) 
				: FilterOutputMgrBase( a_pIlv, a_inner ) {}

			virtual void ProcessOutput( int a_nFilterID, float a_outVal, int a_nBackShift );
		};

		class Diff2MarkerOutputMgr : public FilterOutputMgrBase
		{
		public:
			Diff2MarkerOutputMgr( ImageLineViewer2 * a_pIlv, IFilterOutputMgrRef a_inner = NULL ) 
				: FilterOutputMgrBase( a_pIlv, a_inner ) {}

			virtual void ProcessOutput( int a_nFilterID, float a_outVal, int a_nBackShift );
		};


	public:

		ImageLineViewer2( F32ImageRef a_srcImg, LinePathRef a_lp );


		virtual void ReceiveFilterOutput( int a_nFilterID, F32ColorVal a_outVal, int a_nBackShift );
		virtual void ReceiveFilterOutput( int a_nFilterID, float a_outVal, int a_nBackShift );

		virtual void NotifyAllOutputDone( );


		F32ImageRef GetResultImg();

		U8ImageRef GetSignalDspImg();




	protected:

		void DoPrepare();

		//int AddFilter( ColorFilter1DSystemBuilder * pFiltSysBld, 
		//	IColorFilter1DRef a_filt, IFilterOutputMgrRef a_outMgr, int a_nSrcID = -1 );

		//int AddFilter( ColorFilter1DSystemBuilder * pFiltSysBld, 
		//	IFilter1DRef a_filt, IFilterOutputMgrRef a_outMgr, int a_nSrcID = -1 );

		//int AddColorToSingleConverter( ColorFilter1DSystemBuilder * pFiltSysBld, 
		//	IFilterOutputMgrRef a_outMgr, int a_nSrcID = -1 );


		//int AddSingleFilter(

		void DoProcess();

		void InitRgnInfoVect();

		//inline RgnInfo * FindRootRgnBef( RgnInfo * a_pEdgeRgnBef, RgnInfo * a_pEdgeRgn );
		//inline RgnInfo * FindRootRgnAft( RgnInfo * a_pEdgeRgn , RgnInfo * a_pEdgeRgnAft);

		inline RgnInfo * FindRootRgnBef( RgnInfo * a_pEdgeRgn );
		inline RgnInfo * FindRootRgnAft( int a_limIOL = -1 );



		void DoProcessEdges();

		//void DrawCircle( RgnInfo * a_pRgn, U8ColorVal a_color );

		RgnInfo * GetPointRgn(int x, int y)
		{ 
			return &m_rgnInfoVect[m_rgnIndexCalc.Calc(x, y)]; 
		}

		RgnInfo * GetBackInputRgn( int a_nBackShift )
		{ 
			return m_inputRgnPtrVect[ m_inputRgnPtrVect.GetSize() - 1 - a_nBackShift ]; 
		}


		friend class IFilterOutputMgr;


	protected:

		int m_rootIdx;

		//ColorFilter1DSystemBuilder m_filtSysBld;

		const int m_nAprSize;

		IndexCalc2D m_rgnIndexCalc;

		F32ImageRef m_srcImg;
		
		LinePathRef m_lp;

		F32ImageRef m_resImg;

		U8ImageRef m_sigDspImg;

		FixedVector<RgnInfo> m_rgnInfoVect;

		FixedVector< RgnInfo * > m_inputRgnPtrVect;

		FixedVector< RgnInfo * > m_edgeRgnPtrVect;
		FixedVector< RgnInfo * > m_rootRgnPtrVect;

		//FixedVector< IFilterOutputMgr * > m_filterOutputMgrVect;
		FixedVector< IFilterOutputMgrRef > m_filterOutputMgrVect;

		ColorFilter1DSystemRef m_filtSys;
	};


	typedef Hcpl::ObjRef< ImageLineViewer2 > ImageLineViewer2Ref;

}