#pragma once

#pragma inline_depth( 255 )

#include <stdlib.h>


#include <NovelCVLib\Common\Debug.h>
#include <NovelCVLib\Common\Object.h>

#include <NovelCVLib\Ncv\PixelLinkOwner.h>

namespace Ncv
{
	using namespace Ncpp;

	//class F32PixelLinkEx;
	class F32PixelLinkOwner3C;

	class F32PixelLinkEx : public PixelLink<F32PixelLinkOwner3C>
	{


	};


	//class F32PixelLinkOwner3C : public PixelLinkOwner<F32PixelLinkOwner3C, F32ColorVal, F32PixelLinkEx>
	class F32PixelLinkOwner3C : public PixelLinkOwner<F32ColorVal, F32PixelLinkEx>
	{


	};


	//typedef PixelLinkOwner<F32ColorVal> F32PixelLinkOwner3C;



}