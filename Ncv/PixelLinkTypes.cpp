#pragma once

#pragma inline_depth( 255 )

#include <stdlib.h>


#include <NovelCVLib\Common\Debug.h>
#include <NovelCVLib\Common\Object.h>

#include <NovelCVLib\Ncv\PixelLinkTypes.h>

namespace Ncv
{
	using namespace Ncpp;

	PixelLinkType PixelLinkTypes::RC(PixelLinkIndex::RC, 1, 0);
	PixelLinkType PixelLinkTypes::RD(PixelLinkIndex::RD, 1, 1);
	PixelLinkType PixelLinkTypes::CD(PixelLinkIndex::CD, 0, 1);
	PixelLinkType PixelLinkTypes::LD(PixelLinkIndex::LD, -1, 1);

	PixelLinkType PixelLinkTypes::LC(PixelLinkIndex::LC, -1, 0);
	PixelLinkType PixelLinkTypes::LU(PixelLinkIndex::LU, -1, -1);
	PixelLinkType PixelLinkTypes::CU(PixelLinkIndex::CU, 0, -1);
	PixelLinkType PixelLinkTypes::RU(PixelLinkIndex::RU, 1, -1);

}