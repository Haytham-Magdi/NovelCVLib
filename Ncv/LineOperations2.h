#pragma once

#include <NovelCVLib\Ncpp\Common\commonLib_Misc.h>
//#include <NovelCVLib\OpenCV\CvIncludes.h>
//#include <NovelCVLib\OpenCV\Types.h>
//#include <NovelCVLib\OpenCV\error.h>
//#include <NovelCVLib\OpenCV\funcs1.h>
#include <vector>
//#include <NovelCVLib\OpenCV\Image.h>
#include <NovelCVLib\Ncv\ConflictInfo2.h>

//#include <NovelCVLib\Ncpp\Common\commonLib_Misc.h>



namespace Ncv
{
	using namespace Ncpp;

	namespace LineOperations2
	{
		template<class T>
		void FillLine(const VirtArrayAccessor_1D<T> & a_acc, const T & a_val)
		{
			PtrIterator2<T> ptrItr = a_acc.GenPtrIterator();

			for (; ptrItr.CanMove(); ptrItr.MoveBgn())
			{
				T * ptr = ptrItr.GetBgn();
				ElementOperations2::Assign<T>(ptr, a_val);
			}
		}

		template<class T>
		void DivideLineByNum(const VirtArrayAccessor_1D<T> & a_acc, const float a_num)
		{
			PtrIterator2<T> ptrItr = a_acc.GenPtrIterator();

			for (; ptrItr.CanMove(); ptrItr.MoveBgn())
			{
				T * ptr = ptrItr.GetBgn();
				ElementOperations2::DivideByNum<T>(*ptr, a_num, ptr);
			}
		}

		template<class T>
		void MultiplyLineByNum(const VirtArrayAccessor_1D<T> & a_acc, const float a_num)
		{
			PtrIterator2<T> ptrItr = a_acc.GenPtrIterator();

			for (; ptrItr.CanMove(); ptrItr.MoveBgn())
			{
				T * ptr = ptrItr.GetBgn();
				ElementOperations2::MultiplyByNum<T>(*ptr, a_num, ptr);
			}
		}

		template<class T>
		void CopyLine(const VirtArrayAccessor_1D<T> & a_destAcc, const VirtArrayAccessor_1D<T> & a_srcAcc)
		{
			Ncpp_ASSERT(a_srcAcc.GetSize() == a_destAcc.GetSize());

			PtrIterator2<T> ptrItr_Src = a_srcAcc.GenPtrIterator();
			PtrIterator2<T> ptrItr_Dest = a_destAcc.GenPtrIterator();

			for (; ptrItr_Src.CanMove(); ptrItr_Src.MoveBgn(), ptrItr_Dest.MoveBgn())
			{
				T * ptr_Src = ptrItr_Src.GetBgn();
				T * ptr_Dest = ptrItr_Dest.GetBgn();

				ElementOperations2::Assign<T>(ptr_Dest, *ptr_Src);
			}
		}

		template<class T>
		void CalcMagLine(const VirtArrayAccessor_1D<T> & a_inpAcc, const VirtArrayAccessor_1D<float> & a_outAcc)
		{
			Ncpp_ASSERT(a_inpAcc.GetSize() == a_outAcc.GetSize());

			PtrIterator2<T> ptrItr_Inp = a_inpAcc.GenPtrIterator();
			PtrIterator2<float> ptrItr_Out = a_outAcc.GenPtrIterator();

			for (; ptrItr_Inp.CanMove(); ptrItr_Inp.MoveBgn(), ptrItr_Out.MoveBgn())
			{
				T * ptr_Inp = ptrItr_Inp.GetBgn();
				float * ptr_Out = ptrItr_Out.GetBgn();

				*ptr_Out = ElementOperations2::CalcMag<T>(*ptr_Inp);
			}
		}

		template<class T>
		void CalcMagSqrLine(const VirtArrayAccessor_1D<T> & a_inpAcc, const VirtArrayAccessor_1D<float> & a_outAcc)
		{
			Ncpp_ASSERT(a_inpAcc.GetSize() == a_outAcc.GetSize());

			PtrIterator2<T> ptrItr_Inp = a_inpAcc.GenPtrIterator();
			PtrIterator2<float> ptrItr_Out = a_outAcc.GenPtrIterator();

			for (; ptrItr_Inp.CanMove(); ptrItr_Inp.MoveBgn(), ptrItr_Out.MoveBgn())
			{
				T * ptr_Inp = ptrItr_Inp.GetBgn();
				float * ptr_Out = ptrItr_Out.GetBgn();

				*ptr_Out = ElementOperations2::CalcMagSqr<T>(*ptr_Inp);
			}
		}

