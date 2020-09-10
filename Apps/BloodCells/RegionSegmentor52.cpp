#include <NovelCVLib/Common/commonLib.h>
// #include <NovelCVLib\Ncv\CvIncludes.h>
// #include <NovelCVLib\Ncv\Types.h>
// #include <NovelCVLib\Ncv\error.h>
// #include <vector>
#include <NovelCVLib/OpenCV/Channel.h>
#include <NovelCVLib/OpenCV/Image.h>
#include <NovelCVLib/OpenCV/funcs1.h>

#include <NovelCVLib/Apps/BloodCells/RegionSegmentor52.h>

#define M_PI 3.14159265358979323846

namespace Ncv
{
	using namespace Ncpp;
	using namespace Ncpp::Math;

	//static MgrOfLinkTypes::CoreStuff m_core;
	//RegionSegmentor52::MgrOfLinkTypes::CoreStuff m_core;

	int RegionSegmentor52::RgnInfo::s_MergeOrder = 0;


	RegionSegmentor52::~RegionSegmentor52()
	{

	}



	RegionSegmentor52::RegionSegmentor52(const ActualArrayAccessor_2D<F32PixelLinkOwner3C> & a_ploAcc)
	{	
		m_nVisitID = 0;

        a_ploAcc.CopyTo(&m_ploAcc);
		m_ploAcc_1D = m_ploAcc.GenAcc_1D();

		m_rgnConflict_Provider = new MultiAllocProvider<RgnConflict>(a_ploAcc.CalcSize_1D() / 4);
		m_linkAction_Provider = new MultiAllocProvider<LinkAction_2>(a_ploAcc.CalcSize_1D() * 8);

		InitScaleAndMaxDif();

		m_linkActionMergeQues.InitSize( GetMaxDif() * 2 + 2 );

		InitRgnInfoVect();

		// m_pDbgRgn = & m_rgnInfoVect[ 535326 ];

		// m_nTestRgnIdx = a_ploAcc.CalcIndex_1D(17, 353);




	}



	void RegionSegmentor52::InitRgnInfoVect(void)
	{
		RgnInfo::s_MergeOrder = 0;


		Size_2D srcSiz = m_ploAcc.GetSize();

		m_rgnInfoVect.InitSize(m_ploAcc.CalcSize_1D());

		ActualArrayAccessor_2D<RgnInfo> rgnInfoAcc;
		rgnInfoAcc.Init(m_rgnInfoVect.GetHeadPtr(), m_ploAcc.GetSize());

		for(int y=0; y < rgnInfoAcc.GetSize_Y(); y++)
		{
			for(int x=0; x < rgnInfoAcc.GetSize_X(); x++)
			{	
				RgnInfo * pRgnInfo = &rgnInfoAcc.GetAt(x, y);

				pRgnInfo->nIndex = rgnInfoAcc.CalcIndex_1D(x, y);

				pRgnInfo->pos.x = x;
				pRgnInfo->pos.y = y;

				pRgnInfo->nLastVisitID = 0;

			}	//	end for x.
		}	//	end for y.

	}


	
	void RegionSegmentor52::Segment()
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



		// for(int e=0; e < nLim_e; e++)
		// {
		// 	e = e;
		// 	for(int i=0; i < 2; i++)
		// 	//for(int i=0; i < 1; i++)
		// 	{
				LinkAction_2 * pLA = nullptr;

				do
				{
					pLA = m_linkActionMergeQues.PopPtrMin();

					if( nullptr == pLA )
						continue;

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
						
						// m_nVisitID++;

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

				
		// 	}	//	end for i.

		// }	//	end for e.

		

	}


	bool RegionSegmentor52::HaveConflict( RgnInfo * a_pMinSizRgn, RgnInfo * a_pMaxSizRgn)
	{
		RegionSegmentor52::RgnConflict * pConflict = GetConflictIfExists( a_pMinSizRgn, a_pMaxSizRgn);
		return nullptr != pConflict;
	}


