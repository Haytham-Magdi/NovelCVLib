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

			//ShowImage(cx.m_org_Img->GetSrcImg(), cx.MakeStrWithId("org_Img->GetSrcImg()").c_str());

			cx.m_avgStandev_X_Img = F32ImageArrayHolder1C::CreateEmptyFrom(cx.m_org_Img);
			Calc_AvgStandevImage_X(cx.m_org_Img->GetVirtAccessor(), cx.m_magSqr_Img->GetVirtAccessor(),
				cx.m_avgStandev_X_Img->GetVirtAccessor(), Range<int>::New(-2, 2), Range<int>::New(-2, 2));

			if (1 == cx.m_nIndex)
			{
				//ShowImage(cx.m_avgStandev_X_Img->GetSrcImg(), cx.MakeStrWithId("m_avgStandev_X_Img->GetSrcImg()").c_str());
				ShowImage(GenTriChGrayImg(cx.m_avgStandev_X_Img->GetSrcImg()), cx.MakeStrWithId("m_avgStandev_X_Img->GetSrcImg()").c_str());
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

			//Window<int> avgWin = Window<int>::New(-1, 1, -5, 5);
			//Window<int> avgWin = Window<int>::New(-1, 1, -2, 2);

			Window<int> avgWin = Window<int>::New(-1, 0, -2, 2);
			//Window<int> avgWin = Window<int>::New(0, 0, -2, 2);

			//Window<int> avgWin = Window<int>::New(-2, 2, -2, 2);
			//Window<int> avgWin = Window<int>::New(-2, 1, -2, 2);

			cx.m_conflict_Img = ArrayHolderUtil::CreateEmptyFrom<ConflictInfo2>(cx.m_org_Img->AsHolderRef());

			//F32ImageArrayHolder3C_Ref avg_Img = cx.m_org_Img->CloneEmpty();
			F32ImageArrayHolder3C_Ref avg_Img = F32ImageArrayHolder3C::CreateEmptyFrom(cx.m_org_Img);
			AvgImage(cx.m_org_Img->GetVirtAccessor(), avg_Img->GetVirtAccessor(), avgWin);

			//F32ImageArrayHolder1C_Ref avg_MagSqr_Img = new F32ImageArrayHolder1C(cx.m_org_Img->GetVirtAccessor().GetSize());
			F32ImageArrayHolder1C_Ref avg_MagSqr_Img = F32ImageArrayHolder1C::CreateEmptyFrom(cx.m_org_Img);
			AvgImage(cx.m_magSqr_Img->GetVirtAccessor(), avg_MagSqr_Img->GetVirtAccessor(), avgWin);

			Range<int> confRange = Range<int>::New(
				-1 - avgWin.Get_X2(), 1 - avgWin.Get_X1());

			CalcConflictImage_X(avg_Img->GetVirtAccessor(), avg_MagSqr_Img->GetVirtAccessor(),
				cx.m_conflict_Img->GetVirtAccessor(), confRange);

			//if (0 == cx.m_nIndex)
			{
				//DisplayConflictImg();
			}

		}

		void ImgAngleDirMgr::Proceed_2_2()
		{
			//Context & cx = *m_context;
			//Context & ncx = *m_normalContext;
			//AngleDirMgrColl_Context & pcx = *m_parentContext;

			AffectCommonConflict();
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

			if (0 == m_context->m_nIndex)
			{
				GlobalStuff::SetLinePathImg(GenTriChGrayImg(standev_InrWide_Img->GetSrcImg())); GlobalStuff::ShowLinePathImg();
				ShowImage(standev_InrWide_Img->GetSrcImg(), "standev_InrWide_Img->GetSrcImg()");
			}

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
			//		//-10 - avgWin.Get_X2(), 10 - avgWin.Get_X1());
			//		//-1 - avgWin.Get_X2(), 1 - avgWin.Get_X1());
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
			

			ActualArrayAccessor_2D<PixelStandevInfo> commonAcc = m_parentContext->m_standevInfoImg->GetActualAccessor();
			Ncpp_ASSERT(Size_2D::AreEqual(orgToRotMap_Acc.GetSize(), commonAcc.GetSize()));

			ActualArrayAccessor_1D<PixelStandevInfo> commonAcc_1D = commonAcc.GenAcc_1D();



			//float * localAcc_1D = (float *)cx.m_avgStandev_X_Img->GetActualAccessor().GetData();
			ActualArrayAccessor_1D<float> localAcc_1D = cx.m_avgStandev_X_Img->GetActualAccessor().GenAcc_1D();
			ActualArrayAccessor_1D<float> localAcc_1D_Norm = ncx.m_avgStandev_X_Img->GetActualAccessor().GenAcc_1D();

			for (int y = 0; y < orgToRotMap_Acc.GetSize_Y(); y++)
			{
				const int nOffset_Y = y * orgToRotMap_Acc.GetSize_X();

				for (int x = 0; x < orgToRotMap_Acc.GetSize_X(); x++)
				{
					const int nOffsetInOrg_1D = nOffset_Y + x;

					PixelStandevInfo & rCommonPsi = commonAcc_1D[nOffsetInOrg_1D];

					//if (IsUndefined(rCommonPsi))
					//{
					//	continue;
					//}
					AssertValue(rCommonPsi);

					int nOffsetInRot_1D = orgToRotMapAcc_1D[nOffsetInOrg_1D];
					//Ncpp_ASSERT(nOffsetInRot_1D >= 0);

					const float standev_Local = localAcc_1D[nOffsetInRot_1D];
					const float standev_Norm = localAcc_1D_Norm[nOffsetInRot_1D];

					if (IsUndefined(standev_Local))
					{
						//SetToUndefined(&rCommonPsi);
						continue;
					}
					
					//Ncpp_ASSERT(standev_Local >= 0.0f || standev_Local > -5000.0f);
					AssertValue(standev_Local);
					Ncpp_ASSERT(standev_Local >= 0);

					//if (standev_Local < rCommonPsi.Val)
					if (1 == cx.m_nIndex)
					{
						////Ncpp_ASSERT(standev_Norm >= rCommonPsi.NormVal);
						//Ncpp_ASSERT(standev_Norm + 50 >= rCommonPsi.NormVal);

						//Assign(&rCommonPsi.Val, standev_Local);
						////Assign(&rCommonPsi.NormVal, standev_Norm);
						//Assign(&rCommonPsi.NormVal, standev_Local);
						
						Assign(&rCommonPsi.Val, 150);
						Assign(&rCommonPsi.NormVal, 150);
						
						Assign(&rCommonPsi.Dir, cx.m_nIndex);
					}

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

			ActualArrayAccessor_1D<VectorVal<Float, 4>> commonAcc_1D = pcx.m_avgPStandev_InrWide_Img->GetActualAccessor().GenAcc_1D();
			ActualArrayAccessor_1D<VectorVal<Float, 4>> localAcc_1D = cx.m_avgPStandev_InrWide_Img->GetActualAccessor().GenAcc_1D();

			for (int y = 0; y < orgToRotMap_Acc.GetSize_Y(); y++)
			{
				const int nOffset_Y = y * orgToRotMap_Acc.GetSize_X();

				for (int x = 0; x < orgToRotMap_Acc.GetSize_X(); x++)
				{
					const int nOffsetInOrg_1D = nOffset_Y + x;

					VectorVal<Float, 4> * pCommonVal = &commonAcc_1D[nOffsetInOrg_1D];
					if (IsUndefined(*pCommonVal))
						continue;

					AssertValue(*pCommonVal);

					int nOffsetInRot_1D = orgToRotMapAcc_1D[nOffsetInOrg_1D];
					Ncpp_ASSERT(nOffsetInRot_1D >= 0);

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
		

		void ImgAngleDirMgr::AffectCommonConflict()
		{
			const ActualArrayAccessor_2D<int> & orgToRotMap_Acc = m_context->m_orgToRotMap_Img->GetActualAccessor();

			ActualArrayAccessor_1D<int> orgToRotMapAcc_1D = orgToRotMap_Acc.GenAcc_1D();
			ActualArrayAccessor_1D<int> rotToOrgMap_Acc_1D = m_context->m_rotToOrgMap_Img->GetActualAccessor().GenAcc_1D();

			ActualArrayAccessor_1D<ConflictInfo2_Ex> commonImgAcc_1D = m_parentContext->m_conflictInfoImg->GetActualAccessor().GenAcc_1D();
			ActualArrayAccessor_1D<ConflictInfo2> localAcc_1D = m_context->m_conflict_Img->GetActualAccessor().GenAcc_1D();
			
			for (int y = 0; y < orgToRotMap_Acc.GetSize_Y(); y++)
			{
				const int nOffset_Y = y * orgToRotMap_Acc.GetSize_X();

				for (int x = 0; x < orgToRotMap_Acc.GetSize_X(); x++)
				{
					const int nOffsetInOrg_1D = nOffset_Y + x;

					ConflictInfo2_Ex & rCommonConf = commonImgAcc_1D[nOffsetInOrg_1D];
					
					AssertValue(rCommonConf);

					const int nOffsetInRot_1D = orgToRotMapAcc_1D[nOffsetInOrg_1D];

					ConflictInfo2 & conf_Local = localAcc_1D[nOffsetInRot_1D];

					if (IsUndefined(conf_Local))
						continue;


					if (conf_Local.Exists)
					{
						Ncpp_ASSERT(conf_Local.Offset_Side_1 >= 0);
						int nOffset_Side_1_Mapped = rotToOrgMap_Acc_1D[conf_Local.Offset_Side_1];
						if (nOffset_Side_1_Mapped < 0)
							continue;

						Ncpp_ASSERT(conf_Local.Offset_Side_2 >= 0);
						int nOffset_Side_2_Mapped = rotToOrgMap_Acc_1D[conf_Local.Offset_Side_2];
						if (nOffset_Side_2_Mapped < 0)
							continue;

						rCommonConf.Exists = true;
						rCommonConf.Offset_Side_1 = nOffset_Side_1_Mapped;
						rCommonConf.Offset_Side_2 = nOffset_Side_2_Mapped;

						rCommonConf.Dir = m_context->m_nIndex;
					}

				}
			}

		}

		void ImgAngleDirMgr::AffectCommonWideConflictDiff()
		{
			Context & cx = *m_context;
			Context & ncx = *m_normalContext;
			AngleDirMgrColl_Context & pcx = *m_parentContext;

			const ActualArrayAccessor_2D<int> & orgToRotMap_Acc = cx.m_orgToRotMap_Img->GetActualAccessor();
			ActualArrayAccessor_1D<int> orgToRotMapAcc_1D = orgToRotMap_Acc.GenAcc_1D();

			ActualArrayAccessor_1D<float> commonAcc_1D = pcx.m_wideConflictDiff_Img->GetActualAccessor().GenAcc_1D();

			float * localAcc_1D = (float *)cx.m_wideConflictDiff_Img->GetActualAccessor().GetData();
			//float * localAcc_1D_Norm = (float *)ncx.m_wideConflictDiff_Img->GetActualAccessor().GetData();

			for (int y = 0; y < orgToRotMap_Acc.GetSize_Y(); y++)
			{
				const int nOffset_Y = y * orgToRotMap_Acc.GetSize_X();

				for (int x = 0; x < orgToRotMap_Acc.GetSize_X(); x++)
				{
					const int nOffsetInOrg_1D = nOffset_Y + x;

					float & rCommonConf = commonAcc_1D[nOffsetInOrg_1D];
					AssertValue(rCommonConf);

					int nOffsetInRot_1D = orgToRotMapAcc_1D[nOffsetInOrg_1D];
					Ncpp_ASSERT(nOffsetInRot_1D >= 0);

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
			//F32ImageRef confDsp_Img = F32Image::Create(cvSize(confAcc->GetNofSteps_X_Org(), confAcc->GetNofSteps_Y_Org()), 3);
			F32ImageRef confDsp_Img = F32Image::Create(toCvSize(confAcc.GetSize()), 3);

			confDsp_Img->SetAll(0);

			const int nSize_1D = confAcc.CalcSize_1D();

			F32ColorVal * destPtr = (F32ColorVal *)confDsp_Img->GetDataPtr();
			ConflictInfo2 * srcPtr = (ConflictInfo2 *)confAcc.GetData();

			float angle_Old = -1;
			for (int i = 0; i < nSize_1D; i++)
			{
				ConflictInfo2 & rSrc = srcPtr[i];
				AssertValue(rSrc);

				F32ColorVal & rDest = destPtr[i];

				//rDest.val0 = 0;
				//rDest.val1 = 255;
				//rDest.val2 = 255;

				//continue;

				//Ncpp_ASSERT(-1 != rSrc.Dir);

				if (rSrc.Exists)
				{
					F32ColorVal & rDest_Side_1 = destPtr[rSrc.Offset_Side_1];
					F32ColorVal & rDest_Side_2 = destPtr[rSrc.Offset_Side_2];

					rDest.val0 = 0;
					rDest.val1 = 0;
					rDest.val2 = 255;

					rDest_Side_1.val0 = 0;
					rDest_Side_1.val1 = 255;
					rDest_Side_1.val2 = 0;

					rDest_Side_2.val0 = 0;
					rDest_Side_2.val1 = 255;
					rDest_Side_2.val2 = 0;
				}
				//else
				//{
				//	rDest.val0 = 0;
				//	rDest.val1 = 0;
				//	rDest.val2 = 0;
				//}
			}

			ShowImage(confDsp_Img, cx.MakeStrWithId("confDsp_Img").c_str());
		}

	}
}

