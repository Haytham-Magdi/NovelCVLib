#include <NovelCVLib\Ncpp\Common\commonLib_Misc.h>
#include <NovelCVLib\OpenCV\CvIncludes.h>
#include <NovelCVLib\OpenCV\Types.h>
#include <NovelCVLib\OpenCV\error.h>
#include <vector>
#include <NovelCVLib\OpenCV\Channel.h>
#include <NovelCVLib\OpenCV\Image.h>
#include <NovelCVLib\OpenCV\funcs1.h>

#include <NovelCVLib\Apps\BloodCells\ImgAngleDirMgr.h>


//#define M_PI 3.14159265358979323846
#define M_PI 3.14159265358979323846f


namespace Ncv
{
	using namespace Ncpp;
	//using namespace Ncpp::Math;

	using namespace Ncv::ImageOperations2;
	
	namespace Ns_BloodCells
	{

		ImgAngleDirMgr::ImgAngleDirMgr(ImgAngleDirMgr_Context_Ref a_context, ImgAngleDirMgr_Context_Ref a_normalContext,
			AngleDirMgrColl_Context_Ref a_parentContext)
		{
			m_context = a_context;
			m_normalContext = a_normalContext;
			m_parentContext = a_parentContext;
		}

		ImgAngleDirMgr::Context::Context(int a_nIndex, ImgSizeRotationRef a_imgRot, F32ImageArrayHolder3C_Ref a_org_Img,
			F32ImageArrayHolder1C_Ref a_magSqr_Img, char a_hv)
		{
			m_nIndex = a_nIndex;
			m_imgRot = a_imgRot;

			m_org_Img = a_org_Img;
			m_magSqr_Img = a_magSqr_Img;

			Ncpp_ASSERT(a_hv == 'H' || a_hv == 'V');
			m_hv = a_hv;

			{
				char idStr_0[70];
				sprintf(idStr_0, "%.2f, %c: ", m_imgRot->GetAngleByDigree(), m_hv);
				m_idStr = idStr_0;
			}

		}

		void ImgAngleDirMgr::Proceed_1_1()
		{
			Context & cx = *m_context;


			//if (1 == cx.m_nIndex)
			//{
			//	ShowImage(cx.m_org_Img->GetSrcImg(), cx.MakeStrWithId("org_Img->GetSrcImg()").c_str());
			//}


			cx.m_standev_X_Img = F32ImageArrayHolder1C::CreateEmptyFrom(cx.m_org_Img);
			CalcStandevImage_X(cx.m_org_Img->GetVirtAccessor(), cx.m_magSqr_Img->GetVirtAccessor(),
				cx.m_standev_X_Img->GetVirtAccessor(), Range<int>::New(-1, 1));
			//cx.m_standev_X_Img->GetVirtAccessor(), Range<int>::New(-2, 2));
			//cx.m_standev_X_Img->GetVirtAccessor(), Range<int>::New(-20, 20));

			if (0 == cx.m_nIndex)
			{
				ShowImage(GenTriChGrayImg(cx.m_standev_X_Img->GetSrcImg()), cx.MakeStrWithId("m_standev_X_Img->GetSrcImg()").c_str());
				GlobalStuff::SetLinePathImg(GenTriChGrayImg(cx.m_standev_X_Img->GetSrcImg()));
				GlobalStuff::ShowLinePathImg();
			}


			cx.m_normAvgStandev_X_Img = F32ImageArrayHolder1C::CreateEmptyFrom(cx.m_org_Img);
			Calc_NormAvgStandevImage_X(cx.m_org_Img->GetVirtAccessor(), cx.m_magSqr_Img->GetVirtAccessor(),
				
				//cx.m_normAvgStandev_X_Img->GetVirtAccessor(), Range<int>::New(-2, 2), Range<int>::New(-2, 2));
			cx.m_normAvgStandev_X_Img->GetVirtAccessor(), Range<int>::New(-1, 1), Range<int>::New(-1, 1));
			//cx.m_normAvgStandev_X_Img->GetVirtAccessor(), Range<int>::New(-1, 1), Range<int>::New(-2, 2));
			
			//cx.m_normAvgStandev_X_Img->GetVirtAccessor(), Range<int>::New(-1, 1), Range<int>::New(-3, 3));
			//cx.m_normAvgStandev_X_Img->GetVirtAccessor(), Range<int>::New(-3, 3), Range<int>::New(-1, 1));
			//cx.m_normAvgStandev_X_Img->GetVirtAccessor(), Range<int>::New(-3, 3), Range<int>::New(-3, 3));
			
			//cx.m_normAvgStandev_X_Img->GetVirtAccessor(), Range<int>::New(-7, 7), Range<int>::New(-7, 7));
				//cx.m_normAvgStandev_X_Img->GetVirtAccessor(), Range<int>::New(-3, 3), Range<int>::New(-3, 3));
			//cx.m_normAvgStandev_X_Img->GetVirtAccessor(), Range<int>::New(-2, 2), Range<int>::New(-6, 6));
				//cx.m_normAvgStandev_X_Img->GetVirtAccessor(), Range<int>::New(-2, 2), Range<int>::New(0, 1));
			//cx.m_normAvgStandev_X_Img->GetVirtAccessor(), Range<int>::New(-2, 2), Range<int>::New(0, 0));
			//cx.m_normAvgStandev_X_Img->GetVirtAccessor(), Range<int>::New(-6, 6), Range<int>::New(-6, 6));
			//cx.m_normAvgStandev_X_Img->GetVirtAccessor(), Range<int>::New(-6, 6), Range<int>::New(-2, 2));
			//cx.m_normAvgStandev_X_Img->GetVirtAccessor(), Range<int>::New(-36, 36), Range<int>::New(-36, 36));
			//cx.m_normAvgStandev_X_Img->GetVirtAccessor(), Range<int>::New(-6, 6), Range<int>::New(-36, 36));
			//cx.m_normAvgStandev_X_Img->GetVirtAccessor(), Range<int>::New(-36, 36), Range<int>::New(-6, 6));

			if (1 == cx.m_nIndex)
			//if (0 == cx.m_nIndex)
			{
				//float & elm1 = cx.m_normAvgStandev_X_Img->GetActualAccessor().GetAt(45, 77);
				// float & elm1 = cx.m_normAvgStandev_X_Img->GetActualAccessor().GetAt(215, 40);
				//elm1 = 255;

				////ShowImage(cx.m_normAvgStandev_X_Img->GetSrcImg(), cx.MakeStrWithId("m_normAvgStandev_X_Img->GetSrcImg()").c_str());
				//ShowImage(GenTriChGrayImg(cx.m_normAvgStandev_X_Img->GetSrcImg()), cx.MakeStrWithId("m_normAvgStandev_X_Img->GetSrcImg()").c_str());
			}
			
		}

		void ImgAngleDirMgr::Proceed_1_2()
		{
			AffectCommonAvgStandev();
		}

