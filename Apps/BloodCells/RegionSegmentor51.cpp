#include <NovelCVLib\Cpp\Common\commonLib.h>
#include <NovelCVLib\Hcv\CvIncludes.h>
#include <NovelCVLib\Hcv\Types.h>
#include <NovelCVLib\Hcv\error.h>
#include <vector>
#include <NovelCVLib\Hcv\Channel.h>
#include <NovelCVLib\Hcv\Image.h>
#include <NovelCVLib\Hcv\funcs1.h>

#include <NovelCVLib\Hcv\RegionSegmentor51.h>

#define M_PI 3.14159265358979323846

namespace Hcv
{
	using namespace Hcpl;
	using namespace Hcpl::Math;

	//static MgrOfLinkTypes::CoreStuff m_core;
	//RegionSegmentor51::MgrOfLinkTypes::CoreStuff m_core;

	int RegionSegmentor51::RgnInfo::s_MergeOrder = 0;


	RegionSegmentor51::~RegionSegmentor51()
	{

	}



	RegionSegmentor51::RegionSegmentor51(F32ImageRef a_src, S16ImageRef a_rootImg,
		int a_nDifThreshold, F32ImageRef a_rootValImg) : 
	m_rgnIndexCalc(a_src->GetWidth(), a_src->GetHeight()), m_nAprSize( GlobalStuff::AprSize1D )
	//m_rgnIndexCalc(a_src->GetWidth(), a_src->GetHeight()), m_nAprSize( 0 )
	{	
		m_difThreshold = a_nDifThreshold;
		m_nofConflicts = 0;
		m_nofPrimConfRgns = 0;
		m_nVisitID = 0;

		m_orgSrc = a_src;

		



		{
			F32ColorVal colorFact;

			colorFact.val0 = 0.51 * 0.5;
			colorFact.val1 = 1.44 * 0.5;
			colorFact.val2 = 1.048 * 0.5;

			//m_orgSrc = GenMultByColorImg( m_orgSrc, colorFact);
			m_src = m_orgSrc;
		}

		{
			PrepareSrcGradImg();
		}



		InitMaxDif();

		//m_difQues.Init( GetMaxDif() + 1 );
		//m_difQues.Init( GetMaxDif() * 1000 + 1 );
		//m_difQues.Init( GetMaxDif() + 2 );

		m_linkActionMergeQues.InitSize( GetMaxDif() * 2 + 2 );
		m_linkActionEdgeQues.InitSize( GetMaxDif() * 2 + 2 );

		m_edgeInfo_Ques.InitSize( m_linkActionMergeQues.GetNofQues() );

		m_medTraceQues.Init( m_linkActionMergeQues.GetNofQues() );


		m_edgeFwdRgnVect.SetCapacity(3000);

		m_edgeBkdRgnVect.SetCapacity(3000);
		
		InitRgnInfoVect();

		//m_pDbgRgn = & m_rgnInfoVect[ 282873 ];
		//m_pDbgRgn = & m_rgnInfoVect[ 110507 ];
		//m_pDbgRgn = & m_rgnInfoVect[ 109981 ];
		//m_pDbgRgn = & m_rgnInfoVect[ 101785 ];		
		//m_pDbgRgn = & m_rgnInfoVect[ 286705 ];
		m_pDbgRgn = & m_rgnInfoVect[ 535326 ];

		//m_pDbgRgn = GetPointRgn( 301, 348 );
		

		

		{	
			IndexCalc2D idx2D( m_src->GetSize().width,
				m_src->GetSize().height );

			m_nTestRgnIdx = idx2D.Calc( 17, 353 );
		}


		InitLinks();		

		m_rgnConflictVect.SetCapacity( 
			1000000);
		
		m_nofConflicts = 0;

		ScanImageLines();
	}