		//template<class T>
		//void AssertValues_Line(const VirtArrayAccessor_1D<T> & a_inpAcc)
		//{
		//	PtrIterator2<T> ptrItr_Inp = a_inpAcc.GenPtrIterator();

		//	for (; ptrItr_Inp.CanMove(); ptrItr_Inp.MoveBgn())
		//	{
		//		T * ptr_Inp = ptrItr_Inp.GetBgn();

		//		ElementOperations2::AssertValue<T>(ptr_Inp);
		//	}
		//}

		template<class T>
		void AvgLine(const VirtArrayAccessor_1D<T> & a_inpAcc, const VirtArrayAccessor_1D<T> & a_outAcc, const Range<int> & a_range)
		{
			Ncpp_ASSERT(a_inpAcc.GetSize() == a_outAcc.GetSize());
			Ncpp_ASSERT(a_range.GetBgn() <= 0);
			Ncpp_ASSERT(0 <= a_range.GetEnd());

			T zeroVal;
			SetToZero<T>(&zeroVal);

			FillLine<T>(a_outAcc, zeroVal);

			const int nSize_1D = a_inpAcc.GetSize();

			const int nBefDiff = -a_range.GetBgn();
			const int nAftDiff = a_range.GetEnd();

			const int nCenterEnd = nSize_1D - 1 - nAftDiff;
			const int nRangeLen = nBefDiff + 1 + nAftDiff;

			T sum;
			T * pDest;
			SetToZero<T>(&sum);

			for (int i = 0; i < nRangeLen; i++)
			{
				Add(sum, a_inpAcc[i], &sum);
			}
			pDest = (T *)&a_outAcc[nBefDiff];
			Assign(pDest, sum);
			DivideByNum(*pDest, nRangeLen, pDest);

			for (int i = nBefDiff + 1; i <= nCenterEnd; i++)
			{
				pDest = (T *)&a_outAcc[i];

				Subtract(sum, a_inpAcc[(i - 1) - nBefDiff], &sum);
				Add(sum, a_inpAcc[i + nAftDiff], &sum);

				Assign(pDest, sum);
				DivideByNum(*pDest, nRangeLen, pDest);
			}

			///////////////////////////////

			//	Fill bgn gap in output
			{
				const T & rSrc = a_outAcc[nBefDiff];
				for (int i = 0; i < nBefDiff; i++)
				{
					pDest = (T *)&a_outAcc[i];
					Assign(pDest, rSrc);
				}
			}

			//	Fill end gap in output
			{
				const int nSrcIdx = (nSize_1D - 1) - nAftDiff;
				const T & rSrc = a_outAcc[nSrcIdx];

				for (int i = nSrcIdx + 1; i < nSize_1D; i++)
				{
					pDest = (T *)&a_outAcc[i];
					Assign(pDest, rSrc);
				}
			}

		}