		void ImgAngleDirMgr::Proceed_2_1()
		{
			Context & cx = *m_context;
			Context & ncx = *m_normalContext;
			AngleDirMgrColl_Context & pcx = *m_parentContext;


			////	for debug.
			//if (//0 != cx.m_nIndex &&
			//	//4 != cx.m_nIndex
			//	1 != cx.m_nIndex
			//	)
			//{
			//	return;
			//}

			cx.m_conflict_Img = ArrayHolderUtil::CreateEmptyFrom<ConflictInfo2>(cx.m_org_Img->AsHolderRef());

			{
				ActualArrayAccessor_2D<ConflictInfo2> cnfAcc =
					cx.m_conflict_Img->GetActualAccessor();

				ActualArrayAccessor_1D<ConflictInfo2> cnfAcc_1D =
					cnfAcc.GenAcc_1D();

				for (int i = 0; i < cnfAcc_1D.GetSize(); i++)
				{
					S32Point pnt = cnfAcc.CalcPointFromIndex_1D(i);

					S32Point testPnt(500, 444);
					if (0 == cx.m_nIndex &&
						S32Point::AreEqual(pnt, testPnt))
					{
						i = i;
					}

					ConflictInfo2 & rConf = cnfAcc_1D[i];
					rConf.Index = i;
				}
			}


//-------------------------------

			////Window<int> avgWin = Window<int>::New(-1, 1, -5, 5);
			////Window<int> avgWin = Window<int>::New(-1, 1, -2, 2);

			////Window<int> avgWin = Window<int>::New(-1, 0, -2, 2);
			////////Window<int> avgWin = Window<int>::New(0, 0, -2, 2);
			//// Window<int> avgWin = Window<int>::New(-2, 0, 0, 0);
			////Window<int> avgWin = Window<int>::New(-1, 0, -1, 1);

			//Window<int> avgWin = Window<int>::New(-1, 0, 0, 0);
			////Window<int> avgWin = Window<int>::New(-1, 1, 0, 0);

			////Window<int> avgWin = Window<int>::New(-3, 3, 0, 0);
			////Window<int> avgWin = Window<int>::New(-1, 1, 0, 0);

			////Window<int> avgWin = Window<int>::New(-2, 2, -2, 2);
			////Window<int> avgWin = Window<int>::New(-2, 1, -2, 2);


			//F32ImageArrayHolder3C_Ref avg_Img = F32ImageArrayHolder3C::CreateEmptyFrom(cx.m_org_Img);
			//AvgImage(cx.m_org_Img->GetVirtAccessor(), avg_Img->GetVirtAccessor(), avgWin);

			//F32ImageArrayHolder1C_Ref avg_MagSqr_Img = F32ImageArrayHolder1C::CreateEmptyFrom(cx.m_org_Img);
			//AvgImage(cx.m_magSqr_Img->GetVirtAccessor(), avg_MagSqr_Img->GetVirtAccessor(), avgWin);

			//Range<int> confRange = Range<int>::New(-1 - avgWin.GetX2(), 1 - avgWin.GetX1());
			////Range<int> confRange = Range<int>::New(0 - avgWin.GetX2(), 2 - avgWin.GetX1());
			////Range<int> confRange = Range<int>::New(1 - avgWin.GetX2(), 2 - avgWin.GetX1());
			////Range<int> confRange = Range<int>::New(-1 - avgWin.GetX2(), 0 - avgWin.GetX1());
			////Range<int> confRange = Range<int>::New(-7 - avgWin.GetX2(), 7 - avgWin.GetX1());

			//CalcConflictImage_X(avg_Img->GetVirtAccessor(), avg_MagSqr_Img->GetVirtAccessor(),
			//	cx.m_conflict_Img->GetVirtAccessor(), confRange);


//-------------------------------

			////Window<int> avgWin = Window<int>::New(-1, 1, -5, 5);
			////Window<int> avgWin = Window<int>::New(-1, 1, -2, 2);

			////Window<int> avgWin = Window<int>::New(-1, 0, -2, 2);
			////////Window<int> avgWin = Window<int>::New(0, 0, -2, 2);
			//// Window<int> avgWin = Window<int>::New(-2, 0, 0, 0);
			////Window<int> avgWin = Window<int>::New(-1, 0, -1, 1);

			////Window<int> avgWin = Window<int>::New(-1, 0, 0, 0);
			//Window<int> avgWin = Window<int>::New(-1, 1, 0, 0);

			////Window<int> avgWin = Window<int>::New(-3, 3, 0, 0);
			////Window<int> avgWin = Window<int>::New(-1, 1, 0, 0);

			////Window<int> avgWin = Window<int>::New(-2, 2, -2, 2);
			////Window<int> avgWin = Window<int>::New(-2, 1, -2, 2);


			//F32ImageArrayHolder3C_Ref avg_Img = F32ImageArrayHolder3C::CreateEmptyFrom(cx.m_org_Img);
			//AvgImage(cx.m_org_Img->GetVirtAccessor(), avg_Img->GetVirtAccessor(), avgWin);

			//F32ImageArrayHolder1C_Ref avg_MagSqr_Img = F32ImageArrayHolder1C::CreateEmptyFrom(cx.m_org_Img);
			//AvgImage(cx.m_magSqr_Img->GetVirtAccessor(), avg_MagSqr_Img->GetVirtAccessor(), avgWin);

			//Range<int> confRange = Range<int>::New(-1 - avgWin.GetX2(), 1 - avgWin.GetX1());
			////Range<int> confRange = Range<int>::New(0 - avgWin.GetX2(), 2 - avgWin.GetX1());
			////Range<int> confRange = Range<int>::New(1 - avgWin.GetX2(), 2 - avgWin.GetX1());
			////Range<int> confRange = Range<int>::New(-1 - avgWin.GetX2(), 0 - avgWin.GetX1());
			////Range<int> confRange = Range<int>::New(-7 - avgWin.GetX2(), 7 - avgWin.GetX1());

			//F32ImageArrayHolder1C_Ref normStandev_X_Img;
			//{
			//	normStandev_X_Img = F32ImageArrayHolder1C::CreateEmptyFrom(cx.m_org_Img);
			//	//normStandev_X_Img = F32ImageArrayHolder1C::CreateEmptyFrom(cx.m_org_Img)->CreateTransposedProxy();

			//	//Calc_NormAvgStandevImage_X(cx.m_org_Img->GetVirtAccessor(), cx.m_magSqr_Img->GetVirtAccessor(),
			//	//	//normStandev_X_Img->GetVirtAccessor(), Range<int>::New(-2, 2), Range<int>::New(-2, 2));
			//	//normStandev_X_Img->GetVirtAccessor(), Range<int>::New(-2, 2), Range<int>::New(0, 0));

			//	Calc_NormAvgStandevImage_X(cx.m_org_Img->GetVirtAccessor().GenTranspose(), cx.m_magSqr_Img->GetVirtAccessor().GenTranspose(),
			//		//normStandev_X_Img->GetVirtAccessor().GenTranspose(), Range<int>::New(-2, 2), Range<int>::New(0, 0));
			//		normStandev_X_Img->GetVirtAccessor().GenTranspose(), Range<int>::New(-1, 1), Range<int>::New(0, 0));

			//}

			//CalcConflictImage2_X(avg_Img->GetVirtAccessor(), avg_MagSqr_Img->GetVirtAccessor(),
			//	normStandev_X_Img->GetVirtAccessor(), cx.m_conflict_Img->GetVirtAccessor(), confRange);




//-------------------------------

			////Window<int> avgWin = Window<int>::New(-1, 1, -5, 5);
			////Window<int> avgWin = Window<int>::New(-1, 1, -2, 2);

			////Window<int> avgWin = Window<int>::New(-1, 0, -2, 2);
			////////Window<int> avgWin = Window<int>::New(0, 0, -2, 2);
			//// Window<int> avgWin = Window<int>::New(-2, 0, 0, 0);
			////Window<int> avgWin = Window<int>::New(-1, 0, -1, 1);

			//Window<int> avgWin = Window<int>::New(-1, 0, 0, 0);
			////Window<int> avgWin = Window<int>::New(-1, 1, 0, 0);

			////Window<int> avgWin = Window<int>::New(-3, 3, 0, 0);
			////Window<int> avgWin = Window<int>::New(-1, 1, 0, 0);

			////Window<int> avgWin = Window<int>::New(-2, 2, -2, 2);
			////Window<int> avgWin = Window<int>::New(-2, 1, -2, 2);


			//F32ImageArrayHolder3C_Ref avg_Img = F32ImageArrayHolder3C::CreateEmptyFrom(cx.m_org_Img);
			//AvgImage(cx.m_org_Img->GetVirtAccessor(), avg_Img->GetVirtAccessor(), avgWin);

			//F32ImageArrayHolder1C_Ref avg_MagSqr_Img = F32ImageArrayHolder1C::CreateEmptyFrom(cx.m_org_Img);
			//AvgImage(cx.m_magSqr_Img->GetVirtAccessor(), avg_MagSqr_Img->GetVirtAccessor(), avgWin);


			////Window<int> avgWin_Center = Window<int>::New(-1, 1, 0, 0);
			//Window<int> avgWin_Center = Window<int>::New(0, 0, 0, 0);

			//F32ImageArrayHolder3C_Ref avg_Center_Img = F32ImageArrayHolder3C::CreateEmptyFrom(cx.m_org_Img);
			//AvgImage(cx.m_org_Img->GetVirtAccessor(), avg_Center_Img->GetVirtAccessor(), avgWin_Center);

			//F32ImageArrayHolder1C_Ref avg_MagSqr_Center_Img = F32ImageArrayHolder1C::CreateEmptyFrom(cx.m_org_Img);
			//AvgImage(cx.m_magSqr_Img->GetVirtAccessor(), avg_MagSqr_Center_Img->GetVirtAccessor(), avgWin_Center);


			//Range<int> confRange = Range<int>::New(-1 - avgWin.GetX2(), 1 - avgWin.GetX1());
			////Range<int> confRange = Range<int>::New(-2 - avgWin.GetX2(), 1 - avgWin.GetX1());
			////Range<int> confRange = Range<int>::New(-2 - avgWin.GetX2(), 2 - avgWin.GetX1());
			////Range<int> confRange = Range<int>::New(0 - avgWin.GetX2(), 2 - avgWin.GetX1());
			////Range<int> confRange = Range<int>::New(1 - avgWin.GetX2(), 2 - avgWin.GetX1());
			////Range<int> confRange = Range<int>::New(-1 - avgWin.GetX2(), 0 - avgWin.GetX1());
			////Range<int> confRange = Range<int>::New(-7 - avgWin.GetX2(), 7 - avgWin.GetX1());

			//F32ImageArrayHolder1C_Ref normStandev_X_Img;
			//{
			//	normStandev_X_Img = F32ImageArrayHolder1C::CreateEmptyFrom(cx.m_org_Img);
			//	//normStandev_X_Img = F32ImageArrayHolder1C::CreateEmptyFrom(cx.m_org_Img)->CreateTransposedProxy();

			//	//Calc_NormAvgStandevImage_X(cx.m_org_Img->GetVirtAccessor(), cx.m_magSqr_Img->GetVirtAccessor(),
			//	//	//normStandev_X_Img->GetVirtAccessor(), Range<int>::New(-2, 2), Range<int>::New(-2, 2));
			//	//normStandev_X_Img->GetVirtAccessor(), Range<int>::New(-2, 2), Range<int>::New(0, 0));

			//	Calc_NormAvgStandevImage_X(cx.m_org_Img->GetVirtAccessor().GenTranspose(), cx.m_magSqr_Img->GetVirtAccessor().GenTranspose(),
			//		//normStandev_X_Img->GetVirtAccessor().GenTranspose(), Range<int>::New(-2, 2), Range<int>::New(0, 0));
			//		//normStandev_X_Img->GetVirtAccessor().GenTranspose(), Range<int>::New(-1, 1), Range<int>::New(0, 0));
			//	normStandev_X_Img->GetVirtAccessor().GenTranspose(), Range<int>::New(-1, 0), Range<int>::New(0, 0));

			//}

			//CalcThinConflictImage_X(
			//	avg_Img->GetVirtAccessor(), avg_MagSqr_Img->GetVirtAccessor(),
			//	avg_Center_Img->GetVirtAccessor(), avg_MagSqr_Center_Img->GetVirtAccessor(),
			//	normStandev_X_Img->GetVirtAccessor(), cx.m_conflict_Img->GetVirtAccessor(), confRange);

			
//-------------------------------


			////Window<int> avgWin = Window<int>::New(-1, 0, -1, 1);
			//Window<int> avgWin = Window<int>::New(0, 0, 0, 0);

			cx.m_diff1_1_Img = F32ImageArrayHolder3C::CreateEmptyFrom(cx.m_org_Img);
			cx.m_diff_2_Img = F32ImageArrayHolder3C::CreateEmptyFrom(cx.m_org_Img);
			cx.m_diff1_2_Img = F32ImageArrayHolder3C::CreateEmptyFrom(cx.m_org_Img);


			////cx.m_bidiffInfo_Img = F32ImageArrayHolder3C::CreateEmptyFrom(cx.m_org_Img);
			//cx.m_bidiffInfo_Img = ArrayHolderUtil::CreateEmptyFrom<BidiffInfo>(cx.m_org_Img->AsHolderRef());


			const int posDist = pcx.GetDiffPosDist();

			//F32ImageArrayHolder3C_Ref avg_Img = F32ImageArrayHolder3C::CreateEmptyFrom(cx.m_org_Img);
			//AvgImage(cx.m_org_Img->GetVirtAccessor(), avg_Img->GetVirtAccessor(), avgWin);

			//Range<int> diffRange = Range<int>::New(-10 - avgWin.GetX2(), 10 - avgWin.GetX1());
			//Range<int> diffRange = Range<int>::New(-1 - avgWin.GetX2(), 1 - avgWin.GetX1());

			////Range<int> diffRange = Range<int>::New(-1 - avgWin.GetX2(), 0 - avgWin.GetX1());
			//Range<int> diffRange = Range<int>::New(-posDist - avgWin.GetX2(), 0 - avgWin.GetX1());
			//Range<int> diffRange1_2 = Range<int>::New(-(posDist * 3) - avgWin.GetX2(), 0 - avgWin.GetX1());

			Range<int> diffRange = Range<int>::New(-posDist, 0);
			Range<int> diffRange1_2 = Range<int>::New(-(posDist * 3), 0);

			//Range<int> diffRange = Range<int>::New(0 - avgWin.GetX2(), 1 - avgWin.GetX1());
			//Range<int> diffRange = Range<int>::New(0 - avgWin.GetX2(), -1 - avgWin.GetX1());

			F32ImageArrayHolder3C_Ref avg_Img = F32ImageArrayHolder3C::CreateEmptyFrom(cx.m_org_Img);
			AvgImage_X(cx.m_org_Img->GetVirtAccessor(), avg_Img->GetVirtAccessor(),
				Range<int>::New(1 - posDist, 0));


			CalcDiffImageX(avg_Img->GetVirtAccessor(), cx.m_diff1_1_Img->GetVirtAccessor(), diffRange);
			CalcDiffImageX(cx.m_diff1_1_Img->GetVirtAccessor(), cx.m_diff_2_Img->GetVirtAccessor(), diffRange);
			CalcDiffImageX(avg_Img->GetVirtAccessor(), cx.m_diff1_2_Img->GetVirtAccessor(), diffRange1_2);

			//CalcDiffImageX(cx.m_org_Img->GetVirtAccessor(), cx.m_diff1_1_Img->GetVirtAccessor(), diffRange);
			//CalcDiffImageX(cx.m_diff1_1_Img->GetVirtAccessor(), cx.m_diff_2_Img->GetVirtAccessor(), diffRange);
			//CalcDiffImageX(cx.m_org_Img->GetVirtAccessor(), cx.m_diff1_2_Img->GetVirtAccessor(), diffRange1_2);


			//CalcConflictImage_X_FromDiffImages(cx.m_diff1_1_Img->GetVirtAccessor(), cx.m_diff1_2_Img->GetVirtAccessor(),
			//	cx.m_diff_2_Img->GetVirtAccessor(), cx.m_conflict_Img->GetVirtAccessor(), posDist);

			CalcConflictImage_X_FromDiffImages2(cx.m_org_Img->GetVirtAccessor(), cx.m_diff1_1_Img->GetVirtAccessor(),
				cx.m_diff_2_Img->GetVirtAccessor(), cx.m_conflict_Img->GetVirtAccessor(), posDist);



//--------------------------------


			//if (0 == cx.m_nIndex)
			//{
			//	DisplayConflictImg();
			//}

		}

