#pragma once

#include <NovelCVLib\Ncpp\Common\commonLib_Misc.h>
//#include <NovelCVLib\OpenCV\CvIncludes.h>
//#include <NovelCVLib\OpenCV\Types.h>
//#include <NovelCVLib\OpenCV\error.h>
//#include <NovelCVLib\OpenCV\funcs1.h>
//#include <NovelCVLib\OpenCV\Image.h>
#include <NovelCVLib\ElementOperations2\ElementOperations2.h>
#include <NovelCVLib\Ncv\LineOperations2.h>
#include <NovelCVLib\Ncpp\Common\ArrayHolderUtil.h>



namespace Ncv
{
	using namespace Ncpp;
	using namespace LineOperations2;
	using namespace ElementOperations2;

	namespace ImageOperations2
	{
		template<class T>
		void FillImage_Stripes_X(const VirtArrayAccessor_2D<T> & a_acc, const T & a_val1, const T & a_val2, int a_stripWidth)
		{
			T * valArr[2];
			valArr[0] = &a_val1;
			valArr[1] = &a_val2;

			int valIdx = 1;

			const VirtArrayAccessor_1D<T> & acc_Y = a_acc.GenAccessor_Y();
			VirtArrayAccessor_1D<T> & acc_X = a_acc.GenAccessor_X();

			PtrIterator2<T> ptrItr_Y = acc_Y->GenPtrIterator();

			for (int i = 0; ptrItr_Y.CanMove(); ptrItr_Y.MoveBgn(), i++)
			{
				T * ptr_Y = ptrItr_Y.GetBgn();

				if (0 == i % a_stripWidth)
				{
					valIdx = 1 - valIdx;
				}

				acc_X.SetData(ptr_Y);
				FillLine<T>(acc_X, *valArr[valIdx]);
			}
		}

		template<class T>
		void FillImage(const VirtArrayAccessor_2D<T> & a_acc, const T & a_val)
		{
			const VirtArrayAccessor_1D<T> & acc_Y = a_acc.GenAccessor_Y();
			VirtArrayAccessor_1D<T> & acc_X = a_acc.GenAccessor_X();

			PtrIterator2<T> ptrItr_Y = acc_Y->GenPtrIterator();

			//for (int i = 0; ptrItr_Y.CanMove(); ptrItr_Y.MoveBgn(), i++)
			for (; ptrItr_Y.CanMove(); ptrItr_Y.MoveBgn())
			{
				T * ptr_Y = ptrItr_Y.GetBgn();

				acc_X.SetData(ptr_Y);
				FillLine<T>(acc_X, a_val);
			}
		}

		template<class T>
		void DivideImageByNum(const VirtArrayAccessor_2D<T> & a_acc, const float a_num)
		{
			const VirtArrayAccessor_1D<T> & acc_Y = a_acc.GenAccessor_Y();
			VirtArrayAccessor_1D<T> & acc_X = a_acc.GenAccessor_X();

			PtrIterator2<T> ptrItr_Y = acc_Y->GenPtrIterator();

			for (int i = 0; ptrItr_Y.CanMove(); ptrItr_Y.MoveBgn(), i++)
			{
				T * ptr_Y = ptrItr_Y.GetBgn();

				acc_X.SetData(ptr_Y);
				DivideLineByNum<T>(acc_X, a_num);
			}
		}

		template<class T>
		void MultiplyImageByNum(const VirtArrayAccessor_2D<T> & a_acc, const float a_num)
		{
			const VirtArrayAccessor_1D<T> & acc_Y = a_acc.GenAccessor_Y();
			VirtArrayAccessor_1D<T> & acc_X = a_acc.GenAccessor_X();

			PtrIterator2<T> ptrItr_Y = acc_Y->GenPtrIterator();

			for (int i = 0; ptrItr_Y.CanMove(); ptrItr_Y.MoveBgn(), i++)
			{
				T * ptr_Y = ptrItr_Y.GetBgn();

				acc_X.SetData(ptr_Y);
				MultiplyLineByNum<T>(acc_X, a_num);
			}
		}

