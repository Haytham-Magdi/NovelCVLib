#pragma once

#include <NovelCVLib\Ncpp\Common\commonLib_Misc.h>
#include <NovelCVLib\Ncpp\Math\mathLib.h>
#include <NovelCVLib\OpenCV\CvIncludes.h>
#include <NovelCVLib\OpenCV\Types.h>
#include <NovelCVLib\OpenCV\error.h>
#include <vector>
#include <NovelCVLib\OpenCV\Channel.h>
#include <NovelCVLib\OpenCV\Image.h>

//#include <NovelCVLib\Ncv\ImageLineItrProvider.h>
//#include <NovelCVLib\Ncv\ImageItrMgr.h>

#include <NovelCVLib\Apps\Binarization2\ImgAngleDirMgr.h>
//#include <NovelCVLib\Apps\Binarization2\ImgSizeRotationColl.h>
#include <NovelCVLib\Apps\Binarization2\AngleDirMgrColl_Context.h>
#include <NovelCVLib\Ncv\ImgSizeRotationColl.h>


namespace Ncv
{
	namespace Ns_Binarization
	{

		class AngleDirMgrColl : public Ncpp::Object
		{
		protected:

			class RgnInfo
			{
			public:

				//RgnInfo * pPrev;	//	for being ListQue Entry
			};

			class LinkAction_2 : public MultiListQueMember< LinkAction_2 >
			{
			public:

				int nIndex;

				RgnInfo * pRgn1;
				RgnInfo * pRgn2;
			};




		public:

			//AngleDirMgrColl(ImgSizeRotationCollRef a_rotColl, int a_nAprLen_1, int a_nAprLen_2);
			AngleDirMgrColl(F32ImageRef a_srcImg, ImgSizeRotationCollRef a_rotColl);

			//ImgAngleDirMgrRef GetRotAt(int a_nRotIdx)
			//{
			//	return m_angleDirMgrArr[a_nRotIdx];
			//}

			//int GetNofRots()
			//{
			//	return m_angleDirMgrArr.GetSize();
			//}

			//F32ImageRef GetSrcImg()
			//{
			//	return m_srcImg;
			//}

		protected:

			void Prepare();
			void DisplayStandiv_Dir_Img();
			void DisplayConflictImg();
			void ManageThresholding_0();
			void ManageThresholding();

		protected:

			AngleDirMgrColl_Context_Ref m_context_H;
			AngleDirMgrColl_Context_Ref m_context_V;

			F32ImageRef m_srcImg;
			ImgSizeRotationCollRef m_rotColl;
			//F32ImageRef m_srcImg;

			//int m_nAprLen_1;
			//int m_nAprLen_2;

			//int m_nofRots;
			FixedVector< ImgAngleDirMgrRef > m_angleDirMgrArr;
		};

		typedef Ncpp::ObjRef< AngleDirMgrColl > AngleDirMgrCollRef;
	}

}