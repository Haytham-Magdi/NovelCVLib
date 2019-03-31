#pragma once

#pragma inline_depth( 255 )

#include <stdlib.h>


#include <NovelCVLib\Common\Debug.h>
#include <NovelCVLib\Common\Object.h>

#include <NovelCVLib\OpenCV\ImageArrayHolderTypeDefs.h>

#include <NovelCVLib\Ncv\F32PixelLink3C_Defs.h>
#include <NovelCVLib\Ncv\PixelLinkUtil.h>


namespace Ncv
{
	namespace F32PixelLink3C_Util
	{

		using namespace Ncpp;
		using namespace PixelLinkUtil;

		


		template<class F32PixelLinkOwner3C, class T_Elm, class T_PixelLink, class T_CoreSharedPixelLink >
		//void TryPixelLinkStuff(const ActualArrayAccessor_2D<F32ColorVal> & srcElmAcc)
		void TryPixelLinkStuff(F32ImageArrayHolder3C_Ref src_Img)
		{
			ArrayHolder_2D_Ref<F32PixelLinkOwner3C> pixelLinkOwnerHolder = 
				PixelLinkUtil::GenPixelLinkOwnerHolder<F32PixelLinkOwner3C, F32ColorVal, F32PixelLink3C, F32CoreSharedPixelLink3C,
				CoreSharedPixelLinkDiffMag_Initializer<F32PixelLinkOwner3C, F32ColorVal, F32PixelLink3C, F32CoreSharedPixelLink3C >> (src_Img->AsHolderRef());

		}


	}

}