		template<class T>
		void CopyImage(const VirtArrayAccessor_2D<T> & a_destAcc, const VirtArrayAccessor_2D<T> & a_srcAcc)
		{
			const VirtArrayAccessor_1D<T> & acc_Src_Y = a_srcAcc.GenAccessor_Y();
			VirtArrayAccessor_1D<T> & acc_Src_X = a_srcAcc.GenAccessor_X();

			const VirtArrayAccessor_1D<T> & acc_Dest_Y = a_destAcc.GenAccessor_Y();
			VirtArrayAccessor_1D<T> & acc_Dest_X = a_destAcc.GenAccessor_X();

			Ncpp_ASSERT(acc_Src_Y.GetSize() == acc_Dest_Y.GetSize());

			PtrIterator2<T> ptrItr_Src_Y = acc_Src_Y->GenPtrIterator();
			PtrIterator2<T> ptrItr_Dest_Y = acc_Dest_Y->GenPtrIterator();

			for (; ptrItr_Src_Y.CanMove(); ptrItr_Src_Y.MoveBgn(), ptrItr_Dest_Y.MoveBgn())
			{
				T * ptr_Src_Y = ptrItr_Src_Y.GetBgn();
				T * ptr_Dest_Y = ptrItr_Dest_Y.GetBgn();

				acc_Src_X.SetData(ptr_Src_Y);
				acc_Dest_X.SetData(ptr_Dest_Y);

				CopyLine<T>(acc_Dest_X, acc_Src_X);
			}
		}

		template<class T>
		void CalcMagImage(const VirtArrayAccessor_2D<T> & a_inpAcc, MemAccessor_2D_REF(float) a_outAcc)
		{
			const VirtArrayAccessor_1D<T> & acc_Inp_Y = a_inpAcc.GenAccessor_Y();
			VirtArrayAccessor_1D<T> & acc_Inp_X = a_inpAcc.GenAccessor_X();

			const VirtArrayAccessor_1D<float> & acc_Out_Y = a_outAcc.GenAccessor_Y();
			VirtArrayAccessor_1D<float> & acc_Out_X = a_outAcc.GenAccessor_X();

			Ncpp_ASSERT(acc_Inp_Y.GetSize() == acc_Out_Y.GetSize());

			PtrIterator2<T> ptrItr_Inp_Y = acc_Inp_Y->GenPtrIterator();
			PtrIterator2<float> ptrItr_Out_Y = acc_Out_Y->GenPtrIterator();

			for (; ptrItr_Inp_Y.CanMove(); ptrItr_Inp_Y.MoveBgn(), ptrItr_Out_Y.MoveBgn())
			{
				T * ptr_Inp_Y = ptrItr_Inp_Y.GetBgn();
				float * ptr_Out_Y = ptrItr_Out_Y.GetBgn();

				acc_Inp_X.SetData(ptr_Inp_Y);
				acc_Out_X.SetData(ptr_Out_Y);

				CalcMagLine<T>(acc_Inp_X, acc_Out_X);
			}
		}

		template<class T>
		void CalcMagSqrImage(const VirtArrayAccessor_2D<T> & a_inpAcc, MemAccessor_2D_REF(float) a_outAcc)
		{
			const VirtArrayAccessor_1D<T> & acc_Inp_Y = a_inpAcc.GenAccessor_Y();
			VirtArrayAccessor_1D<T> & acc_Inp_X = a_inpAcc.GenAccessor_X();

			const VirtArrayAccessor_1D<float> & acc_Out_Y = a_outAcc.GenAccessor_Y();
			VirtArrayAccessor_1D<float> & acc_Out_X = a_outAcc.GenAccessor_X();

			Ncpp_ASSERT(acc_Inp_Y.GetSize() == acc_Out_Y.GetSize());

			PtrIterator2<T> ptrItr_Inp_Y = acc_Inp_Y->GenPtrIterator();
			PtrIterator2<float> ptrItr_Out_Y = acc_Out_Y->GenPtrIterator();

			for (; ptrItr_Inp_Y.CanMove(); ptrItr_Inp_Y.MoveBgn(), ptrItr_Out_Y.MoveBgn())
			{
				T * ptr_Inp_Y = ptrItr_Inp_Y.GetBgn();
				float * ptr_Out_Y = ptrItr_Out_Y.GetBgn();

				acc_Inp_X.SetData(ptr_Inp_Y);
				acc_Out_X.SetData(ptr_Out_Y);

				CalcMagSqrLine<T>(acc_Inp_X, acc_Out_X);
			}
		}