	RegionSegmentor52::RgnConflict * RegionSegmentor52::GetConflictIfExists( RgnInfo * a_pMinSizRgn, RgnInfo * a_pMaxSizRgn)
	{
		m_nVisitID++;

		APtrList< RgnConflict > & minConfList = a_pMinSizRgn->conflictList;

		RegionSegmentor52::RgnConflict * pConflict = minConfList.Last();

		while( nullptr != pConflict )
		{
			RgnInfo * pPeerRgn = pConflict->pPeerRgn;

			pPeerRgn = pPeerRgn->GetActRootAfterNecessaryUpdating();
 			pConflict->pPeerRgn = pPeerRgn;

			if( pPeerRgn == a_pMaxSizRgn )
				return pConflict;

			RgnConflict * pNext = minConfList.Next();
			
			if( pPeerRgn->nLastVisitID == m_nVisitID )
				minConfList.RemovePtr( pConflict );

			pPeerRgn->nLastVisitID = m_nVisitID;

			pConflict = pNext;
		}

		return nullptr;
	}


	void RegionSegmentor52::RemoveDuplicateConflicts( RgnInfo * a_pRgn )
	{
		m_nVisitID++;

		//static int cnt1 = 0;
		//cnt1++;

		//if (2 == cnt1)
		//	cnt1 = cnt1;

		APtrList< RgnConflict > & confList = 
			a_pRgn->conflictList;

		RgnConflict * pConflict = confList.Last();

		while( nullptr != pConflict )
		{
			pConflict->pPeerRgn = pConflict->pPeerRgn->GetActRootAfterNecessaryUpdating();
			RgnInfo * pPeerRgn = pConflict->pPeerRgn;

			RgnConflict * pNext = confList.Next();
			
			if( pPeerRgn->nLastVisitID == m_nVisitID )
				confList.RemovePtr( pConflict );

			pPeerRgn->nLastVisitID = m_nVisitID;

			pConflict = pNext;
		}

		//Ncpp_ASSERT(confList.GetSize() > 0);
	}


	void RegionSegmentor52::PrepareRgnLinkActions( RgnInfo * a_pRgn )
	{
		// if( 122171 == a_pRgn->nIndex )
		// 	a_pRgn = a_pRgn;


		F32PixelLinkOwner3C & rPlo = m_ploAcc_1D[a_pRgn->nIndex];

		for (int j = 0; j < NOF_ALL_PIXEL_LINK_TYPES; j++)
		{
			F32PixelLink3C & rLink = rPlo.GetLinkAt((PixelLinkIndex)j);
			if (!rLink.Exists())
				continue;

			LinkAction_2 * pLA = m_linkAction_Provider->ProvideNewElementPtr();

			RgnInfo * pRgn_Peer;
			{
				const int ownerIndex_Peer = rLink.GetPeerOwnerPtr() - m_ploAcc_1D.GetData();
				pRgn_Peer = &m_rgnInfoVect[ownerIndex_Peer];
			}

			pLA->pRgn1 = a_pRgn;
			pLA->pRgn2 = pRgn_Peer;

			const float linkDiff = rLink.GetCoreSharedLinkPtr()->DiffMag;
			const int nQueIdx = (int)(linkDiff * m_difScale);

			m_linkActionMergeQues.PushPtr(nQueIdx , pLA);

		}	//	end for j.


	}


	void RegionSegmentor52::CreateConflict( const int a_rgnIndex1, const int a_rgnIndex2)
	{
		CreateConflict_Direct( &m_rgnInfoVect[a_rgnIndex1], &m_rgnInfoVect[a_rgnIndex2] );
	}

	void RegionSegmentor52::CreateConflict_Direct( RgnInfo * a_pRgn1, RgnInfo * a_pRgn2)
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

		if(!a_pRgn1->isInDirectConflict)
		{
			a_pRgn1->SetRootToSelf();
			PrepareRgnLinkActions(a_pRgn1);
			a_pRgn1->isInDirectConflict = true;
		}		
		
		if(!a_pRgn2->isInDirectConflict)
		{
			a_pRgn2->SetRootToSelf();
			PrepareRgnLinkActions(a_pRgn2);
			a_pRgn2->isInDirectConflict = true;
		}		

	}




//////////////////////////////////////////////////////////////







}