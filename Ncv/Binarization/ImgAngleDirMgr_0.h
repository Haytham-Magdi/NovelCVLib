#pragma once

#include <Novel-Lib\Ncpp\Common\commonLib.h>
#include <Novel-Lib\Ncpp\Math\mathLib.h>
#include <Novel-Lib\Ncv\OpenCV\CvIncludes.h>
#include <Novel-Lib\Ncv\OpenCV\Types.h>
#include <Novel-Lib\Ncv\OpenCV\error.h>
#include <vector>
#include <Novel-Lib\Ncv\OpenCV\Channel.h>
#include <Novel-Lib\Ncv\OpenCV\Image.h>

//#include <Novel-Lib\Ncv\ImageLineItrProvider.h>
//#include <Novel-Lib\Ncv\ImageItrMgr.h>



namespace Ncv
{
	namespace Ns_Binarization
	{

		class ImgAngleDirMgr : FRM_Object
		{
		public:

			ImgAngleDirMgr(F32ImageRef a_srcImg, float a_angDig);

			F32ImageRef GetSrcImg()
			{
				return m_srcImg;
			}

			float GetAngleByDigree()
			{
				return m_angDig;
			}

			CvSize GetResImgSiz()
			{
				return m_resSiz;
			}

			S32ImageRef Get_ResToSrcMapImage()
			{
				return m_resToSrcMapImg;
			}

			F32ImageRef GetResImg()
			{
				return m_resImg;
			}

			S32ImageRef Get_SrcToResMapImage()
			{
				return m_srcToResMapImg;
			}

			ImageItrMgrRef GetImageItrMgr()
			{
				return m_imageItrMgr;
			}

		protected:

			void Prepare();

			void PrepareResImg();

			int AddRound(int a_num);

			int AddRoundByMin(int a_num);

			//void PrepareProvArr();
			void PrepareImageItrMgr();



		protected:

			F32ImageRef m_srcImg;
			float m_angDig;
			float m_angRad;

			int m_nScale;
			int m_nRound;
			int m_nRoundByMin;
			int m_nCos;
			int m_nSin;

			CvSize m_resSiz;
			S32ImageRef m_resToSrcMapImg;
			F32ImageRef m_resImg;
			S32ImageRef m_srcToResMapImg;

			FixedVector< LineLimit > m_lineLimit_H_Arr;
			FixedVector< LineLimit > m_lineLimit_V_Arr;

			//FixedVector< ImageLineItrProvider > m_lineItrProv_Arr;

			ImageItrMgrRef m_imageItrMgr;

		};

		typedef Ncpp::ObjRef< ImgAngleDirMgr > ImgAngleDirMgrRef;
	};



}