	void RegionSegmentor51::InitRgnInfoVect(void)
	{
		RgnInfo::s_MergeOrder = 0;

		CvSize srcSiz = m_src->GetSize();

		m_rgnInfoVect.SetSize(srcSiz.width * srcSiz.height);

		m_medTraceRgnPtrVect.SetCapacity( m_rgnInfoVect.GetSize() );

		//m_traceRootAllocVect.SetCapacity( m_rgnInfoVect.GetSize() );
		m_traceRootAllocVect.SetCapacity( 10000000 );


/*		F32ChannelRef srcCh0 = m_src->GetAt(0);
		F32ChannelRef srcCh1 = m_src->GetAt(1);
		F32ChannelRef srcCh2 = m_src->GetAt(2);

		F32ChannelRef rvCh0 = m_rootValImg->GetAt(0);
		F32ChannelRef rvCh1 = m_rootValImg->GetAt(1);
		F32ChannelRef rvCh2 = m_rootValImg->GetAt(2);*/

		//S16ChannelRef rootCh0 = m_rootImg->GetAt(0);


		RgnSegmDiameter rsDiam;

		rsDiam.SetDiamFull( m_nAprSize );

		{
			//int nDiamCore = ( m_nAprSize - 2 ) / 3;
			int nDiamCore = rsDiam.GetDiamCore();
			

			//int nDiamInr_1 = nDiamCore * 2 + 1;
			int nDiamInr_1 = rsDiam.GetDiamInr_1();
		}


		{
			F32ImageRef img1 = m_src;
				
			IImgDataMgr_2_FactorySetRef imgFactoryMgr = 
				////new ImgDataMgr_2_FactorySet_CovMat();
				new ImgDataMgr_2_FactorySet_LocHist();
				////new ImgDataMgr_2_FactorySet_GridPal();
				//new ImgDataMgr_2_FactorySet_Simple();
			

			//IImgCoreSrcRef ids1 = new ImgDataSrc_LocHist(img1);
			////IImgCoreSrcRef ids1 = new ImgDataSrc_GridPal(img1);
			IImgCoreSrcRef ids1 = new ImgDataSrc_LocHist(img1);
			

			RgnSegmDiameter rsDiam;
			rsDiam.SetDiamFull( GlobalStuff::AprSize1D );

			int nAprSiz_Far = rsDiam.GetDiamFull();
			//int nAprSiz_Far = rsDiam.GetDiamFull() + 4;
		
			//int nAprSiz_Loc = rsDiam.GetDiamInr_1();
			int nAprSiz_Loc = rsDiam.GetDiamFull();

			ImageRotationMgr_ExParamsRef rotParams = 
				new ImageRotationMgr_ExParams(
				//img1, NULL, 0, nAprSiz_Far, nAprSiz_Loc, imgFactoryMgr );
				img1, ids1, 0, nAprSiz_Far, nAprSiz_Loc, imgFactoryMgr );

			
		
			m_imgScanMgr = new ImgScanMgr( rotParams, 4,
				cvPoint( 40, 40 ) );
		}





		for(int y=0; y < srcSiz.height; y++)
		{
			for(int x=0; x < srcSiz.width; x++)
			{	
				RgnInfo * pRgnInfo = GetPointRgn(x, y);

				pRgnInfo->nIndex = m_rgnIndexCalc.Calc(x, y);

				pRgnInfo->pixColors = (F32ColorVal *)m_src->GetPixAt(x, y);

				pRgnInfo->pos.x = x;
				pRgnInfo->pos.y = y;

				pRgnInfo->nLastVisitID = 0;

				RgnLink * links = pRgnInfo->links;
				for(int i=0; i < 8; i++)
				{
					links[i].bProcessed = true;
					links[i].bExists = false;					
					links[i].dir = (RgnLinkDir)i;
				}

			}	//	end for x.
		}	//	end for y.

	}

	inline void RegionSegmentor51::CreateLink( RgnInfo * a_pRgn, 
		int x, int y, RgnLinkDir a_dir)
	{	
		static int dx[] = {1, 1, 0, -1};
		static int dy[] = {0, 1, 1, 1};

		const int nLinkIndex = (int)a_dir;

		RgnInfo * pRgn2 = GetPointRgn( x + dx[ nLinkIndex ], 
			y + dy[ nLinkIndex ]);

		RgnLink & rLink = a_pRgn->links[ nLinkIndex ];
		RgnLink & rLinkR2 = pRgn2->links[ nLinkIndex + 4 ];

		rLink.bProcessed = rLinkR2.bProcessed = false;
		rLink.bExists = rLinkR2.bExists = true;
		
		rLink.pRgn1 = a_pRgn;
		rLink.pRgn2 = pRgn2;

		rLinkR2.pRgn1 = pRgn2;
		rLinkR2.pRgn2 = a_pRgn;
	} 