		template<class T>
		void AssertValues_Image(const VirtArrayAccessor_2D<T> & a_inpAcc)
		{
			const VirtArrayAccessor_1D<T> & acc_Inp_Y = a_inpAcc.GenAccessor_Y();
			VirtArrayAccessor_1D<T> & acc_Inp_X = a_inpAcc.GenAccessor_X();

			PtrIterator2<T> ptrItr_Inp_Y = acc_Inp_Y->GenPtrIterator();

			for (; ptrItr_Inp_Y.CanMove(); ptrItr_Inp_Y.MoveBgn())
			{
				T * ptr_Inp_Y = ptrItr_Inp_Y.GetBgn();

				acc_Inp_X.SetData(ptr_Inp_Y);
				AssertValues_Line<T>(acc_Inp_X);
			}
		}

		template<class T>
		void AvgImage_X(const VirtArrayAccessor_2D<T> & a_inpAcc, const VirtArrayAccessor_2D<T> & a_outAcc, const Range<int> & a_range_X)
		{
			const VirtArrayAccessor_1D<T> & acc_Inp_Y = a_inpAcc.GenAccessor_Y();
			VirtArrayAccessor_1D<T> & acc_Inp_X = a_inpAcc.GenAccessor_X();

			const VirtArrayAccessor_1D<T> & acc_Out_Y = a_outAcc.GenAccessor_Y();
			VirtArrayAccessor_1D<T> & acc_Out_X = a_outAcc.GenAccessor_X();

			Ncpp_ASSERT(acc_Inp_Y.GetSize() ==
				acc_Out_Y.GetSize());

			PtrIterator2<T> ptrItr_Inp_Y = acc_Inp_Y->GenPtrIterator();
			PtrIterator2<T> ptrItr_Out_Y = acc_Out_Y->GenPtrIterator();

			for (; ptrItr_Inp_Y.CanMove(); ptrItr_Inp_Y.MoveBgn(), ptrItr_Out_Y.MoveBgn())
			{
				T * ptr_Inp_Y = ptrItr_Inp_Y.GetBgn();
				T * ptr_Out_Y = ptrItr_Out_Y.GetBgn();

				acc_Inp_X.SetData(ptr_Inp_Y);
				acc_Out_X.SetData(ptr_Out_Y);

				AvgLine(acc_Inp_X, acc_Out_X, a_range_X);
			}
		}

		template<class T>
		void AvgImage(const VirtArrayAccessor_2D<T> & a_inpAcc, const VirtArrayAccessor_2D<T> & a_outAcc, const Window<int> & a_window)
		{
			TempImageAccessor_REF(T) tmpImgAcc = new ArrayHolderUtil<T>(a_outAcc->GetOffsetCalc());

			AvgImage_X<T>(a_inpAcc, tmpImgAcc->GetMemAccessor(), a_window.GetRange_X());
			//AvgImage_X<T>(a_inpAcc, a_outAcc, a_range_X);

			//return;

			const VirtArrayAccessor_2D<T> & outAcc2 = a_outAcc->Clone();
			outAcc2->SwitchXY();

			tmpImgAcc->SwitchXY();

			AvgImage_X<T>(tmpImgAcc->GetMemAccessor(), outAcc2, a_window.GetRange_Y());
		}

