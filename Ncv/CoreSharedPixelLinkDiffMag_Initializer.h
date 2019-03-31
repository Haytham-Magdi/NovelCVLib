#pragma once

#pragma inline_depth( 255 )

#include <stdlib.h>


#include <NovelCVLib\Common\Debug.h>
#include <NovelCVLib\Common\Object.h>

//#include <NovelCVLib\OpenCV\ImageArrayHolderTypeDefs.h>

//#include <NovelCVLib\Ncv\F32PixelLink3C_Defs.h>


namespace Ncv
{
	namespace PixelLinkUtil
	{

		using namespace Ncpp;


		template<class T_PixelLinkOwner, class T_Elm, class T_PixelLink, class T_CoreSharedPixelLink>
		class CoreSharedPixelLinkDiffMag_Initializer
		{
		public:

			static void InitCoreLink(T_PixelLink & a_primaryLink)
			{
				Ncpp_ASSERT(a_primaryLink.IsPrimary());

				T_CoreSharedPixelLink * pCoreLink = a_primaryLink.GetCoreSharedLink();
				T_PixelLinkOwner * pLinkOwner = a_primaryLink.GetOwnerPtr();
				T_PixelLinkOwner * pLinkPeerOwner = a_primaryLink.GetPeerOwnerPtr();

				T_Elm tmpElm;
				Subtract(*pLinkOwner->GetElmPtr(), *pLinkPeerOwner->GetElmPtr(), &tmpElm);
				Assign(&pCoreLink->DiffMag, CalcMag(tmpElm));
			}


		};


	}

}