	void RegionSegmentor51::InitLinks(void)
	{
		const int nSrcWidth = m_src->GetWidth();
		const int nSrcHeight = m_src->GetHeight();

		m_linkAction_2_Arr.SetSize( 
		//m_linkAction_2_Arr.SetCapacity( 
			nSrcWidth * nSrcHeight * 4 );

		// m_linkAction_Provider.Init( 30000 );
		m_linkAction_Provider = new MultiAllocProvider<LinkAction>(30000);

		FixedVector< LinkAction > & rLinkActionVect = 
			m_linkAction_Provider.GetAllocArr();


		for( int i=0; i < rLinkActionVect.GetSize(); i++ )
			rLinkActionVect[ i ].nIndex = i;


		for(int y=0; y<nSrcHeight-1; y++)
		{
			for(int x=1; x<nSrcWidth-1; x++)
			{	
				//	RC, RB, CB, LB

				RgnInfo * pRgn = GetPointRgn(x, y);

				
				CreateLink(pRgn, x, y, RC);
				CreateLink(pRgn, x, y, RB);
				CreateLink(pRgn, x, y, CB);
				CreateLink(pRgn, x, y, LB);
			}
		}

		for(int y=0, x=0; y<nSrcHeight-1; y++)
		{
			//	RC, RB, CB

			RgnInfo * pRgn = GetPointRgn(x, y);

			
			CreateLink(pRgn, x, y, RC);
			CreateLink(pRgn, x, y, RB);
			CreateLink(pRgn, x, y, CB);
		}

		for(int y=nSrcHeight-1, x=0; x<nSrcWidth-1; x++)
		{	
			// RC

			RgnInfo * pRgn = GetPointRgn(x, y);

			
			CreateLink(pRgn, x, y, RC);
		}

		for(int y=0, x=nSrcWidth-1; y<nSrcHeight-1; y++)
		{
			//	CB, LB

			RgnInfo * pRgn = GetPointRgn(x, y);

			
			CreateLink(pRgn, x, y, CB);
			CreateLink(pRgn, x, y, LB);
		}

	}

	
	void RegionSegmentor51::Segment()
	{
		//m_pDbgRgn = & m_rgnInfoVect[ 110507 ];

		RgnInfo * pTestRgn = & m_rgnInfoVect[ m_nTestRgnIdx ];

		const int nLastLA_Index = GlobalStuff::m_nLA_Index;


		const int nLim_e = 1;
		//const int nLim_e = 2;
		//const int nLim_e = 3;
		//const int nLim_e = 4;
		//const int nLim_e = 5;
		//const int nLim_e = 6;
		//const int nLim_e = 7;
		//const int nLim_e = 15;
		//const int nLim_e = 20;



		for(int e=0; e < nLim_e; e++)
		{
			e = e;
			for(int i=0; i < 2; i++)
			//for(int i=0; i < 1; i++)
			{
				LinkAction_2 * pLA = NULL;

				do
				{
					pLA = m_linkActionMergeQues.PopPtrMin();

					if( NULL == pLA )
					{
						continue;
					}


					RgnInfo * pRgn1 = pLA->pRgn1;
					RgnInfo * pRgn2 = pLA->pRgn2;

					GlobalStuff::m_nLA_Index = pLA->nIndex;

					{
						int nLastLA_MinIdx = 
							m_linkActionMergeQues.GetLastMinIndex();

						while(
							//true)
							false)
							//m_edgeInfo_Ques.Get_CurMinIndex() < 
							//nLastLA_MinIdx )
							//nLastLA_MinIdx * 0.7 )
							//nLastLA_MinIdx * 0.1 )
							//nLastLA_MinIdx * 3 )
						{
							UpdateActRgn( pRootRgn1 );
							RgnInfo * pRgnAct1 = pRootRgn1->GetActRgn();

							UpdateActRgn( pRootRgn2 );
							RgnInfo * pRgnAct2 = pRootRgn2->GetActRgn();

							if( pRgnAct1 == pRgnAct2 )
								continue;

							CreateConflict( pRgnAct1, pRgnAct2);
						}

					}



					RgnInfo * pRootRgn1 = pRgn1->GetRootAfterNecessaryUpdating();

					if( NULL == pRootRgn1 )
					{
						// Bug
						ThrowHcvException();
					}

					RgnInfo * pRootRgn2 = pRgn2->GetRootAfterNecessaryUpdating();

					//const int nTestIdx = 181157;
					const int nTestIdx = 173209;

					
					if( nTestIdx == pRgn1->nIndex ||
						 nTestIdx == pRgn2->nIndex )
					{
						i = i;
					}


					bool bMergeRoots = false;

					//if( 1 != i )
					//if( 0 == i )
					//if( 0 == i || e >= 1 )
					//if( 0 == i || e >= 1 )
					{
						if( NULL != pRootRgn1 && NULL != pRootRgn2 )
						{
							if( 0 == i )
							{

								if( pRootRgn1 == pRootRgn2 )
									continue;

								bMergeRoots = true;
							}

						}
						else		//	NULL == pRootRgn2
						{
							//if( NULL != pRgn1->pTraceRootElm )
								//continue;

							if( 1 == i )
								i = i;

							UpdateActRgn( pRootRgn1 );
							RgnInfo * pActRgn1 = pRootRgn1->GetActRgn();

							bool bAddRgn = true;


							if( bAddRgn )
							{	
								//*pRgn2->pixColors = *pRgn1->pixColors;

								//if( m_maxDif_Buf[ pRgn2->nIndex ] <=
									//m_maxDif_Buf[ pRootRgn1->nIndex ] )
								if( m_scanPix_Buf[ pRgn2->nIndex ].maxSlopeVal <= 35 )
								{
									pRgn2->BeARoot();
									pRgn2->SetActRgn( pRootRgn1->GetActRgn() );
								}
								else
								{
									pRgn2->SetRootRgn( pRootRgn1 );
								}

								pRgn2->pSrcRgn = pRgn1;

								pActRgn1->IncPopulationBy( pRgn2 );

								//Manage_EI_Activation( pRgn1, pRgn2 );

								PrepareRgnLinkActions( pRgn2, 0 );
							}

							continue;
						}

					}

					//else	//	i > 0
//--					if( 1 == i )
					//if( bMergeRoots )
					{
						UpdateActRgn( pRgn1 );
						RgnInfo * pActRgn1 = pRgn1->GetActRgn();

						if( NULL == pRgn2->GetRootAfterNecessaryUpdating() )
						{
							// Bug
							ThrowHcvException();
						}

						UpdateActRgn( pRgn2 );
						RgnInfo * pActRgn2 = pRgn2->GetActRgn();



						bool bHaveConflict = false;

						m_nVisitID++;

						RgnInfo * pMinSizRgn, * pMaxSizRgn;

						if( pActRgn1 == pActRgn2 )	
						{
							continue;
						}
						else
						{
							if( pActRgn1->conflictList.GetSize() <
								pActRgn2->conflictList.GetSize() )
							{
								pMinSizRgn = pActRgn1;
								pMaxSizRgn = pActRgn2;
							}
							else
							{
								pMinSizRgn = pActRgn2;
								pMaxSizRgn = pActRgn1;
							}

							bHaveConflict = HaveConflict( pMinSizRgn, pMaxSizRgn );
						}


						if( 122171 == pRgn2->nIndex )
							pRgn2 = pRgn2;


						if( bHaveConflict )
						//if(true)
						{
							continue;
						}
						else
						{
	//		NoConflict:
						
								
							if( pActRgn1 == pActRgn2 )	
								continue;							
							
							if( pRootRgn2->bIsPassiveRoot )
							{
								//*pRootRgn2->pixColors = *pRootRgn1->pixColors;
								//pRootRgn2->bIsPassiveRoot = false;

								//PrepareRgnLinkActions( pRootRgn2, 
									//m_linkActionMergeQues.GetLastMinIndex() );
							}

							if( 0 != pMinSizRgn->conflictList.GetSize() )
								RemoveDuplicateConflicts( pMaxSizRgn );

							{
								RgnInfo * pMasterRgn, * pSlaveRgn;

								if( pRootRgn2->bIsPassiveRoot ||
									pActRgn1 < pActRgn2 )	
								{
									pMasterRgn = pActRgn1;
									pSlaveRgn = pActRgn2;
								}
								else
								{
									pMasterRgn = pActRgn2;
									pSlaveRgn = pActRgn1;
								}

								pMasterRgn->conflictList.TakeListElements(
									pSlaveRgn->conflictList );
								pSlaveRgn->SetActRgn( pMasterRgn );

								pMasterRgn->IncPopulationBy( pSlaveRgn );

								//Manage_EI_Activation( pRgn1, pRgn2 );
							}

							if( pRootRgn2->bIsPassiveRoot )
							{
								pRootRgn2->SetRootRgn( pRootRgn1 );

								pRootRgn2->bIsPassiveRoot = false;

								PrepareRgnLinkActions( pRgn2, 
									m_linkActionMergeQues.GetLastMinIndex() );
							}

						}
					}
				}while( NULL != pLA );

				
			}	//	end for i.

		}	//	end for e.

		//ShowImage( GenMergeOrderImage(), "MergeOrderImage");	

		{
			F32ImageRef sgmImg2 = GenSegmentedImage2();
			ShowImage( sgmImg2, "GenSegmentedImage_2");	
			SaveImage( sgmImg2, "sgmImg2.jpg" );
		}

		ShowImage( 
			//GenColorDsp( 
			( 
			GenU8FromF32Image( GenMergeOrderImage() )), 			
			"MergeOrderImage");	

		//ShowImage( GenRootRgnImage(), "RootRgnImage" );
		

	}

