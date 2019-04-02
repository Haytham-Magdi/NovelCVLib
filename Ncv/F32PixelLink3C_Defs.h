#pragma once

#pragma inline_depth( 255 )

#include <stdlib.h>


#include <NovelCVLib\Common\Debug.h>
#include <NovelCVLib\Common\Object.h>

#include <NovelCVLib\Ncv\PixelLinkOwner.h>
#include <NovelCVLib\Ncv\CoreSharedPixelLinkDiffMag_Initializer.h>
#include <NovelCVLib\Ncv\F32SimpleCoreSharedPixelLink.h>



namespace Ncv
{
	using namespace Ncpp;

	//class F32PixelLink3C;
	class F32PixelLinkOwner3C;



	typedef PixelLink<F32PixelLinkOwner3C, F32SimpleCoreSharedPixelLink> F32PixelLink3C;

	//class F32PixelLink3C : public PixelLink<F32PixelLinkOwner3C, F32SimpleCoreSharedPixelLink>
	//{

	//};


	class F32PixelLinkOwner3C : public PixelLinkOwner<F32ColorVal, F32PixelLink3C, F32SimpleCoreSharedPixelLink>
	{


	};


	//typedef PixelLinkOwner<F32ColorVal, F32PixelLink3C, F32SimpleCoreSharedPixelLink> F32PixelLinkOwner3C;



	typedef CoreSharedPixelLinkDiffMag_Initializer<F32PixelLinkOwner3C, F32ColorVal, F32PixelLink3C, F32SimpleCoreSharedPixelLink > F32CoreSharedPixelLink3C_DiffMagSimpleInitializer;


}