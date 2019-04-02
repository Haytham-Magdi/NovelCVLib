#pragma once

#pragma inline_depth( 255 )

#include <stdlib.h>


#include <NovelCVLib\Common\Debug.h>
#include <NovelCVLib\Common\Object.h>

#include <NovelCVLib\OpenCV\ImageArrayHolderTypeDefs.h>


//#include <NovelCVLib\Ncv\F32PixelLink3C_Defs.h>
#include <NovelCVLib\Ncv\CoreSharedPixelLinkDiffMag_Initializer.h>


namespace Ncv
{
	namespace PixelLinkUtil
	{

		using namespace Ncpp;



		template<class T_PixelLinkOwner, class T_Elm, class T_PixelLink, class T_CoreSharedPixelLink, class T_CoreSharedPixelLinkInitializer >
		void InitPixelLinksForOwnerOnImgFrame(int x, int y,
			const ActualArrayAccessor_2D<T_PixelLinkOwner> & ploAcc, Size_2D & imgSize)
		{
			F32Point pnt(x, y);
			T_PixelLinkOwner & rPlo = ploAcc.GetAt(x, y);

			for (int i = 0; i < NOF_PRIMARY_PIXEL_LINK_TYPES; i++)
			{
				const PixelLinkIndex linkIndex = (PixelLinkIndex)i;

				PixelLinkType & plType = PixelLinkTypes::GetAt(linkIndex);
				PixelLinkType & plPeerType = PixelLinkTypes::GetAt(plType.GetReverseIndex());

				S32Point shiftedPnt(x + plType.GetShiftX(), y + plType.GetShiftY());
				const bool isShiftedPntInSize = shiftedPnt.IsInSize(imgSize);

				if (isShiftedPntInSize)
				{
					T_PixelLinkOwner & rPeerPlo = ploAcc.GetAt(shiftedPnt.GetX(), shiftedPnt.GetY());

					T_CoreSharedPixelLink & rCoreSharedLink = rPlo.GetCoreSharedLinkAt(plType.GetIndex());

					T_PixelLink & rLink = rPlo.GetLinkAt(plType.GetIndex());
					rLink.Init(&plType, &rPlo, &rPeerPlo, &rCoreSharedLink, true);
					//CoreSharedPixelLinkDiffMag_Initializer<T_PixelLinkOwner, T_Elm, T_PixelLink, T_CoreSharedPixelLink>::InitCoreLink(rLink);
					T_CoreSharedPixelLinkInitializer::InitCoreLink(rLink);
					//T_CoreSharedPixelLinkInitializer<T_PixelLinkOwner, T_Elm, T_PixelLink, T_CoreSharedPixelLink>::InitCoreLink(rLink);

					T_PixelLink & rPeerReverseLink = rPeerPlo.GetLinkAt(plType.GetReverseIndex());
					rPeerReverseLink.Init(&plPeerType, &rPeerPlo, &rPlo, &rCoreSharedLink, true);
				}
				else
				{
					T_PixelLink & rLink = rPlo.GetLinkAt(plType.GetIndex());
					rLink.Init(&plType, &rPlo, nullptr, nullptr, false);
				}

			}	//	end Primary Index for	


			for (int i = NOF_PRIMARY_PIXEL_LINK_TYPES; i < NOF_ALL_PIXEL_LINK_TYPES; i++)
			{
				const PixelLinkIndex linkIndex = (PixelLinkIndex)i;

				PixelLinkType & plType = PixelLinkTypes::GetAt(linkIndex);

				S32Point shiftedPnt(x + plType.GetShiftX(), y + plType.GetShiftY());
				const bool isShiftedPntInSize = shiftedPnt.IsInSize(imgSize);

				if (!isShiftedPntInSize)
				{
					T_PixelLink & rLink = rPlo.GetLinkAt(plType.GetIndex());
					rLink.Init(&plType, &rPlo, nullptr, nullptr, false);
				}

			}	//	end Reverse Index for	

		}