		void ImgAngleDirMgr::Proceed_2_2()
		{
			//Context & cx = *m_context;
			//Context & ncx = *m_normalContext;
			//AngleDirMgrColl_Context & pcx = *m_parentContext;

			//ConfirmConflict();
			AffectCommonConflict();
		}

		void ImgAngleDirMgr::Proceed_2b_1()
		{
			Context & cx = *m_context;
			Context & ncx = *m_normalContext;
			AngleDirMgrColl_Context & pcx = *m_parentContext;

			//F32ImageArrayHolder3C_Ref diff_Img_1;
			//diff_Img_1 = F32ImageArrayHolder3C::CreateEmptyFrom(cx.m_org_Img);
			
			cx.m_diff1_1_Img = F32ImageArrayHolder3C::CreateEmptyFrom(cx.m_org_Img);
			cx.m_diff_2_Img = F32ImageArrayHolder3C::CreateEmptyFrom(cx.m_org_Img);
			cx.m_diff1_2_Img = F32ImageArrayHolder3C::CreateEmptyFrom(cx.m_org_Img);

			//cx.m_bidiffInfo_Img = F32ImageArrayHolder3C::CreateEmptyFrom(cx.m_org_Img);
			cx.m_bidiffInfo_Img = ArrayHolderUtil::CreateEmptyFrom<BidiffInfo>(cx.m_org_Img->AsHolderRef());

			
			const int posDist = pcx.GetDiffPosDist();

			//Window<int> avgWin = Window<int>::New(-1, 0, -1, 1);
			//Window<int> avgWin = Window<int>::New(0, 0, 0, 0);
			Window<int> avgWin = Window<int>::New(0, 0, 0, 0);

			F32ImageArrayHolder3C_Ref avg_Img = F32ImageArrayHolder3C::CreateEmptyFrom(cx.m_org_Img);
			//AvgImage(cx.m_org_Img->GetVirtAccessor(), avg_Img->GetVirtAccessor(), avgWin);
			AvgImage_X(cx.m_org_Img->GetVirtAccessor(), avg_Img->GetVirtAccessor(), 
				Range<int>::New(-posDist, 0));

			//Range<int> diffRange = Range<int>::New(-10 - avgWin.GetX2(), 10 - avgWin.GetX1());
			//Range<int> diffRange = Range<int>::New(-1 - avgWin.GetX2(), 1 - avgWin.GetX1());
			
			//Range<int> diffRange = Range<int>::New(-1 - avgWin.GetX2(), 0 - avgWin.GetX1());
			Range<int> diffRange = Range<int>::New(-posDist - avgWin.GetX2(), 0 - avgWin.GetX1());
			Range<int> diffRange1_2 = Range<int>::New( -(posDist * 3) - avgWin.GetX2(), 0 - avgWin.GetX1());
			

			//Range<int> diffRange = Range<int>::New(0 - avgWin.GetX2(), 1 - avgWin.GetX1());
			//Range<int> diffRange = Range<int>::New(0 - avgWin.GetX2(), -1 - avgWin.GetX1());

			CalcDiffImageX(avg_Img->GetVirtAccessor(), cx.m_diff1_1_Img->GetVirtAccessor(), diffRange);
			CalcDiffImageX(cx.m_diff1_1_Img->GetVirtAccessor(), cx.m_diff_2_Img->GetVirtAccessor(), diffRange);
			CalcDiffImageX(avg_Img->GetVirtAccessor(), cx.m_diff1_2_Img->GetVirtAccessor(), diffRange1_2);

			PrepareBidiffInfoImageFromDiffImages(cx.m_diff1_1_Img->GetVirtAccessor(), cx.m_diff_2_Img->GetVirtAccessor(),
				cx.m_bidiffInfo_Img->GetVirtAccessor(), posDist);

			if (0 == cx.m_nIndex)
			{
				DisplayDiffImages();
			}

		}

		
		void ImgAngleDirMgr::Proceed_2b_2()
		{
				//Context & cx = *m_context;
				//Context & ncx = *m_normalContext;
				//AngleDirMgrColl_Context & pcx = *m_parentContext;

				AffectCommonBidiffInfo();
		}


		void ImgAngleDirMgr::Proceed_2c_1()
		{
			Context & cx = *m_context;
			Context & ncx = *m_normalContext;
			AngleDirMgrColl_Context & pcx = *m_parentContext;

			if (0 != cx.m_nIndex)
			//if (2 != cx.m_nIndex)
			//if (3 != cx.m_nIndex)
				//if (4 != cx.m_nIndex)
				return;





			////Window<int> avgWin = Window<int>::New(-2, 2, 0, 0);
			//Window<int> avgWin = Window<int>::New(-20, 20, 0, 0);

			//Range<int> avgRangeBef = Range<int>::New(-1, 0);
			//Range<int> avgRangeBef = Range<int>::New(0, 1);
			//Range<int> avgRangeBef = Range<int>::New(-1, 0);
			//Range<int> avgRangeBef = Range<int>::New(-1, 1);
			Range<int> avgRangeBef = Range<int>::New(-2, 2);
			//Range<int> avgRangeBef = Range<int>::New(-3, 3);
			//Range<int> avgRangeBef = Range<int>::New(-4, 4);
			//Range<int> avgRangeBef = Range<int>::New(-20, 20);
			//Range<int> avgRangeBef = Range<int>::New(-7, 7);
			//Range<int> avgRangeBef = Range<int>::New(-5, 5);
			//Range<int> avgRangeBef = Range<int>::New(-3, 3);

			//Range<int> avgRangeAft = Range<int>::New(-1, 0);
			//Range<int> avgRangeAft = Range<int>::New(-1, 1);
			Range<int> avgRangeAft = Range<int>::New(-2, 2);
			//Range<int> avgRangeAft = Range<int>::New(-3, 3);

			//F32ImageArrayHolder3C_Ref res_Img = F32ImageArrayHolder3C::CreateEmptyFrom(cx.m_org_Img);
			//FillImage(res_Img->GetVirtAccessor(), F32ColorVal(0, 100, 0));
			//CalcHighPassEdgeImage_X(cx.m_org_Img->GetVirtAccessor(), res_Img->GetVirtAccessor(), avgRangeBef.GetEnd());


			F32ImageArrayHolder3C_Ref avgBef_Img = F32ImageArrayHolder3C::CreateEmptyFrom(cx.m_org_Img);
			F32ImageArrayHolder1C_Ref standevBef_Img = F32ImageArrayHolder1C::CreateEmptyFrom(cx.m_org_Img);
			//AvgImage_X(cx.m_org_Img->GetVirtAccessor(), avgBef_Img->GetVirtAccessor(), avgRangeBef);

			Calc_Avg_And_Standev_Image(cx.m_org_Img->GetVirtAccessor(), avgBef_Img->GetVirtAccessor(),
				standevBef_Img->GetVirtAccessor(), Window<int>::FromRangeX(avgRangeBef));

			F32ImageArrayHolder3C_Ref withAvgDiff_Img = F32ImageArrayHolder3C::CreateEmptyFrom(cx.m_org_Img);
			SubtractImages(cx.m_org_Img->GetVirtAccessor(), avgBef_Img->GetVirtAccessor(), withAvgDiff_Img->GetVirtAccessor());

			F32ImageArrayHolder1C_Ref withAvgDiffMag_Img = F32ImageArrayHolder1C::CreateEmptyFrom(cx.m_org_Img);
			CalcMagImage(withAvgDiff_Img->GetVirtAccessor(), withAvgDiffMag_Img->GetVirtAccessor());

			F32ImageArrayHolder3C_Ref avgAft_Img = F32ImageArrayHolder3C::CreateEmptyFrom(cx.m_org_Img);
			F32ImageArrayHolder1C_Ref standevAft_Img = F32ImageArrayHolder1C::CreateEmptyFrom(cx.m_org_Img);

			Calc_Avg_And_Standev_Image(withAvgDiff_Img->GetVirtAccessor(), avgAft_Img->GetVirtAccessor(),
				standevAft_Img->GetVirtAccessor(), Window<int>::FromRangeX(avgRangeAft));





			//Range<int> shiftDiffRange = Range<int>::New(-1, 0);
			//Range<int> shiftDiffRange = Range<int>::New(-2, 0);
			//Range<int> shiftDiffRange = Range<int>::New(-3, 0);
			Range<int> shiftDiffRange = Range<int>::New(-avgRangeBef.GetEnd(), 0);


			F32ImageArrayHolder3C_Ref shiftDiff_Img = F32ImageArrayHolder3C::CreateEmptyFrom(cx.m_org_Img);
			CalcDiffImageX(withAvgDiff_Img->GetVirtAccessor(), shiftDiff_Img->GetVirtAccessor(), shiftDiffRange);

			F32ImageArrayHolder1C_Ref shiftDiffMag_Img = F32ImageArrayHolder1C::CreateEmptyFrom(cx.m_org_Img);
			CalcMagImage(shiftDiff_Img->GetVirtAccessor(), shiftDiffMag_Img->GetVirtAccessor());

			//F32ImageArrayHolder3C_Ref sqrVector_Img = F32ImageArrayHolder3C::CreateEmptyFrom(cx.m_org_Img);
			//CalcSqrVectorImage(withAvgDiff_Img->GetVirtAccessor(), sqrVector_Img->GetVirtAccessor());

			//F32ImageArrayHolder3C_Ref avgSqrVector_Img = F32ImageArrayHolder3C::CreateEmptyFrom(cx.m_org_Img);
			//AvgImage_X(sqrVector_Img->GetVirtAccessor(), avgSqrVector_Img->GetVirtAccessor(), avgRangeBef);


			F32ImageArrayHolder3C_Ref res2_Img = F32ImageArrayHolder3C::CreateEmptyFrom(cx.m_org_Img);
			FillImage(res2_Img->GetVirtAccessor(), F32ColorVal(0, 100, 0));
			//CalcHighPassEdgeImage_X(cx.m_org_Img->GetVirtAccessor(), res_Img->GetVirtAccessor(), avgRangeBef.GetEnd());
			CalcHighPassEdgeImage_X_Core2(cx.m_org_Img->GetVirtAccessor(), 
				withAvgDiffMag_Img->GetVirtAccessor(),
				shiftDiffMag_Img->GetVirtAccessor(),
				res2_Img->GetVirtAccessor(), avgRangeBef.GetEnd());

			


			F32ImageArrayHolder3C_Ref disp_Img = F32ImageArrayHolder3C::CreateEmptyFrom(cx.m_org_Img);
			AddValueToImage(withAvgDiff_Img->GetVirtAccessor(), disp_Img->GetVirtAccessor(), F32ColorVal::FromNum(130));
			//AddValueToImage(shiftDiff_Img->GetVirtAccessor(), disp_Img->GetVirtAccessor(), F32ColorVal::FromNum(130));
			//DivideImageByNum(sqrVector_Img->GetVirtAccessor(), disp_Img->GetVirtAccessor(), 100);

			F32ImageArrayHolder3C_Ref disp2_Img = F32ImageArrayHolder3C::CreateEmptyFrom(cx.m_org_Img);
			AddValueToImage(shiftDiff_Img->GetVirtAccessor(), disp2_Img->GetVirtAccessor(), F32ColorVal::FromNum(130));

			//CopyImage(disp_Img->GetVirtAccessor(), standevBef_Img->GetVirtAccessor());

			//if (0 == cx.m_nIndex)
			{
				//ShowImage(disp_Img->GetSrcImg(), "2c_1: disp_Img");
				////ShowImage(avgBef_Img->GetSrcImg(), "2c_1: avgBef_Img");
				////ShowImage(sqrVector_Img->GetSrcImg(), "2c_1: sqrVector_Img");
				////ShowImage(avgSqrVector_Img->GetSrcImg(), "2c_1: avgSqrVector_Img");
				//ShowImage(GenTriChGrayImg(standevBef_Img->GetSrcImg()), "2c_1: standevBef_Img");
				//ShowImage(GenTriChGrayImg(standevAft_Img->GetSrcImg()), "2c_1: standevBef_Img");
				////ShowImage(disp2_Img->GetSrcImg(), "2c_1: disp2_Img");
				////ShowImage(res_Img->GetSrcImg(), "2c_1: res_Img");


				GlobalStuff::SetLinePathImg(avgBef_Img->GetSrcImg());
				
				GlobalStuff::SetLinePathImg(disp_Img->GetSrcImg());
				//GlobalStuff::SetLinePathImg(GenTriChGrayImg(withAvgDiffMag_Img->GetSrcImg()));

				//GlobalStuff::SetLinePathImg(GenTriChGrayImg(standevBef_Img->GetSrcImg()));
				//GlobalStuff::SetLinePathImg(GenTriChGrayImg(standevAft_Img->GetSrcImg()));
			
				GlobalStuff::SetLinePathImg(disp2_Img->GetSrcImg());
				//GlobalStuff::SetLinePathImg(GenTriChGrayImg(shiftDiffMag_Img->GetSrcImg()));

				//GlobalStuff::SetLinePathImg(res_Img->GetSrcImg());
				GlobalStuff::SetLinePathImg(res2_Img->GetSrcImg());


				GlobalStuff::ShowLinePathImg();



			}


		}


