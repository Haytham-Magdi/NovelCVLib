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

			void Init(int a_srcPixIndex)
			{
				m_srcPixIndex = a_srcPixIndex;
			}

			int GetSrcPixIndex() { return m_srcPixIndex; }

			StaticAllocVector<int, 15> FavourateFriendsArr;

			bool AreFriendsComplete()
			{
				return !FavourateFriendsArr.HasFreeCapacity();
			}

		private:
			
			int m_srcPixIndex;
		};


	private:


		class PixSpreadLink : public MultiListQueMember< PixSpreadLink >
		{
		public:

			void Init(int a_srcPixIndex, int a_peerPixIndex, PixSpreadOp * a_pSpreadOp)
			{
				//m_srcPixIndex = a_srcPixIndex;
				m_peerPixIndex = a_peerPixIndex;

				m_pSpreadOp = a_pSpreadOp;
			}

		public:

			//int GetSrcPixIndex() { return m_srcPixIndex; }

			int GetPeerPixIndex() { return m_peerPixIndex; }

			PixSpreadOp * GetSpreadOp() { return m_pSpreadOp; }

			int GetOpSrcPixIndex() { return GetSpreadOp()->GetSrcPixIndex(); }


		private:

			//int m_srcPixIndex;
			int m_peerPixIndex;
			
			PixSpreadOp * m_pSpreadOp;
		};



    public:

		EdgeTrackingMgr2() 
		{

		}

		void Proceed(const ActualArrayAccessor_2D<F32PixelLinkOwner3C> & ploAcc,
			const ActualArrayAccessor_2D<F32ColorVal> valuesAcc);



	private:



	private:

		ExtendableMultiAllocPtrPoolRef< EdgeTrackingMgr2::PixSpreadLink> m_spreadLinkPool;
		MultiAllocProviderRef<EdgeTrackingMgr2::PixSpreadOp> m_spreadOpProvider;

    };







}