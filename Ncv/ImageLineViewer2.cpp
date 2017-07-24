#include <NovelCVLib\NcppCommon\commonLib.h>
#include <NovelCVLib\Ncv\CvIncludes.h>
#include <NovelCVLib\Ncv\Types.h>
#include <NovelCVLib\Ncv\error.h>
#include <vector>
#include <NovelCVLib\Ncv\Channel.h>
#include <NovelCVLib\Ncv\Image.h>
#include <NovelCVLib\Ncv\funcs1.h>

#include <NovelCVLib\Ncv\ImageLineViewer2.h>

#include <NovelCVLib\Ncv\ImgDataMgr_Simple_2.h>


namespace Hcv
{
	using namespace Hcpl;
	//using namespace Hcpl::Math;

	ImageLineViewer2::ImageLineViewer2( F32ImageRef a_srcImg, LinePathRef a_lp  ) : 
	m_rgnIndexCalc(a_srcImg->GetWidth(), a_srcImg->GetHeight()), //m_filtSysBld( this ),
		m_nAprSize( GlobalStuff::AprSize1D )
	{
		m_srcImg = a_srcImg;

		m_resImg = a_srcImg->Clone();
		

		m_lp = a_lp;

		

		DoPrepare();

		DoProcess( );
	}


	F32ImageRef ImageLineViewer2::GetResultImg()
	{

		return m_resImg;
	}

	U8ImageRef ImageLineViewer2::GetSignalDspImg()
	{

		return m_sigDspImg;
	}


