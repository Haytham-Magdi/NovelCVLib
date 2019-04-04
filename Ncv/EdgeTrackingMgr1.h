#pragma once

#pragma inline_depth( 255 )

#include <stdlib.h>


#include <NovelCVLib\Common\Debug.h>
#include <NovelCVLib\Common\Object.h>

#include <NovelCVLib\Ncv\F32PixelLink3C_Util.h>

#include <NovelCVLib\Ncv\SimplePixelRgn.h>


namespace Ncv
{
	using namespace Ncpp;

	//template<class T_PixelRgnEx>
    class EdgeTrackingMgr1
    {
        public:

			EdgeTrackingMgr1() 
			{

			}

			void Proceed(const ActualArrayAccessor_2D<F32PixelLinkOwner3C> & ploAcc,
				const ActualArrayAccessor_2D<SimplePixelRgn> pixelRgnAcc);



	private:



	private:


    };







}