		template<class T>
		void AvgImage_Weighted_X(const VirtArrayAccessor_2D<T> & a_inpAcc, MemAccessor_2D_REF(float) a_weightAcc, const VirtArrayAccessor_2D<T> & a_outAcc, const Range<int> & a_range_X)
		{
			const VirtArrayAccessor_1D<T> & acc_Inp_Y = a_inpAcc.GenAccessor_Y();
			VirtArrayAccessor_1D<T> & acc_Inp_X = a_inpAcc.GenAccessor_X();

			const VirtArrayAccessor_1D<float> & acc_Weight_Y = a_weightAcc.GenAccessor_Y();
			VirtArrayAccessor_1D<float> & acc_Weight_X = a_weightAcc.GenAccessor_X();

			const VirtArrayAccessor_1D<T> & acc_Out_Y = a_outAcc.GenAccessor_Y();
			VirtArrayAccessor_1D<T> & acc_Out_X = a_outAcc.GenAccessor_X();

			Ncpp_ASSERT(acc_Inp_Y.GetSize() == acc_Weight_Y.GetSize());
			Ncpp_ASSERT(acc_Inp_Y.GetSize() == acc_Out_Y.GetSize());

			PtrIterator2<T> ptrItr_Inp_Y = acc_Inp_Y->GenPtrIterator();
			PtrIterator2<float> ptrItr_Weight_Y = acc_Weight_Y->GenPtrIterator();
			PtrIterator2<T> ptrItr_Out_Y = acc_Out_Y->GenPtrIterator();

			for (; ptrItr_Inp_Y.CanMove(); ptrItr_Inp_Y.MoveBgn(), ptrItr_Weight_Y.MoveBgn(), ptrItr_Out_Y.MoveBgn())
			{
				T * ptr_Inp_Y = ptrItr_Inp_Y.GetBgn();
				float * ptr_Weight_Y = ptrItr_Weight_Y.GetBgn();
				T * ptr_Out_Y = ptrItr_Out_Y.GetBgn();

				acc_Inp_X.SetData(ptr_Inp_Y);
				acc_Weight_X.SetData(ptr_Weight_Y);
				acc_Out_X.SetData(ptr_Out_Y);

				AvgLine_Weighted(acc_Inp_X, acc_Weight_X, acc_Out_X, a_range_X);
			}
		}

		template<class T>
		void AvgImage_Weighted(const VirtArrayAccessor_2D<T> & a_inpAcc, MemAccessor_2D_REF(float) a_weightAcc, const VirtArrayAccessor_2D<T> & a_outAcc, const Window<int> & a_window)
		{
			TempImageAccessor_REF(T) tmpImgAcc = new ArrayHolderUtil<T>(a_outAcc->GetOffsetCalc());

			AvgImage_Weighted_X(a_inpAcc, a_weightAcc, tmpImgAcc->GetMemAccessor(), a_window.GetRange_X());

			const VirtArrayAccessor_2D<T> & outAcc2 = a_outAcc->Clone();
			outAcc2->SwitchXY();

			tmpImgAcc->SwitchXY();

			AvgImage_X<T>(tmpImgAcc->GetMemAccessor(), outAcc2, a_window.GetRange_Y());
		}





		template<class T>
		void CalcSqrtImage(const VirtArrayAccessor_2D<T> & a_inpAcc, MemAccessor_2D_REF(float) a_outAcc)
		{
			const VirtArrayAccessor_1D<T> & acc_Inp_Y = a_inpAcc.GenAccessor_Y();
			VirtArrayAccessor_1D<T> & acc_Inp_X = a_inpAcc.GenAccessor_X();

			const VirtArrayAccessor_1D<float> & acc_Out_Y = a_outAcc.GenAccessor_Y();
			VirtArrayAccessor_1D<float> & acc_Out_X = a_outAcc.GenAccessor_X();

			Ncpp_ASSERT(acc_Inp_Y.GetSize() ==
				acc_Out_Y.GetSize());

			PtrIterator2<T> ptrItr_Inp_Y = acc_Inp_Y->GenPtrIterator();
			PtrIterator2<float> ptrItr_Out_Y = acc_Out_Y->GenPtrIterator();

			for (; ptrItr_Inp_Y.CanMove(); ptrItr_Inp_Y.MoveBgn(), ptrItr_Out_Y.MoveBgn())
			{
				T * ptr_Inp_Y = ptrItr_Inp_Y.GetBgn();
				float * ptr_Out_Y = ptrItr_Out_Y.GetBgn();

				acc_Inp_X.SetData(ptr_Inp_Y);
				acc_Out_X.SetData(ptr_Out_Y);

				CalcSqrtLine<T>(acc_Inp_X, acc_Out_X);
			}
		}