	void ImageLineViewer2::DoPrepare()
	{

		InitRgnInfoVect();

		int maxLen = -1;
		{
			CvSize srcImgSiz = m_srcImg->GetSize();
			maxLen = sqrt( (double)( Sqr( srcImgSiz.width ) + Sqr( srcImgSiz.height ) ) ) * 1.3;
		}

		m_inputRgnPtrVect.SetCapacity( maxLen );

		m_edgeRgnPtrVect.SetCapacity( maxLen );

		m_rootRgnPtrVect.SetCapacity( maxLen );

		m_filterOutputMgrVect.SetCapacity( 300 );

		int halfAprSize = m_nAprSize / 2;
		if( 0 == halfAprSize % 2 )
			halfAprSize++;

		{
			ColorFilter1DSystemBuilder fsb1( this );

			int lastMainID = -10;
			{
				lastMainID = AddFilter( &fsb1, 
					//new CompositeColorFilter1D( LinearAvgFilter1D::Create( m_nAprSize ) ), 
					//new CompositeColorFilter1D( LinearAvgFilter1D::Create( 5 ) ), 
					//new CompositeColorFilter1D( LinearAvgFilter1D::Create( 9 ) ), 
					new CompositeColorFilter1D( LinearAvgFilter1D::Create( 1 ) ), 
					//new AvgOutputMgr( this ), lastMainID);
					//new DummyOutputMgr( this ), lastMainID);										
					
						new ColorOutputMgr( this, 
						//u8ColorVal(255, 150, 255),
						//u8ColorVal(255, 150, 255),
						//u8ColorVal(255, 150, 255)

						//u8ColorVal( 0, 0, 255 ),
						//u8ColorVal( 0, 0, 100 ),
						//u8ColorVal( 0, 0, 100 )

						u8ColorVal( 255, 0, 0 ),
						u8ColorVal( 0, 255, 0 ),
						u8ColorVal( 0, 0, 255 )

					) , lastMainID);

			}
			

			{
				AddColorToSingleConverter( &fsb1,					
					//new SingleOutputMgr( this, u8ColorVal(255, 255, 255) ));
					//new SingleOutputMgr( this, u8ColorVal(255, 150, 255) ));				
					new DummyOutputMgr( this ));
			}


			int nApr_12 = 7;

			int nID_2;
			{
				nID_2 = AddFilter( &fsb1, 
					//new CompositeColorFilter1D( LinearDiffFilter1D::Create( 3 ) ),
					new CompositeColorFilter1D( LinearDiffFilter1D::Create( nApr_12 ) ),
					new DummyOutputMgr( this ), lastMainID);
					//new SingleOutputMgr( this, u8ColorVal(255, 255, 255) ), lastMainID);
			}

			{
				AddColorToSingleConverter( &fsb1,					
					//new SingleOutputMgr( this, u8ColorVal(0, 255, 255) ));
					//new SingleOutputMgr( this, u8ColorVal(255, 0, 180) ));
					new DummyOutputMgr( this ));
			}

			{
				AddFilter( &fsb1, 
					//new CompositeColorFilter1D( LinearDiffFilter1D::Create( 3 ) ),
					new CompositeColorFilter1D( LinearDiffFilter1D::Create( nApr_12 ) ),
					new DummyOutputMgr( this ), nID_2 );
					//new SingleOutputMgr( this, u8ColorVal(255, 255, 255) ), lastMainID);
			}

			{
				AddColorToSingleConverter( &fsb1,					
					//new SingleOutputMgr( this, u8ColorVal( 255, 0, 255) ));
					//new SingleOutputMgr( this, u8ColorVal(255, 0, 180) ));
					new DummyOutputMgr( this ));
			}


/*
			{
				AddFilter( &fsb1, new MaxFilter1D( 3 ),										
					//new SingleOutputMgr( this, u8ColorVal(0, 140, 255) ) );				
					new DummyOutputMgr( this ));
			}
*/

			{
				AddFilter( &fsb1, LinearAvgFilter1D::Create( 3 ),										
					new DummyOutputMgr( this ));
					//new SingleOutputMgr( this, u8ColorVal(0, 255, 255) ));
			}


/*
			{
				AddFilter( &fsb1, LinearAvgFilter1D::Create( 3 ),										
					new SingleOutputMgr( this, u8ColorVal(0, 140, 255) ) );				
			}
*/

			{
				lastMainID = AddFilter( &fsb1, 
					new CompositeColorFilter1D( LinearDiffFilter1D::Create( m_nAprSize ) ),
					//new CompositeColorFilter1D( LinearDiffFilter1D::Create( m_nAprSize * 1.5 ) ),
					//new CompositeColorFilter1D( LinearDiffFilter1D::Create( 11, m_nAprSize ) ),
					//new CompositeColorFilter1D( LinearDiffFilter1D::Create( 3, 20 ) ),
					//new CompositeColorFilter1D( LinearDiffFilter1D::Create( 15, 1 ) ),
					new DummyOutputMgr( this ), lastMainID);
			}

			int diff1SingID = -1;
			{
				diff1SingID = AddColorToSingleConverter( &fsb1,					
					//new SingleOutputMgr( this, u8ColorVal(255, 255, 255) ));
					new DummyOutputMgr( this ));
			}
/*
			{
				diff1SingID = AddFilter( &fsb1, new MaxFilter1D( 3 ),										
					//new SingleOutputMgr( this, u8ColorVal(0, 140, 255) ) );				
					new DummyOutputMgr( this ), diff1SingID);
			}
*/
			{
				int nofAvgs = 3;
				//int nofAvgs = 1;

				//int nAprSiz = 5;
				//int nAprSiz = halfAprSize ;
				int nAprSiz = ( halfAprSize > 5 ) ? 5 : halfAprSize;

				for(int i=0; i < nofAvgs; i++)
				{
					if( i == nofAvgs - 1 )
					{
						diff1SingID = AddFilter( &fsb1, LinearAvgFilter1D::Create( nAprSiz ),										
							//new SingleOutputMgr( this, u8ColorVal(255, 0, 0) ), diff1SingID);				
							new DummyOutputMgr( this ), diff1SingID);				
					}
					else
					{
						diff1SingID = AddFilter( &fsb1, LinearAvgFilter1D::Create( nAprSiz ),										
							new DummyOutputMgr( this ), diff1SingID);
					}
				}
			}

			{
				AddFilter( &fsb1, LinearDiffFilter1D::Create( m_nAprSize ),										
					new DummyOutputMgr( this ), diff1SingID );
					//new SingleOutputMgr( this, u8ColorVal(0, 255, 255) ), diff1SingID );
			}


			{
				//AddFilter( &fsb1, new PeakMarkerFilter1D( 20 ),
				AddFilter( &fsb1, new PeakMarkerFilter1D( 20 ),
					new Diff1MarkerOutputMgr( this, 
						//new SingleOutputMgr( this, u8ColorVal(0, 128, 0) )), diff1SingID );				
						new DummyOutputMgr( this )), diff1SingID );
			}


			{
				AddFilter( &fsb1, new ValleyMarkerFilter1D( 3 ),
					new Diff2MarkerOutputMgr( this, 
						new SingleOutputMgr( this, u8ColorVal(0, 0, 255) )), diff1SingID );				
						//new DummyOutputMgr( this )), diff1SingID );										


					//new SingleOutputMgr( this, u8ColorVal(160, 0, 160) ), diff1SingID);
					//new DummyOutputMgr( this ), diff1SingID);										
			}


/*
			{
				AddFilter( &fsb1, new ValleyMaximizerFilter1D( m_nAprSize ),
				//AddFilter( &fsb1, new ValleyMaximizerFilter1D( halfAprSize ),
					//new SingleOutputMgr( this, u8ColorVal(160, 0, 160) ), diff1SingID);
					new DummyOutputMgr( this ), diff1SingID);										
			}

			{
				AddFilter( &fsb1, LinearAvgFilter1D::Create( halfAprSize ),										
					//new SingleOutputMgr( this, u8ColorVal(255, 0, 0) ));				
					new SingleOutputMgr( this, u8ColorVal(160, 0, 160) ));
					//new DummyOutputMgr( this ));
			}

			{
				AddFilter( &fsb1, new PeakMarkerFilter1D( 10 ),
					new Diff2MarkerOutputMgr( this, 
						//new SingleOutputMgr( this, u8ColorVal(0, 0, 255) )) );				
						new DummyOutputMgr( this )) );										

			}
*/

/*
			{
				lastMainID = AddFilter( &fsb1, 
					new CompositeColorFilter1D( LinearDiffFilter1D::Create( m_nAprSize ) ),
					new DummyOutputMgr( this ), lastMainID);
			}

			{
				AddColorToSingleConverter( &fsb1,
					//new SingleOutputMgr( this, u8ColorVal(160, 0, 160) ));
					//new SingleOutputMgr( this, u8ColorVal(0, 255, 150) ));
					new DummyOutputMgr( this ));										
			}


			{
				AddFilter( &fsb1, LinearAvgFilter1D::Create( halfAprSize ),										
					//new DummyOutputMgr( this ));
					new SingleOutputMgr( this, u8ColorVal(160, 0, 160) ));
			}


			{
				AddFilter( &fsb1, new PeakCleanerFilter1D( m_nAprSize ),										
					new SingleOutputMgr( this, u8ColorVal(0, 255, 150) ));
					//new SingleOutputMgr( this, u8ColorVal(0, 128, 255) ));						
					//new DummyOutputMgr( this ));
			}

			{
				AddFilter( &fsb1, new PeakMarkerFilter1D( ),
					new Diff2MarkerOutputMgr( this, u8ColorVal(0, 0, 255) ));				
			}
*/

			{
				//AddFilter( &fsb1, LinearAvgFilter1D::Create( halfAprSize ),										
				//	new SingleOutputMgr( this, u8ColorVal(0, 128, 255) ));						
			}


/*
			{
				AddFilter( &fsb1, LinearDiffFilter1D::Create( m_nAprSize ),										
					new SingleOutputMgr( this, u8ColorVal(160, 0, 160) ));						
			}
*/

/*
			{
				AddFilter( &fsb1, LinearDiffFilter1D::Create( m_nAprSize ),					
					//new SingleOutputMgr( this, u8ColorVal(0, 128, 255) ));						
					new DummyOutputMgr( this ));										
			}




			{
				AddFilter( &fsb1, new AbsFilter1D(),					
					//new SingleOutputMgr( this, u8ColorVal(0, 128, 255) ));									
					new SingleOutputMgr( this, u8ColorVal(255, 128, 0) ));									
			}

			{
				//AddFilter( &fsb1, LinearAvgFilter1D::Create( 15 ),					
					//new SingleOutputMgr( this, u8ColorVal(0, 128, 255) ));									
			}

			{
				lastMainID = AddFilter( &fsb1, 
					new CompositeColorFilter1D( LinearDiffFilter1D::Create( m_nAprSize ) ),
					new DummyOutputMgr( this ), lastMainID);
			}

			{
				AddColorToSingleConverter( &fsb1,
					new SingleOutputMgr( this, u8ColorVal(160, 0, 160) ));
					//new SingleOutputMgr( this, u8ColorVal(0, 255, 150) ));
					//new DummyOutputMgr( this ));										
			}
*/
			m_filtSys = fsb1.GetResult();
			m_filtSys->ResetInput();
		}


	}




