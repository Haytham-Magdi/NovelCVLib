#pragma once

#pragma inline_depth( 255 )

#include <stdlib.h>


#include <NovelCVLib\Common\Debug.h>
#include <NovelCVLib\Common\Object.h>

#include <NovelCVLib\Ncv\PixelLinkOwner.h>

namespace Ncv
{
	using namespace Ncpp;

	class PixelLinkEx;

	class F32PixelLinkOwner3C : public PixelLinkOwner<F32PixelLinkOwner3C, F32ColorVal, PixelLinkEx>
	{


	};


	class PixelLinkEx : public PixelLink<F32PixelLinkOwner3C>
	{


	};




	//typedef PixelLinkOwner<F32ColorVal> F32PixelLinkOwner3C;





}