		template<class T>
		void Calc_Avg_And_Standev_Image(const VirtArrayAccessor_2D<T> & a_inp_Acc, const VirtArrayAccessor_2D<T> & a_out_Avg_Acc,
			MemAccessor_2D_REF(float) a_out_Standev_Acc, const Window<int> & a_Win)
		{
			//TempImageAccessor_REF(T) avg_Img = new TempImageAccessor_REF<T>(a_inp_Acc->GetOffsetCalc());
			AvgImage(a_inp_Acc, a_out_Avg_Acc, a_Win);

			//ShowImage(avg_Img->GetSrcImg(), "avg_Img->GetSrcImg()");
			
			TempImageAccessor_REF(float) magSqr_Img = new ArrayHolderUtil<float>(a_inp_Acc->GetOffsetCalc());
			CalcMagSqrImage(a_inp_Acc, magSqr_Img->GetMemAccessor());

			TempImageAccessor_REF(float) avg_MagSqr_Img = new ArrayHolderUtil<float>(a_inp_Acc->GetOffsetCalc());
			AvgImage(magSqr_Img->GetMemAccessor(), avg_MagSqr_Img->GetMemAccessor(), a_Win);

			//standev_Img = new F32ImageAccessor1C(a_inp_Acc->GetOffsetCalc());
			CalcStandevImage(a_out_Avg_Acc, avg_MagSqr_Img->GetMemAccessor(), a_out_Standev_Acc);
		}

		template<class T>
		void CalcStandevImage(const VirtArrayAccessor_2D<T> & a_avg_Acc, MemAccessor_2D_REF(float) a_avg_MagSqr_Acc,
			MemAccessor_2D_REF(float) a_outAcc)
		{
			const VirtArrayAccessor_1D<T> & acc_Avg_Y = a_avg_Acc.GenAccessor_Y();
			VirtArrayAccessor_1D<T> & acc_Avg_X = a_avg_Acc.GenAccessor_X();

			const VirtArrayAccessor_1D<float> & acc_Avg_MagSqr_Y = a_avg_MagSqr_Acc.GenAccessor_Y();
			VirtArrayAccessor_1D<float> & acc_Avg_MagSqr_X = a_avg_MagSqr_Acc.GenAccessor_X();

			const VirtArrayAccessor_1D<float> & acc_Out_Y = a_outAcc.GenAccessor_Y();
			VirtArrayAccessor_1D<float> & acc_Out_X = a_outAcc.GenAccessor_X();

			Ncpp_ASSERT(acc_Avg_Y.GetSize() == acc_Avg_MagSqr_Y.GetSize());
			Ncpp_ASSERT(acc_Avg_Y.GetSize() == acc_Out_Y.GetSize());

			//Ncpp_ASSERT(acc_Avg_X.GetSize() == acc_Avg_MagSqr_X.GetSize());
			//Ncpp_ASSERT(acc_Avg_X.GetSize() == acc_Out_X.GetSize());

			PtrIterator2<T> ptrItr_Avg_Y = acc_Avg_Y->GenPtrIterator();
			PtrIterator2<float> ptrItr_Avg_MagSqr_Y = acc_Avg_MagSqr_Y->GenPtrIterator();
			PtrIterator2<float> ptrItr_Out_Y = acc_Out_Y->GenPtrIterator();

			for (; ptrItr_Avg_Y.CanMove();
				ptrItr_Avg_Y.MoveBgn(), ptrItr_Avg_MagSqr_Y.MoveBgn(), ptrItr_Out_Y.MoveBgn())
			{
				T * ptr_Avg_Y = ptrItr_Avg_Y.GetBgn();
				float * ptr_Avg_MagSqr_Y = ptrItr_Avg_MagSqr_Y.GetBgn();
				float * ptr_Out_Y = ptrItr_Out_Y.GetBgn();

				acc_Avg_X.SetData(ptr_Avg_Y);
				acc_Avg_MagSqr_X.SetData(ptr_Avg_MagSqr_Y);
				acc_Out_X.SetData(ptr_Out_Y);

				CalcStandevLine<T>(acc_Avg_X, acc_Avg_MagSqr_X, acc_Out_X);
			}
		}

