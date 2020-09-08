#include <Lib\Cpp\Common\commonLib.h>
#include <Lib\Hcv\CvIncludes.h>
#include <Lib\Hcv\Types.h>
#include <Lib\Hcv\error.h>
#include <vector>
#include <Lib\Hcv\Channel.h>
#include <Lib\Hcv\Image.h>
#include <Lib\Hcv\funcs1.h>

#include <Lib\Hcv\RegionSegmentor51.h>

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


		m_standDiv_Buf = m_imgScanMgr->GetMaxGrad_Loc_Img(
			)->GetPixAt(0, 0);


		//ImgDataMgr_CovMat * pDataMgr_Exact = dynamic_cast<ImgDataMgr_CovMat *>
		//	((IImgDataMgr *)m_imgDataMgr); 

		//m_dataElm_Buf = & (pDataMgr_Exact->GetDataArr())[0];

		//m_dataElm_Mean_Buf = & (pDataMgr_Exact->GetDataArr_Mean())[0];

		//m_avgSqrMag_Buf = & (pDataMgr_Exact->GetAvgSqrMag_Arr())[0];




		for(int y=0; y < srcSiz.height; y++)
		{
			for(int x=0; x < srcSiz.width; x++)
			{	
				RgnInfo * pRgnInfo = GetPointRgn(x, y);

				pRgnInfo->nIndex = m_rgnIndexCalc.Calc(x, y);

				pRgnInfo->pPrev = pRgnInfo;

				
				//pRgnInfo->pDataElm = & m_dataElm_Buf[ pRgnInfo->nIndex ];

				//pRgnInfo->dataElm_Mean.Copy( 
				//	m_dataElm_Mean_Buf[ pRgnInfo->nIndex ] );

				//pRgnInfo->magSqr = m_avgSqrMag_Buf[ pRgnInfo->nIndex ];



				pRgnInfo->pixColors = 
					(F32ColorVal *)m_src->GetPixAt(x, y);

				pRgnInfo->showColor = *pRgnInfo->pixColors;


				//pRgnInfo->bIsInConflict = false;

				pRgnInfo->accXYDistFromRoot = 0;
				pRgnInfo->maxAccXYDistFromRoot = -1;

				pRgnInfo->minDistFromRoot = 0;

				pRgnInfo->bFstFromBadSrc = false;

				pRgnInfo->bBadFillDone = false;

				pRgnInfo->bBad_UnfillDone = false;

				pRgnInfo->bInIntersection = false;

				pRgnInfo->bFromBadSrc = false;

				pRgnInfo->m_pDeepSrcBadRgn = NULL;

				pRgnInfo->bFromBadSrc_Org = false;

				pRgnInfo->bFrom_MaybeBadSrc = false;				

				pRgnInfo->bMaybe_FstFromBadSrc = false;				

				pRgnInfo->bInNativeTrace = false;				

				pRgnInfo->bFromSureBadSrc = false;

				pRgnInfo->m_pMinDist_EI = NULL;

				pRgnInfo->pTraceRootElm = NULL;

				pRgnInfo->pTraceFwdRoot = NULL;
				pRgnInfo->pTraceBkdRoot = NULL;

				pRgnInfo->nTraceID = -1;

				pRgnInfo->nMaxDistMet = 0;
				pRgnInfo->distMagFromRoot = 500 * m_difScale;

				//pRgnInfo->meanColors.val0 = 0;
				//pRgnInfo->meanColors.val1 = 0;
				//pRgnInfo->meanColors.val2 = 0;

				pRgnInfo->meanColors.val0 = pRgnInfo->pixColors->val0;
				pRgnInfo->meanColors.val1 = pRgnInfo->pixColors->val1;
				pRgnInfo->meanColors.val2 = pRgnInfo->pixColors->val2;
				

				//pRgnInfo->nPixCnt = 0;
				pRgnInfo->nPixCnt = 1;

				pRgnInfo->pos.x = x;
				pRgnInfo->pos.y = y;

				pRgnInfo->nLastVisitID = 0;

				RgnLink * links = pRgnInfo->links;
				for(int i=0; i<8; i++)
				{
					links[i].bProcessed = true;
					links[i].bExists = false;					
					links[i].dir = (RgnLinkDir)i;
				}

				pRgnInfo->bHasConflicts = false;
			}
		}

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

		m_linkAction_PtrPrvider.Init( 10000000 );

		//m_eiAcc_PtrPrvider.Init( 500000 );

		FixedVector< LinkAction > & rLinkActionVect = 
			m_linkAction_PtrPrvider.GetAllocArr();


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

	S16ImageRef RegionSegmentor51::GenDifImg(bool a_bRC, bool a_bRB,
		bool a_bCB, bool a_bLB)
	{
		S16ImageRef ret = S16Image::Create(m_src->GetSize(), 1);
		ret->SetAll(0);


		S16ChannelRef retCh0 = ret->GetAt(0);

		bool dirFlags[] = {false, false, false, false};

		if(a_bRC)
		dirFlags[RC] = true;
		if(a_bRB)
		dirFlags[RB] = true;
		if(a_bCB)
		dirFlags[CB] = true;
		if(a_bLB)
		dirFlags[LB] = true;


		//F32Point testPnt( 417, 534 );
		F32Point testPnt( 419, 532 );


		int nTestCnt = 0;

		for(int i=0; i < m_rgnInfoVect.GetSize(); i++)
		{
			RgnInfo * pRgn = &m_rgnInfoVect[i];

			RgnLink * links = pRgn->links;

			for(int j=0; j<4; j++)
			{
				if( links[j].bExists && dirFlags[j] )
				{
					if( pRgn->GetActRgn() != links[j].pRgn2->GetActRgn() )
					{
						//if( F32Point::Sub( testPnt, pRgn->pos ).CalcMag() < 2 ) 
						if( F32Point::Sub( testPnt, pRgn->pos ).CalcMag() < 3 ) 
						{
							RgnInfo * pActRgn1 = pRgn->GetActRgn();
							RgnInfo * pActRgn2 = links[j].pRgn2->GetActRgn();

							if( pActRgn1->nPixCnt < 20 ||
								pActRgn2->nPixCnt < 20 )
							{
								i = i;
							}

							nTestCnt++;

							i = i;
						}

						retCh0->SetAt( pRgn->pos.x, pRgn->pos.y, 255);
					}
				}
			}
		}

		return ret;
	}



	
	HistoGramRef RegionSegmentor51::GenDifHisto(bool a_bRC, bool a_bRB,
		bool a_bCB, bool a_bLB)
	{
		HistoGramRef hist = new HistoGram( GetMaxDif() + 1 );
		/*		FixedVector<Int32> & rHistVect = *hist->GetVectPtr();

		bool dirFlags[] = {false, false, false, false};

		if(a_bRC)
		dirFlags[RC] = true;
		if(a_bRB)
		dirFlags[RB] = true;
		if(a_bCB)
		dirFlags[CB] = true;
		if(a_bLB)
		dirFlags[LB] = true;


		ListQue< RgnLink > tmpQue;

		for(int i=0; i<m_difQues.GetNofQues(); i++)
		{
		RgnLink * pLink = m_difQues.PopPtr(i);

		while(NULL != pLink)
		{
		if( ! dirFlags[ pLink->dir ] )
		continue;

		rHistVect[ i ]++;

		tmpQue.PushPtr(pLink);
		pLink = m_difQues.PopPtr(i);
		}

		m_difQues.PushQue(i, &tmpQue);
		}*/

		return hist;
	}

	
	
	
	
	void RegionSegmentor51::Segment()
	{
		//m_pDbgRgn = & m_rgnInfoVect[ 110507 ];

		RgnInfo * pTestRgn = & m_rgnInfoVect[ m_nTestRgnIdx ];

		const int nLastLA_Index = GlobalStuff::m_nLA_Index;

		ListQue< LinkAction > tmpQue;

		//MultiListQue< LinkAction > m_difQues;
		
		MultiListQue< LinkAction > interRootQues;
		
		interRootQues.Init( m_linkActionMergeQues.GetNofQues() );

		//ListQue< LinkAction > interRootQue;


		const int nLim_e = 1;
		//const int nLim_e = 2;
		//const int nLim_e = 3;
		//const int nLim_e = 4;
		//const int nLim_e = 5;
		//const int nLim_e = 6;
		//const int nLim_e = 7;
		//const int nLim_e = 15;
		//const int nLim_e = 20;


		EdgeInfoAccessor eiAcc( this );


		for(int e=0; e < nLim_e; e++)
		{
			e = e;
			for(int i=0; i < 2; i++)
			//for(int i=0; i < 1; i++)
			{
				LinkAction_2 * pLA = NULL;

				do
				{
					pLA = PopMinPtr_From_MergeQues();

					if( NULL == pLA )
					{
						continue;
					}

					//RgnInfo * pRgn1 = pLA->pLink1->pRgn1;
					//RgnInfo * pRgn2 = pLA->pLink1->pRgn2;

					RgnInfo * pRgn1 = pLA->pRgn1;
					RgnInfo * pRgn2 = pLA->pRgn2;

					if( 122171 == pRgn1->nIndex )
						pRgn1 = pRgn1;

					if( 122171 == pRgn2->nIndex )
						pRgn2 = pRgn2;


					if( 2110125 == pLA->nIndex )
						i = i;

					if( 169560 == pRgn1->nIndex )
						i = i;

					if( 169560 == pRgn2->nIndex )
						i = i;


					//pRgn1->bIsPassiveRoot = false;
					//pRgn2->bIsPassiveRoot = false;


					GlobalStuff::m_nLA_Index = pLA->nIndex;

					//if( 3590427 == pLA->nIndex )
					if( 284395 == pLA->nIndex )
						pLA = pLA;


					//int nDistCur = m_linkActionMergeQues.GetLastMinIndex();

					//int nDistAct = (int)CalcRgnDif( pRgn1, pRgn2 );

					//if( nDistAct > nDistCur )
					//{
					//	pLA->nScaledDist = nDistAct;
					//	Push_LA_To_MergeQues( nDistAct, pLA );

					//	continue;
					//}






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
							ImgScanMgr_Ns::EdgeInfo * pEI = 
								m_edgeInfo_Ques.PopPtrMin();

							if( NULL == pEI )
								break;

							ImgScanMgr_Ns::EdgeInfo & rEI = *pEI;

							if( rEI.IsCanceled )
								continue;

							eiAcc.SetEdgeInfo( & rEI );

							RgnInfo * pRootRgn1 = eiAcc.GetR1_Rgn();
							RgnInfo * pRootRgn2 = eiAcc.GetR2_Rgn();

							UpdateActRgn( pRootRgn1 );
							RgnInfo * pRgnAct1 = pRootRgn1->GetActRgn();

							UpdateActRgn( pRootRgn2 );
							RgnInfo * pRgnAct2 = pRootRgn2->GetActRgn();

							if( pRgnAct1 == pRgnAct2 )
								continue;

							//CreateConflict( pRootRgn1, pRootRgn2, eiAcc.GetEdge_Rgn(), & rEI  );
							CreateConflict( pRgnAct1, pRgnAct2, eiAcc.GetEdge_Rgn(), & rEI  );
						}

					}



					RgnInfo * pRootRgn1 = pRgn1->GetRootRgn();

					if( NULL == pRootRgn1 )
					{
						// Bug
						ThrowHcvException();
					}

					RgnInfo * pRootRgn2 = pRgn2->GetRootRgn();

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

								//float distCur = m_linkActionMergeQues.GetLastMinIndex();


								//-- interRootQues.PushPtr(
								//-- 	m_linkActionMergeQues.GetLastMinIndex(), pLA );



								//float dist = CalcRgnDif( pRootRgn1, pRootRgn2 );
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

						if( NULL == pRgn2->GetRootRgn() )
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

							if( 3590427 == pLA->nIndex )
								pLA = pLA;

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


				//for(int k=0; k < interRootQues.GetNofQues(); k++)
				//{
				//	//LinkAction * pLA = interRootQues.PopPtr();
				//	LinkAction * pLA = interRootQues.PopPtr(k);

				//	while( NULL != pLA )
				//	{
				//		//m_difQues.PushPtr(0, pLA);
				//		Push_LA_To_MergeQues(k, pLA);

				//		//pLA = interRootQues.PopPtr();
				//		pLA = interRootQues.PopPtr(k);
				//	}
				//}


				
			}


			m_pAnyRoot = NULL;

			for(int i=0; i < m_rgnInfoVect.GetSize(); i++)
			{
				RgnInfo * pRgn = &m_rgnInfoVect[i];

				if( NULL == pRgn->GetRootRgn() )
				{
					if( NULL == m_pAnyRoot )
					{
						m_pAnyRoot = pRgn;
						pRgn->BeARoot();
					}
					else
					{
						pRgn->SetRootRgn( m_pAnyRoot );
					}
				}
			}

			for(int i=0; i < m_rgnInfoVect.GetSize(); i++)
			{
				RgnInfo * pRgn = & m_rgnInfoVect[i];
				UpdateActRgn( pRgn );
			}

			if( 1 == e )
			{
				for(int i=0; i < m_rgnInfoVect.GetSize(); i++)
				{
					RgnInfo * pRgn2 = &m_rgnInfoVect[i];
					
					RgnInfo * pActRgn2 = pRgn2->GetActRgn();
					
					//if( 1 == pActRgn2->nPixCnt )
					if( pActRgn2->nPixCnt < 20 )
						i = i;
				}
			}


		}

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
		

		Gen_SegData();
	}

	float RegionSegmentor51::CalcRgnDif(RgnInfo * a_pRgn1, RgnInfo * a_pRgn2)
	{
		ThrowHcvException();

		return -1;

		//float dist = m_difScale * m_imgDataMgr->CalcDif(
			//a_pRgn1->nIndex, a_pRgn2->nIndex);
		
		//UpdateActRgn(a_pRgn1);

		//UpdateActRgn(a_pRgn2);

		//RgnInfo * pRgnAct_1 = a_pRgn1->GetActRgn_2();
		//RgnInfo * pRgnAct_2 = a_pRgn2->GetActRgn_2();


		//ImgDataElm_CovMat elm_Mean_1;

		//elm_Mean_1.Copy( pRgnAct_1->dataElm_Mean );
		//elm_Mean_1.DividSelfBy( pRgnAct_1->nPixCnt );


		//ImgDataElm_CovMat_2 elm_Mean_2;

		//elm_Mean_2.Copy( pRgnAct_2->dataElm_Mean );
		//elm_Mean_2.DividSelfBy( pRgnAct_2->nPixCnt );


		//elm_Mean_1.IncBy( elm_Mean_2 );
		//elm_Mean_1.DividSelfBy( 2 );
		//	
		//float magSqr = ( pRgnAct_1->magSqr / pRgnAct_1->nPixCnt +
		//	pRgnAct_2->magSqr / pRgnAct_2->nPixCnt ) / 2;

		//float dist = magSqr - elm_Mean_1.CalcMagSqr();
		//
		//if( dist < 0 )
		//	dist = 0;

		//dist = sqrt( dist );

		//if( dist > 1000 )
		//	dist = dist;

		//dist *= m_difScale;

		//dist += m_nAprSize;

		////dist = m_difScale * ImgDataElm_CovMat_2::CalcDif(
		////	*a_pRgn1->pDataElm, *a_pRgn2->pDataElm);
		////	//*pRgnAct_1->pDataElm, *pRgnAct_2->pDataElm);


		//return dist;
	}

	void RegionSegmentor51::UpdateActRgn(RgnInfo * a_pRgn)
	{
		if( NULL == a_pRgn->GetRootRgn() )
			return;
		
		if( a_pRgn->GetRootRgn() == a_pRgn->GetRootRgn()->GetActRgn() )
			return;

		static FixedVector<RgnInfo *> rgnVect(10000);
		rgnVect.SetSize(10000);
		static int nMaxNofRgns = rgnVect.GetSize();

		RgnInfo * pActRgn;
		do
		{
			pActRgn = a_pRgn ;
			int nofRgns = 0;

//			while(pActRgn != pActRgn->GetActRgn() && nofRgns < nMaxNofRgns)
			while(pActRgn != pActRgn->GetActRgn())
			{
				rgnVect[nofRgns++] = pActRgn;
				pActRgn = pActRgn->GetActRgn();
			}

			for(int i=0; i<nofRgns; i++)
				rgnVect[i]->SetActRgn( pActRgn );

		}while( pActRgn != pActRgn->GetActRgn() );
	}



	S16ImageRef RegionSegmentor51::GenSegmentedImage( bool a_bShowMeanColor )
	{
		//Gen_SegData();

		S16ImageRef ret = S16Image::Create(m_src->GetSize(), 3);
		//S16ImageRef ret = GenS16FromF32Image(
			//GenSegmentedImage2());

		//return ret;

		for(int i=0; i < m_rgnInfoVect.GetSize(); i++)
		{
			RgnInfo * pRgn = &m_rgnInfoVect[i];
			RgnInfo * pActRgn = pRgn->GetActRgn();

			//pActRgn->IncPopulationBy( 

			//pActRgn->meanColors.IncBy( *pActRgn->pixColors );

			//pActRgn->nPixCnt++;
		}

		for(int i=0; i < m_rgnInfoVect.GetSize(); i++)
		{
			RgnInfo * pRgn = &m_rgnInfoVect[i];
			RgnInfo * pActRgn = pRgn->GetActRgn();

			if( pActRgn == pRgn )
			{
				pRgn->meanColors.DividSelfBy( pRgn->nPixCnt );

				if( false == a_bShowMeanColor )
				{
					pRgn->meanColors.val0 = rand() % 256;
					pRgn->meanColors.val1 = rand() % 256;
					pRgn->meanColors.val2 = rand() % 256;
				}
			}
		}

		S16ChannelRef retCh0 = ret->GetAt(0);
		S16ChannelRef retCh1 = ret->GetAt(1);
		S16ChannelRef retCh2 = ret->GetAt(2);

		for(int i=0; i < m_rgnInfoVect.GetSize(); i++)
		{
			RgnInfo * pRgn = &m_rgnInfoVect[i];
			RgnInfo * pActRgn = pRgn->GetActRgn();
																			
				

			{
				if(pRgn->bShowLocalColor)
				//if(false)
				{
					/*
					retCh0->SetAt( pRgn->pos.x, pRgn->pos.y, (short)pRgn->pixColors->val0 );
					retCh1->SetAt( pRgn->pos.x, pRgn->pos.y, (short)pRgn->pixColors->val1 );
					retCh2->SetAt( pRgn->pos.x, pRgn->pos.y, (short)pRgn->pixColors->val2 );
					*/

					retCh0->SetAt( pRgn->pos.x, pRgn->pos.y, (short)pRgn->showColor.val0 );
					retCh1->SetAt( pRgn->pos.x, pRgn->pos.y, (short)pRgn->showColor.val1 );
					retCh2->SetAt( pRgn->pos.x, pRgn->pos.y, (short)pRgn->showColor.val2 );
					
				}
				else
				{
					retCh0->SetAt( pRgn->pos.x, pRgn->pos.y, (short)pActRgn->meanColors.val0 );
					retCh1->SetAt( pRgn->pos.x, pRgn->pos.y, (short)pActRgn->meanColors.val1 );
					retCh2->SetAt( pRgn->pos.x, pRgn->pos.y, (short)pActRgn->meanColors.val2 );
				}

			}
		}

		m_outImg = ret;

		return ret;
	}




	F32ImageRef RegionSegmentor51::GenSegmentedImage2( bool a_bShowMeanColor )
	{
		S16ImageRef difImg = GenDifImg( true, true, true, true );

		//F32ImageRef ret = F32Image::Create(m_src->GetSize(), 3);
		F32ImageRef ret = m_src->Clone();




		for(int i=0; i < m_rgnInfoVect.GetSize(); i++)
		{
			RgnInfo * pRgn = &m_rgnInfoVect[i];
			RgnInfo * pActRgn = pRgn->GetActRgn();

		}

		F32ChannelRef retCh0 = ret->GetAt(0);
		F32ChannelRef retCh1 = ret->GetAt(1);
		F32ChannelRef retCh2 = ret->GetAt(2);

		for(int i=0; i < m_rgnInfoVect.GetSize(); i++)
		{
			RgnInfo * pRgn = &m_rgnInfoVect[i];
			RgnInfo * pActRgn = pRgn->GetActRgn();

			F32ColorVal * retPix = (F32ColorVal *)ret->GetPixAt( pRgn->pos.x, pRgn->pos.y );

			short * pDifPix = difImg->GetPixAt( pRgn->pos.x, pRgn->pos.y );

			if( *pDifPix > 0 )
			{
				retPix->AssignVal( 255, 255, 255 );
			}
			else
			{
				retPix->MultSelfBy( 0.8 );
			}
				

		}

		return ret;
	}



	void RegionSegmentor51::ShowValleyPath(int a_x, int a_y)
	{
		Hcv::S16ImageRef img0 = this->GenSegmentedImage(false);
		//Hcv::F32ImageRef img1 = this->GenSegmentedImage2(false);

		//img1 = img1->Clone();
		Hcv::F32ImageRef img1 = GenF32FromS16Image( img0 );


		RgnInfo * pRgn1 = GetPointRgn( a_x, a_y );


		ShowImage(img1, "RgnSgmImg");

	}


	void RegionSegmentor51::ShowSrcPath(int a_x, int a_y)
	{
		//a_x = 266;
		//a_y = 426;

		//a_x = 588;
		//a_y = 341;


		Hcv::S16ImageRef img0 = this->GenSegmentedImage(false);
		//Hcv::F32ImageRef img1 = this->GenSegmentedImage2(false);

		//img1 = img1->Clone();
		Hcv::F32ImageRef img1 = GenF32FromS16Image( img0 );


		RgnInfo * pRgn1 = GetPointRgn( a_x, a_y );

		Signal1DBuilderRef sb0 = new Signal1DBuilder( 1300 );
		Signal1DBuilderRef sb1 = new Signal1DBuilder( 1300 );
		Signal1DBuilderRef sb2 = new Signal1DBuilder( 1300 );


		RgnInfo * pRgn1_Old = NULL;

		int nSrcCnt = 0;
		do
		{
			F32ColorVal * pColor = (F32ColorVal *)img1->GetPixAt(
				pRgn1->pos.x, pRgn1->pos.y );

			{
				float gradVal = *m_srcGrad->GetPixAt(
					pRgn1->pos.x, pRgn1->pos.y );

				sb0->AddValue( gradVal );
			}

			{
				float rootDist = *m_rootRgnImg->GetPixAt(
					pRgn1->pos.x, pRgn1->pos.y );

				sb1->AddValue( rootDist );
			}

			{
				float minRootDist = pRgn1->minDistFromRoot / m_difScale;

				sb2->AddValue( minRootDist );
			}

			pColor->AssignVal( 0, 255, 0 );

			pRgn1_Old = pRgn1;
			pRgn1 = pRgn1->pSrcRgn;

			nSrcCnt++;

			if( nSrcCnt >= 1500 )
				break;

		}while( NULL != pRgn1 );

		{
			//F32ColorVal * pColor = (F32ColorVal *)img1->GetPixAt(
				//a_x, a_y );

			//pColor->AssignVal( 0, 0, 255 );

			RgnInfo * pRgn1_1 = GetPointRgn( a_x, a_y );

			DrawCircle( img1, F32Point( a_x, a_y ), u8ColorVal( 0, 0, 255 ) );

			DrawCircle( img1, pRgn1_Old->pos, u8ColorVal( 0, 140, 255 ) );

			UpdateActRgn( pRgn1_1 );
			UpdateActRgn( pRgn1_Old );

			Hcpl_ASSERT( pRgn1_1->GetActRgn() == pRgn1_Old->GetActRgn() );



			if( NULL != pRgn1_1->m_pDeepSrcBadRgn )
			{
				DrawCircle( img1, pRgn1_1->m_pDeepSrcBadRgn->pos, 
				u8ColorVal( 0, 255, 255 ) );
			}

		}


		ShowImage(img1, "RgnSgmImg");

		{
			Signal1DViewer sv1;

			sv1.AddSignal( sb0->GetResult(), u8ColorVal( 255, 0, 0 ) );
			sv1.AddSignal( sb1->GetResult(), u8ColorVal( 0, 255, 0 ) );
			sv1.AddSignal( sb2->GetResult(), u8ColorVal( 0, 0, 255 ) );

			ShowImage( sv1.GenDisplayImage(), "Src Path" );
		}

	}


	void RegionSegmentor51::ShowEdgeOfConflict()
	{
		const float x1 = IOMgr::ReadInt("x1");
		const float y1 = IOMgr::ReadInt("y1");
		const float x2 = IOMgr::ReadInt("x2");
		const float y2 = IOMgr::ReadInt("y2");


		RgnInfo * pRgn1 = GetPointRgn(x1, y1);

		UpdateActRgn( pRgn1 );
		RgnInfo * pActRgn1 = pRgn1->GetActRgn();


		RgnInfo * pRgn2 = GetPointRgn(x2, y2);

		UpdateActRgn( pRgn2 );
		RgnInfo * pActRgn2 = pRgn2->GetActRgn();


		RgnConflict * pConflict = GetExistingConflict( pActRgn1, pActRgn2);

		if( NULL == pConflict )
			pConflict = pConflict;
		
		if( NULL != pConflict )
		{
			//Hcv::S16ImageRef img1 = this->GenSegmentedImage(false);
			//Hcv::F32ImageRef img1 = this->GenSegmentedImage2(false);

			Hcv::F32ImageRef img1 = GenF32FromS16Image(
				this->GenSegmentedImage(false) );

			img1 = img1->Clone();

			{
				RgnInfo * pRgn = pConflict->pOrgEdge;

				DrawCircle( img1, pRgn->pos, 
					u8ColorVal( 0, 255, 0 ), 3 );
			}

			{
				RgnInfo * pRgn = pConflict->pOrgR1;

				DrawCircle( img1, pRgn->pos, 
					u8ColorVal( 0, 0, 255 ), 3 );
			}

			{
				RgnInfo * pRgn = pConflict->pOrgR2;

				DrawCircle( img1, pRgn->pos, 
					u8ColorVal( 0, 0, 255 ), 3 );
			}

			{
				RgnInfo * pRgn = pConflict->pOrgDeep1;

				DrawCircle( img1, pRgn->pos, 
					u8ColorVal( 0, 180, 255 ), 3 );
			}

			{
				RgnInfo * pRgn = pConflict->pOrgDeep2;

				DrawCircle( img1, pRgn->pos, 
					u8ColorVal( 0, 180, 255 ), 3 );
			}

			ShowImage(img1, "RgnSgmImg");

		}







/*
		HCV_CALL(

			cvCircle (
				img1->GetIplImagePtr(),
				//cvPoint( x1, y1 ),
				cvPoint( x1, y1 ),
				3,
				//CV_RGB( a_color.val2, a_color.val1, a_color.val0 ),
				CV_RGB( 0, 255, 0 ),
				-1 // CV_FILL
			) );


		HCV_CALL(

			cvCircle (
				img1->GetIplImagePtr(),
				cvPoint( x2, y2 ),
				3,
				//CV_RGB( a_color.val2, a_color.val1, a_color.val0 ),
				CV_RGB( 255, 0, 0 ),
				-1 // CV_FILL
			) );
*/

		//ShowImage(img1, "RgnSgmImg");


	}