		template<class T_PixelLinkOwner, class T_Elm, class T_PixelLink, class T_CoreSharedPixelLink, class T_CoreSharedPixelLinkInitializer >
		//void TryPixelLinkStuff(F32ImageArrayHolder3C_Ref a_srcHolder)
		//ArrayHolder_2D_Ref<T_PixelLinkOwner> TryPixelLinkStuff(ArrayHolder_2D_Ref<T_Elm> a_srcHolder)
		ArrayHolder_2D_Ref<T_PixelLinkOwner> GenPixelLinkOwnerHolder(ArrayHolder_2D_Ref<T_Elm> a_srcHolder)
		{
			//ArrayHolder_2D_Ref<T_PixelLinkOwner> pixelLinkOwnerHolder =
			//	ArrayHolderUtil::CreateEmptyFrom<T_PixelLinkOwner>(a_srcHolder->AsHolderRef());

			ArrayHolder_2D_Ref<T_PixelLinkOwner> pixelLinkOwnerHolder = ArrayHolderUtil::CreateEmptyFrom<T_PixelLinkOwner>(a_srcHolder);

			const ActualArrayAccessor_2D<T_PixelLinkOwner> & ploAcc = pixelLinkOwnerHolder->GetActualAccessor();

			{
				const ActualArrayAccessor_2D<T_Elm> srcElmAcc = a_srcHolder->GetActualAccessor();
				Ncpp_ASSERT(Size_2D::AreEqual(ploAcc.GetSize(), srcElmAcc.GetSize()));

				{
					const ActualArrayAccessor_1D<T_PixelLinkOwner> ploAcc_1D = ploAcc.GenAcc_1D();
					const ActualArrayAccessor_1D<T_Elm> orgElmAcc_1D = srcElmAcc.GenAcc_1D();

					for (int i = 0; i < ploAcc_1D.GetSize(); i++)
					{
						T_Elm & rOrgElm = orgElmAcc_1D[i];
						T_PixelLinkOwner & rPloElm = ploAcc_1D[i];

						rPloElm.SetElm(&rOrgElm);
					}
				}
			}

			Size_2D imgSize = ploAcc.GetSize();

			{

				for (int y = 0, x = 0; x < ploAcc.GetSize_X(); x++)
				{
					InitPixelLinksForOwnerOnImgFrame<T_PixelLinkOwner, T_Elm, T_PixelLink, T_CoreSharedPixelLink, T_CoreSharedPixelLinkInitializer>(x, y, ploAcc, imgSize);
				}

				for (int y = ploAcc.GetSize_Y() - 1, x = 0; x < ploAcc.GetSize_X(); x++)
				{
					InitPixelLinksForOwnerOnImgFrame<T_PixelLinkOwner, T_Elm, T_PixelLink, T_CoreSharedPixelLink, T_CoreSharedPixelLinkInitializer>(x, y, ploAcc, imgSize);
				}

				for (int y = 0, x = 0; y < ploAcc.GetSize_Y(); y++)
				{
					InitPixelLinksForOwnerOnImgFrame<T_PixelLinkOwner, T_Elm, T_PixelLink, T_CoreSharedPixelLink, T_CoreSharedPixelLinkInitializer>(x, y, ploAcc, imgSize);
				}

				for (int y = 0, x = ploAcc.GetSize_X() - 1; y < ploAcc.GetSize_Y(); y++)
				{
					InitPixelLinksForOwnerOnImgFrame<T_PixelLinkOwner, T_Elm, T_PixelLink, T_CoreSharedPixelLink, T_CoreSharedPixelLinkInitializer>(x, y, ploAcc, imgSize);
				}

			}	//	end of Frame pixels stuff.


			for (int y = 1; y < ploAcc.GetSize_Y() - 1; y++)
			{
				for (int x = 1; x < ploAcc.GetSize_X() - 1; x++)
				{
					T_PixelLinkOwner & rPlo = ploAcc.GetAt(x, y);

					for (int i = 0; i < NOF_PRIMARY_PIXEL_LINK_TYPES; i++)
					{
						const PixelLinkIndex linkIndex = (PixelLinkIndex)i;

						PixelLinkType & plType = PixelLinkTypes::GetAt(linkIndex);
						PixelLinkType & plPeerType = PixelLinkTypes::GetAt(plType.GetReverseIndex());

						T_CoreSharedPixelLink & rCoreSharedLink = rPlo.GetCoreSharedLinkAt(plType.GetIndex());

						const int shiftedX = x + plType.GetShiftX();
						const int shiftedY = y + plType.GetShiftY();

						Ncpp_ASSERT(S32Point(shiftedX, shiftedY).IsInSize(imgSize));

						T_PixelLinkOwner & rPeerPlo = ploAcc.GetAt(shiftedX, shiftedY);

						T_PixelLink & rLink = rPlo.GetLinkAt(plType.GetIndex());
						rLink.Init(&plType, &rPlo, &rPeerPlo, &rCoreSharedLink, true);
						T_CoreSharedPixelLinkInitializer::InitCoreLink(rLink);

						T_PixelLink & rPeerReverseLink = rPeerPlo.GetLinkAt(plType.GetReverseIndex());
						rPeerReverseLink.Init(&plPeerType, &rPeerPlo, &rPlo, &rCoreSharedLink, true);

					}	//	end Index for	

				}	//	end X for.
			}	//	end Y for.

			return pixelLinkOwnerHolder;
		}

	}

}