		template<class T>
		void CalcConflictImage_X(const VirtArrayAccessor_2D<T> & a_avg_Acc, MemAccessor_2D_REF(float) a_avg_MagSqr_Acc,
			MemAccessor_2D_REF(ConflictInfo2) a_outAcc, const Range<int> & a_range_X)
		{
			const VirtArrayAccessor_1D<T> & acc_Avg_Y = a_avg_Acc.GenAccessor_Y();
			VirtArrayAccessor_1D<T> & acc_Avg_X = a_avg_Acc.GenAccessor_X();

			const VirtArrayAccessor_1D<float> & acc_Avg_MagSqr_Y = a_avg_MagSqr_Acc.GenAccessor_Y();
			VirtArrayAccessor_1D<float> & acc_Avg_MagSqr_X = a_avg_MagSqr_Acc.GenAccessor_X();

			const VirtArrayAccessor_1D<ConflictInfo2> & acc_Out_Y = a_outAcc.GenAccessor_Y();
			VirtArrayAccessor_1D<ConflictInfo2> & acc_Out_X = a_outAcc.GenAccessor_X();

			Ncpp_ASSERT(acc_Avg_Y.GetSize() == acc_Avg_MagSqr_Y.GetSize());
			Ncpp_ASSERT(acc_Avg_Y.GetSize() == acc_Out_Y.GetSize());

			PtrIterator2<T> ptrItr_Avg_Y = acc_Avg_Y->GenPtrIterator();
			PtrIterator2<float> ptrItr_Avg_MagSqr_Y = acc_Avg_MagSqr_Y->GenPtrIterator();
			PtrIterator2<ConflictInfo2> ptrItr_Out_Y = acc_Out_Y->GenPtrIterator();

			for (; ptrItr_Avg_Y.CanMove();
				ptrItr_Avg_Y.MoveBgn(), ptrItr_Avg_MagSqr_Y.MoveBgn(), ptrItr_Out_Y.MoveBgn())
			{
				T * ptr_Avg_Y = ptrItr_Avg_Y.GetBgn();
				float * ptr_Avg_MagSqr_Y = ptrItr_Avg_MagSqr_Y.GetBgn();
				ConflictInfo2 * ptr_Out_Y = ptrItr_Out_Y.GetBgn();

				acc_Avg_X.SetData(ptr_Avg_Y);
				acc_Avg_MagSqr_X.SetData(ptr_Avg_MagSqr_Y);
				acc_Out_X.SetData(ptr_Out_Y);

				CalcConflictLine<T>(acc_Avg_X, acc_Avg_MagSqr_X, acc_Out_X, a_range_X);
			}
		}

