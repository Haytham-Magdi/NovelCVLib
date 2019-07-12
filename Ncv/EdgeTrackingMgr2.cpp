#pragma once

#pragma inline_depth( 255 )

#include <stdlib.h>


#include <NovelCVLib\Common\Debug.h>
#include <NovelCVLib\Common\Object.h>
#include <NovelCVLib\Ncpp\Common\CommonMultiListQueMember.h>

#include <NovelCVLib\Ncv\EdgeTrackingMgr2.h>



namespace Ncv
{
	using namespace Ncpp;



	void EdgeTrackingMgr2::Proceed(const ActualArrayAccessor_2D<F32PixelLinkOwner3C> & ploAcc,
		const ActualArrayAccessor_2D<F32ColorVal> valuesAcc)
	{
		Ncpp_ASSERT(Size_2D::AreEqual(ploAcc.GetSize(), valuesAcc.GetSize()));

		m_spreadOpProvider = new MultiAllocProvider<EdgeTrackingMgr2::PixSpreadOp>(ploAcc.CalcSize_1D());
		m_spreadLinkPool = new ExtendableMultiAllocPtrPool<EdgeTrackingMgr2::PixSpreadLink>(ploAcc.CalcSize_1D() * 10);

		//m_spreadOpProvider = new MultiAllocProvider<EdgeTrackingMgr2::PixSpreadOp>(ploAcc.CalcSize_1D() / 3);
		//m_spreadLinkPool = new ExtendableMultiAllocPtrPool<EdgeTrackingMgr2::PixSpreadLink>(ploAcc.CalcSize_1D());



		const ActualArrayAccessor_1D<F32ColorVal> valuesAcc_1D = valuesAcc.GenAcc_1D();

		//const SimplePixelRgn * pixelRgnHeadPtr = pixelRgnAcc_1D.GetData();

		const ActualArrayAccessor_1D<F32PixelLinkOwner3C> ploAcc_1D = ploAcc.GenAcc_1D();
		const F32PixelLinkOwner3C * linkOwnerHeadPtr = ploAcc_1D.GetData();


		//FixedVector<CommonMultiListQueMember<F32PixelLink3C>> queMemberVect(ploAcc_1D.GetSize() * NOF_PRIMARY_PIXEL_LINK_TYPES);

		const int nQueScale = 10;

		MultiListQueMgr< PixSpreadLink > linkMngQues;
		linkMngQues.InitSize(700 * nQueScale + 2);


		for (int i = 0; i < ploAcc_1D.GetSize(); i++)
		{
			const F32PixelLinkOwner3C & rPlo = ploAcc_1D[i];

			PixSpreadOp * pSpreadOp = m_spreadOpProvider->ProvideNewElementPtr();
			pSpreadOp->Init(i);


			for (int j = 0; j < NOF_ALL_PIXEL_LINK_TYPES; j++)
			{
				F32PixelLink3C & rLink = rPlo.GetLinkAt((PixelLinkIndex)j);

				if (!rLink.Exists())
				{
					continue;
				}

				PixSpreadLink * pSpreadLink = m_spreadLinkPool->ProvidePtr();

				const int peerIndex = rLink.GetPeerOwnerPtr() - linkOwnerHeadPtr;

				pSpreadLink->Init(i, peerIndex, pSpreadOp);

				F32ColorVal & rSrcVal = valuesAcc_1D[i];
				F32ColorVal & rPeerVal = valuesAcc_1D[peerIndex];

				const float valDiff = CalcSubtractionMag(rSrcVal, rPeerVal);

				const int queIndex = valDiff * nQueScale;
				linkMngQues.PushPtr(queIndex, pSpreadLink);
			}
		}	//	end Init Ques for.


		PixSpreadLink * pSpreadLink = nullptr;
		int nPushedCnt = 0;

		do
		{
			pSpreadLink = linkMngQues.PopPtrMin();
			if (nullptr == pSpreadLink)
			{
				continue;
			}

			nPushedCnt++;

			if (pSpreadLink->GetSpreadOp()->AreFriendsComplete())
			{
				goto SPREAD_LINK_DONE;
			}

			const int opSrcIndex = pSpreadLink->GetOpSrcPixIndex();

			const int peerIndex = pSpreadLink->GetPeerPixIndex();
			Ncpp_ASSERT(peerIndex != opSrcIndex);

			//if (peerIndex == opSrcIndex)
			//{
			//	goto SPREAD_LINK_DONE;
			//}

			FixedCapacityVectorAccessor<int> & rFriendsArr = pSpreadLink->GetSpreadOp()->FavourateFriendsVectorAcc;

			{
				//FixedCapacityVectorAccessor<int> & rFriendsArr = pSpreadLink->GetSpreadOp()->FavourateFriendsVectorAcc;
				for (int j = 0; j < rFriendsArr.GetSize(); j++)
				{
					if (peerIndex == rFriendsArr[j])
					{
						goto SPREAD_LINK_DONE;
					}
				}
			}



			const F32ColorVal & rOpSrcVal = valuesAcc_1D[pSpreadLink->GetOpSrcPixIndex()];

			const F32PixelLinkOwner3C & rPeerPlo1 = ploAcc_1D[pSpreadLink->GetPeerPixIndex()];

			for (int i = 0; i < NOF_ALL_PIXEL_LINK_TYPES; i++)
			{
				F32PixelLink3C & rPeerSideLink = rPeerPlo1.GetLinkAt((PixelLinkIndex)i);

				if (!rPeerSideLink.Exists())
				{
					continue;
				}

				const int sidePeerIndex = rPeerSideLink.GetPeerOwnerPtr() - linkOwnerHeadPtr;

				if (sidePeerIndex == opSrcIndex)
				{
					continue;
				}

				{
					//FixedCapacityVectorAccessor<int> & rFriendsArr = pSpreadLink->GetSpreadOp()->FavourateFriendsVectorAcc;
					for (int j = 0; j < rFriendsArr.GetSize(); j++)
					{
						if (sidePeerIndex == rFriendsArr[j])
						{
							goto END_SIDE_PEER_FOR;
						}
					}
				}


				const F32ColorVal & rSidePeerVal = valuesAcc_1D[sidePeerIndex];
				const float valDiff = CalcSubtractionMag(rOpSrcVal, rSidePeerVal);

				PixSpreadLink * pSideSpreadLink = m_spreadLinkPool->ProvidePtr();
				pSideSpreadLink->Init(opSrcIndex, sidePeerIndex, pSpreadLink->GetSpreadOp());

				const int queIndex = valDiff * nQueScale;
				linkMngQues.PushPtr(queIndex, pSideSpreadLink);

			END_SIDE_PEER_FOR:
				continue;

			}	//	end Side Peer for.

			rFriendsArr.PushBack(peerIndex);


		SPREAD_LINK_DONE:
			
			m_spreadLinkPool->TakePtrBack(pSpreadLink);


		} while (nullptr != pSpreadLink);




		////const float mergeThreshold = 3.0f;
		////const float mergeThreshold = 5.0f;
		//const float mergeThreshold = 12.0f;
		////const float mergeThreshold = 18.0f;

		//CommonMultiListQueMember<F32PixelLink3C> * pQueMember = nullptr;
		//int nPushedCnt = 0;

		//do
		//{
		//	//pQueMember = linkMngQues.PopPtrMin();
		//	pQueMember = linkMngQues.PopPtrMax();
		//	if (nullptr == pQueMember)
		//	{
		//		continue;
		//	}

		//	nPushedCnt++;


		//	F32PixelLink3C & rMainLink = *pQueMember->pInner;
		//	Ncpp_ASSERT(rMainLink.Exists());

		//	//if (!rMainLink.Exists())
		//	//{
		//	//	continue;
		//	//}

		//	rMainLink.GetCoreSharedLinkPtr()->IsProcessed = true;

		//	const int ownerIndex1 = rMainLink.GetOwnerPtr() - linkOwnerHeadPtr;
		//	const int ownerIndex2 = rMainLink.GetPeerOwnerPtr() - linkOwnerHeadPtr;

		//	//SimplePixelRgn & rRgn1 = pixelRgnAcc_1D[ownerIndex1];
		//	//SimplePixelRgn & rRgn2 = pixelRgnAcc_1D[ownerIndex2];

		//	//if (SimplePixelRgn::DoBothRgnsHaveTheSameRoot(rRgn1, rRgn2))
		//	//{
		//	//	continue;
		//	//}

		//	//Ncpp_ASSERT(!SimplePixelRgn::DoBothRgnsHaveTheSameRoot(rRgn1, rRgn2));

		//	const F32PixelLinkOwner3C & rMainLinkOwner = *rMainLink.GetOwnerPtr();
		//	const F32PixelLinkOwner3C & rMainLinkPeerOwner = *rMainLink.GetPeerOwnerPtr();

		//	const float mainLinkDiffMag = rMainLink.GetCoreSharedLinkPtr()->DiffMag;

		//	Ncpp_ASSERT(!SimplePixelRgn::DoBothRgnsHaveTheSameRoot(rRgn1, rRgn2));

		//	for (int i = 0; i < NOF_ALL_PIXEL_LINK_TYPES; i++)
		//	{
		//		Ncpp_ASSERT(!SimplePixelRgn::DoBothRgnsHaveTheSameRoot(rRgn1, rRgn2));

		//		F32PixelLink3C & rOwnerSideLink = rMainLinkOwner.GetLinkAt((PixelLinkIndex)i);

		//		if (!rOwnerSideLink.Exists())
		//		{
		//			continue;
		//		}

		//		if (rOwnerSideLink.GetCoreSharedLinkPtr() == rMainLink.GetCoreSharedLinkPtr())
		//		{
		//			continue;
		//		}
		//		Ncpp_ASSERT(rOwnerSideLink.GetPeerOwnerPtr() != &rMainLinkPeerOwner);

		//		if (!rOwnerSideLink.GetCoreSharedLinkPtr()->IsProcessed)
		//		{
		//			continue;
		//		}

		//		const float ownerLinkDiffMag = rOwnerSideLink.GetCoreSharedLinkPtr()->DiffMag;


		//		for (int j = 0; j < NOF_ALL_PIXEL_LINK_TYPES; j++)
		//		{
		//			Ncpp_ASSERT(!SimplePixelRgn::DoBothRgnsHaveTheSameRoot(rRgn1, rRgn2));

		//			F32PixelLink3C & rPeerOwnerSideLink = rMainLinkPeerOwner.GetLinkAt((PixelLinkIndex)j);

		//			if (!rPeerOwnerSideLink.Exists())
		//			{
		//				continue;
		//			}

		//			if (rPeerOwnerSideLink.GetCoreSharedLinkPtr() == rMainLink.GetCoreSharedLinkPtr())
		//			{
		//				continue;
		//			}
		//			Ncpp_ASSERT(rPeerOwnerSideLink.GetPeerOwnerPtr() != &rMainLinkOwner);

		//			if (!rPeerOwnerSideLink.GetCoreSharedLinkPtr()->IsProcessed)
		//			{
		//				continue;
		//			}



		//			if (rOwnerSideLink.GetPeerOwnerPtr() == rPeerOwnerSideLink.GetPeerOwnerPtr())
		//			{
		//				const float peerOwnerLinkDiffMag = rPeerOwnerSideLink.GetCoreSharedLinkPtr()->DiffMag;

		//				//const float maxCmpRatio = 0.25f;
		//				const float maxCmpRatio = 0.4f;

		//				if (
		//					//mainLinkDiffMag > 17 &&
		//					ownerLinkDiffMag > 17 &&
		//					(mainLinkDiffMag / ownerLinkDiffMag) < maxCmpRatio &&

		//					peerOwnerLinkDiffMag > 17 &&
		//					(mainLinkDiffMag / peerOwnerLinkDiffMag) < maxCmpRatio
		//					)
		//				{
		//					Ncpp_ASSERT(!SimplePixelRgn::DoBothRgnsHaveTheSameRoot(rRgn1, rRgn2));

		//					SimplePixelRgn::MergeRgns(rRgn1, rRgn2);
		//					
		//					//break;
		//					goto Outer_While_End;
		//				}

		//			}

		//		}	//	end j for.

		//	}	//	end i for.





		//	//const float mainLinkDiffMag = rLink.GetCoreSharedLinkPtr()->DiffMag;
		//	//if (mainLinkDiffMag > mergeThreshold)
		//	//{
		//	//	continue;
		//	//}

		//	//SimplePixelRgn::MergeRgns(rRgn1, rRgn2);

		//Outer_While_End:
		//	;

		//} while (nullptr != pQueMember);




	}



}