		template<class T>
		void AvgLine_Weighted(const VirtArrayAccessor_1D<T> & a_inpAcc, const VirtArrayAccessor_1D<float> & a_weightAcc, const VirtArrayAccessor_1D<T> & a_outAcc, const Range<int> & a_range)
		{
			Ncpp_ASSERT(a_inpAcc.GetSize() == a_outAcc.GetSize());
			Ncpp_ASSERT(a_inpAcc.GetSize() == a_weightAcc.GetSize());
			Ncpp_ASSERT(a_range.GetBgn() <= 0);
			Ncpp_ASSERT(0 <= a_range.GetEnd());

			T zeroVal;
			SetToZero<T>(&zeroVal);

			FillLine<T>(a_outAcc, zeroVal);

			const int nSize_1D = a_inpAcc.GetSize();

			const int nBefDiff = -a_range.GetBgn();
			const int nAftDiff = a_range.GetEnd();

			const int nCenterEnd = nSize_1D - 1 - nAftDiff;
			const int nRangeLen = nBefDiff + 1 + nAftDiff;

			T * pDest;

			T sum;
			SetToZero<T>(&sum);
			int sum_Wt = 0;

			T inp2;

			for (int i = 0; i < nRangeLen; i++)
			{
				Assign(&inp2, &a_inpAcc[i]);
				MultiplyByNum(inp2, a_weightAcc[i], &inp2);

				sum_Wt += a_weightAcc[i];
				Add(sum, inp2, &sum);
			}
			if (sum_Wt > 0.2f)
			{
				pDest = &a_outAcc[nBefDiff];
				Assign(pDest, sum);
				DivideByNum(*pDest, sum_Wt, pDest);
			}

			for (int i = nBefDiff + 1; i <= nCenterEnd; i++)
			{
				pDest = &a_outAcc[i];

				int idx = (i - 1) - nBefDiff;
				Assign(&inp2, &a_inpAcc[idx]);
				MultiplyByNum(inp2, a_weightAcc[idx], &inp2);

				Subtract(sum, inp2, &sum);
				sum_Wt -= a_weightAcc[idx];

				idx = i + nAftDiff;
				Assign(&inp2, &a_inpAcc[idx]);
				MultiplyByNum(inp2, a_weightAcc[idx], &inp2);

				Add(sum, inp2, &sum);
				sum_Wt += a_weightAcc[idx];

				if (sum_Wt > 0.2f)
				{
					Assign(pDest, &sum);
					DivideByNum(*pDest, sum_Wt, pDest);
				}

				//float mag1 = CalcMag(pDest);
				//Ncpp_ASSERT(mag1 < 600);
			}

			///////////////////////////////

			//	Fill bgn gap in output
			{
				T & rSrc = a_outAcc[nBefDiff];
				for (int i = 0; i < nBefDiff; i++)
				{
					pDest = &a_outAcc[i];
					Assign(pDest, rSrc);
				}
			}

			//	Fill end gap in output
			{
				const int nSrcIdx = (nSize_1D - 1) - nAftDiff;
				T & rSrc = a_outAcc[nSrcIdx];

				for (int i = nSrcIdx + 1; i < nSize_1D; i++)
				{
					pDest = &a_outAcc[i];
					Assign(pDest, rSrc);
				}
			}

		}

		template<class T>
		void CalcSqrtLine(const VirtArrayAccessor_1D<T> & a_inpAcc, const VirtArrayAccessor_1D<float> & a_outAcc)
		{
			Ncpp_ASSERT(a_inpAcc.GetSize() == a_outAcc.GetSize());

			PtrIterator2<T> ptrItr_Inp = a_inpAcc.GenPtrIterator();
			PtrIterator2<float> ptrItr_Out = a_outAcc.GenPtrIterator();

			for (; ptrItr_Inp.CanMove(); ptrItr_Inp.MoveBgn(), ptrItr_Out.MoveBgn())
			{
				T * ptr_Inp = ptrItr_Inp.GetBgn();
				float * ptr_Out = ptrItr_Out.GetBgn();

				*ptr_Out = ElementOperations2::CalcSqrt<T>(*ptr_Inp);
			}
		}

		template<class T>
		void CalcStandevLine(const VirtArrayAccessor_1D<T> & a_avg_Acc, const VirtArrayAccessor_1D<float> & a_avg_MagSqr_Acc,
			const VirtArrayAccessor_1D<float> & a_outAcc)
		{
			Ncpp_ASSERT(a_avg_Acc.GetSize() == a_avg_MagSqr_Acc.GetSize());
			Ncpp_ASSERT(a_avg_Acc.GetSize() == a_outAcc.GetSize());

			PtrIterator2<T> ptrItr_Avg = a_avg_Acc.GenPtrIterator();
			PtrIterator2<float> ptrItr_Avg_MagSqr = a_avg_MagSqr_Acc.GenPtrIterator();
			PtrIterator2<float> ptrItr_Out = a_outAcc.GenPtrIterator();

			for (; ptrItr_Avg.CanMove();
				ptrItr_Avg.MoveBgn(), ptrItr_Avg_MagSqr.MoveBgn(), ptrItr_Out.MoveBgn())
			{
				T * ptr_Avg = ptrItr_Avg.GetBgn();
				float * ptr_Avg_MagSqr = ptrItr_Avg_MagSqr.GetBgn();
				float * ptr_Out = ptrItr_Out.GetBgn();

				*ptr_Out = ElementOperations2::CalcStandev<T>(*ptr_Avg, *ptr_Avg_MagSqr);
			}
		}