		void ImgAngleDirMgr::Proceed_3_1()
		{
			Context & cx = *m_context;
			Context & ncx = *m_normalContext;
			AngleDirMgrColl_Context & pcx = *m_parentContext;


			//F32ImageArrayHolder1C_Ref standev_InrWide_Img = new F32ImageArrayHolder1C(cx.m_org_Img->GetVirtAccessor().GetSize());
			F32ImageArrayHolder1C_Ref standev_InrWide_Img = F32ImageArrayHolder1C::CreateEmptyFrom(cx.m_org_Img);

			const int nInrRad = 5;
			//const int nInrRad = 5 * 2;
			//const int nInrRad = 8;
			//F32ImageArrayHolder3C_Ref avg_InrWide_Img = new F32ImageArrayHolder3C(cx.m_org_Img->GetVirtAccessor().GetSize());
			F32ImageArrayHolder3C_Ref avg_InrWide_Img = F32ImageArrayHolder3C::CreateEmptyFrom(cx.m_org_Img);
			////F32VectorValImageArrayHolder_3C_Ref avg_InrWide_Img = new F32VectorValImageArrayHolder_3C(cx.m_org_Img->GetVirtAccessor().GetSize());
			//F32VectorValImageArrayHolder_3C_Ref avg_InrWide_Img = F32VectorValImageArrayHolder_3C::CreateEmptyFrom(cx.m_org_Img);
			{
				Calc_Avg_And_Standev_Image(cx.m_org_Img->GetVirtAccessor(), avg_InrWide_Img->GetVirtAccessor(), standev_InrWide_Img->GetVirtAccessor(),
					Window<int>::New(-nInrRad, nInrRad, -nInrRad, nInrRad));

				MultiplyImageByNum(standev_InrWide_Img->GetVirtAccessor(), 2);
				//AssertValues_Image(avg_InrWide_Img->GetVirtAccessor());
			}

			//if (0 == m_context->m_nIndex)
			//{
			//	GlobalStuff::SetLinePathImg(GenTriChGrayImg(standev_InrWide_Img->GetSrcImg())); GlobalStuff::ShowLinePathImg();
			//	ShowImage(standev_InrWide_Img->GetSrcImg(), "standev_InrWide_Img->GetSrcImg()");
			//}

			////F32VectorValImageArrayHolder_4C_Ref cx.m_avgPStandev_InrWide_Img = new F32VectorValImageArrayHolder_4C(cx.m_org_Img->GetVirtAccessor().GetSize());
			//F32VectorValImageArrayHolder_4C_Ref cx.m_avgPStandev_InrWide_Img = F32VectorValImageArrayHolder_4C::CreateEmptyFrom(cx.m_org_Img);
			//cx.m_avgPStandev_InrWide_Img = new F32VectorValImageArrayHolder_4C(cx.m_org_Img->GetVirtAccessor().GetSize());
			cx.m_avgPStandev_InrWide_Img = F32VectorValImageArrayHolder_4C::CreateEmptyFrom(cx.m_org_Img);
			{
				const int nSize_1D = avg_InrWide_Img->GetActualAccessor().CalcSize_1D();

				F32VectorVal<4> * dest_Ptr = (F32VectorVal<4> *)cx.m_avgPStandev_InrWide_Img->GetActualAccessor().GetData();
				F32VectorVal<3> * src_Avg_Ptr = (F32VectorVal<3> *)avg_InrWide_Img->GetActualAccessor().GetData();
				float * src_Standev_Ptr = (float *)standev_InrWide_Img->GetActualAccessor().GetData();

				for (int i = 0; i < nSize_1D; i++)
				{
					AssertUndefinedOrValid(*(&src_Avg_Ptr[i]));
					AssertUndefinedOrValid(src_Standev_Ptr[i]);

					*((F32VectorVal<3> *)&dest_Ptr[i]) = *(&src_Avg_Ptr[i]);
					dest_Ptr[i].Vals[3] = src_Standev_Ptr[i];
				}
			}

		}

		void ImgAngleDirMgr::Proceed_3_2()
		{
			//Context & cx = *m_context;
			//Context & ncx = *m_normalContext;
			//AngleDirMgrColl_Context & pcx = *m_parentContext;

			AffectCommonAvgPStandev_InrWide();
		}

		void ImgAngleDirMgr::Proceed_4_1()
		{
			Context & cx = *m_context;
			Context & ncx = *m_normalContext;
			AngleDirMgrColl_Context & pcx = *m_parentContext;

			//const int nOutRad = 5;
			const int nOutRad = 8;
			//const int nOutRad = 8 * 2;
			{
				//F32ImageArrayHolder1C_Ref standev_OutWide_Img = new F32ImageArrayHolder1C(cx.m_org_Img->GetVirtAccessor().GetSize());
				F32ImageArrayHolder1C_Ref standev_OutWide_Img = F32ImageArrayHolder1C::CreateEmptyFrom(cx.m_org_Img);
				//F32VectorValImageArrayHolder_4C_Ref avg_OutWide_Img = new F32VectorValImageArrayHolder_4C(cx.m_org_Img->GetVirtAccessor().GetSize());
				F32VectorValImageArrayHolder_4C_Ref avg_OutWide_Img = F32VectorValImageArrayHolder_4C::CreateEmptyFrom(cx.m_org_Img);

				Calc_Avg_And_Standev_Image(cx.m_avgPStandev_InrWide_Img->GetVirtAccessor(), avg_OutWide_Img->GetVirtAccessor(), standev_OutWide_Img->GetVirtAccessor(),
					//Window<int>::New(-nOutRad, nOutRad, -nOutRad, nOutRad));
					Window<int>::New(-nOutRad, nOutRad, 0, 0));

				cx.m_wideConflictDiff_Img = standev_OutWide_Img;

				//GlobalStuff::SetLinePathImg(GenTriChGrayImg(standev_OutWide_Img->GetSrcImg())); GlobalStuff::ShowLinePathImg();
				//ShowImage(standev_OutWide_Img->GetSrcImg(), "standev_OutWide_Img->GetSrcImg()");
			}


			////------------

			////cx.m_wideConflictDiff_Img = new F32ImageArrayHolder1C(cx.m_org_Img->GetVirtAccessor().GetSize());
			//cx.m_wideConflictDiff_Img = F32ImageArrayHolder1C::CreateEmptyFrom(cx.m_org_Img);
			//{
			//	////Window<int> avgWin = Window<int>::New(-1, 1, -5, 5);
			//	////Window<int> avgWin = Window<int>::New(-1, 1, -2, 2);
			//	//Window<int> avgWin = Window<int>::New(-10, 10, -10, 10);
			//	////Window<int> avgWin = Window<int>::New(0, 0, -2, 2);
			//	Window<int> avgWin = Window<int>::New(-nOutRad, nOutRad, -nOutRad, nOutRad);

			////	F32VectorValImageArrayHolder_4C_Ref avg_Img = new F32VectorValImageArrayHolder_4C(cx.m_org_Img->GetVirtAccessor().GetSize());
			//	F32VectorValImageArrayHolder_4C_Ref avg_Img = F32VectorValImageArrayHolder_4C::CreateEmptyFrom(cx.m_org_Img);
			//	AvgImage(cx.m_avgPStandev_InrWide_Img->GetVirtAccessor(), avg_Img->GetVirtAccessor(), avgWin);

			////	F32ImageArrayHolder1C_Ref magSqr_Img = new F32ImageArrayHolder1C(cx.m_org_Img->GetVirtAccessor().GetSize());
			//	F32ImageArrayHolder1C_Ref magSqr_Img = F32ImageArrayHolder1C::CreateEmptyFrom(cx.m_org_Img);
			//	CalcMagSqrImage(cx.m_avgPStandev_InrWide_Img->GetVirtAccessor(), magSqr_Img->GetVirtAccessor());

			////	F32ImageArrayHolder1C_Ref avg_MagSqr_Img = new F32ImageArrayHolder1C(cx.m_org_Img->GetVirtAccessor().GetSize());
			//	F32ImageArrayHolder1C_Ref avg_MagSqr_Img = F32ImageArrayHolder1C::CreateEmptyFrom(cx.m_org_Img);
			//	AvgImage(magSqr_Img->GetVirtAccessor(), avg_MagSqr_Img->GetVirtAccessor(), avgWin);

			//	Range<int> confRange = Range<int>::New(
			//		//-10 - avgWin.GetX2(), 10 - avgWin.GetX1());
			//		//-1 - avgWin.GetX2(), 1 - avgWin.GetX1());
			//		-1 - nOutRad - nInrRad, 1 + nOutRad + nInrRad);

			//	Calc_ConflictDiff_Image_X(avg_Img->GetVirtAccessor(), avg_MagSqr_Img->GetVirtAccessor(),
			//		cx.m_wideConflictDiff_Img->GetVirtAccessor(), confRange);

			//	//GlobalStuff::SetLinePathImg(GenTriChGrayImg(cx.m_wideConflictDiff_Img->GetSrcImg())); GlobalStuff::ShowLinePathImg();
			//	//ShowImage(cx.m_wideConflictDiff_Img->GetSrcImg(), cx.MakeStrWithId("cx.m_wideConflictDiff_Img->GetSrcImg()").c_str());
			//}




		}