	float RegionSegmentor51::CalcRgnDif(RgnInfo * a_pRgn1, RgnInfo * a_pRgn2)
	{
		ThrowHcvException();

		return -1;
	}




	RegionSegmentor51::LinkAction * RegionSegmentor51::ProvideLinkAction( 
		//RegionSegmentor51::RgnInfo * a_pRgn, RegionSegmentor51::RgnInfo * a_pRgn2 )
		RgnInfo * a_pRgn, RgnInfo * a_pRgn2 )
	{
		static int dxArr[] = { 1, 1, 0, -1,		-1, -1, 0, 1 };
		static int dyArr[] = { 0, 1, 1, 1,		0, -1, -1, -1 };

		static int xyToDirMap[ 3 ][ 3 ]; 

		static bool bMapNotReady = true;


		if( bMapNotReady )
		{
			int * mapBuf1D = & xyToDirMap[ 0 ][ 0 ];

			for( int i=0; i < 9; i++ )
				mapBuf1D[ i ] = -1;

			for( int i=0; i < 8; i++ )
			{
				int dx = dxArr[ i ];
				int dy = dyArr[ i ];

				//int * pVal = & xyToDirMap[ dx + 1 ][ dy + 1 ];
				xyToDirMap[ dx + 1 ][ dy + 1 ] = i;
			}



			bMapNotReady = false;
		}

		F32Point difPnt = F32Point::Sub( a_pRgn2->pos, a_pRgn->pos );

		Hcpl_ASSERT( fabs( difPnt.x ) <= 1 && fabs( difPnt.y ) <= 1 );

		RgnLinkDir dir = 
			(RgnLinkDir) xyToDirMap[ (int)(difPnt.x + 1) ][ (int)(difPnt.y + 1) ];

		Hcpl_ASSERT( (int)dir < 8 && (int)dir >= 0 );


		return ProvideLinkAction( a_pRgn, dir );
	}