		template<class T>
		void Calc_ConflictDiff_Image_X(const VirtArrayAccessor_2D<T> & a_avg_Acc, MemAccessor_2D_REF(float) a_avg_MagSqr_Acc,
			MemAccessor_2D_REF(float) a_outAcc, const Range<int> & a_range_X)
		{
			const VirtArrayAccessor_1D<T> & acc_Avg_Y = a_avg_Acc.GenAccessor_Y();
			VirtArrayAccessor_1D<T> & acc_Avg_X = a_avg_Acc.GenAccessor_X();

			const VirtArrayAccessor_1D<float> & acc_Avg_MagSqr_Y = a_avg_MagSqr_Acc.GenAccessor_Y();
			VirtArrayAccessor_1D<float> & acc_Avg_MagSqr_X = a_avg_MagSqr_Acc.GenAccessor_X();

			const VirtArrayAccessor_1D<float> & acc_Out_Y = a_outAcc.GenAccessor_Y();
			VirtArrayAccessor_1D<float> & acc_Out_X = a_outAcc.GenAccessor_X();

			Ncpp_ASSERT(acc_Avg_Y.GetSize() == acc_Avg_MagSqr_Y.GetSize());
			Ncpp_ASSERT(acc_Avg_Y.GetSize() == acc_Out_Y.GetSize());

			PtrIterator2<T> ptrItr_Avg_Y = acc_Avg_Y->GenPtrIterator();
			PtrIterator2<float> ptrItr_Avg_MagSqr_Y = acc_Avg_MagSqr_Y->GenPtrIterator();
			PtrIterator2<float> ptrItr_Out_Y = acc_Out_Y->GenPtrIterator();

			for (; ptrItr_Avg_Y.CanMove();
				ptrItr_Avg_Y.MoveBgn(), ptrItr_Avg_MagSqr_Y.MoveBgn(), ptrItr_Out_Y.MoveBgn())
			{
				T * ptr_Avg_Y = ptrItr_Avg_Y.GetBgn();
				float * ptr_Avg_MagSqr_Y = ptrItr_Avg_MagSqr_Y.GetBgn();
				float * ptr_Out_Y = ptrItr_Out_Y.GetBgn();

				acc_Avg_X.SetData(ptr_Avg_Y);
				acc_Avg_MagSqr_X.SetData(ptr_Avg_MagSqr_Y);
				acc_Out_X.SetData(ptr_Out_Y);

				Calc_ConflictDiff_Line<T>(acc_Avg_X, acc_Avg_MagSqr_X, acc_Out_X, a_range_X);
			}
		}

		template<class T>
		void Cala_AvgStandevImage_X(const VirtArrayAccessor_2D<T> & a_inpAcc, MemAccessor_2D_REF(float) a_magSqrAcc,
			MemAccessor_2D_REF(float) a_outAcc, const Range<int> a_standevRange_X, const Range<int> a_avgRange_Y)
		{
			Ncpp_ASSERT(a_inpAcc->GetNofSteps_X() == a_magSqrAcc->GetNofSteps_X());
			Ncpp_ASSERT(a_inpAcc->GetNofSteps_X() == a_outAcc->GetNofSteps_X());

			Ncpp_ASSERT(a_inpAcc->GetNofSteps_Y() == a_magSqrAcc->GetNofSteps_Y());
			Ncpp_ASSERT(a_inpAcc->GetNofSteps_Y() == a_outAcc->GetNofSteps_Y());



			TempImageAccessor_REF(T) tmpAvgAcc_X = new ArrayHolderUtil<T>(a_inpAcc->GetOffsetCalc());
			AvgImage_X(a_inpAcc, tmpAvgAcc_X->GetMemAccessor(), a_standevRange_X);

			TempImageAccessor_REF(float) tmpAvg_MagSqr_X_Acc = new ArrayHolderUtil<float>(a_outAcc->GetOffsetCalc());
			AvgImage_X(a_magSqrAcc, tmpAvg_MagSqr_X_Acc->GetMemAccessor(), a_standevRange_X);

			TempImageAccessor_REF(float) tmpStandev_X_Acc = new ArrayHolderUtil<float>(a_outAcc->GetOffsetCalc());
			CalcStandevImage(tmpAvgAcc_X->GetMemAccessor(), tmpAvg_MagSqr_X_Acc->GetMemAccessor(),
				tmpStandev_X_Acc->GetMemAccessor());

			MemAccessor_2D_REF(float) outAcc_2 = a_outAcc->Clone();
			outAcc_2->SwitchXY();

			MemAccessor_2D_REF(float) standev_X_Acc_2 = tmpStandev_X_Acc->GetMemAccessor()->Clone();
			standev_X_Acc_2->SwitchXY();

			AvgImage_X(standev_X_Acc_2, outAcc_2, a_avgRange_Y);
		}




	};
}