/*
	void RegionSegmentor51::PrepareConflicts()
	{
		//m_rgnConflictVect.SetSize( m_nofConflicts );
		m_rgnConflictVect.SetSize( 
			//m_nofPrimConfRgns * m_confCheckPtMgr.GetNofCheckPoints() * 2 );
			10000000);
		
		m_nofConflicts = 0;

		RgnInfo * pRgn = m_RgnOfConflictQue.PopPtr();

		while( NULL != pRgn )
		{
			PrepareRgnConflicts( pRgn );

			pRgn = m_RgnOfConflictQue.PopPtr();

//			if( NULL == pRgn->GetActRgn() )
//				pRgn = pRgn;

		}	//	while
	}
	*/

	//RegionSegmentor51::LinkAction * RegionSegmentor51::CloneLinkAction(LinkAction * a_pLA )
	//{
	//	LinkAction * pLA = &m_linkActionVect[ m_nofLinkActions++ ];

	//	*pLA = *a_pLA;

	//	return pLA;
	//}

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


		LinkAction * pLA = m_linkAction_PtrPrvider.ProvidePtr();

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



		Hcpl_ASSERT( NULL != pRgn1->GetRootRgn() );



		LinkAction * pLA = m_linkAction_PtrPrvider.ProvidePtr();

		//pRgn1 = a_pRgn;
		//pRgn2 = a_pRgn2;
		pLA->pLink1 = & a_rLink;
		//pLA->pLink2 = &a_rLink2;


		float distNew;

		{		
			float distRoot = -1;
			//float distNear;			
			{
				RgnInfo * pRgnTmp;
				/*if( NULL != a_pRgn2->GetRootRgn() )
					pRgnTmp = a_pRgn2->GetRootRgn();
				else*/
					pRgnTmp = pRgn2;

				//distRoot = CalcRgnDif( pRgn1->GetRootRgn(), pRgnTmp );

				//distNear = CalcRgnDif( a_pRgn, pRgnTmp );
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

		//if( nDistNew > pRgn1->GetRootRgn()->RootMedColorDist )
			//nDistNew = ( GetMaxDif() - 1 ) * m_difScale;


		if( NULL != a_rLink.pCurLA && a_rLink.pCurLA->bIsActive )
		{
			if( nDistNew >= a_rLink.pCurLA->nScaledDist )
				return;
			else
				a_rLink.pCurLA->bIsActive = false;
		}
				

		pLA->nScaledDist = nDistNew;

		////if( nDistNew <= pRgn1->GetRootRgn()->RootMedColorDist )
		//	Push_LA_To_MergeQues( nDistNew, pLA);		
	}

	void RegionSegmentor51::Push_LA_To_MergeQues( int a_nIndex, LinkAction_2 * pLA )
	{
		//pLA->bIsActive = true;

		m_linkActionMergeQues.PushPtr( a_nIndex, pLA);
	}


	RegionSegmentor51::LinkAction_2 * RegionSegmentor51::PopMinPtr_From_MergeQues()
	{
		PopPtr:

		LinkAction_2 * pLA = m_linkActionMergeQues.PopPtrMin();

		if( NULL != pLA )
		{
			//if( ! pLA->bIsActive )
			//	goto PopPtr;
			//else
				//pLA->bIsActive = false;
		}

		return pLA;
	}

					

	RegionSegmentor51::LinkAction_2 * RegionSegmentor51::PopMaxPtr_From_MergeQues()
	{
		PopPtr:

		LinkAction_2 * pLA = m_linkActionMergeQues.PopPtrMax();

		if( NULL != pLA )
		{
			//if( ! pLA->bIsActive )
			//	goto PopPtr;
			//else
			//	pLA->bIsActive = false;
		}

		return pLA;
	}

					

	bool RegionSegmentor51::HaveConflict( RgnInfo * a_pMinSizRgn, RgnInfo * a_pMaxSizRgn)
	{
		RegionSegmentor51::RgnConflict * pConflict = GetExistingConflict( a_pMinSizRgn, a_pMaxSizRgn);

		if( NULL != pConflict )
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	RegionSegmentor51::RgnConflict * RegionSegmentor51::GetExistingConflict( RgnInfo * a_pMinSizRgn, RgnInfo * a_pMaxSizRgn)
	{
		//bool bRet = false;

		APtrList< RgnConflict > & minConfList = 
			a_pMinSizRgn->conflictList;

		RegionSegmentor51::RgnConflict * pConflict = minConfList.Last();

		while( NULL != pConflict )
		{
			RgnInfo * pPeerRgn = pConflict->pPeerRgn;

			UpdateActRgn( pPeerRgn );
			pPeerRgn = pPeerRgn->GetActRgn();
 			pConflict->pPeerRgn = pPeerRgn;

			if( pPeerRgn == a_pMaxSizRgn )
				//return true;
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

	S16ImageRef RegionSegmentor51::GenConflictImg(bool a_bRC, bool a_bRB,
			bool a_bCB, bool a_bLB)
	{
		S16ImageRef ret = S16Image::Create(m_src->GetSize(), 1);
		ret->SetAll(0);

		S16ChannelRef retCh0 = ret->GetAt(0);

		bool dirFlags[] = {false, false, false, false};

		if(a_bRC)
		dirFlags[RC] = true;
		if(a_bRB)
		dirFlags[RB] = true;
		if(a_bCB)
		dirFlags[CB] = true;
		if(a_bLB)
		dirFlags[LB] = true;

		for(int i=0; i < m_rgnInfoVect.GetSize(); i++)
		{
			RgnInfo * pRgn = &m_rgnInfoVect[i];

			RgnLink * links = pRgn->links;

			for(int j=0; j<4; j++)
			{
				if( links[j].bExists && dirFlags[j] )
				{
					if( IsConflictDist( links[j].DistMag ) )
					{
						retCh0->SetAt( pRgn->pos.x, pRgn->pos.y, 255);
					}
				}
			}
		}

		return ret;
	}



	void RegionSegmentor51::CreateConflict( RgnInfo * a_pRgn1, RgnInfo * a_pRgn2, RgnInfo * a_pOrgEdge, ImgScanMgr_Ns::EdgeInfo * a_pEI )
	{
		if( NULL == a_pOrgEdge )
			a_pOrgEdge = a_pOrgEdge;

		//if( ! a_pEI->DoesConflict() )
			//return;

		int a = 0;
		
		if( a_pRgn1->pRgn_DeepR != a_pRgn1 )
			a = 0;

		if( a_pRgn2->pRgn_DeepR != a_pRgn2 )
			a = 0;

		{
			RgnConflict * pRc = &m_rgnConflictVect[ m_nofConflicts++ ];
			pRc->pNext = pRc;
			pRc->pPrev = pRc;

			pRc->pEI = a_pEI;
			pRc->pOrgEdge = a_pOrgEdge;
			pRc->pOrgR1 = a_pRgn1;
			pRc->pOrgR2 = a_pRgn2;

			pRc->pOrgDeep1 = a_pRgn1->pRgn_DeepR;
			pRc->pOrgDeep2 = a_pRgn2->pRgn_DeepR;

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




	void RegionSegmentor51::PostScanPrepare()
	{
		FixedVector< ImgScanMgr_Ns::EdgeInfo > & rEdgeInfoArr = 
			m_imgScanMgr->GetEdgeInfoArr();


		EdgeInfoAccessor eiAcc( this );

		CvSize srcSize = m_src->GetSize();


		for( int k=0; k < rEdgeInfoArr.GetSize(); k++ )
		{
			ImgScanMgr_Ns::EdgeInfo & rEI = rEdgeInfoArr[ k ];

			if( rEI.IsCanceled )
				continue;

			eiAcc.SetEdgeInfo( & rEI );

			//pRgn_R1->pRgn_DeepR = pRgn_R1;
			//pRgn_R2->pRgn_DeepR = pRgn_R2;
		}

	}


	void RegionSegmentor51::ScanImageLines()
	{
		CvSize siz1 = m_src->GetSize();

		//m_conflictScanner = new ConflictScanner2( m_src );

		//const int nHalfAprSize = m_conflictScanner->GetAprSize() / 2;

		//m_conflictScanner = NULL;



		//GlobalStuff::SetLinePathImg( scanImage );


/////////////////////////



		//m_maxDif_Buf = & (m_imgScanMgr->GetMaxDif_Arr())[0];

		//m_scanPix_Buf = & (m_imgScanMgr->GetPixInfoArr())[0];

		//{
		//	FixedVector< EdgeScan::ScanDirMgrExtRef > & rScanMgrExt_Arr =
		//		m_imgScanMgr->GetScanDirExtArr();

		//	for( int i = 0; i < 4; i++ )
		//	{
		//		m_dir_difBuf_Arr[ i ] = m_dir_difBuf_Arr[ i + 4 ] =
		//			&(rScanMgrExt_Arr[ i * 2 ]->m_difGlobArr)[ 0 ];
		//	}
		//}


		PostScanPrepare();


		static int dxArr[] = {1, 1, 0, -1};
		static int dyArr[] = {0, 1, 1, 1};

		int nCurTraceProcID = 0;

		FixedVector< ImgScanMgr_Ns::EdgeInfo > & rEdgeInfoArr = 
			m_imgScanMgr->GetEdgeInfoArr();

		EdgeInfoAccessor eiAcc( this );

		CvSize srcSize = m_src->GetSize();
		
		m_standDev_Buf = m_imgScanMgr->GetMaxGrad_Loc_Img(
			)->GetPixAt( 0, 0 );

		float * standDiv_Buf = m_standDev_Buf;

		for( int k=0; k < rEdgeInfoArr.GetSize(); k++ )
		{
			ImgScanMgr_Ns::EdgeInfo & rEI = rEdgeInfoArr[ k ];

			if( rEI.IsCanceled )
				continue;

			eiAcc.SetEdgeInfo( & rEI );



			RgnInfo * pRgnEdge = eiAcc.GetEdge_Rgn();

			RgnInfo * pRootRgn1 = eiAcc.GetR1_Rgn();
			RgnInfo * pRootRgn2 = eiAcc.GetR2_Rgn();


			{
				int nQueIdx = (int) ( (
					standDiv_Buf[ pRgnEdge->nIndex ] * m_difScale ) / 2 );

				MaxFinder< float > & rMaxFnd = 
					ImgDataElm_CovMat::MaxFnd_Dif;

				m_edgeInfo_Ques.PushPtr( nQueIdx, & rEI );

				int b = 0;

				b = 0;
			}
		}






		for( int k=0; k < rEdgeInfoArr.GetSize(); k++ )
		{
			ImgScanMgr_Ns::EdgeInfo & rEI = rEdgeInfoArr[ k ];

			//rEI.InrR1_IOL = rEI.Med1_IOL;
			//rEI.InrR2_IOL = rEI.Med2_IOL;

			if( rEI.IsCanceled )
				continue;

			eiAcc.SetEdgeInfo( & rEI );

			RgnInfo * pRootRgn1 = eiAcc.GetR1_Rgn();
			RgnInfo * pRootRgn2 = eiAcc.GetR2_Rgn();
		}


		for( int k=0; k < rEdgeInfoArr.GetSize(); k++ )
		{
			ImgScanMgr_Ns::EdgeInfo & rEI = rEdgeInfoArr[ k ];

			if( rEI.IsCanceled )
				continue;

			eiAcc.SetEdgeInfo( & rEI );


			RgnInfo * pRgnEdge = eiAcc.GetEdge_Rgn();

			RgnInfo * pRootRgn1 = eiAcc.GetR1_Rgn();
			RgnInfo * pRootRgn2 = eiAcc.GetR2_Rgn();


			pRootRgn1->BeARoot();		
			//PrepareRgnLinkActions( pRootRgn1, 0 );
			
			pRootRgn2->BeARoot();		
			//PrepareRgnLinkActions( pRootRgn2, 0 );

			CreateConflict( pRootRgn1, pRootRgn2, eiAcc.GetEdge_Rgn(), & rEI  );
		}

		F32Point testPnt( 135, 180 );

		{
			int nSrcSiz1D = m_rgnInfoVect.GetSize();

			for( int i=0; i < nSrcSiz1D; i++ )
			{
				RgnInfo * pRgn = & m_rgnInfoVect[ i ];

				if( ! pRgn->IsRoot() )
				{
					pRgn->BeARoot();
					//PrepareRgnLinkActions( pRgn, 0 );	
				}
				//else
				//{
				//	pRgn = pRgn;
				//}
			}

		}


		{
			FixedVector< ImgScanMgr_Ns::EdgeInfo > & rEdgeInfoArr = 
				m_imgScanMgr->GetEdgeInfoArr();

			FixedVector< ImgScanMgr_Ns::PixLinking > & rPixLinkingArr =
				m_imgScanMgr->GetPixLinkingArr();

			int nLA_Cnt = 0;

			for( int i=0; i < rPixLinkingArr.GetSize(); i++ )
			{
				ImgScanMgr_Ns::PixLinking & rPL = rPixLinkingArr[ i ];

				for( int j=0; j < 4; j++ )
				{
					ImgScanMgr_Ns::PixLink & rLink = rPL.Links[ j ];

					Hcpl_ASSERT( rLink.Rate >= 0 );

					if( rLink.nIOA_Peer < 0 )
						continue;
										
					LinkAction_2 * pLA = & m_linkAction_2_Arr[ nLA_Cnt ];

					pLA->nIndex = nLA_Cnt;

					pLA->pRgn1 = & m_rgnInfoVect[ rPL.nIOA ];
					pLA->pRgn2 = & m_rgnInfoVect[ rLink.nIOA_Peer ];
					
					this->Push_LA_To_MergeQues( 
						rLink.Rate * m_difScale, pLA );

					nLA_Cnt++;
				}
			}

		}


		RgnInfo * pRgn_R1_Test = & m_rgnInfoVect[ 251299 ];

		F32ImageRef scanImage = this->GenScanImage();
	}



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



	F32ImageRef RegionSegmentor51::GenScanImage()
	{
		F32ImageRef ret = this->m_src->Clone();

		ret->SetAll( 0 );

		U8ColorVal colorEdge1( 0, 210, 0 );

		U8ColorVal colorEdgeArr[ 4 ];

		{
			colorEdgeArr[0].AssignVal( 0, 180, 0 );
			colorEdgeArr[1].AssignVal( 255, 0, 0 );
			colorEdgeArr[2].AssignVal( 0, 0, 255 );
			colorEdgeArr[3].AssignVal( 0, 180, 255 );			
		}

		U8ColorVal colorRootClear( 255, 255, 255 );
		U8ColorVal colorRootInTrace( 255, 0, 200 );

		FixedVector< ImgScanMgr_Ns::EdgeInfo > & rEdgeInfoArr = 
			m_imgScanMgr->GetEdgeInfoArr();

		EdgeInfoAccessor eiAcc( this );

		for( int k=0; k < rEdgeInfoArr.GetSize(); k++ )
		{
			ImgScanMgr_Ns::EdgeInfo & rEI = rEdgeInfoArr[ k ];


			if( rEI.IsCanceled )
				continue;

			eiAcc.SetEdgeInfo( & rEdgeInfoArr[ k ] );


			{
				F32ColorVal * pix = (F32ColorVal *) ret->GetPixAt( 
					eiAcc.GetEdge_Rgn()->pos.x, eiAcc.GetEdge_Rgn()->pos.y );

				//U8ColorVal color1 = colorEdgeArr[ (int)rEI.Dir ];
				U8ColorVal color1 = colorEdge1;

				pix->val0 = color1.val0;
				pix->val1 = color1.val1;
				pix->val2 = color1.val2;
			}


			{
				RgnInfo * pRgn = eiAcc.GetR1_Rgn();

				F32ColorVal * pix = (F32ColorVal *) ret->GetPixAt( pRgn->pos.x, pRgn->pos.y );
				
				U8ColorVal color1;

/*				if( rEI.Dir != pRgn->localGradDir && pRgn->localGradVal > 0.5 )
				{
					pRgn->bIsPassiveRoot = true;
					color1 = colorRootInTrace;
				}
				else*/
					color1 = colorRootClear;

				pix->val0 = color1.val0;
				pix->val1 = color1.val1;
				pix->val2 = color1.val2;
			}


			{
				RgnInfo * pRgn = eiAcc.GetR2_Rgn();

				F32ColorVal * pix = (F32ColorVal *) ret->GetPixAt( pRgn->pos.x, pRgn->pos.y );
				
				U8ColorVal color1;

/*				if( rEI.Dir != pRgn->localGradDir && pRgn->localGradVal > 0.5 )
				{
					pRgn->bIsPassiveRoot = true;
					color1 = colorRootInTrace;
				}
				else*/
					color1 = colorRootClear;
					
				pix->val0 = color1.val0;
				pix->val1 = color1.val1;
				pix->val2 = color1.val2;
			}
		}

		return ret;
	}



	F32ImageRef RegionSegmentor51::GenRootRgnImage()
	{
		F32ImageRef ret = F32Image::Create( m_src->GetSize(), 3 );

		F32Point testPnt( 135, 180 );


		for( int i=0; i < m_rgnInfoVect.GetSize(); i++ )
		{
			RgnInfo * pRgn = &m_rgnInfoVect[ i ];

			F32ColorVal * pix = (F32ColorVal *)ret->GetPixAt( pRgn->pos.x, pRgn->pos.y );

			if( pRgn->IsRoot() )
			{
				//if( 284516 == pRgn->nIndex )

				pix->AssignVal( 255, 255, 255 );

				if( 122171 == pRgn->nIndex )
					i = i;

				if( F32Point::Sub( testPnt, pRgn->pos ).CalcMag() < 5 ) 
					i = i;
			}
			else
			{
				pix->AssignVal( 0, 0, 0 );
			}
		}

/*
		//if( 282873 == pRgn->nIndex )
		{
			{
				RgnInfo * pEdgeRgn = &m_rgnInfoVect[ 230998 ];			

				DrawCircle( ret, pEdgeRgn->pos, u8ColorVal( 255, 155, 0 ), 5 );
			}

			{
				RgnInfo * pMed1_Rgn = &m_rgnInfoVect[ 204649 ];			

				DrawCircle( ret, pMed1_Rgn->pos, u8ColorVal( 255, 0, 155 ), 5 );
			}

			{
				RgnInfo * pMed2_Rgn = &m_rgnInfoVect[ 340512 ];			

				DrawCircle( ret, pMed2_Rgn->pos, u8ColorVal( 255, 0, 155 ), 5 );
			}

			RgnInfo * pRgn = &m_rgnInfoVect[ 282873 ];

			DrawCircle( ret, pRgn->pos, u8ColorVal( 0, 255, 0 ), 5 );
			//pix->AssignVal( 0, 255, 0 );


			RgnInfoListElm * pRootElm = pRgn->pTraceRootElm;

			if( NULL != pRootElm )
			{
				UpdateActRgn( pRgn );
				RgnInfo * pActRgn_0 = pRgn->GetActRgn();

				bool bMergeOK = false;

				do
				{
					UpdateActRgn( pRootElm->pRgn );
					RgnInfo * pActRgnR = pRootElm->pRgn->GetActRgn();

					if(	pActRgnR == pActRgn_0 )
					{
						bMergeOK = true;
						break;
					}

					DrawCircle( ret, pRootElm->pRgn->pos, 
						u8ColorVal( 255, 0, 255 ), 5 );

					pRootElm = pRootElm->pNext;
				}while( NULL != pRootElm );

			}

		}
*/



		return ret;
	}


	F32ImageRef RegionSegmentor51::GenMergeOrderImage()
	{
		F32ImageRef ret = this->m_src->Clone();

		//const float dspLim = ( 256 * 3 );
		const float dspLim = ( 256 );

		const float divFact = RgnInfo::s_MergeOrder / ( dspLim - 1 );

		for( int i=0; i < m_rgnInfoVect.GetSize(); i++ )
		{
			RgnInfo * pRgn = &m_rgnInfoVect[ i ];

			F32ColorVal * pix = (F32ColorVal *) ret->GetPixAt( pRgn->pos.x, pRgn->pos.y );


			const int nDspVal = (int) (pRgn->nMergeOrder / divFact);

			pix->val0 = nDspVal;
			pix->val1 = nDspVal;
			pix->val2 = nDspVal;


/*

			float val = nDspVal;

			if( nDspVal / 256 == 2 )			
			{
				pix->val1 = nDspVal % 256;
				pix->val2 = 255;
				pix->val0 = 255;
			}
			else
				pix->val1 = 0;


			if( nDspVal / 256 == 1 )			
			{
				pix->val2 = nDspVal % 256;
				pix->val0 = 255;
			}
			else
				pix->val2 = 0;


			if( nDspVal / 256 == 0 )			
				pix->val0 = nDspVal % 256;
*/
		}


		return ret;
	}


	void RegionSegmentor51::PrepareSrcGradImg()
	{

		//m_srcGrad = GenMorphGradImg( m_src, 3 );
		//m_srcGrad = GenCvSmoothedImg( m_srcGrad, 3 );

//		m_srcGrad = GenMorphGradImg( m_src, 1 );
//		m_srcGrad = GenCvSmoothedImg( m_srcGrad, 5 );

		//m_srcGrad = GenMorphGradImg( m_src, 7 );
		//m_srcGrad = GenCvSmoothedImg( m_srcGrad, 11 );

		m_srcGrad = CircDiff::GenResult( m_src, 7 );
		//m_srcGrad = GenCvSmoothedImg( m_srcGrad, 5 );
		

		//m_srcGrad = GenMorphGradImg( m_src, 14 );
		//m_srcGrad = GenCvSmoothedImg( m_srcGrad, 21 );
		//m_srcGrad = GenCvSmoothedImg( m_srcGrad, 5 );

		//m_srcGrad = GenCvErodeCircleImg(m_srcGrad, 1);

		//SobelBuilder sb1( m_src, 5 );

		//m_srcGrad = sb1.


/*
		m_srcGrad = GenMorphGradImg( m_src, 3 );
		m_srcGrad = GenCvDilateCircleImg(m_srcGrad, 2);
		m_srcGrad = GenCvErodeCircleImg(m_srcGrad, 2);
		m_srcGrad = GenCvSmoothedImg( m_srcGrad, 3 );
		m_srcGrad = GenCvErodeCircleImg(m_srcGrad, 2);
*/

//		m_srcGrad = GenMorphGradImg( m_src, 2 );
	}

	
	void RegionSegmentor51::Gen_SegData()
	{
		//ImgSegDataMgrRef sdm1 = new ImgSegDataMgr(

		CvSize srcSiz = m_src->GetSize();


		//FixedVector< RgnInfo * > segRgn_Arr;
		//segRgn_Arr.SetCapacity( m_rgnInfoVect.GetSize() );

		FixedVector< int > pixInt_Arr;
		pixInt_Arr.SetSize( m_rgnInfoVect.GetSize() );


		int nSegCnt = 0;

		for(int i=0; i < m_rgnInfoVect.GetSize(); i++)
		{
			RgnInfo * pRgn = &m_rgnInfoVect[i];
			RgnInfo * pActRgn = pRgn->GetActRgn();

			if( pActRgn == pRgn )
			{
				//segRgn_Arr.PushBack( pRgn );
				pRgn->nSegIndex = nSegCnt++;
			}
		}

		
		for(int i=0; i < m_rgnInfoVect.GetSize(); i++)
		{
			RgnInfo * pRgn = &m_rgnInfoVect[i];
			RgnInfo * pActRgn = pRgn->GetActRgn();

			Hcpl_ASSERT( pActRgn->nSegIndex >= 0 );

			pixInt_Arr[ i ] = pActRgn->nSegIndex;
		}

		
		int nofSegments = nSegCnt;
				
		{
			int nSrcSiz_1D = srcSiz.width * srcSiz.height;

			char sMark[] = "Seg2_File";

			int nMarkLen = strlen(sMark);

			int nCnt = 0;

			FixedVector<byte> fileData_Arr;

			fileData_Arr.SetSize(
				1 + nMarkLen + 12 + nSrcSiz_1D * sizeof(int) );

			fileData_Arr[ nCnt ] = (byte)nMarkLen;
			nCnt++;

			memcpy( & fileData_Arr[ nCnt ], sMark, nMarkLen );
			nCnt += nMarkLen;


			*((int *)(& fileData_Arr[ nCnt ])) = srcSiz.width;
			nCnt += sizeof(int);

			*((int *)(& fileData_Arr[ nCnt ])) = srcSiz.height;
			nCnt += sizeof(int);

			*((int *)(& fileData_Arr[ nCnt ])) = nofSegments;
			nCnt += sizeof(int);


			{
				int nSiz_1 = ( fileData_Arr.GetSize() ) - nCnt;
				int nSiz_2 = ( pixInt_Arr.GetSize() * sizeof(int) );

				Hcpl_ASSERT( nSiz_1 == nSiz_2 );
			}

			int * pixFile_Buf = ( int * ) & fileData_Arr[ nCnt ];

			memcpy( pixFile_Buf, & pixInt_Arr[ 0 ], 
				pixInt_Arr.GetSize() * sizeof(int) );



			CString sFilePath = 
				"E:\\HthmWork\\Lib\\BSDS_300_2\\cbisRes.seg2";

			if( -1 != GlobalStuff::m_imgFilePath.Find(
				"D:\\HthmWork_D\\Berkeley-Image-DataSet\\BSDS-300\\Final-Extracted\\BSDS300-images\\BSDS300\\images" ))
			{
				char sAprSize[100];
				sprintf(sAprSize, "%d", (int)GlobalStuff::AprSize1D );


				sFilePath = 
					//"E:\\HthmWork\\Lib\\BSDS_300_2\\CBIS\\CBIS_" +
					"E:\\HthmWork\\Lib\\BSDS_300_2\\CBIS\\AprSiz" +
					CString( sAprSize )+
					CString( "\\Segms\\" );

				FilePathMgr fpm1( GlobalStuff::m_imgFilePath.GetBuffer() );

				FixedVector< char > fileTitle_Arr;

				fpm1.GetFileTitle( fileTitle_Arr );

				sFilePath += 
					CString( fileTitle_Arr.GetHeadPtr() ) + ".seg2";
			}





			if( false )
			{
				CFile file1;

				if( ! file1.Open(sFilePath, CFile::modeCreate | CFile::modeWrite) )
					ThrowHcvException();
			
				file1.Write( & fileData_Arr[ 0 ], fileData_Arr.GetSize() );

				file1.Close();
			}

			

		}


	}



}