	RegionSegmentor51::LinkAction * RegionSegmentor51::ProvideLinkAction(RgnInfo * a_pRgn, RgnLinkDir a_dir )
	{
		// Hthm tmp
		//ThrowHcvException();

		int x = a_pRgn->pos.x;
		int y = a_pRgn->pos.y;

		static int dx[] = {1, 1, 0, -1};
		static int dy[] = {0, 1, 1, 1};

		const int nLinkIndex = (int)a_dir;

		//RgnInfo * pRgn2 = GetPointRgn( x + dx[ nLinkIndex ], 
		//	y + dy[ nLinkIndex ]);

		RgnLink & rLink = a_pRgn->links[ nLinkIndex ];

		if( false == rLink.bExists )
		{
			return NULL;
		}

		RgnInfo * pRgn2 = rLink.pRgn2;

		RgnLink & rLinkR2 = pRgn2->links[ nLinkIndex + 4 ];


		LinkAction * pLA = m_linkAction_Provider.ProvidePtr();

		//pRgn1 = a_pRgn;
		//pRgn2 = pRgn2;
		pLA->pLink1 = &rLink;
		//pLA->pLink2 = &rLinkR2;




		return pLA;
	}




	void RegionSegmentor51::PrepareLinkAction( 
			RgnLink & a_rLink, float a_distBef, bool a_bSetProcessed )
	{
		ThrowHcvException();

		RgnInfo * pRgn1 = a_rLink.pRgn1;
		RgnInfo * pRgn2 = a_rLink.pRgn2;

		Hcpl_ASSERT( NULL != pRgn1->GetRootAfterNecessaryUpdating() );

		LinkAction * pLA = m_linkAction_Provider.ProvidePtr();

		//pRgn1 = a_pRgn;
		//pRgn2 = a_pRgn2;
		pLA->pLink1 = & a_rLink;
		//pLA->pLink2 = &a_rLink2;


		float distNew;

		{		
			float distRoot = -1;
			{
			}

			//float distNear = CalcRgnDif( pRgn1, pRgn2 );

			//distNew = distRoot;
			//distNew = ( distRoot + distNear ) / 2;
			//distNew = a_rLink.DistMag;

			//float gradVal = *m_srcGrad->GetPixAt(
				//pRgn2->pos.x, pRgn2->pos.y );


			//distNew = distRoot;
			//distNew = gradVal * m_difScale;


			//distNew = m_maxDif_Buf[ pRgn1->nIndex ] * m_difScale;

			distNew = m_standDev_Buf[ pRgn1->nIndex ] * m_difScale;
			//distNew = (( m_standDev_Buf[ pRgn1->nIndex ] +
				//m_standDev_Buf[ pRgn2->nIndex ] ) / 2 ) * m_difScale;


			//distNew = (( distNear + m_standDev_Buf[ pRgn1->nIndex ] +
				//m_standDev_Buf[ pRgn2->nIndex ] ) / 1 ) * m_difScale;
				//m_standDev_Buf[ pRgn2->nIndex ] ) / 3 ) * m_difScale;

			

			//if( distNew < distRoot )
				//distNew = distRoot;

			//distNew = distNear;


			//distNew = 
				//m_dir_difBuf_Arr [ (int)a_rLink.dir ] [ a_pRgn->nIndex ] * m_difScale;

			


		}


		//a_rLink.DistMag = a_rLink2.DistMag = distNew;
		
		//if( a_bSetProcessed )
		//a_rLink.bProcessed = a_rLink2.bProcessed = true;
		a_rLink.bProcessed = true;

		
		//if( pRgn1->bFstFromBadSrc && pRgn2->bFromBadSrc )

		//if( pRgn1->bFstFromBadSrc || pRgn2->bFstFromBadSrc )
		//if( pRgn1->bInTraceDam_Pos || pRgn2->bInTraceDam_Pos )
		//if( NULL == pRgn1->pShortestEI &&
		//if( 0 == pRgn1->nTraceRank &&
		//	
		//	//pRgn1->pShortestEI  != pRgn2->pShortestEI )
		//	//NULL != pRgn2->pShortestEI )
		//	0 != pRgn2->nTraceRank )

		if( pRgn1->nTraceRank < pRgn2->nTraceRank )
		{			
			//distNew = GetMaxDif() - 1;
			distNew = distNew;
		}

		
		int nDistNew = (int)distNew;

		Hcpl_ASSERT( nDistNew >= 0 );

		//if( nDistNew > pRgn1->GetRootAfterNecessaryUpdating()->RootMedColorDist )
			//nDistNew = ( GetMaxDif() - 1 ) * m_difScale;


		if( NULL != a_rLink.pCurLA && a_rLink.pCurLA->bIsActive )
		{
			if( nDistNew >= a_rLink.pCurLA->nScaledDist )
				return;
			else
				a_rLink.pCurLA->bIsActive = false;
		}
				

		pLA->nScaledDist = nDistNew;
	}