	int ImageLineViewer2::AddFilter( ColorFilter1DSystemBuilder * pFiltSysBld, 
		IColorFilter1DRef a_filt, IFilterOutputMgrRef a_outMgr, int a_nSrcID )
	{
		int id = pFiltSysBld->AddFilter( a_filt, a_nSrcID );						

		m_filterOutputMgrVect.PushBack( a_outMgr );

		return id;
	}
	

	int ImageLineViewer2::AddFilter( ColorFilter1DSystemBuilder * pFiltSysBld, 
		IFilter1DRef a_filt, IFilterOutputMgrRef a_outMgr, int a_nSrcID )
	{
		int id = pFiltSysBld->AddFilter( a_filt, a_nSrcID );						

		m_filterOutputMgrVect.PushBack( a_outMgr );

		return id;
	}
	

	int ImageLineViewer2::AddColorToSingleConverter( ColorFilter1DSystemBuilder * pFiltSysBld, 
		IFilterOutputMgrRef a_outMgr, int a_nSrcID )
	{
		int id = pFiltSysBld->AddColorToSingleConverter( a_nSrcID );						

		m_filterOutputMgrVect.PushBack( a_outMgr );

		return id;
	}


	void ImageLineViewer2::InitRgnInfoVect()
	{
		CvSize srcSiz = m_srcImg->GetSize();

		m_rgnInfoVect.SetSize(srcSiz.width * srcSiz.height);

		for(int y=0; y < srcSiz.height; y++)
		{
			for(int x=0; x < srcSiz.width; x++)
			{	
				RgnInfo * pRgn = GetPointRgn(x, y);

				pRgn->pImgPix = (F32ColorVal *) m_srcImg->GetPixAt( x, y );
				pRgn->pShowPix = (F32ColorVal *) m_resImg->GetPixAt( x, y );

				//pRgn->pShowPix->AssignVal( 0, 0, 0 );

				pRgn->pos.x = x;
				pRgn->pos.y = y;	

			}
		}


	}


