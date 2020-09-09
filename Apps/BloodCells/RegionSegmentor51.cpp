#include <NovelCVLib/Common/commonLib.h>
// #include <NovelCVLib\Hcv\CvIncludes.h>
// #include <NovelCVLib\Hcv\Types.h>
// #include <NovelCVLib\Hcv\error.h>
// #include <vector>
#include <NovelCVLib/OpenCV/Channel.h>
#include <NovelCVLib/OpenCV/Image.h>
#include <NovelCVLib/OpenCV/funcs1.h>

#include <NovelCVLib/Apps/BloodCells/RegionSegmentor51.h>

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



	RegionSegmentor51::RegionSegmentor51(ActualArrayAccessor_2D<F32PixelLinkOwner3C> & a_ploAcc)
	{	
		m_nVisitID = 0;

        a_ploAcc.CopyTo(&m_ploAcc);

		m_rgnConflict_Provider = new MultiAllocProvider<RgnConflict>(a_ploAcc.CalcSize_1D());

		InitMaxDif();

		m_linkActionMergeQues.InitSize( GetMaxDif() * 2 + 2 );

		InitRgnInfoVect();

		// m_pDbgRgn = & m_rgnInfoVect[ 535326 ];

		// m_nTestRgnIdx = a_ploAcc.CalcIndex_1D(17, 353);




	}



	void RegionSegmentor51::InitRgnInfoVect(void)
	{
		RgnInfo::s_MergeOrder = 0;


		Size_2D srcSiz = m_ploAcc->GetSize();

		m_rgnInfoVect.SetSize(m_ploAcc.CalcSize_1D());

		ActualArrayAccessor_2D<RgnInfo> rgnInfoAcc;


		for(int y=0; y < rgnInfoAcc.GetSizeY(); y++)
		{
			for(int x=0; x < rgnInfoAcc.GetSizeX(); x++)
			{	
				RgnInfo * pRgnInfo = &rgnInfoAcc.GetAt(x, y);

				pRgnInfo->nIndex = rgnInfoAcc.CalcIndex_1D(x, y);

				pRgnInfo->pos.x = x;
				pRgnInfo->pos.y = y;

				pRgnInfo->nLastVisitID = 0;

			}	//	end for x.
		}	//	end for y.

	}


	
	void RegionSegmentor51::Segment()
	{
		//m_pDbgRgn = & m_rgnInfoVect[ 110507 ];

		// RgnInfo * pTestRgn = & m_rgnInfoVect[ m_nTestRgnIdx ];

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
				LinkAction_2 * pLA = nullptr;

				do
				{
					pLA = m_linkActionMergeQues.PopPtrMin();

					if( nullptr == pLA )
					{
						continue;
					}

					GlobalStuff::m_nLA_Index = pLA->nIndex;

					RgnInfo * pActRgn1;
					{
						RgnInfo * pRgn1 = pLA->pRgn1;

						pActRgn1 = pRgn1->GetActRootAfterNecessaryUpdating();
						Ncpp_ASSERT(nullptr != pActRgn1);
					}

					RgnInfo * pRgn2 = pLA->pRgn2;
					Ncpp_ASSERT(nullptr != pRgn2);

					RgnInfo * pRootRgn2 = pRgn2->GetDirectRoot();

					// const int nTestIdx = 173209;
					
					// if( nTestIdx == pRgn1->nIndex ||
					// 	 nTestIdx == pRgn2->nIndex )
					// {
					// 	i = i;
					// }


					if(nullptr == pRootRgn2)
					{
						pRgn2->SetDirectRoot( pActRgn1);
						PrepareRgnLinkActions(pRgn2);

						continue;
					}


					// if(nTestIdx == pRgn2->nIndex)
					// 		i = i;

					RgnInfo * pActRgn2 = pRootRgn2->GetActRootAfterNecessaryUpdating();
					Ncpp_ASSERT(nullptr != pActRgn2);

					if( pActRgn1 == pActRgn2 )
						continue;

					//	Merging Roots
					{
						// Ncpp_ASSERT(pActRgn1 != pActRgn2);
						
						m_nVisitID++;

						RgnInfo * pMinSizRgn, * pMaxSizRgn;

						AssignForCondition( 
							pActRgn1->conflictList.GetSize() < pActRgn2->conflictList.GetSize(), 
							pActRgn1, pActRgn2, pMinSizRgn, pMaxSizRgn);

						const bool bHaveConflict = HaveConflict( pMinSizRgn, pMaxSizRgn );
						if( bHaveConflict )
							continue;


						// No Conflict
						{
							// if( 0 != pMinSizRgn->conflictList.GetSize() )
							// 	RemoveDuplicateConflicts( pMaxSizRgn );

							RgnInfo * pMasterRgn, * pSlaveRgn;
							AssignForCondition(pActRgn1 < pActRgn2, pActRgn1, pActRgn2, pMasterRgn, pSlaveRgn);

							pMasterRgn->conflictList.TakeListElements(
								pSlaveRgn->conflictList );

							pSlaveRgn->SetDirectRoot( pMasterRgn );

							RemoveDuplicateConflicts( pMasterRgn );

						}	//	end block: No Conflict
					}	//	end block: Merging Roots

				}while( nullptr != pLA );

				
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



	bool RegionSegmentor51::RgnInfo::HaveConflict( RgnInfo * a_pMinSizRgn, RgnInfo * a_pMaxSizRgn)
	{
		RegionSegmentor51::RgnConflict * pConflict = GetConflictIfExists( a_pMinSizRgn, a_pMaxSizRgn);
		return nullptr != pConflict;
	}


	RegionSegmentor51::RgnConflict * RegionSegmentor51::GetConflictIfExists( RgnInfo * a_pMinSizRgn, RgnInfo * a_pMaxSizRgn)
	{
		APtrList< RgnConflict > & minConfList = a_pMinSizRgn->conflictList;

		RegionSegmentor51::RgnConflict * pConflict = minConfList.Last();

		while( nullptr != pConflict )
		{
			RgnInfo * pPeerRgn = pConflict->pPeerRgn;

			pPeerRgn = pPeerRgn->GetActRootAfterNecessaryUpdating();
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

		return nullptr;
	}

	void RegionSegmentor51::RemoveDuplicateConflicts( RgnInfo * a_pRgn )
	{
		APtrList< RgnConflict > & confList = 
			a_pRgn->conflictList;

		RgnConflict * pConflict = confList.Last();

		while( nullptr != pConflict )
		{
 			pConflict->pPeerRgn = pPeerRgn->GetActRootAfterNecessaryUpdating();
			RgnInfo * pPeerRgn = pConflict->pPeerRgn;

			RgnConflict * pNext = confList.Next();
			
			if( pPeerRgn->nLastVisitID == m_nVisitID )
				confList.RemovePtr( pConflict );

			pPeerRgn->nLastVisitID = m_nVisitID;

			pConflict = pNext;
		}
	}


	void RegionSegmentor51::PrepareRgnLinkActions( RgnInfo * a_pRgn )
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


	void RegionSegmentor51::CreateConflict( const int a_rgnIndex1, const int a_rgnIndex2);
	{
		CreateConflict_Direct( &m_rgnInfoVect[a_rgnIndex1], &m_rgnInfoVect[a_rgnIndex2] );
	}

	void RegionSegmentor51::CreateConflict_Direct( RgnInfo * a_pRgn1, RgnInfo * a_pRgn2)
	{
		{
			RgnConflict * pRc = m_rgnConflict_Provider->ProvideNewElementPtr();
			
			pRc->pNext = pRc;
			pRc->pPrev = pRc;

			pRc->pPeerRgn = a_pRgn2;
			a_pRgn1->conflictList.PushLast( pRc );
		}

		{
			RgnConflict * pRc2 = m_rgnConflict_Provider->ProvideNewElementPtr();
			pRc2->pNext = pRc2;
			pRc2->pPrev = pRc2;

			pRc2->pPeerRgn = a_pRgn1;
			a_pRgn2->conflictList.PushLast( pRc2 );
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







}