		void ImgAngleDirMgr::Proceed_4_2()
		{
			AffectCommonWideConflictDiff();
		}

		void ImgAngleDirMgr::AffectCommonAvgStandev()
		{
			Context & cx = *m_context;
			Context & ncx = *m_normalContext;

			const ActualArrayAccessor_2D<int> & orgToRotMap_Acc = cx.m_orgToRotMap_Img->GetActualAccessor();
			ActualArrayAccessor_1D<int> orgToRotMapAcc_1D = orgToRotMap_Acc.GenAcc_1D();
			
			const ActualArrayAccessor_2D<int> & rotToOrgMap_Acc = cx.m_rotToOrgMap_Img->GetActualAccessor();
			ActualArrayAccessor_1D<int> rotToOrgMapAcc_1D = rotToOrgMap_Acc.GenAcc_1D();

			// const ActualArrayAccessor_2D<int> & rotToOrgMap_Acc = cx.m_rotToOrgMap_Img->GetActualAccessor();

			ActualArrayAccessor_2D<PixelStandevInfoCmn> commonAcc = m_parentContext->m_standevInfoCmnImg->GetActualAccessor();
			Ncpp_ASSERT(Size_2D::AreEqual(orgToRotMap_Acc.GetSize(), commonAcc.GetSize()));

			ActualArrayAccessor_1D<PixelStandevInfoCmn> commonAcc_1D = commonAcc.GenAcc_1D();



			//float * localAcc_1D = (float *)cx.m_normAvgStandev_X_Img->GetActualAccessor().GetData();
			ActualArrayAccessor_1D<float> localAcc_1D = cx.m_normAvgStandev_X_Img->GetActualAccessor().GenAcc_1D();
			ActualArrayAccessor_1D<float> localAcc_1D_Norm = ncx.m_normAvgStandev_X_Img->GetActualAccessor().GenAcc_1D();

			//for (int y = 0; y < orgToRotMap_Acc.GetSize_Y(); y++)
			//{
			//	const int nOffset_Y = y * orgToRotMap_Acc.GetSize_X();

			//	for (int x = 0; x < orgToRotMap_Acc.GetSize_X(); x++)
			//	{
			//		const int nOffsetInOrg_1D = nOffset_Y + x;

			for (int y = 0; y < rotToOrgMap_Acc.GetSize_Y(); y++)
			{
				const int nOffset_Y = y * rotToOrgMap_Acc.GetSize_X();

				for (int x = 0; x < rotToOrgMap_Acc.GetSize_X(); x++)
				{
					const int nOffsetInRot_1D = nOffset_Y + x;

					int nOffsetInOrg_1D = rotToOrgMapAcc_1D[nOffsetInRot_1D];
					if (IsUndefined(nOffsetInOrg_1D))
					{
						continue;
					}

					PixelStandevInfoCmn & rCommonPsi = commonAcc_1D[nOffsetInOrg_1D];


					// S32Point pntInRot = rotToOrgMap_Acc.CalcPointFromIndex_1D(nOffsetInRot_1D);

					const float standev_Local = localAcc_1D[nOffsetInRot_1D];
					const float standev_Norm = localAcc_1D_Norm[nOffsetInRot_1D];

					rCommonPsi.allVals[cx.m_nIndex] = standev_Local;

					if (IsUndefined(standev_Local) || IsUndefined(standev_Norm))
					{
						continue;
					}
					
					//Ncpp_ASSERT(standev_Local >= 0.0f || standev_Local > -5000.0f);
					AssertValue(standev_Local);
					Ncpp_ASSERT(standev_Local >= -0.001);

					//if (standev_Local < rCommonPsi.Val)
					////if (1 == cx.m_nIndex)
					//{
					//	Assign(&rCommonPsi.Val, standev_Local);
					//	Assign(&rCommonPsi.NormLeastVal, standev_Norm);
					//	
					//	Assign(&rCommonPsi.Dir, cx.m_nIndex);
					//}


					if (IsUndefined(rCommonPsi))
					{
						Assign(&rCommonPsi.LeastVal, standev_Local);
						Assign(&rCommonPsi.NormLeastVal, standev_Norm);

						Assign(&rCommonPsi.LeastValDir, cx.m_nIndex);

						Assign(&rCommonPsi.SecondLeastVal, standev_Local);
						Assign(&rCommonPsi.NormSecondLeastVal, standev_Norm);

						Assign(&rCommonPsi.SecondLeastValDir, cx.m_nIndex);

						continue;
					}

					AssertValue(rCommonPsi);

					if (standev_Local < rCommonPsi.LeastVal)
					{
						Assign(&rCommonPsi.SecondLeastVal, rCommonPsi.LeastVal);
						Assign(&rCommonPsi.NormSecondLeastVal, rCommonPsi.NormLeastVal);

						Assign(&rCommonPsi.SecondLeastValDir, rCommonPsi.LeastValDir);

						Assign(&rCommonPsi.LeastVal, standev_Local);
						Assign(&rCommonPsi.NormLeastVal, standev_Norm);

						Assign(&rCommonPsi.LeastValDir, cx.m_nIndex);
					}
					else if (standev_Local < rCommonPsi.SecondLeastVal)
					{
						Assign(&rCommonPsi.SecondLeastVal, standev_Local);
						Assign(&rCommonPsi.NormSecondLeastVal, standev_Norm);

						Assign(&rCommonPsi.SecondLeastValDir, cx.m_nIndex);
					}

					AssertValue(rCommonPsi);

					////else if (standev_Local > rCommonPsi.MaxVal)
					//if (standev_Local > rCommonPsi.MaxVal)
					//{
					//	Assign(&rCommonPsi.MaxVal, standev_Local);
					//	Assign(&rCommonPsi.MaxValDir, cx.m_nIndex);
					//}

				}
			}

		}

		void ImgAngleDirMgr::AffectCommonAvgPStandev_InrWide()
		{
			Context & cx = *m_context;
			Context & ncx = *m_normalContext;
			AngleDirMgrColl_Context & pcx = *m_parentContext;

			const ActualArrayAccessor_2D<int> & orgToRotMap_Acc = cx.m_orgToRotMap_Img->GetActualAccessor();
			ActualArrayAccessor_1D<int> orgToRotMapAcc_1D = orgToRotMap_Acc.GenAcc_1D();

			ActualArrayAccessor_2D<int> rotToOrgMap_Acc = m_context->m_rotToOrgMap_Img->GetActualAccessor();
			ActualArrayAccessor_1D<int> rotToOrgMapAcc_1D = rotToOrgMap_Acc.GenAcc_1D();

			ActualArrayAccessor_1D<VectorVal<Float, 4>> commonAcc_1D = pcx.m_avgPStandev_InrWide_Img->GetActualAccessor().GenAcc_1D();
			ActualArrayAccessor_1D<VectorVal<Float, 4>> localAcc_1D = cx.m_avgPStandev_InrWide_Img->GetActualAccessor().GenAcc_1D();

			//for (int y = 0; y < orgToRotMap_Acc.GetSize_Y(); y++)
			//{
			//	const int nOffset_Y = y * orgToRotMap_Acc.GetSize_X();

			//	for (int x = 0; x < orgToRotMap_Acc.GetSize_X(); x++)
			//	{
			//		const int nOffsetInOrg_1D = nOffset_Y + x;

			for (int y = 0; y < rotToOrgMap_Acc.GetSize_Y(); y++)
			{
				const int nOffset_Y = y * rotToOrgMap_Acc.GetSize_X();

				for (int x = 0; x < rotToOrgMap_Acc.GetSize_X(); x++)
				{
					const int nOffsetInRot_1D = nOffset_Y + x;

					Ncpp_ASSERT(nOffsetInRot_1D >= 0);

					int nOffsetInOrg_1D = rotToOrgMapAcc_1D[nOffsetInRot_1D];
					if (IsUndefined(nOffsetInOrg_1D))
					{
						continue;
					}


					VectorVal<Float, 4> * pCommonVal = &commonAcc_1D[nOffsetInOrg_1D];
					if (IsUndefined(*pCommonVal))
						continue;

					AssertValue(*pCommonVal);

					VectorVal<Float, 4> & val_Local = localAcc_1D[nOffsetInRot_1D];
					AssertUndefinedOrValid(val_Local);
					if (IsUndefined(val_Local))
					{
						//SetToUndefined(pCommonVal);
						continue;
					}
					
					IncBy(*pCommonVal, val_Local);
				}
			}

		}
		

