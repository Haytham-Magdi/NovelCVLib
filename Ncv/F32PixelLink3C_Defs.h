#pragma once

#pragma inline_depth( 255 )

#include <stdlib.h>


#include <NovelCVLib\Common\Debug.h>
#include <NovelCVLib\Common\Object.h>

#include <NovelCVLib\Ncv\PixelLinkOwner.h>

namespace Ncv
{
	using namespace Ncpp;

	//class F32PixelLink3C;
	class F32PixelLinkOwner3C;


	class F32CoreSharedPixelLink3C
	{
	public:

		float DiffMag;
	};


	class F32PixelLink3C : public PixelLink<F32PixelLinkOwner3C, F32CoreSharedPixelLink3C>
	{

	};


	//class F32PixelLinkOwner3C : public PixelLinkOwner<F32PixelLinkOwner3C, F32ColorVal, F32PixelLink3C>
	class F32PixelLinkOwner3C : public PixelLinkOwner<F32ColorVal, F32PixelLink3C, F32CoreSharedPixelLink3C>
	{


	};


	//typedef PixelLinkOwner<F32ColorVal> F32PixelLinkOwner3C;



}