	void ImageLineViewer2::DoProcess()
	{

		FixedVector< int > popIndex_Arr(10000);



		F32ImageRef img1 = m_srcImg;

		F32ImageRef img1Dsp = m_resImg;

		LinePathRef lp = m_lp;
		

		{
			F32ColorVal color1 = { 180, 0, 0 };

			IIterator_REF( F32Point ) iter1 = lp;


			F32ColorVal * pix2 = nullptr;


			int indexOnLine = 0;

			CvSize srcSiz = m_srcImg->GetSize();

			IndexCalc2D idx2D( srcSiz.width, srcSiz.height );


			do
			{
				//F32Point cp = lp->GetCurrent();
				F32Point cp = iter1->GetCurrent();

				popIndex_Arr.PushBack( idx2D.Calc( (int)cp.x, (int)cp.y ) );


				{
					F32ColorVal * pix88 = 
						(F32ColorVal *)img1Dsp->GetPixAt( (int)cp.x, (int)cp.y );

					*pix88 = color1;
				}

				{
					RgnInfo * pRgn = GetPointRgn( (int)cp.x, (int)cp.y );

					pRgn->IndexOnLine = indexOnLine++;

					m_inputRgnPtrVect.PushBack( pRgn );				
				}

				{
					pix2 = (F32ColorVal *)img1->GetPixAt( (int)cp.x, (int)cp.y );

					m_filtSys->InputVal( *pix2 );
				}


			//}while(lp->MoveNext());
			}while(iter1->MoveNext());


			IImgDataMgrRef idm1 = new ImgDataMgr_Simple_2(
				//GlobalStuff::GetLinePathImg(), GlobalStuff::AprSize1D);
				m_srcImg, GlobalStuff::AprSize1D);

			IImgPopulationRef imgPop = idm1->CreatePopulation();

			imgPop->AddRange_Thick( & popIndex_Arr[ 0 ], popIndex_Arr.GetSize() );

			float standDiv = imgPop->CalcStandDiv();

			{
				Signal1DViewerRef sv2 = new Signal1DViewer();

				for( int i=0; i < m_filterOutputMgrVect.GetSize(); i++ )
					m_filterOutputMgrVect[i]->ProvideSignal( sv2 );
				
				{
					Signal1DBuilder sb0( 2000, 0 );

					sb0.AddConstArr( standDiv, popIndex_Arr.GetSize() );

					sv2->AddSignal( sb0.GetResult(), u8ColorVal( 255, 255, 255 ) );
				}

				m_sigDspImg = sv2->GenDisplayImage();
			}

			DoProcessEdges();
		}

	}


