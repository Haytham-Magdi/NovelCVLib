#pragma once

#pragma inline_depth( 255 )

#include <stdlib.h>


#include <NovelCVLib\Common\Debug.h>
#include <NovelCVLib\Common\Object.h>

#include <NovelCVLib\Ncpp\Common\StaticAllocVector.h>

#include <NovelCVLib\Ncv\F32PixelLink3C_Util.h>
#include <NovelCVLib\Ncv\SimplePixelRgn.h>

#include <NovelCVLib\Ncpp\Common\ExtendableMultiAllocPtrPool.h>

namespace Ncv
{
	using namespace Ncpp;

    class EdgeTrackingMgr2
    {
	public:

		class PixSpreadOp
		{

		public:

			int SrcPixIndex;

			StaticAllocVector<int, 15> FavourateFriendsArr;

		};


	private:

		class PixSpreadLink
		{
		public:

			void Init(int a_srcPixIndex, int a_peerPixIndex)
			{
				SrcPixIndex = a_srcPixIndex;
				PeerPixIndex = a_peerPixIndex;
			}

			int SrcPixIndex;
			int PeerPixIndex;
		};



    public:

		EdgeTrackingMgr2() 
		{

		}

		void Proceed(const ActualArrayAccessor_2D<F32PixelLinkOwner3C> & ploAcc,
			const ActualArrayAccessor_2D<SimplePixelRgn> pixelRgnAcc);



	private:



	private:

		ExtendableMultiAllocPtrPoolRef<EdgeTrackingMgr2::PixSpreadLink> m_spreadLinkPool;
		MultiAllocProviderRef<EdgeTrackingMgr2::PixSpreadOp> m_spreadOpProvider;

    };







}