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



	PixelLinkType & PixelLinkTypes::GetAt(PixelLinkIndex a_index)
	{
		switch (a_index)
		{
		case PixelLinkIndex::RC:
			return PixelLinkTypes::RC;

		case PixelLinkIndex::RD:
			return PixelLinkTypes::RD;

		case PixelLinkIndex::CD:
			return PixelLinkTypes::CD;

		case PixelLinkIndex::LD:
			return PixelLinkTypes::LD;


		case PixelLinkIndex::LC:
			return PixelLinkTypes::LC;

		case PixelLinkIndex::LU:
			return PixelLinkTypes::LU;

		case PixelLinkIndex::CU:
			return PixelLinkTypes::CU;

		case PixelLinkIndex::RU:
			return PixelLinkTypes::RU;


		default:
			throw "Invalic case.";
		}
	}



}