	void ImageLineViewer2::ReceiveFilterOutput( int a_nFilterID, F32ColorVal a_outVal, int a_nBackShift )
	{
		IFilterOutputMgrRef outMgr = m_filterOutputMgrVect[ a_nFilterID ];

		outMgr->ProcessOutput( a_nFilterID, a_outVal, a_nBackShift );
	}

	void ImageLineViewer2::ReceiveFilterOutput( int a_nFilterID, float a_outVal, int a_nBackShift )
	{
		IFilterOutputMgrRef outMgr = m_filterOutputMgrVect[ a_nFilterID ];

		outMgr->ProcessOutput( a_nFilterID, a_outVal, a_nBackShift );
	}

	void ImageLineViewer2::NotifyAllOutputDone( )
	{

	}


	void ImageLineViewer2::ColorOutputMgr::ProcessOutput( int a_nFilterID, F32ColorVal a_outVal, int a_nBackShift )
	{
		ProcessInner( a_nFilterID, a_outVal, a_nBackShift );

		if( nullptr == m_sb0 )
		{
			 m_sb0 = new Signal1DBuilder( 700, a_nBackShift );
			 m_sb1 = new Signal1DBuilder( 700, a_nBackShift );
			 m_sb2 = new Signal1DBuilder( 700, a_nBackShift );			
		}

		m_sb0->AddValue( a_outVal.val0 );
		m_sb1->AddValue( a_outVal.val1 );
		m_sb2->AddValue( a_outVal.val2 );
	}

	void ImageLineViewer2::ColorOutputMgr::ProvideSignal( Signal1DViewerRef a_sv )
	{
		ProvideInnerSignal( a_sv );

		/*
		a_sv->AddSignal( m_sb0->GetResult(), u8ColorVal(200, 0, 0) );
		a_sv->AddSignal( m_sb1->GetResult(), u8ColorVal(0, 180, 0) );
		a_sv->AddSignal( m_sb2->GetResult(), u8ColorVal(0, 0, 255) );
		*/

		a_sv->AddSignal( m_sb0->GetResult(), m_valColor0 );
		a_sv->AddSignal( m_sb1->GetResult(), m_valColor1 );
		a_sv->AddSignal( m_sb2->GetResult(), m_valColor2 );		
	}



