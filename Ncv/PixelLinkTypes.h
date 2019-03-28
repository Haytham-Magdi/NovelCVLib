#pragma once

#pragma inline_depth( 255 )

#include <stdlib.h>


#include <NovelCVLib\Common\Debug.h>
#include <NovelCVLib\Common\Object.h>

#include <NovelCVLib\Ncv\PixelLinkType.h>

namespace Ncv
{
	using namespace Ncpp;


    class PixelLinkTypes
    {
        public:
        
			static PixelLinkType RC;
			static PixelLinkType RD;
			static PixelLinkType CD;
			static PixelLinkType LD;

			static PixelLinkType LC;
			static PixelLinkType LU;
			static PixelLinkType CU;
			static PixelLinkType RU;

			static PixelLinkType & GetAt(PixelLinkIndex a_index);
    };







}