		void ImgAngleDirMgr::ConfirmConflict()
		{
			Context & cx = *m_context;
			Context & ncx = *m_normalContext;
			AngleDirMgrColl_Context & pcx = *m_parentContext;


			////	for debug.
			//if (//0 != cx.m_nIndex &&
			//	//4 != cx.m_nIndex
			//	1 != cx.m_nIndex
			//	)
			//{
			//	return;
			//}


			//const ActualArrayAccessor_2D<int> & orgToRotMap_Acc = cx.m_orgToRotMap_Img->GetActualAccessor();

			//ActualArrayAccessor_1D<int> orgToRotMapAcc_1D = orgToRotMap_Acc.GenAcc_1D();
			
			ActualArrayAccessor_2D<int> rotToOrgMap_Acc = cx.m_rotToOrgMap_Img->GetActualAccessor();
			ActualArrayAccessor_1D<int> rotToOrgMapAcc_1D = rotToOrgMap_Acc.GenAcc_1D();

			//ActualArrayAccessor_1D<ConflictInfo2_Ex> commonImgAcc_1D = m_parentContext->m_conflictInfoImg->GetActualAccessor().GenAcc_1D();
			
			//ActualArrayAccessor_2D<ConflictInfo2> localAcc = cx.m_conflict_Img->GetActualAccessor();
			VirtArrayAccessor_2D<ConflictInfo2> localVirtAcc = cx.m_conflict_Img->GetVirtAccessor();
			//ActualArrayAccessor_1D<ConflictInfo2> localAcc_1D = localAcc.GenAcc_1D();
			
			//Ncpp_ASSERT(Size_2D::AreEqual(localVirtAcc.GetSize(), rotToOrgMap_Acc.GetSize()));


			//ActualArrayAccessor_2D<PixelStandevInfoCmn> commonPsiAcc = m_parentContext->m_standevInfoCmnImg->GetActualAccessor();
			//ActualArrayAccessor_1D<PixelStandevInfoCmn> commonPsiAcc_1D = commonPsiAcc.GenAcc_1D();

			//--
			
			//ActualArrayAccessor_1D<float> localStandevX_Acc_1D = cx.m_normAvgStandev_X_Img->GetActualAccessor().GenAcc_1D();
			//ActualArrayAccessor_1D<float> localStandevX_Acc_1D_Norm = ncx.m_normAvgStandev_X_Img->GetActualAccessor().GenAcc_1D();


			
			
			//--


			//for (int y = 0; y < orgToRotMap_Acc.GetSize_Y(); y++)
			//{
			//	const int nOffset_Y = y * orgToRotMap_Acc.GetSize_X();

			//	for (int x = 0; x < orgToRotMap_Acc.GetSize_X(); x++)
			//	{
			//		const int nOffsetInOrg_1D = nOffset_Y + x;

			//		ConflictInfo2_Ex & rCommonConf = commonImgAcc_1D[nOffsetInOrg_1D];
			//		
			//		AssertValue(rCommonConf);

			//		const int nOffsetInRot_1D = orgToRotMapAcc_1D[nOffsetInOrg_1D];

			const int crossMarg = 1;
			//const int crossMarg = 3;
			//const int crossMarg = 5;

			//for (int y = crossMarg; y < rotToOrgMap_Acc.GetSize_Y() - crossMarg; y++)
			//{
			//	const int nOffset_Y = y * rotToOrgMap_Acc.GetSize_X();

			//	for (int x = 0; x < rotToOrgMap_Acc.GetSize_X(); x++)
			//	{
			//		const int nOffsetInRot_1D = nOffset_Y + x;

			//for (int y = crossMarg, nOffsetInRot_0_1D = 0; y < localVirtAcc.GetSize_Y() - crossMarg; y++)
			for (int y = crossMarg; y < localVirtAcc.GetSize_Y() - crossMarg; y++)
			{
				//const int nOffset_Y = y * rotToOrgMap_Acc.GetSize_X();

				//for (int x = 0; x < localVirtAcc.GetSize_X(); x++, nOffsetInRot_0_1D++)
				for (int x = 0; x < localVirtAcc.GetSize_X(); x++)
				{

					//	for debug.
					const int nOffsetInRot_1D = localVirtAcc.CalcActualIndex_1D(x, y);
					//Ncpp_ASSERT(nOffsetInRot_1D == nOffsetInRot_0_1D);

					if (144467 == nOffsetInRot_1D && 1 == cx.m_nIndex)
					{
						x = x;
					}

					//ConflictInfo2 & conf_Local = localAcc_1D[nOffsetInRot_1D];
					ConflictInfo2 & conf_Local = localVirtAcc.GetAt(x, y);
					if (IsUndefined(conf_Local))
						continue;

					//	for debug.
					const int nOffsetInOrg_1D = rotToOrgMapAcc_1D[nOffsetInRot_1D];
					Ncpp_ASSERT(!IsUndefined(nOffsetInOrg_1D));


					//ConflictInfo2_Ex & rCommonConf = commonImgAcc_1D[nOffsetInOrg_1D];
					//AssertValue(rCommonConf);


					//const float standev_Local = localStandevX_Acc_1D[nOffsetInRot_1D];
					//const float standev_Norm = localStandevX_Acc_1D_Norm[nOffsetInRot_1D];


					//const PixelStandevInfoCmn & rCommonPsi = commonPsiAcc_1D[nOffsetInOrg_1D];

					////	for debug.
					//const int dirIndex = cx.m_nIndex;
					////if (2156 == rCommonPsi.Index)
					////if (135426 == rCommonPsi.Index)
					////if (142213 == rCommonPsi.Index)
					//if (52104 == rCommonPsi.Index)
					//{
					//	x = x;
					//}

					if (!conf_Local.Exists)
					{
						continue;
					}


					Ncpp_ASSERT(conf_Local.Offset_Side_1 >= 0);
					// S32Point rotPnt_Side1 = rotToOrgMap_Acc.CalcPointFromIndex_1D(conf_Local.Offset_Side_1);
					// Ncpp_ASSERT(rotPnt_Side1.GetX() >= 0 && rotPnt_Side1.GetY() >= 0);

					//int nOffset_Side_1_Mapped = rotToOrgMapAcc_1D[conf_Local.Offset_Side_1];
					//Ncpp_ASSERT(nOffset_Side_1_Mapped >= 0);
					//if (nOffset_Side_1_Mapped < 0)
					//	continue;

					Ncpp_ASSERT(conf_Local.Offset_Side_2 >= 0);
					// S32Point rotPnt_Side2 = rotToOrgMap_Acc.CalcPointFromIndex_1D(conf_Local.Offset_Side_2);
					// Ncpp_ASSERT(rotPnt_Side2.GetX() >= 0 && rotPnt_Side2.GetY() >= 0);

					//int nOffset_Side_2_Mapped = rotToOrgMapAcc_1D[conf_Local.Offset_Side_2];
					//Ncpp_ASSERT(nOffset_Side_2_Mapped >= 0);
					//if (nOffset_Side_2_Mapped < 0)
					//	continue;

					//if (IsUndefined(standev_Local) || IsUndefined(standev_Norm))
					//{
					//	continue;
					//}

					////if (standev_Local > 0.5 * standev_Norm)
					////if (standev_Local > 2 * standev_Norm)
					////if (standev_Local < 2 * standev_Norm)
					//if (standev_Local < 3 * standev_Norm)
					//{
					//	continue;
					//}

					//if (standev_Local < 20)
					//{
					//	continue;
					//}

					ConflictInfo2 & conf_Bef_Local = localVirtAcc.GetAt(x, y - crossMarg);
					//if (IsUndefined(conf_Bef_Local) || !conf_Bef_Local.Exists)
					if (IsUndefined(conf_Bef_Local))
						continue;

					ConflictInfo2 & conf_Aft_Local = localVirtAcc.GetAt(x, y + crossMarg);
					//if (IsUndefined(conf_Aft_Local) || !conf_Aft_Local.Exists)
					if (IsUndefined(conf_Aft_Local))
						continue;

					//if (conf_Bef_Local.Exists != conf_Aft_Local.Exists)
					if (!conf_Bef_Local.Exists || !conf_Aft_Local.Exists)
						continue;


					conf_Local.IsConfirmed = true;

				}	//	end for x.
			}	//	end for y.

			if (0 == cx.m_nIndex ||
				4 == cx.m_nIndex ||
				1 == cx.m_nIndex
				)
			{
				DisplayConflictImg();
			}

		}

		void ImgAngleDirMgr::AffectCommonConflict()
		{
			Context & cx = *m_context;
			Context & ncx = *m_normalContext;
			AngleDirMgrColl_Context & pcx = *m_parentContext;


			//	for debug.
			if (0 != cx.m_nIndex
				//4 != cx.m_nIndex
				//1 != cx.m_nIndex
				)
			{
				return;
			}

			//ActualArrayAccessor_2D<F32ColorVal> orgImg_Acc = cx.m_org_Img->GetActualAccessor();
			ActualArrayAccessor_2D<F32ColorVal> orgImg_Acc = pcx.m_org_Img->GetActualAccessor();
			ActualArrayAccessor_1D<F32ColorVal> orgImg_Acc_1D = orgImg_Acc.GenAcc_1D();

			ActualArrayAccessor_2D<int> rotToOrgMap_Acc = cx.m_rotToOrgMap_Img->GetActualAccessor();
			ActualArrayAccessor_1D<int> rotToOrgMapAcc_1D = rotToOrgMap_Acc.GenAcc_1D();

			ActualArrayAccessor_2D<ConflictInfo2_Ex> commonImgAcc = pcx.m_conflictInfoImg->GetActualAccessor();
			ActualArrayAccessor_1D<ConflictInfo2_Ex> commonImgAcc_1D = commonImgAcc.GenAcc_1D();
			//Ncpp_ASSERT(Size_2D::AreEqual(orgImg_Acc.GetSize(), orgToRotMap_Acc.GetSize()));
			Ncpp_ASSERT(Size_2D::AreEqual(orgImg_Acc.GetSize(), commonImgAcc.GetSize()));

			//ActualArrayAccessor_1D<ConflictInfo2> localAcc_1D = cx.m_conflict_Img->GetActualAccessor().GenAcc_1D();
			ActualArrayAccessor_2D<ConflictInfo2> localAcc = cx.m_conflict_Img->GetActualAccessor();
			ActualArrayAccessor_1D<ConflictInfo2> localAcc_1D = localAcc.GenAcc_1D();

			Ncpp_ASSERT(Size_2D::AreEqual(localAcc.GetSize(), rotToOrgMap_Acc.GetSize()));


			for (int y = 0; y < rotToOrgMap_Acc.GetSize_Y(); y++)
			{
				const int nOffset_Y = y * rotToOrgMap_Acc.GetSize_X();

				for (int x = 0; x < rotToOrgMap_Acc.GetSize_X(); x++)
				{
					const int nOffsetInRot_1D = nOffset_Y + x;

					ConflictInfo2 & conf_Local = localAcc_1D[nOffsetInRot_1D];
					if (IsUndefined(conf_Local))
						continue;

					if (!conf_Local.IsConfirmed)
					{
						continue;
					}

					const int nOffsetInOrg_1D = rotToOrgMapAcc_1D[nOffsetInRot_1D];
					Ncpp_ASSERT(!IsUndefined(nOffsetInOrg_1D));
					//if (IsUndefined(nOffsetInOrg_1D))
					//{
					//	continue;
					//}

					ConflictInfo2_Ex & rCommonConf = commonImgAcc_1D[nOffsetInOrg_1D];
					AssertValue(rCommonConf);



					Ncpp_ASSERT(conf_Local.Offset_Side_1 >= 0);
					// S32Point rotPnt_Side1 = rotToOrgMap_Acc.CalcPointFromIndex_1D(conf_Local.Offset_Side_1);
					// Ncpp_ASSERT(rotPnt_Side1.GetX() >= 0 && rotPnt_Side1.GetY() >= 0);

					int nOffset_Side_1_Mapped = rotToOrgMapAcc_1D[conf_Local.Offset_Side_1];
					Ncpp_ASSERT(nOffset_Side_1_Mapped >= 0);
					if (nOffset_Side_1_Mapped < 0)
						continue;

					Ncpp_ASSERT(conf_Local.Offset_Side_2 >= 0);
					// S32Point rotPnt_Side2 = rotToOrgMap_Acc.CalcPointFromIndex_1D(conf_Local.Offset_Side_2);
					// Ncpp_ASSERT(rotPnt_Side2.GetX() >= 0 && rotPnt_Side2.GetY() >= 0);

					int nOffset_Side_2_Mapped = rotToOrgMapAcc_1D[conf_Local.Offset_Side_2];
					Ncpp_ASSERT(nOffset_Side_2_Mapped >= 0);
					if (nOffset_Side_2_Mapped < 0)
						continue;

					S32Point pntSide1_Mapped = orgImg_Acc.CalcPointFromIndex_1D(nOffset_Side_1_Mapped);
					S32Point pntSide2_Mapped = orgImg_Acc.CalcPointFromIndex_1D(nOffset_Side_2_Mapped);

					F32ColorVal & rMappedToOrgVal_1 = orgImg_Acc_1D[nOffset_Side_1_Mapped];
					F32ColorVal & rMappedToOrgVal_2 = orgImg_Acc_1D[nOffset_Side_2_Mapped];
					F32ColorVal diffInOrg;
					Subtract(rMappedToOrgVal_1, rMappedToOrgVal_2, &diffInOrg);
					float diffMagInOrg = diffInOrg.CalcMag();

					//	for debug.
					S32Point testPnt(353, 63);
					if (S32Point::AreEqual(pntSide1_Mapped, testPnt) ||
						S32Point::AreEqual(pntSide2_Mapped, testPnt)
						)
					{
						x = x;
					}

					////Ncpp_ASSERT(diffMagInOrg > 40);
					//Ncpp_ASSERT(diffMagInOrg > 19);
					////Ncpp_ASSERT(diffMagInOrg > 17);
					////if (diffMagInOrg < 40)
					//if (diffMagInOrg < 19)
					//	continue;

					if (1 != cx.m_nIndex)
						x = x;

					rCommonConf.Exists = true;
					rCommonConf.Offset_Side_1 = nOffset_Side_1_Mapped;
					rCommonConf.Offset_Side_2 = nOffset_Side_2_Mapped;

					rCommonConf.Dir = cx.m_nIndex;

				}	//	end for x.
			}	//	end for y.

			//if (0 == cx.m_nIndex ||
			//	4 == cx.m_nIndex
			//	)
			//{
			//	DisplayConflictImg();
			//}

		}