	void ImageLineViewer2::SingleOutputMgr::ProcessOutput( int a_nFilterID, float a_outVal, int a_nBackShift )
	{
		ProcessInner( a_nFilterID, a_outVal, a_nBackShift );

		if( nullptr == m_sb )
		{
			 m_sb = new Signal1DBuilder( 700, a_nBackShift );
		}

		m_sb->AddValue( a_outVal );
	}

	void ImageLineViewer2::SingleOutputMgr::ProvideSignal( Signal1DViewerRef a_sv )
	{
		ProvideInnerSignal( a_sv );

		// Hthm Tmp
		if( nullptr == m_sb )
		{
			 m_sb = new Signal1DBuilder( 700 );
		}

		//a_sv->AddSignal( m_sb->GetResult(), u8ColorVal(0, 128, 255) );
		a_sv->AddSignal( m_sb->GetResult(), m_color );
	}




	void ImageLineViewer2::Diff1MarkerOutputMgr::ProcessOutput( 
		int a_nFilterID, float a_outVal, int a_nBackShift )
	{
		ProcessInner( a_nFilterID, a_outVal, a_nBackShift );

		U8ColorVal colorHalfEdge( 200, 200, 100 );

		if( a_outVal > 0 )
		{
			RgnInfo * pRgn = m_pIlv->GetBackInputRgn( a_nBackShift );
				
			m_pIlv->m_edgeRgnPtrVect.PushBack( pRgn );
		

			m_pIlv->DrawCircle( pRgn, colorHalfEdge );


//////////////////////////////////


			int halfAprSize = m_pIlv->m_nAprSize / 2;
			if( 0 == halfAprSize % 2 )
				halfAprSize--;

			{
				RgnInfo * pRgnR1 = m_pIlv->GetBackInputRgn( a_nBackShift + halfAprSize );				
				m_pIlv->m_rootRgnPtrVect.PushBack( pRgnR1 );
			}

			{
				RgnInfo * pRgnR2 = m_pIlv->GetBackInputRgn( a_nBackShift - halfAprSize );				
				m_pIlv->m_rootRgnPtrVect.PushBack( pRgnR2 );
			}


		}

/*

		//SingleOutputMgr::ProcessOutput( a_nFilterID, a_outVal, a_nBackShift );

		ProcessInner( a_nFilterID, a_outVal, a_nBackShift );

		if( a_outVal > 0 )
		{
			F32ColorVal color1 = { 0, 180, 0 };

			RgnInfo * pRgn = m_pIlv->GetBackInputRgn( a_nBackShift );

			m_pIlv->m_edgeRgnPtrVect.PushBack( pRgn );


				
			//*pRgn->pShowPix = color1;

			HCV_CALL(

				cvCircle (
					m_pIlv->m_resImg->GetIplImagePtr(),
					cvPoint( pRgn->pos.x, pRgn->pos.y ),
					3,
					//cvScalar( color1.val0, color1.val1, color1.val2 )
					CV_RGB( color1.val2, color1.val1, color1.val0 )
					//CV_RGB( 0, 180, 0 )//, 1, 8
					//int thickness = 1,
					,-1 // CV_FILL
					//int connectivity = 8
				) );
		}

			
			


		//this->



		//a_sv->AddSignal( m_sb->GetResult(), u8ColorVal(0, 128, 255) );
		//a_sv->AddSignal( m_sb->GetResult(), m_color );
		*/
	}





	void ImageLineViewer2::Diff2MarkerOutputMgr::ProcessOutput( 
		int a_nFilterID, float a_outVal, int a_nBackShift )
	{
		ProcessInner( a_nFilterID, a_outVal, a_nBackShift );

		if( a_outVal > 0 )
		{
			RgnInfo * pRgn = m_pIlv->GetBackInputRgn( a_nBackShift );
				
			m_pIlv->m_rootRgnPtrVect.PushBack( pRgn );
		}
	}