	bool RegionSegmentor51::RgnInfo::HaveConflict( RgnInfo * a_pMinSizRgn, RgnInfo * a_pMaxSizRgn)
	{
		RegionSegmentor51::RgnConflict * pConflict = GetConflictIfExists( a_pMinSizRgn, a_pMaxSizRgn);
		return nullptr != pConflict;
	}


	RegionSegmentor51::RgnConflict * RegionSegmentor51::GetConflictIfExists( RgnInfo * a_pMinSizRgn, RgnInfo * a_pMaxSizRgn)
	{
		APtrList< RgnConflict > & minConfList = a_pMinSizRgn->conflictList;

		RegionSegmentor51::RgnConflict * pConflict = minConfList.Last();

		while( NULL != pConflict )
		{
			RgnInfo * pPeerRgn = pConflict->pPeerRgn;

			pPeerRgn = pPeerRgn->GetRootAfterNecessaryUpdating();
 			pConflict->pPeerRgn = pPeerRgn;

			if( pPeerRgn == a_pMaxSizRgn )
				return pConflict;

			RgnConflict * pNext = minConfList.Next();
			
			if( pPeerRgn->nLastVisitID == m_nVisitID )
			{
				minConfList.RemovePtr( pConflict );
			}

			pPeerRgn->nLastVisitID = m_nVisitID;

			pConflict = pNext;
		}

		//return false;
		return NULL;
	}