		void ImgAngleDirMgr::AffectCommonBidiffInfo()
		{

			Context & cx = *m_context;
			Context & ncx = *m_normalContext;
			AngleDirMgrColl_Context & pcx = *m_parentContext;

			const ActualArrayAccessor_2D<int> & orgToRotMap_Acc = cx.m_orgToRotMap_Img->GetActualAccessor();
			ActualArrayAccessor_1D<int> orgToRotMapAcc_1D = orgToRotMap_Acc.GenAcc_1D();

			const ActualArrayAccessor_2D<int> & rotToOrgMap_Acc = cx.m_rotToOrgMap_Img->GetActualAccessor();
			ActualArrayAccessor_1D<int> rotToOrgMapAcc_1D = rotToOrgMap_Acc.GenAcc_1D();

			ActualArrayAccessor_2D<BidiffInfoCommon> commonAcc = m_parentContext->m_bidiffInfoCommonImg->GetActualAccessor();
			Ncpp_ASSERT(Size_2D::AreEqual(orgToRotMap_Acc.GetSize(), commonAcc.GetSize()));

			ActualArrayAccessor_1D<BidiffInfoCommon> commonAcc_1D = commonAcc.GenAcc_1D();


			ActualArrayAccessor_2D<PixelStandevInfoCmn> commonPsiAcc = m_parentContext->m_standevInfoCmnImg->GetActualAccessor();
			ActualArrayAccessor_1D<PixelStandevInfoCmn> commonPsiAcc_1D = commonPsiAcc.GenAcc_1D();




			//ActualArrayAccessor_2D<BidiffInfo> localAcc = cx.m_bidiffInfo_Img->GetActualAccessor();
			//ActualArrayAccessor_2D<BidiffInfo> localAcc_Norm = ncx.m_bidiffInfo_Img->GetActualAccessor();

			VirtArrayAccessor_2D<BidiffInfo> localVirtAcc = cx.m_bidiffInfo_Img->GetVirtAccessor();
			VirtArrayAccessor_2D<BidiffInfo> localVirtAcc_Norm = ncx.m_bidiffInfo_Img->GetVirtAccessor();

			//float * localAcc_1D = (float *)cx.m_normAvgStandev_X_Img->GetActualAccessor().GetData();
			ActualArrayAccessor_1D<BidiffInfo> localAcc_1D = cx.m_bidiffInfo_Img->GetActualAccessor().GenAcc_1D();
			ActualArrayAccessor_1D<BidiffInfo> localAcc_1D_Norm = ncx.m_bidiffInfo_Img->GetActualAccessor().GenAcc_1D();

			const float diff2CmpRatio = 0.7;
			//const float diff2CmpRatio = 0.4;

			const int posDist_Local = pcx.GetDiffPosDist() * localVirtAcc.GetStepSize_X();
			const int posDist_Norm = pcx.GetDiffPosDist() * localVirtAcc_Norm.GetStepSize_X();

			for (int y = 0; y < rotToOrgMap_Acc.GetSize_Y(); y++)
			{
				const int nOffset_Y = y * rotToOrgMap_Acc.GetSize_X();

				for (int x = 0; x < rotToOrgMap_Acc.GetSize_X(); x++)
				{
					const int nOffsetInRot_1D = nOffset_Y + x;

					const int nOffsetInOrg_1D = rotToOrgMapAcc_1D[nOffsetInRot_1D];

					if (IsUndefined(nOffsetInOrg_1D))
					{
						continue;
					}


					const PixelStandevInfoCmn & rCommonPsi = commonPsiAcc_1D[nOffsetInOrg_1D];




					
					if (IsUndefined(rCommonPsi))
					{
						continue;
					}

					//if (IsUndefined(rCommonPsi) || !rCommonPsi.IsDirClear() ||
					//if (!rCommonPsi.IsDirClear() || rCommonPsi.LeastValDir != m_context->m_nIndex)
					if (!rCommonPsi.IsDirClear())
					{
						//Ncpp_ASSERT(!IsUndefined(rCommonPsi));
						continue;
					}


					//	for debug.
					const int dirIndex = m_context->m_nIndex;
					if (2156 == rCommonPsi.Index)
					{
						x = x;
					}


					if (rCommonPsi.LeastValDir != m_context->m_nIndex)
					{
						//Ncpp_ASSERT(!IsUndefined(rCommonPsi));
						continue;
					}




					BidiffInfoCommon & rCommonBdc = commonAcc_1D[nOffsetInOrg_1D];

					//const int nOffsetInOrg_1D_2 = rotToOrgMapAcc_1D[nOffsetInRot_1D];

					////Ncpp_ASSERT(nOffsetInOrg_1D == nOffsetInOrg_1D_2);
					//Ncpp_ASSERT(nOffsetInOrg_1D == nOffsetInOrg_1D_2 || IsUndefined(nOffsetInOrg_1D_2));

					S32Point pntInRot = rotToOrgMap_Acc.CalcPointFromIndex_1D(nOffsetInRot_1D);

					const BidiffInfo & rBidiffInfo_Local = localAcc_1D[nOffsetInRot_1D];
					const BidiffInfo & rBidiffInfo_Norm = localAcc_1D_Norm[nOffsetInRot_1D];

					//rCommonBdc.allVals[cx.m_nIndex] = bidiffInfo_Local;

					if ((IsUndefined(rBidiffInfo_Local.Diff1_BkwdMag) && IsUndefined(rBidiffInfo_Local.Diff1_FwdMag)) ||
						(IsUndefined(rBidiffInfo_Norm.Diff1_BkwdMag) && IsUndefined(rBidiffInfo_Norm.Diff1_FwdMag)) ||
						(IsUndefined(rBidiffInfo_Norm.Diff2_Mag)))
					{
						continue;
					}

					float bidiffInfoMin_Local, bidiffInfoMax_Local;
					{
						MaxFinder<float> maxFinder;
						MinFinder<float> minFinder;

						if (!IsUndefined(rBidiffInfo_Local.Diff1_BkwdMag))
						{
							maxFinder.PushValue(rBidiffInfo_Local.Diff1_BkwdMag);
							minFinder.PushValue(rBidiffInfo_Local.Diff1_BkwdMag);
						}

						if (!IsUndefined(rBidiffInfo_Local.Diff1_FwdMag))
						{
							maxFinder.PushValue(rBidiffInfo_Local.Diff1_FwdMag);
							minFinder.PushValue(rBidiffInfo_Local.Diff1_FwdMag);
						}

						bidiffInfoMax_Local = maxFinder.FindMax();
						AssertValue(bidiffInfoMax_Local);
						Ncpp_ASSERT(bidiffInfoMax_Local >= -0.001);

						bidiffInfoMin_Local = minFinder.FindMin();
						AssertValue(bidiffInfoMin_Local);
						Ncpp_ASSERT(bidiffInfoMin_Local >= -0.001);
					}

					float bidiffInfoMin_Norm, bidiffInfoMax_Norm, bidiffInfoDiff2_Norm;
					{
						MaxFinder<float> maxFinder;
						MinFinder<float> minFinder;

						if (!IsUndefined(rBidiffInfo_Norm.Diff1_BkwdMag))
						{
							maxFinder.PushValue(rBidiffInfo_Norm.Diff1_BkwdMag);
							minFinder.PushValue(rBidiffInfo_Norm.Diff1_BkwdMag);
						}

						if (!IsUndefined(rBidiffInfo_Norm.Diff1_FwdMag))
						{
							maxFinder.PushValue(rBidiffInfo_Norm.Diff1_FwdMag);
							minFinder.PushValue(rBidiffInfo_Norm.Diff1_FwdMag);
						}

						bidiffInfoMax_Norm = maxFinder.FindMax();
						AssertValue(bidiffInfoMax_Norm);
						Ncpp_ASSERT(bidiffInfoMax_Norm >= -0.001);

						bidiffInfoMin_Norm = minFinder.FindMin();
						AssertValue(bidiffInfoMin_Norm);
						Ncpp_ASSERT(bidiffInfoMin_Norm >= -0.001);

						bidiffInfoDiff2_Norm = rBidiffInfo_Norm.Diff2_Mag;
					}



					//if (standev_Local < rCommonBdc.Val)
					////if (1 == cx.m_nIndex)
					//{
					//	Assign(&rCommonBdc.Val, standev_Local);
					//	Assign(&rCommonBdc.NormLeastVal, standev_Norm);
					//	
					//	Assign(&rCommonBdc.Dir, cx.m_nIndex);
					//}



					//if (4 == cx.m_nIndex)
					//if (bidiffInfoMax_Norm > 300 && 4 == cx.m_nIndex && 158 == y)
					//if ((0 == cx.m_nIndex || 4 == cx.m_nIndex) && 129 == x && 158 == y)
					//if ((0 == cx.m_nIndex || 4 == cx.m_nIndex) && 430 == x && 231 == y)
					if ((0 == cx.m_nIndex || 4 == cx.m_nIndex) && 539 == x && 282 == y)
					{
						x = x;
					}

					const bool isEdge = bidiffInfoDiff2_Norm > diff2CmpRatio * bidiffInfoMax_Norm && bidiffInfoMax_Norm > 20
						&& bidiffInfoMin_Local < 0.4 * bidiffInfoMax_Norm
						//&& bidiffInfoMax_Local < 0.4 * bidiffInfoMax_Norm
						//&& 0 == cx.m_nIndex % 2
						;


					if (IsUndefined(rCommonBdc))
					{
						//if (bidiffInfoMax_Norm > 0)
						if (bidiffInfoMax_Norm > 300 && 4 == cx.m_nIndex && 158 == y)
						{
							x = x;
						}

						Assign(&rCommonBdc.LeastValDirMaxVal, bidiffInfoMax_Local);
						Assign(&rCommonBdc.LeastValDirMinVal, bidiffInfoMin_Local);
						//Assign(&rCommonBdc.LeastVal, bidiffInfoMin_Local);
						Assign(&rCommonBdc.NormLeastVal, bidiffInfoMax_Norm);
						Assign(&rCommonBdc.NormDiff2LeastVal, bidiffInfoDiff2_Norm);

						if (isEdge)
						{
							if (174251 == rCommonBdc.Index)
							{
								x = x;
							}

							rCommonBdc.IsEdge = true;
						}
						else
						{
							rCommonBdc.IsEdge = false;
						}

						Assign(&rCommonBdc.LeastValDir, cx.m_nIndex);

						Assign(&rCommonBdc.SecondLeastVal, bidiffInfoMax_Local);
						//Assign(&rCommonBdc.SecondLeastVal, bidiffInfoMin_Local);
						Assign(&rCommonBdc.NormSecondLeastVal, bidiffInfoMax_Norm);

						Assign(&rCommonBdc.SecondLeastValDir, cx.m_nIndex);

						continue;
					}

					AssertValue(rCommonBdc);

					if (!isEdge)
					{
						continue;
					}

					if (174251 == rCommonBdc.Index)
					{
						x = x;
					}

					if (!rCommonBdc.IsEdge || bidiffInfoMax_Local < rCommonBdc.LeastValDirMaxVal)
						//if (bidiffInfoMin_Local < rCommonBdc.LeastVal)
					{
						if (0 != cx.m_nIndex)
						{
							x = x;
						}

						Assign(&rCommonBdc.SecondLeastVal, rCommonBdc.LeastValDirMaxVal);
						Assign(&rCommonBdc.NormSecondLeastVal, rCommonBdc.NormLeastVal);

						Assign(&rCommonBdc.SecondLeastValDir, rCommonBdc.LeastValDir);

						Assign(&rCommonBdc.LeastValDirMaxVal, bidiffInfoMax_Local);
						Assign(&rCommonBdc.LeastValDirMinVal, bidiffInfoMin_Local);
						//Assign(&rCommonBdc.LeastVal, bidiffInfoMin_Local);
						Assign(&rCommonBdc.NormLeastVal, bidiffInfoMax_Norm);
						Assign(&rCommonBdc.NormDiff2LeastVal, bidiffInfoDiff2_Norm);

						Assign(&rCommonBdc.LeastValDir, cx.m_nIndex);
					}
					else if (bidiffInfoMax_Local < rCommonBdc.SecondLeastVal)
						//else if (bidiffInfoMin_Local < rCommonBdc.SecondLeastVal)
					{
						Assign(&rCommonBdc.SecondLeastVal, bidiffInfoMax_Local);
						//Assign(&rCommonBdc.SecondLeastVal, bidiffInfoMin_Local);
						Assign(&rCommonBdc.NormSecondLeastVal, bidiffInfoMax_Norm);

						Assign(&rCommonBdc.SecondLeastValDir, cx.m_nIndex);
					}

					rCommonBdc.IsEdge = true;

					AssertValue(rCommonBdc);

					////else if (bidiffInfoMax_Local > rCommonBdc.MaxVal)
					//if (bidiffInfoMax_Local > rCommonBdc.MaxVal)
					//{
					//	Assign(&rCommonBdc.MaxVal, bidiffInfoMax_Local);
					//	Assign(&rCommonBdc.MaxValDir, cx.m_nIndex);
					//}

				}	//	x for end.
			}	//	y	for end.


		}

