#pragma once

#pragma inline_depth( 255 )

#include <stdlib.h>


#include <NovelCVLib\Common\Debug.h>
#include <NovelCVLib\Common\Object.h>

#include <NovelCVLib\OpenCV\ImageArrayHolderTypeDefs.h>

#include <NovelCVLib\Ncv\PixelLinkUtil.h>

#include <NovelCVLib\Ncv\F32PixelLink3C_Util.h>


namespace Ncv
{
	namespace F32PixelLink3C_Util
	{

		using namespace Ncpp;
		using namespace PixelLinkUtil;

		

		void TryPixelLinkStuff(F32ImageArrayHolder3C_Ref src_Img)
		{
			ArrayHolder_2D_Ref<F32PixelLinkOwner3C> pixelLinkOwnerHolder =
				PixelLinkUtil::GenPixelLinkOwnerHolder<F32PixelLinkOwner3C, F32ColorVal, F32PixelLink3C, F32SimpleCoreSharedPixelLink,
				F32CoreSharedPixelLink3C_DiffMagSimpleInitializer>(src_Img->AsHolderRef());
			//CoreSharedPixelLinkDiffMag_Initializer > (src_Img->AsHolderRef());



		}




	}

}