	void RegionSegmentor51::RemoveDuplicateConflicts( RgnInfo * a_pRgn )
	{
		APtrList< RgnConflict > & confList = 
			a_pRgn->conflictList;

		RgnConflict * pConflict = confList.Last();

		while( NULL != pConflict )
		{
			RgnInfo * pPeerRgn = pConflict->pPeerRgn;

			UpdateActRgn( pPeerRgn );
			pPeerRgn = pPeerRgn->GetActRgn();
 			pConflict->pPeerRgn = pPeerRgn;


			RgnConflict * pNext = confList.Next();
			
			if( pPeerRgn->nLastVisitID == m_nVisitID )
			{
				confList.RemovePtr( pConflict );
			}

			pPeerRgn->nLastVisitID = m_nVisitID;

			pConflict = pNext;
		}
	}


	void RegionSegmentor51::PrepareRgnLinkActions( RgnInfo * a_pRgn, float a_distBef )
	{
		ThrowHcvException();

		if( 122171 == a_pRgn->nIndex )
			a_pRgn = a_pRgn;



		RgnLink * links = a_pRgn->links;

		for(int i=0; i<4; i++)
		{
			RgnLink & rLink = links[i];

//			if( rLink.bProcessed )
			if( false == rLink.bExists )
				continue;

			//RgnInfo * pRgn2 = rLink.pRgn2;
			//RgnLink & rLink2 = pRgn2->links[ i + 4 ];

			//if( pRgn2->bInTrace )
				//continue;

			PrepareLinkAction( rLink, a_distBef );
		}

		for(int i=4; i<8; i++)
		{
			RgnLink & rLink = links[i];

//			if( rLink.bProcessed )
			if( false == rLink.bExists )
				continue;

			//RgnInfo * pRgn2 = rLink.pRgn2;
			//RgnLink & rLink2 = pRgn2->links[ i - 4 ];

			//if( pRgn2->bInTrace )
				//continue;

			PrepareLinkAction( rLink, a_distBef );
		}

	}




	void RegionSegmentor51::CreateConflict( RgnInfo * a_pRgn1, RgnInfo * a_pRgn2)
	{
		if( NULL == a_pOrgEdge )
			a_pOrgEdge = a_pOrgEdge;

		//if( ! a_pEI->DoesConflict() )
			//return;

		int a = 0;
		
		{
			RgnConflict * pRc = &m_rgnConflictVect[ m_nofConflicts++ ];
			pRc->pNext = pRc;
			pRc->pPrev = pRc;

			pRc->pEI = a_pEI;
			pRc->pOrgEdge = a_pOrgEdge;
			pRc->pOrgR1 = a_pRgn1;
			pRc->pOrgR2 = a_pRgn2;

			pRc->pPeerRgn = a_pRgn2->pRgn_DeepR;
			a_pRgn1->pRgn_DeepR->conflictList.PushLast( pRc );
		}

		{
			RgnConflict * pRc2 = &m_rgnConflictVect[ m_nofConflicts++ ];
			pRc2->pNext = pRc2;
			pRc2->pPrev = pRc2;

			pRc2->pEI = a_pEI;
			pRc2->pOrgEdge = a_pOrgEdge;
			pRc2->pOrgR1 = a_pRgn1;
			pRc2->pOrgR2 = a_pRgn2;

			pRc2->pOrgDeep1 = a_pRgn1->pRgn_DeepR;
			pRc2->pOrgDeep2 = a_pRgn2->pRgn_DeepR;

			pRc2->pPeerRgn = a_pRgn1->pRgn_DeepR;
			a_pRgn2->pRgn_DeepR->conflictList.PushLast( pRc2 );
		}
	}


//////////////////////////////////////////////////////////////


	void RegionSegmentor51::MgrOfLinkTypes::CoreStuff::InitLinkTypeMgrs()
	{
		static int dx[] = {1, 1, 0, -1,   -1, -1, 0, 1};
		static int dy[] = {0, 1, 1, 1,   0, -1, -1, -1};

		m_linkTypeMgrVect.SetSize(8);

		m_dxyIndexMap[ m_dxyIndexCalc.Calc( 0 + 1, 0 + 1) ] = -1;

		for(int i=0; i < m_linkTypeMgrVect.GetSize(); i++)
		{
			F32Point point(dx[i], dy[i]);
						
			m_linkTypeMgrVect[i].Init( &m_linkTypeMgrVect[0], i, point );


			m_dxyIndexMap[ m_dxyIndexCalc.Calc( dx[i] + 1, dy[i] + 1) ] = i;
		}

	}