		void ImgAngleDirMgr::AffectCommonWideConflictDiff()
		{
			Context & cx = *m_context;
			Context & ncx = *m_normalContext;
			AngleDirMgrColl_Context & pcx = *m_parentContext;

			const ActualArrayAccessor_2D<int> & orgToRotMap_Acc = cx.m_orgToRotMap_Img->GetActualAccessor();
			ActualArrayAccessor_1D<int> orgToRotMapAcc_1D = orgToRotMap_Acc.GenAcc_1D();

			ActualArrayAccessor_2D<int> rotToOrgMap_Acc = m_context->m_rotToOrgMap_Img->GetActualAccessor();
			ActualArrayAccessor_1D<int> rotToOrgMapAcc_1D = rotToOrgMap_Acc.GenAcc_1D();

			ActualArrayAccessor_1D<float> commonAcc_1D = pcx.m_wideConflictDiff_Img->GetActualAccessor().GenAcc_1D();

			float * localAcc_1D = (float *)cx.m_wideConflictDiff_Img->GetActualAccessor().GetData();
			//float * localAcc_1D_Norm = (float *)ncx.m_wideConflictDiff_Img->GetActualAccessor().GetData();

			//for (int y = 0; y < orgToRotMap_Acc.GetSize_Y(); y++)
			//{
			//	const int nOffset_Y = y * orgToRotMap_Acc.GetSize_X();

			//	for (int x = 0; x < orgToRotMap_Acc.GetSize_X(); x++)
			//	{
			//		const int nOffsetInOrg_1D = nOffset_Y + x;

			for (int y = 0; y < rotToOrgMap_Acc.GetSize_Y(); y++)
			{
				const int nOffset_Y = y * rotToOrgMap_Acc.GetSize_X();

				for (int x = 0; x < rotToOrgMap_Acc.GetSize_X(); x++)
				{
					const int nOffsetInRot_1D = nOffset_Y + x;

					Ncpp_ASSERT(nOffsetInRot_1D >= 0);


					int nOffsetInOrg_1D = rotToOrgMapAcc_1D[nOffsetInRot_1D];
					if (IsUndefined(nOffsetInOrg_1D))
					{
						continue;
					}


					float & rCommonConf = commonAcc_1D[nOffsetInOrg_1D];
					AssertValue(rCommonConf);

					float & conf_Local = localAcc_1D[nOffsetInRot_1D];
					if (IsUndefined(conf_Local))
					{
						continue;
					}

					if (conf_Local > rCommonConf)
					{
						rCommonConf = conf_Local;
					}

				}
			}


		}

		void ImgAngleDirMgr::DisplayConflictImg()
		{
			Context & cx = *m_context;

			const ActualArrayAccessor_2D<ConflictInfo2> & confAcc = cx.m_conflict_Img->GetActualAccessor();
			F32ImageRef confDsp_Img = F32Image::Create(toCvSize(confAcc.GetSize()), 3);

			confDsp_Img->SetAll(0);

			ActualArrayAccessor_1D<F32ColorVal> dispAcc_1D((F32ColorVal *)confDsp_Img->GetDataPtr(), confDsp_Img->GetSize1D());


			const ActualArrayAccessor_1D<ConflictInfo2> & confAcc_1D = confAcc.GenAcc_1D();

			//	for debug,
			//int dbgCenter_Pnt(0, 0), dbgSide1_Pnt(0, 0), dbgSide2_Pnt(0, 0);
			int dbgCenter_Idx = -1;

			//float angle_Old = -1;
			for (int i = 0; i < confAcc_1D.GetSize(); i++)
			{
				ConflictInfo2 & rSrc = confAcc_1D[i];
				if (IsUndefined(rSrc))
				{
					continue;
				}

				AssertValue(rSrc);

				F32ColorVal & rDest = dispAcc_1D[i];

				//rDest.val0 = 0;
				//rDest.val1 = 255;
				//rDest.val2 = 255;

				//continue;

				//Ncpp_ASSERT(-1 != rSrc.Dir);

				//if (rSrc.Exists)
				if (rSrc.IsConfirmed)
				{
					//	for debug,
					dbgCenter_Idx = i;

					F32ColorVal & rDest_Side_1 = dispAcc_1D[rSrc.Offset_Side_1];
					F32ColorVal & rDest_Side_2 = dispAcc_1D[rSrc.Offset_Side_2];

					rDest.val0 = 0;
					rDest.val1 = 0;
					rDest.val2 = 100;

					//rDest_Side_1.val0 = 0;
					//rDest_Side_1.val1 = 100;
					//rDest_Side_1.val2 = 0;

					//rDest_Side_2.val0 = 0;
					//rDest_Side_2.val1 = 100;
					//rDest_Side_2.val2 = 0;
				}
				//else
				//{
				//	rDest.val0 = 0;
				//	rDest.val1 = 0;
				//	rDest.val2 = 0;
				//}
			}	//	end i for.

			//	for debug,
			{
				//dbgCenter_Idx = 144467;
				dbgCenter_Idx = 288212;
				ConflictInfo2 & rSrc = confAcc_1D[dbgCenter_Idx];
				Ncpp_ASSERT(!IsUndefined(rSrc));

				F32ColorVal & rDest = dispAcc_1D[dbgCenter_Idx];
				F32ColorVal & rDest_Side_1 = dispAcc_1D[rSrc.Offset_Side_1];
				F32ColorVal & rDest_Side_2 = dispAcc_1D[rSrc.Offset_Side_2];

				rDest.val0 = 155;
				//rDest.val1 = 100;
				rDest.val1 = 255;
				//rDest.val2 = 255;
				rDest.val2 = 0;

				//rDest_Side_1.val0 = 0;
				//rDest_Side_1.val1 = 255;
				//rDest_Side_1.val2 = 255;

				//rDest_Side_2.val0 = 0;
				//rDest_Side_2.val1 = 255;
				//rDest_Side_2.val2 = 255;
			}


			ShowImage(confDsp_Img, cx.MakeStrWithId("confDsp_Img").c_str());
		}

		void ImgAngleDirMgr::DisplayDiffImages()
		{
			Context & cx = *m_context;


			F32ImageArrayHolder3C_Ref diff_Img_disp = F32ImageArrayHolder3C::CreateEmptyFrom(cx.m_diff1_1_Img);
			CopyImage(diff_Img_disp->GetVirtAccessor(), cx.m_diff1_1_Img->GetVirtAccessor());
			//CopyImageWithShift(diff_Img_disp->GetVirtAccessor(), cx.m_diff1_1_Img->GetVirtAccessor(), S32Point(70, 70));
			SetUndefinedInImageToZero(diff_Img_disp->GetVirtAccessor());
			AddValueToImage(diff_Img_disp->GetVirtAccessor(), F32ColorVal::FromNum(130));

			F32ImageArrayHolder3C_Ref diff_2_Img_disp = F32ImageArrayHolder3C::CreateEmptyFrom(cx.m_diff_2_Img);
			CopyImage(diff_2_Img_disp->GetVirtAccessor(), cx.m_diff_2_Img->GetVirtAccessor());
			SetUndefinedInImageToZero(diff_2_Img_disp->GetVirtAccessor());
			AddValueToImage(diff_2_Img_disp->GetVirtAccessor(), F32ColorVal::FromNum(130));

			////--

			const ActualArrayAccessor_2D<BidiffInfo> & bidiffInfoAcc = cx.m_bidiffInfo_Img->GetActualAccessor();

			F32ImageRef bidiffInfoDsp_Img = F32Image::Create(toCvSize(bidiffInfoAcc.GetSize()), 3);


			bidiffInfoDsp_Img->SetAll(0);

			ActualArrayAccessor_1D<F32ColorVal> dispAcc_1D((F32ColorVal *)bidiffInfoDsp_Img->GetDataPtr(), bidiffInfoDsp_Img->GetSize1D());

			const ActualArrayAccessor_1D<BidiffInfo> & bidiffInfoAcc_1D = bidiffInfoAcc.GenAcc_1D();

			for (int i = 0; i < bidiffInfoAcc_1D.GetSize(); i++)
			{
				BidiffInfo & rSrc = bidiffInfoAcc_1D[i];

				F32ColorVal & rDest = dispAcc_1D[i];

				//rDest.val0 = 0;

				if (!IsUndefined(rSrc.Diff1_BkwdMag))
				{
					//if (rSrc.Diff1_BkwdMag > 50)
					//{
					//	i = i;
					//}

					AssertValue(rSrc.Diff1_BkwdMag);
					rDest.val1 = rSrc.Diff1_BkwdMag;
				}

				if (!IsUndefined(rSrc.Diff1_FwdMag))
				{
					//if (rSrc.Diff1_FwdMag > 50)
					//{
					//	i = i;
					//}

					AssertValue(rSrc.Diff1_FwdMag);
					rDest.val2 = rSrc.Diff1_FwdMag;
				}

			}

			ShowImage(bidiffInfoDsp_Img, cx.MakeStrWithId("bidiffInfoDsp_Img").c_str());





			ShowImage(diff_Img_disp->GetSrcImg(), cx.MakeStrWithId("diffDsp_Img").c_str());
			ShowImage(diff_2_Img_disp->GetSrcImg(), cx.MakeStrWithId("diff_2_Dsp_Img").c_str());
			
			GlobalStuff::SetLinePathImg(diff_Img_disp->GetSrcImg());
			GlobalStuff::SetLinePathImg(diff_2_Img_disp->GetSrcImg());
			//GlobalStuff::SetLinePathImg(bidiffInfoDsp_Img);
			GlobalStuff::ShowLinePathImg();

		}

	}
}

