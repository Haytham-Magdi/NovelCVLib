#pragma once

#include <NovelCVLib/Common/commonLib.h>
// #include <NovelCVLib\Cpp\Math\mathLib.h>
// #include <NovelCVLib\Ncv\CvIncludes.h>
// #include <NovelCVLib\Ncv\Types.h>
// #include <NovelCVLib\Ncv\error.h>
// #include <vector>

// #include <NovelCVLib\Ncv\Channel.h>
// #include <NovelCVLib\Ncv\Image.h>


#include <NovelCVLib/Ncpp/Common/MultiAllocProvider.h>

#include <NovelCVLib/Ncv/F32PixelLink3C_Defs.h>
#include <NovelCVLib/Ncpp/Common/ActualArrayAccessor_2D.h>
#include <NovelCVLib/Ncpp/Common/S32Point.h>
#include <NovelCVLib/Ncpp/Common/APtrList.h>


namespace Ncv
{

	using namespace Ncpp::Math;


	class RegionSegmentor52 // : public IRegionSegmentor20
	{
//////////////////////////////////////////////////////////////



	public:





//////////////////////////////////////////////////////////////

	protected:

		class RgnInfo;


	public:



		struct RgnConflict
		{
			RgnInfo * pPeerRgn;

			RgnConflict * pNext;	//	for being APtrList Entry
			RgnConflict * pPrev;	//	for being APtrList Entry
		};



		class LinkAction;




		class RgnInfo : public PixelRgn2<RgnInfo>
		{
		protected:
			RgnInfo * pActRgn;

			// // bool bIsRoot;
			RgnInfo * pRootRgn;

		public:


			RgnInfo()
			{
				SetRootToNull();
			}

			int nIndex;
			S32Point pos;

			APtrList< RgnConflict > conflictList;

			// int nMergeOrder;

			static int s_MergeOrder;

			int nLastVisitID;

			// RgnInfo * pPrev;	//	for being ListQue Entry
		};


		class LinkAction_2 : public MultiListQueMember< LinkAction_2 >
		{
		public:

			int nIndex;

			RgnInfo * pRgn1;
			RgnInfo * pRgn2;
		};


	public:

		RegionSegmentor52(const ActualArrayAccessor_2D<F32PixelLinkOwner3C> & a_ploAcc);

		~RegionSegmentor52();
		
		inline bool HaveConflict( RgnInfo * a_pMinSizRgn, RgnInfo * a_pMaxSizRgn);

		virtual void Segment();

		inline void CreateConflict( const int a_rgnIndex1, const int a_rgnIndex2);

	protected:

		void InitRgnInfoVect(void);

		int GetMaxDif() { return m_nMaxDif; }
		float m_difScale;

		void InitScaleAndMaxDif() 
		{ 
			m_difScale = 100;
			//m_difScale = 1;

			m_nMaxDif =  (int)( m_difScale *  
				sqrt( 
			//m_nMaxDif =  ( (
				//(float) ( 3 * Sqr(255)) )); 				
				//(float) ( 3 * Sqr(500)) )); 				
				(float) ( 3 * Sqr(700)) )); 				
				//(float) ( 3 * Sqr(255)) ) * 1.4); 				
		}

		inline RgnConflict * GetConflictIfExists( RgnInfo * a_pMinSizRgn, RgnInfo * a_pMaxSizRgn);

		inline void RemoveDuplicateConflicts( RgnInfo * a_pRgn );

		inline void PrepareRgnLinkActions( RgnInfo * a_pRgn );

		inline void CreateConflict_Direct( RgnInfo * a_pRgn1, RgnInfo * a_pRgn2);



	protected:

		ActualArrayAccessor_2D<F32PixelLinkOwner3C> m_ploAcc;
		ActualArrayAccessor_1D<F32PixelLinkOwner3C> m_ploAcc_1D;

		// LinkAction * pLADbg; 

		int m_nMaxDif;

		FixedVector<RgnInfo> m_rgnInfoVect;

		MultiAllocProviderRef< LinkAction_2 > m_linkAction_Provider;
		MultiAllocProviderRef< RgnConflict > m_rgnConflict_Provider;

		MultiListQueMgr< LinkAction_2 > m_linkActionMergeQues;

		int m_nVisitID;

		// RgnInfo * m_pDbgRgn;

		// int m_nTestRgnIdx;
		
		
	};


	typedef Ncpp::ObjRef< RegionSegmentor52 > RegionSegmentor51Ref;
}