	void RegionSegmentor51::MgrOfLinkTypes::CoreStuff::InitMaps()
	{
		m_linkTypeMgrVect.SetSize(8);

		{
			for(int i=0; i < m_linkTypeMgrVect.GetSize(); i++)
			{
				F32Point uDirXY_i = m_linkTypeMgrVect[i].GetUnitDirXY();

				for(int j=0; j < m_linkTypeMgrVect.GetSize(); j++)
				{
					F32Point uDirXY_j = m_linkTypeMgrVect[j].GetUnitDirXY();

					float dist = F32Point::Sub(uDirXY_i, uDirXY_j).CalcMag(); 
					//m_distMap[ m_mapIndexCalc.Calc(i, j) ] = dist;
					m_distMap[ m_mapIndexCalc.Calc(j, i) ] = dist;
				}
			}
		}

		{
			for(int i=0; i < m_linkTypeMgrVect.GetSize(); i++)
			{				
				for(int j=0; j < m_linkTypeMgrVect.GetSize(); j++)
				{					
					//m_nbrMap[ m_mapIndexCalc.Calc(i, j) ] = j;
					m_nbrMap[ m_mapIndexCalc.Calc(j, i) ] = j;
				}
			}
		}

		{
			for(int i=0; i < m_linkTypeMgrVect.GetSize(); i++)
			{		
				for(int k=0; k < m_linkTypeMgrVect.GetSize(); k++)
				{		
					int minIndex = k;
					//float distMinIndex = m_distMap[ m_mapIndexCalc.Calc(i, minIndex) ]; 
					float distMinIndex = m_distMap[ m_mapIndexCalc.Calc(
						//minIndex, 
						m_nbrMap[ m_mapIndexCalc.Calc(minIndex, i) ],
						i) ]; 

					for(int j=k+1; j < m_linkTypeMgrVect.GetSize(); j++)
					{					
						//float distJ = m_distMap[ m_mapIndexCalc.Calc(i, j) ]; 
						float distJ = m_distMap[ m_mapIndexCalc.Calc(							
							//j, 
							m_nbrMap[ m_mapIndexCalc.Calc(j, i) ],
							i) ]; 

						if( distJ < distMinIndex )
						{
							distMinIndex = distJ;
							minIndex = j;
						}
					}

					// Swap
					//int tmp = m_nbrMap[ m_mapIndexCalc.Calc(i, k) ];
					int tmp = m_nbrMap[ m_mapIndexCalc.Calc(k, i) ];

					//m_nbrMap[ m_mapIndexCalc.Calc(i, k) ] = 
					m_nbrMap[ m_mapIndexCalc.Calc(k, i) ] = 
						//m_nbrMap[ m_mapIndexCalc.Calc(i, minIndex) ];
						m_nbrMap[ m_mapIndexCalc.Calc(minIndex, i) ];

					//m_nbrMap[ m_mapIndexCalc.Calc(i, minIndex) ] = tmp;
					m_nbrMap[ m_mapIndexCalc.Calc(minIndex, i) ] = tmp;
				}
			}
		}

	}



//////////////////////////////////////////////////////////////





	RegionSegmentor51::RgnLink * RegionSegmentor51::GetLinkBetweenRgns( int a_nIdx_1, int a_nIdx_2 )
	{
		if( 0 == a_nIdx_1 && 1 == a_nIdx_2 )
			a_nIdx_1 = a_nIdx_1;

		RgnInfo * pRgn1 = & m_rgnInfoVect[ a_nIdx_1 ];
		RgnInfo * pRgn2 = & m_rgnInfoVect[ a_nIdx_2 ];

		int nDx = pRgn2->pos.x - pRgn1->pos.x;
		Hcpl_ASSERT( abs( nDx <= 1 ) );

		int nDy = pRgn2->pos.y - pRgn1->pos.y;
		Hcpl_ASSERT( abs( nDy <= 1 ) );

		Hcpl_ASSERT( ! ( nDx == 0 && nDy == 0 ) );

		nDx++;
		nDy++;


		static int link_Idx_Arr[] = {

			5, 6, 7,
			4, 0, 0,
			3, 2, 1
		};

		int nIdx_XY = nDx + nDy * 3;

		int nLinkIdx = link_Idx_Arr[ nIdx_XY ];


		RgnLink * pLink = & pRgn1->links[ nLinkIdx ];

		return pLink;
	}




}