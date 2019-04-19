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
		const ActualArrayAccessor_2D<SimplePixelRgn> pixelRgnAcc)
	{
		Ncpp_ASSERT(Size_2D::AreEqual(ploAcc.GetSize(), pixelRgnAcc.GetSize()));

		const ActualArrayAccessor_1D<SimplePixelRgn> pixelRgnAcc_1D = pixelRgnAcc.GenAcc_1D();

		const SimplePixelRgn * pixelRgnHeadPtr = pixelRgnAcc_1D.GetData();

		const ActualArrayAccessor_1D<F32PixelLinkOwner3C> ploAcc_1D = ploAcc.GenAcc_1D();
		const F32PixelLinkOwner3C * linkOwnerHeadPtr = ploAcc_1D.GetData();


		FixedVector<CommonMultiListQueMember<F32PixelLink3C>> queMemberVect(ploAcc_1D.GetSize() * NOF_PRIMARY_PIXEL_LINK_TYPES);

		for (int i = 0; i < ploAcc_1D.GetSize(); i++)
		{
			const F32PixelLinkOwner3C & rPlo = ploAcc_1D[i];

			for (int j = 0; j < NOF_PRIMARY_PIXEL_LINK_TYPES; j++)
			{
				F32PixelLink3C & rLink = rPlo.GetLinkAt((PixelLinkIndex)j);

				queMemberVect.IncSize();
				CommonMultiListQueMember<F32PixelLink3C> & rQueMember = queMemberVect.GetBack();
				rQueMember.pInner = &rLink;
			}
		}


		const int nQueScale = 10;

		MultiListQueMgr< CommonMultiListQueMember<F32PixelLink3C > > linkMngQues;
		linkMngQues.InitSize(700 * nQueScale + 2);

		for (int i = 0; i < queMemberVect.GetSize(); i++)
		{
			CommonMultiListQueMember<F32PixelLink3C> & rQueMember = queMemberVect[i];
			if (!rQueMember.pInner->Exists())
			{
				continue;
			}

			const int queIndex = rQueMember.pInner->GetCoreSharedLinkPtr()->DiffMag * nQueScale;
			linkMngQues.PushPtr(queIndex, &rQueMember);
		}





		//const float mergeThreshold = 3.0f;
		//const float mergeThreshold = 5.0f;
		const float mergeThreshold = 12.0f;
		//const float mergeThreshold = 18.0f;

		CommonMultiListQueMember<F32PixelLink3C> * pQueMember = nullptr;
		int nPushedCnt = 0;

		do
		{
			//pQueMember = linkMngQues.PopPtrMin();
			pQueMember = linkMngQues.PopPtrMax();
			if (nullptr == pQueMember)
			{
				continue;
			}

			nPushedCnt++;


			F32PixelLink3C & rMainLink = *pQueMember->pInner;
			Ncpp_ASSERT(rMainLink.Exists());

			//if (!rMainLink.Exists())
			//{
			//	continue;
			//}

			rMainLink.GetCoreSharedLinkPtr()->IsProcessed = true;

			const int ownerIndex1 = rMainLink.GetOwnerPtr() - linkOwnerHeadPtr;
			const int ownerIndex2 = rMainLink.GetPeerOwnerPtr() - linkOwnerHeadPtr;

			SimplePixelRgn & rRgn1 = pixelRgnAcc_1D[ownerIndex1];
			SimplePixelRgn & rRgn2 = pixelRgnAcc_1D[ownerIndex2];

			if (SimplePixelRgn::DoBothRgnsHaveTheSameRoot(rRgn1, rRgn2))
			{
				continue;
			}

			Ncpp_ASSERT(!SimplePixelRgn::DoBothRgnsHaveTheSameRoot(rRgn1, rRgn2));

			const F32PixelLinkOwner3C & rMainLinkOwner = *rMainLink.GetOwnerPtr();
			const F32PixelLinkOwner3C & rMainLinkPeerOwner = *rMainLink.GetPeerOwnerPtr();

			const float mainLinkDiffMag = rMainLink.GetCoreSharedLinkPtr()->DiffMag;

			Ncpp_ASSERT(!SimplePixelRgn::DoBothRgnsHaveTheSameRoot(rRgn1, rRgn2));

			for (int i = 0; i < NOF_ALL_PIXEL_LINK_TYPES; i++)
			{
				Ncpp_ASSERT(!SimplePixelRgn::DoBothRgnsHaveTheSameRoot(rRgn1, rRgn2));

				F32PixelLink3C & rOwnerSideLink = rMainLinkOwner.GetLinkAt((PixelLinkIndex)i);

				if (!rOwnerSideLink.Exists())
				{
					continue;
				}

				if (rOwnerSideLink.GetCoreSharedLinkPtr() == rMainLink.GetCoreSharedLinkPtr())
				{
					continue;
				}
				Ncpp_ASSERT(rOwnerSideLink.GetPeerOwnerPtr() != &rMainLinkPeerOwner);

				if (!rOwnerSideLink.GetCoreSharedLinkPtr()->IsProcessed)
				{
					continue;
				}

				const float ownerLinkDiffMag = rOwnerSideLink.GetCoreSharedLinkPtr()->DiffMag;


				for (int j = 0; j < NOF_ALL_PIXEL_LINK_TYPES; j++)
				{
					Ncpp_ASSERT(!SimplePixelRgn::DoBothRgnsHaveTheSameRoot(rRgn1, rRgn2));

					F32PixelLink3C & rPeerOwnerSideLink = rMainLinkPeerOwner.GetLinkAt((PixelLinkIndex)j);

					if (!rPeerOwnerSideLink.Exists())
					{
						continue;
					}

					if (rPeerOwnerSideLink.GetCoreSharedLinkPtr() == rMainLink.GetCoreSharedLinkPtr())
					{
						continue;
					}
					Ncpp_ASSERT(rPeerOwnerSideLink.GetPeerOwnerPtr() != &rMainLinkOwner);

					if (!rPeerOwnerSideLink.GetCoreSharedLinkPtr()->IsProcessed)
					{
						continue;
					}



					if (rOwnerSideLink.GetPeerOwnerPtr() == rPeerOwnerSideLink.GetPeerOwnerPtr())
					{
						const float peerOwnerLinkDiffMag = rPeerOwnerSideLink.GetCoreSharedLinkPtr()->DiffMag;

						//const float maxCmpRatio = 0.25f;
						const float maxCmpRatio = 0.4f;

						if (
							//mainLinkDiffMag > 17 &&
							ownerLinkDiffMag > 17 &&
							(mainLinkDiffMag / ownerLinkDiffMag) < maxCmpRatio &&

							peerOwnerLinkDiffMag > 17 &&
							(mainLinkDiffMag / peerOwnerLinkDiffMag) < maxCmpRatio
							)
						{
							Ncpp_ASSERT(!SimplePixelRgn::DoBothRgnsHaveTheSameRoot(rRgn1, rRgn2));

							SimplePixelRgn::MergeRgns(rRgn1, rRgn2);
							
							//break;
							goto Outer_While_End;
						}

					}

				}	//	end j for.

			}	//	end i for.





			//const float mainLinkDiffMag = rLink.GetCoreSharedLinkPtr()->DiffMag;
			//if (mainLinkDiffMag > mergeThreshold)
			//{
			//	continue;
			//}

			//SimplePixelRgn::MergeRgns(rRgn1, rRgn2);

		Outer_While_End:
			;

		} while (nullptr != pQueMember);






		//for (int i = 0; i < ploAcc_1D.GetSize(); i++)
		//{
		//	F32PixelLinkOwner3C & rPlo = ploAcc_1D[i];

		//	for (int j = 0; j < NOF_PRIMARY_PIXEL_LINK_TYPES; j++)
		//	{
		//		F32PixelLink3C & rLink = rPlo.GetLinkAt((PixelLinkIndex)j);
		//		if (!rLink.Exists())
		//		{
		//			continue;
		//		}


		//		const int ownerIndex1 = rLink.GetOwnerPtr() - linkOwnerHeadPtr;
		//		const int ownerIndex2 = rLink.GetPeerOwnerPtr() - linkOwnerHeadPtr;

		//		SimplePixelRgn & rRgn1 = pixelRgnAcc_1D[ownerIndex1];
		//		SimplePixelRgn & rRgn2 = pixelRgnAcc_1D[ownerIndex2];

		//		if (SimplePixelRgn::DoBothRgnsHaveTheSameRoot(rRgn1, rRgn2))
		//		{
		//			continue;
		//		}

		//		const float mainLinkDiffMag = rLink.GetCoreSharedLinkPtr()->DiffMag;
		//		if (mainLinkDiffMag > mergeThreshold)
		//		{
		//			continue;
		//		}

		//		SimplePixelRgn::MergeRgns(rRgn1, rRgn2);

		//	}	//	end j for.

		//}	//	end i for.


	}



}