	void ImageLineViewer2::DoProcessEdges()
	{
		U8ColorVal colorEdge( 0, 230, 0 );
		U8ColorVal colorHalfEdge( 200, 200, 100 );

		U8ColorVal colorRoot( 0, 0, 230 );
		U8ColorVal colorMedRoot( 200, 100, 200 );


		{
			for(int i=0; i < m_rootRgnPtrVect.GetSize(); i++)
			{
				//U8ColorVal color1 = SerialColorMgr::GetCurrent();
				//SerialColorMgr::MoveNext();

				RgnInfo * pRgn = m_rootRgnPtrVect[i];

				DrawCircle( pRgn, colorMedRoot );

			}
		}


		m_rootIdx = 0;

		//for(int i=0, j=0; i < m_edgeRgnPtrVect.GetSize(); i++)
		for(int i=0; i < m_edgeRgnPtrVect.GetSize(); i++)
		{
			//U8ColorVal color1 = { 0, 180, 0 };
			U8ColorVal color1 = colorEdge;
			
			//U8ColorVal color1 = SerialColorMgr::GetCurrent();
			//SerialColorMgr::MoveNext();

			RgnInfo * pEdgeRgn = m_edgeRgnPtrVect[i];

			const int edgeIOL = pEdgeRgn->IndexOnLine;

			RgnInfo * pFstRootRgn = FindRootRgnBef( pEdgeRgn );

			if( nullptr == pFstRootRgn )
				continue;

			RgnInfo * pSndRootRgn = FindRootRgnAft( );

			if( nullptr == pSndRootRgn )
				continue;


			DrawCircle( pFstRootRgn, colorRoot);
			DrawCircle( pSndRootRgn, colorRoot );
			DrawCircle( pEdgeRgn, colorEdge );
		}



	}


	//RgnInfo * ImageLineViewer2::FindRootRgnBef( RgnInfo * a_pEdgeRgnBef, RgnInfo * a_pEdgeRgn )
	ImageLineViewer2::RgnInfo * ImageLineViewer2::FindRootRgnBef( ImageLineViewer2::RgnInfo * a_pEdgeRgn )
	{
		if( 0 == m_rootRgnPtrVect.GetSize() )
			return nullptr;

		const int edgeIOL = a_pEdgeRgn->IndexOnLine;

		if( edgeIOL < m_rootRgnPtrVect[ m_rootIdx ]->IndexOnLine )
			return nullptr;

		for( ; m_rootIdx < m_rootRgnPtrVect.GetSize(); m_rootIdx++ )
		{
			ImageLineViewer2::RgnInfo * pRootRgnAft = m_rootRgnPtrVect[ m_rootIdx ];

			if( pRootRgnAft->IndexOnLine > edgeIOL )
			{
				return m_rootRgnPtrVect[ m_rootIdx - 1 ];
			}

		}

		if( m_rootIdx >= m_rootRgnPtrVect.GetSize() )
			return m_rootRgnPtrVect[ m_rootIdx - 1 ];
	}


	//RgnInfo * ImageLineViewer2::FindRootRgnAft( RgnInfo * a_pEdgeRgn , RgnInfo * a_pEdgeRgnAft)
	ImageLineViewer2::RgnInfo * ImageLineViewer2::FindRootRgnAft( int a_limIOL )
	{
		if( -1 == a_limIOL )
		{
			if( m_rootRgnPtrVect.GetSize() == m_rootIdx )
				return nullptr;
		}
		else
		{
			if( m_rootRgnPtrVect[ m_rootIdx ]->IndexOnLine >= a_limIOL )
				return nullptr;
		}

		return m_rootRgnPtrVect[ m_rootIdx ];
	}





	void ImageLineViewer2::DrawCircle( RgnInfo * a_pRgn, U8ColorVal a_color )
	{

		HCV_CALL(

			cvCircle (
				m_resImg->GetIplImagePtr(),
				cvPoint( a_pRgn->pos.x, a_pRgn->pos.y ),
				//3,
				2,
				CV_RGB( a_color.val2, a_color.val1, a_color.val0 ),
				-1 // CV_FILL
			) );

	}









}