		template<class T>
		void CalcConflictLine(const VirtArrayAccessor_1D<T> & a_avg_Acc, const VirtArrayAccessor_1D<float> & a_avg_MagSqr_Acc,
			const VirtArrayAccessor_1D<ConflictInfo2> & a_outAcc, const Range<int> & a_range)
			//VirtArrayAccessor_1D<ConflictInfo2> & a_outAcc, const Range<int> & a_range)
		{
			{
				ConflictInfo2 val_Init;
				val_Init.Exists = false;
				FillLine<ConflictInfo2>(a_outAcc, val_Init);
			}

			Ncpp_ASSERT(a_avg_Acc.GetSize() == a_avg_MagSqr_Acc.GetSize());
			Ncpp_ASSERT(a_avg_Acc.GetSize() == a_outAcc.GetSize());

			const int nSize_1D = a_outAcc.GetSize();

			const int nBefDiff = -a_range.GetBgn();
			const int nAftDiff = a_range.GetEnd();

			const int nCenterEnd = nSize_1D - 1 - nAftDiff;
			const int nRangeLen = nBefDiff + 1 + nAftDiff;

			for (int i = nBefDiff + 1; i <= nCenterEnd; i++)
			{
				//ConflictInfo2 * pOut = &a_outAcc[i];
				ConflictInfo2 * pOut = (ConflictInfo2 *)&a_outAcc[i];

				const T & avg_1 = a_avg_Acc[i - nBefDiff];
				//float avg_MagSqr_1 = sac_Avg_MagSqr[i - nBefDiff];
				float avg_MagSqr_1 = a_avg_MagSqr_Acc[i - nBefDiff];

				const T & avg_2 = a_avg_Acc[i + nAftDiff];
				//float avg_MagSqr_2 = sac_Avg_MagSqr[i + nAftDiff];
				float avg_MagSqr_2 = a_avg_MagSqr_Acc[i + nAftDiff];

				pOut->Exists = ElementOperations2::CalcConflict(avg_1, avg_MagSqr_1, avg_2, avg_MagSqr_2);
				if (pOut->Exists)
				{
					// to be revised.
					//pOut->pSide_1 = &avg_1;

					pOut->Offset_Side_1 = &avg_1 - a_avg_Acc.GetData_FakeOrg();
					Ncpp_ASSERT(pOut->Offset_Side_1 >= 0);

					//pOut->pSide_2 = &avg_2;

					pOut->Offset_Side_2 = &avg_2 - a_avg_Acc.GetData_FakeOrg();
					Ncpp_ASSERT(pOut->Offset_Side_2 >= 0);
				}
				//else
				//{
				//	pOut->Offset_Side_1 = -7;
				//	pOut->Offset_Side_2 = -7;
				//}
			}
		}

		template<class T>
		void Calc_ConflictDiff_Line(const VirtArrayAccessor_1D<T> & a_avg_Acc, const VirtArrayAccessor_1D<float> & a_avg_MagSqr_Acc,
			const VirtArrayAccessor_1D<float> & a_outAcc, const Range<int> & a_range)
		{
			{
				float val_Init;
				val_Init = 0;
				FillLine<float>(a_outAcc, val_Init);
			}

			Ncpp_ASSERT(a_avg_Acc.GetSize() == a_avg_MagSqr_Acc.GetSize());
			Ncpp_ASSERT(a_avg_Acc.GetSize() == a_outAcc.GetSize());

			const int nSize_1D = a_outAcc.GetSize();

			const int nBefDiff = -a_range.GetBgn();
			const int nAftDiff = a_range.GetEnd();

			const int nCenterEnd = nSize_1D - 1 - nAftDiff;
			const int nRangeLen = nBefDiff + 1 + nAftDiff;

			for (int i = nBefDiff + 1; i <= nCenterEnd; i++)
			{
				float * pOut = &a_outAcc[i];

				const T & avg_1 = &a_avg_Acc[i - nBefDiff];
				//float avg_MagSqr_1 = &sac_Avg_MagSqr[i - nBefDiff];
				float avg_MagSqr_1 = &a_avg_MagSqr_Acc[i - nBefDiff];

				const T & avg_2 = &a_avg_Acc[i + nAftDiff];
				//float avg_MagSqr_2 = &sac_Avg_MagSqr[i + nAftDiff];
				float avg_MagSqr_2 = &a_avg_MagSqr_Acc[i + nAftDiff];

				*pOut = ElementOperations2::Calc_ConflictDiff(avg_1, avg_MagSqr_1, avg_2, avg_MagSqr_2);
			}
		}

	};
}