#pragma once

#include <NovelCVLib/Common/commonLib.h>
// #include <NovelCVLib\Cpp\Math\mathLib.h>
// #include <NovelCVLib\Hcv\CvIncludes.h>
// #include <NovelCVLib\Hcv\Types.h>
// #include <NovelCVLib\Hcv\error.h>
// #include <vector>

// #include <NovelCVLib\Hcv\Channel.h>
// #include <NovelCVLib\Hcv\Image.h>


#include <NovelCVLib\Ncpp\Common\MultiAllocProvider.h>

#include <NovelCVLib\Ncv\F32PixelLink3C_Defs.h>


namespace Hcv
{
	class ImgSegDataMgr;


	using namespace Hcpl::Math;


	class RegionSegmentor51 // : public IRegionSegmentor20
	{
//////////////////////////////////////////////////////////////



	public:





//////////////////////////////////////////////////////////////

	protected:

		class RgnInfo;
		class RgnLink;


	public:



		struct RgnConflict
		{
			RgnInfo * pPeerRgn;

			struct _RgnConflict * pNext;	//	for being APtrList Entry
			struct _RgnConflict * pPrev;	//	for being APtrList Entry
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
			}




			int nIndex;



			S32Point pos;

			//bool bIsInConflict;


			RgnLink links[8];
			APtrList< RgnConflict > conflictList;

			// bool bHasConflicts;


			RgnInfo * pSrcRgn;

			int nTraceID;

			int nMergeOrder;

			// bool bIsPassiveRoot;

			static int s_MergeOrder;

			int nLastVisitID;

			RgnInfo * pPrev;	//	for being ListQue Entry
		};


		class LinkAction_2 : public MultiListQueMember< LinkAction_2 >
		{
		public:

			int nIndex;

			RgnInfo * pRgn1;
			RgnInfo * pRgn2;
		};


	public:

		RegionSegmentor51(const ActualArrayAccessor_2D<F32PixelLinkOwner3C> & a_ploAcc);

		~RegionSegmentor51();
		
		static inline bool HaveConflict( RgnInfo * a_pMinSizRgn, RgnInfo * a_pMaxSizRgn);

		virtual void Segment();
		virtual S16ImageRef GenSegmentedImage(bool a_bShowMeanColor = true);
		
		virtual F32ImageRef GenSegmentedImage2(bool a_bShowMeanColor = true);

		inline void CreateConflict( const int a_rgnIndex1, const int a_rgnIndex1);

	protected:

		void InitLinks(void);

		int GetInverseLinkIndex(int a_index)
		{
			return MgrOfLinkTypes::GetCore()->GetInverseLinkIndex(a_index);
		}


		void InitRgnInfoVect(void);

		int GetMaxDif() { return m_nMaxDif; }
		float m_difScale;

		void InitMaxDif() 
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

		inline float CalcRgnDif(RgnInfo * a_pRgn1, RgnInfo * a_pRgn2);

		inline void CreateLink( RgnInfo * a_pRgn, 
			int x, int y, RgnLinkDir a_dir);

		RgnInfo * GetPointRgn(int x, int y)
		{ 
			return &m_rgnInfoVect[m_rgnIndexCalc.Calc(x, y)]; 
		}

		inline void UpdateActRgn(RgnInfo * a_pRgn);

		inline void PrepareLinkAction( RgnLink & a_rLink, float a_distBef, 
			bool a_bSetProcessed = true);

		//inline LinkAction * ProvideLinkAction(RgnInfo * a_pRgn, RgnLinkDir a_dir, bool a_bSetProcessed = true);
		inline LinkAction * ProvideLinkAction( RgnInfo * a_pRgn, RgnLinkDir a_dir );

		inline LinkAction * ProvideLinkAction( RgnInfo * a_pRgn, RgnInfo * a_pRgn2 );

		//inline LinkAction * CloneLinkAction(LinkAction * a_pLA );

		inline RgnConflict * GetConflictIfExists( RgnInfo * a_pMinSizRgn, RgnInfo * a_pMaxSizRgn);

		inline void RemoveDuplicateConflicts( RgnInfo * a_pRgn );

		inline void PrepareRgnLinkActions( RgnInfo * a_pRgn );

		inline void CreateConflict_Direct( RgnInfo * a_pRgn1, RgnInfo * a_pRgn2);

		RgnLink * GetLinkBetweenRgns( int a_nIdx_1, int a_nIdx_2 );



	protected:

		SlideMgrRef m_slideMgr;

		ActualArrayAccessor_2D<F32PixelLinkOwner3C> m_ploAcc;

		LinkAction * pLADbg; 

		int m_nMaxDif;

		FixedVector<RgnInfo> m_rgnInfoVect;


		// MultiAllocProvider< LinkAction > m_linkAction_Provider;
		MultiAllocProviderRef< LinkAction > m_linkAction_Provider;

		MultiAllocProviderRef< RgnConflict > m_rgnConflict_Provider;


		FixedVector< LinkAction_2 > m_linkAction_2_Arr;

		MultiListQueMgr< LinkAction_2 > m_linkActionMergeQues;

		int m_nVisitID;

		// RgnInfo * m_pDbgRgn;

		// int m_nTestRgnIdx;
		
		
	};


	typedef Hcpl::ObjRef< RegionSegmentor51 > RegionSegmentor51Ref;
}