#pragma once

#include <NovelCVLib\Ncpp\Common\commonLib_Misc.h>
//#include <NovelCVLib\OpenCV\CvIncludes.h>
//#include <NovelCVLib\OpenCV\Types.h>
//#include <NovelCVLib\OpenCV\error.h>
//#include <NovelCVLib\OpenCV\funcs1.h>
#include <vector>
//#include <NovelCVLib\OpenCV\Image.h>
#include <NovelCVLib\Ncv\ConflictInfo2.h>
#include <NovelCVLib\Ncv\Bidiff.h>
#include <NovelCVLib\Ncv\BidiffMag.h>

//#include <NovelCVLib\Ncpp\Common\commonLib_Misc.h>



namespace Ncv
{
	using namespace Ncpp;

	namespace LineOperations2
	{
		template<class T>
		void FillLine(const VirtArrayAccessor_1D<T> & a_acc, const T & a_val)
		{
			AssertValue(a_val);

			PtrIterator2<T> ptrItr = a_acc.GenPtrIterator();

			for (; ptrItr.CanMove(); ptrItr.MoveBgn())
			{
				T * ptr = ptrItr.GetBgn();
				ElementOperations2::Assign<T>(ptr, a_val);
			}
		}

		template<class T>
		void SetLineToUndefined(const VirtArrayAccessor_1D<T> & a_acc)
		{
			PtrIterator2<T> ptrItr = a_acc.GenPtrIterator();

			for (; ptrItr.CanMove(); ptrItr.MoveBgn())
			{
				T * ptr = ptrItr.GetBgn();
				ElementOperations2::SetToUndefined<T>(ptr);
			}
		}

		template<class T>
		void SetUndefinedInLineToValue(const VirtArrayAccessor_1D<T> & a_acc, const T & a_value)
		{
			PtrIterator2<T> ptrItr = a_acc.GenPtrIterator();

			for (; ptrItr.CanMove(); ptrItr.MoveBgn())
			{
				T * ptr = ptrItr.GetBgn();
				if (IsUndefined(*ptr))
				{
					ElementOperations2::Assign<T>(ptr, a_value);
				}
			}
		}

		template<class T>
		void SetUndefinedInLineToZero(const VirtArrayAccessor_2D<T> & a_acc)
		{
			SetUndefinedInLineToValue(a_acc, CreateZeroVal<T>());
		}

		template<class T>
		void SetLineToBadValue(const VirtArrayAccessor_1D<T> & a_acc)
		{
			PtrIterator2<T> ptrItr = a_acc.GenPtrIterator();

			for (; ptrItr.CanMove(); ptrItr.MoveBgn())
			{
				T * ptr = ptrItr.GetBgn();
				ElementOperations2::SetToBadValue<T>(ptr);
			}
		}

		template<class T>
		void AssertLineValues(const VirtArrayAccessor_1D<T> & a_acc)
		{
			PtrIterator2<T> ptrItr = a_acc.GenPtrIterator();

			T * ptr;
			//int cnt = 0;

			//for (; ptrItr.CanMove(); ptrItr.MoveBgn(), cnt++)
			for (; ptrItr.CanMove(); ptrItr.MoveBgn())
			{
				ptr = ptrItr.GetBgn();
				ElementOperations2::AssertValue<T>(*ptr);
			}
		}

		template<class T>
		void AssertLineUndefinedOrValid(const VirtArrayAccessor_1D<T> & a_acc)
		{
			PtrIterator2<T> ptrItr = a_acc.GenPtrIterator();

			T * ptr;
			int cnt = 0;

			for (; ptrItr.CanMove(); ptrItr.MoveBgn(), cnt++)
			{
				ptr = ptrItr.GetBgn();
				ElementOperations2::AssertUndefinedOrValid<T>(*ptr);
			}
		}

		template<class T>
		void AddValueToLine(const VirtArrayAccessor_1D<T> & a_inpAcc, const VirtArrayAccessor_1D<T> & a_outAcc, const T & a_value)
		{
			AssertLineUndefinedOrValid(a_inpAcc);
			AssertLineUndefinedOrValid(a_outAcc);

			Ncpp_ASSERT(a_inpAcc.GetSize() == a_outAcc.GetSize());


			PtrIterator2<T> ptrItr_Inp = a_inpAcc.GenPtrIterator();
			PtrIterator2<T> ptrItr_Out = a_outAcc.GenPtrIterator();


			// manage undefined from bgn.
			for (; ptrItr_Inp.CanMove(); ptrItr_Inp.MoveBgn(), ptrItr_Out.MoveBgn())
			{
				T * ptr_Inp = ptrItr_Inp.GetBgn();
				T * ptr_Out = ptrItr_Out.GetBgn();

				if (IsUndefined(*ptr_Inp))
				{
					SetToUndefined(ptr_Out);
				}
				else
				{
					break;
				}
			}

			// manage undefined from end.
			for (; ptrItr_Inp.CanMove(); ptrItr_Inp.MoveEnd(), ptrItr_Out.MoveEnd())
			{
				T * ptr_Inp = ptrItr_Inp.GetEnd();
				T * ptr_Out = ptrItr_Out.GetEnd();

				if (IsUndefined(*ptr_Inp))
				{
					SetToUndefined(ptr_Out);
				}
				else
				{
					break;
				}
			}


			// do main job.
			int cnt = 0;
			for (; ptrItr_Inp.CanMove(); ptrItr_Inp.MoveBgn(), ptrItr_Out.MoveBgn(), cnt++)
			{
				T * ptr_Inp = ptrItr_Inp.GetBgn();
				T * ptr_Out = ptrItr_Out.GetBgn();

				ElementOperations2::Add<T>(*ptr_Inp, a_value, ptr_Out);
			}
		}
		
		template<class T>
		void DivideLineByNum(const VirtArrayAccessor_1D<T> & a_inpAcc, const VirtArrayAccessor_1D<T> & a_outAcc, const float a_num)
		{
			AssertLineUndefinedOrValid(a_inpAcc);
			AssertLineUndefinedOrValid(a_outAcc);

			Ncpp_ASSERT(a_inpAcc.GetSize() == a_outAcc.GetSize());


			PtrIterator2<T> ptrItr_Inp = a_inpAcc.GenPtrIterator();
			PtrIterator2<T> ptrItr_Out = a_outAcc.GenPtrIterator();


			// manage undefined from bgn.
			for (; ptrItr_Inp.CanMove(); ptrItr_Inp.MoveBgn(), ptrItr_Out.MoveBgn())
			{
				T * ptr_Inp = ptrItr_Inp.GetBgn();
				T * ptr_Out = ptrItr_Out.GetBgn();

				if (IsUndefined(*ptr_Inp))
				{
					SetToUndefined(ptr_Out);
				}
				else
				{
					break;
				}
			}

			// manage undefined from end.
			for (; ptrItr_Inp.CanMove(); ptrItr_Inp.MoveEnd(), ptrItr_Out.MoveEnd())
			{
				T * ptr_Inp = ptrItr_Inp.GetEnd();
				T * ptr_Out = ptrItr_Out.GetEnd();

				if (IsUndefined(*ptr_Inp))
				{
					SetToUndefined(ptr_Out);
				}
				else
				{
					break;
				}
			}


			// do main job.
			int cnt = 0;
			for (; ptrItr_Inp.CanMove(); ptrItr_Inp.MoveBgn(), ptrItr_Out.MoveBgn(), cnt++)
			{
				T * ptr_Inp = ptrItr_Inp.GetBgn();
				T * ptr_Out = ptrItr_Out.GetBgn();

				ElementOperations2::DivideByNum<T>(*ptr_Inp, a_num, ptr_Out);
			}
		}

		template<class T>
		void MultiplyLineByNum(const VirtArrayAccessor_1D<T> & a_inpAcc, const VirtArrayAccessor_1D<T> & a_outAcc, const float a_num)
		{
			AssertLineUndefinedOrValid(a_inpAcc);
			AssertLineUndefinedOrValid(a_outAcc);

			Ncpp_ASSERT(a_inpAcc.GetSize() == a_outAcc.GetSize());


			PtrIterator2<T> ptrItr_Inp = a_inpAcc.GenPtrIterator();
			PtrIterator2<T> ptrItr_Out = a_outAcc.GenPtrIterator();


			// manage undefined from bgn.
			for (; ptrItr_Inp.CanMove(); ptrItr_Inp.MoveBgn(), ptrItr_Out.MoveBgn())
			{
				T * ptr_Inp = ptrItr_Inp.GetBgn();
				T * ptr_Out = ptrItr_Out.GetBgn();

				if (IsUndefined(*ptr_Inp))
				{
					SetToUndefined(ptr_Out);
				}
				else
				{
					break;
				}
			}

			// manage undefined from end.
			for (; ptrItr_Inp.CanMove(); ptrItr_Inp.MoveEnd(), ptrItr_Out.MoveEnd())
			{
				T * ptr_Inp = ptrItr_Inp.GetEnd();
				T * ptr_Out = ptrItr_Out.GetEnd();

				if (IsUndefined(*ptr_Inp))
				{
					SetToUndefined(ptr_Out);
				}
				else
				{
					break;
				}
			}


			// do main job.
			for (; ptrItr_Inp.CanMove(); ptrItr_Inp.MoveBgn(), ptrItr_Out.MoveBgn())
			{
				T * ptr_Inp = ptrItr_Inp.GetBgn();
				T * ptr_Out = ptrItr_Out.GetBgn();

				ElementOperations2::MultiplyByNum<T>(*ptr_Inp, a_num, ptr_Out);
			}
		}


		template<class T>
		void CopyLine(const VirtArrayAccessor_1D<T> & a_destAcc, const VirtArrayAccessor_1D<T> & a_srcAcc)
		{
			AssertLineUndefinedOrValid(a_srcAcc);

			Ncpp_ASSERT(a_srcAcc.GetSize() == a_destAcc.GetSize());

			PtrIterator2<T> ptrItr_Src = a_srcAcc.GenPtrIterator();
			PtrIterator2<T> ptrItr_Dest = a_destAcc.GenPtrIterator();


			// manage undefined from bgn.
			for (; ptrItr_Src.CanMove(); ptrItr_Src.MoveBgn(), ptrItr_Dest.MoveBgn())
			{
				T * ptr_Src = ptrItr_Src.GetBgn();
				T * ptr_Dest = ptrItr_Dest.GetBgn();

				if (IsUndefined(*ptr_Src))
				{
					SetToUndefined(ptr_Dest);
				}
				else
				{
					break;
				}
			}

			// manage undefined from end.
			for (; ptrItr_Src.CanMove(); ptrItr_Src.MoveEnd(), ptrItr_Dest.MoveEnd())
			{
				T * ptr_Src = ptrItr_Src.GetEnd();
				T * ptr_Dest = ptrItr_Dest.GetEnd();

				if (IsUndefined(*ptr_Src))
				{
					SetToUndefined(ptr_Dest);
				}
				else
				{
					break;
				}
			}


			// do main job.
			for (; ptrItr_Src.CanMove(); ptrItr_Src.MoveBgn(), ptrItr_Dest.MoveBgn())
			{
				T * ptr_Src = ptrItr_Src.GetBgn();
				T * ptr_Dest = ptrItr_Dest.GetBgn();

				ElementOperations2::Assign<T>(ptr_Dest, *ptr_Src);
			}
		}

		template<class T>
		void CopyLineWithShift(const VirtArrayAccessor_1D<T> & a_destAcc, const VirtArrayAccessor_1D<T> & a_srcAcc, const int a_shift)
		{
			AssertLineUndefinedOrValid(a_srcAcc);

			Ncpp_ASSERT(a_srcAcc.GetSize() == a_destAcc.GetSize());

			PtrIterator2<T> ptrItr_Src = a_srcAcc.GenPtrIterator();
			PtrIterator2<T> ptrItr_Dest = a_destAcc.GenPtrIterator();




			// manage undefined from bgn.
			for (; ptrItr_Src.CanMove(); ptrItr_Src.MoveBgn(), ptrItr_Dest.MoveBgn())
			{
				T * ptr_Src = ptrItr_Src.GetBgn();
				T * ptr_Dest = ptrItr_Dest.GetBgn();

				if (IsUndefined(*ptr_Src))
				{
					SetToUndefined(ptr_Dest);
				}
				else
				{
					break;
				}
			}

			// manage undefined from end.
			for (; ptrItr_Src.CanMove(); ptrItr_Src.MoveEnd(), ptrItr_Dest.MoveEnd())
			{
				T * ptr_Src = ptrItr_Src.GetEnd();
				T * ptr_Dest = ptrItr_Dest.GetEnd();

				if (IsUndefined(*ptr_Src))
				{
					SetToUndefined(ptr_Dest);
				}
				else
				{
					break;
				}
			}


			// do main job.
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
			AssertLineUndefinedOrValid(a_inpAcc);

			Ncpp_ASSERT(a_inpAcc.GetSize() == a_outAcc.GetSize());

			PtrIterator2<T> ptrItr_Inp = a_inpAcc.GenPtrIterator();
			PtrIterator2<float> ptrItr_Out = a_outAcc.GenPtrIterator();


			// manage undefined from bgn.
			for (; ptrItr_Inp.CanMove(); ptrItr_Inp.MoveBgn(), ptrItr_Out.MoveBgn())
			{
				T * ptr_Inp = ptrItr_Inp.GetBgn();
				float * ptr_Out = ptrItr_Out.GetBgn();

				if (IsUndefined(*ptr_Inp))
				{
					SetToUndefined(ptr_Out);
				}
				else
				{
					break;
				}
			}

			// manage undefined from end.
			for (; ptrItr_Inp.CanMove(); ptrItr_Inp.MoveEnd(), ptrItr_Out.MoveEnd())
			{
				T * ptr_Inp = ptrItr_Inp.GetEnd();
				float * ptr_Out = ptrItr_Out.GetEnd();

				if (IsUndefined(*ptr_Inp))
				{
					SetToUndefined(ptr_Out);
				}
				else
				{
					break;
				}
			}


			// do actual stuff.
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

			AssertLineUndefinedOrValid(a_inpAcc);

			PtrIterator2<T> ptrItr_Inp = a_inpAcc.GenPtrIterator();
			PtrIterator2<float> ptrItr_Out = a_outAcc.GenPtrIterator();

			// manage undefined from bgn.
			for (; ptrItr_Inp.CanMove(); ptrItr_Inp.MoveBgn(), ptrItr_Out.MoveBgn())
			{
				T * ptr_Inp = ptrItr_Inp.GetBgn();
				float * ptr_Out = ptrItr_Out.GetBgn();

				if (IsUndefined(*ptr_Inp))
				{
					SetToUndefined(ptr_Out);
				}
				else
				{
					break;
				}
			}

			// manage undefined from end.
			for (; ptrItr_Inp.CanMove(); ptrItr_Inp.MoveEnd(), ptrItr_Out.MoveEnd())
			{
				T * ptr_Inp = ptrItr_Inp.GetEnd();
				float * ptr_Out = ptrItr_Out.GetEnd();

				if (IsUndefined(*ptr_Inp))
				{
					SetToUndefined(ptr_Out);
				}
				else
				{
					break;
				}
			}

			// do actual stuff.
			for (; ptrItr_Inp.CanMove(); ptrItr_Inp.MoveBgn(), ptrItr_Out.MoveBgn())
			{
				T * ptr_Inp = ptrItr_Inp.GetBgn();
				float * ptr_Out = ptrItr_Out.GetBgn();

				*ptr_Out = ElementOperations2::CalcMagSqr<T>(*ptr_Inp);
			}
		}


		template<class T>
		void AvgLine(const VirtArrayAccessor_1D<T> & a_inpAcc, const VirtArrayAccessor_1D<T> & a_outAcc, const Range<int> & a_range)
		{
			AssertLineUndefinedOrValid(a_inpAcc);

			Ncpp_ASSERT(a_inpAcc.GetSize() == a_outAcc.GetSize());
			Ncpp_ASSERT(a_range.GetBgn() <= 0);
			Ncpp_ASSERT(0 <= a_range.GetEnd());

			T zeroVal;
			SetToZero<T>(&zeroVal);

			const int nSize_1D = a_inpAcc.GetSize();

			const int nBefDiff = -a_range.GetBgn();
			const int nAftDiff = a_range.GetEnd();

			const int nRangeLen = nBefDiff + 1 + nAftDiff;

			int start = 0;
			for (; start < nSize_1D; start++)
			{
				const T & inpVal = a_inpAcc[start];
				if (IsUndefined(inpVal))
				{
					continue;
				}
				else
				{
					break;
				}
			}

			int end = nSize_1D - 1;
			for (; end >= start; end--)
			{
				const T & inpVal = a_inpAcc[end];
				if (IsUndefined(inpVal))
				{
					continue;
				}
				else
				{
					break;
				}
			}


			//------

			if (end + 1 - start < nRangeLen)
			{
				SetLineToUndefined(a_outAcc);
				return;
			}

			// T * orgAccData = a_inpAcc.GetData();

			// VirtArrayAccessor_1D<T> inpAccTest;
			// a_inpAcc.CopyTo(&inpAccTest, start, end);

			// T * testAccData = inpAccTest.GetData();

			// AssertLineValues(inpAccTest);


			const int nCenterEnd = end - nAftDiff;

			T sum;
			SetToZero<T>(&sum);
			for (int i = start; i < start + nRangeLen; i++)
			{
				IncBy(sum, a_inpAcc[i]);
			}

			T * pDest;
			pDest = (T *)&a_outAcc[start + nBefDiff];
			DivideByNum(sum, nRangeLen, pDest);

			for (int i = start + nBefDiff + 1; i <= nCenterEnd; i++)
			{
				DecBy(sum, a_inpAcc[(i - 1) - nBefDiff]);
				IncBy(sum, a_inpAcc[i + nAftDiff]);

				pDest = (T *)&a_outAcc[i];
				DivideByNum(sum, nRangeLen, pDest);

				//AssertUndefinedOrValid(*pDest);
			}

			///////////////////////////////

			//	Fill bgn gap in output
			{
				for (int i = 0; i < start + nBefDiff; i++)
				{
					pDest = (T *)&a_outAcc[i];
					SetToUndefined(pDest);
				}
			}

			//	Fill end gap in output
			{
				const int nSrcIdx = (end) - nAftDiff;

				for (int i = nSrcIdx + 1; i < nSize_1D; i++)
				{
					pDest = (T *)&a_outAcc[i];
					SetToUndefined(pDest);
				}
			}


			AssertLineUndefinedOrValid(a_outAcc);
		}


		template<class T>
		//void AvgLine(const VirtArrayAccessor_1D<T> & a_inpAcc, const VirtArrayAccessor_1D<T> & a_outAcc, const Range<int> & a_range)
		void AvgLine_Weighted(const VirtArrayAccessor_1D<T> & a_inpAcc, const VirtArrayAccessor_1D<float> & a_weightAcc, const VirtArrayAccessor_1D<T> & a_outAcc, const Range<int> & a_range)
		{
			AssertLineUndefinedOrValid(a_inpAcc);

			Ncpp_ASSERT(a_inpAcc.GetSize() == a_outAcc.GetSize());
			Ncpp_ASSERT(a_inpAcc.GetSize() == a_weightAcc.GetSize());
			Ncpp_ASSERT(a_range.GetBgn() <= 0);
			Ncpp_ASSERT(0 <= a_range.GetEnd());

			T zeroVal;
			SetToZero<T>(&zeroVal);

			const int nSize_1D = a_inpAcc.GetSize();

			const int nBefDiff = -a_range.GetBgn();
			const int nAftDiff = a_range.GetEnd();

			const int nRangeLen = nBefDiff + 1 + nAftDiff;


			int start = 0;
			for (; start < nSize_1D; start++)
			{
				const T & inpVal = a_inpAcc[start];
				const T & weightVal = a_weightAcc[start];
				if (IsUndefined(inpVal) || IsUndefined(weight))
				{
					continue;
				}
				else
				{
					break;
				}
			}

			int end = nSize_1D - 1;
			for (; end >= start; end--)
			{
				const T & inpVal = a_inpAcc[end];
				const T & weightVal = a_weightAcc[end];
				if (IsUndefined(inpVal) || IsUndefined(weight))
				{
					continue;
				}
				else
				{
					break;
				}
			}


			//------

			if (end + 1 - start < nRangeLen)
			{
				SetLineToUndefined(a_outAcc);
				return;
			}

			const int nCenterEnd = end - nAftDiff;

			T sum;
			SetToZero<T>(&sum);
			
			int sum_Wt = 0;
			T inp2;

			for (int i = start; i < start + nRangeLen; i++)
			{
				Assign(&inp2, &a_inpAcc[i]);
				MultiplyByNum(inp2, a_weightAcc[i], &inp2);

				IncBy(sum_Wt, a_weightAcc[i]);
				IncBy(sum, inp2);
			}

			T * pDest;

			{
				pDest = (T *)&a_outAcc[start + nBefDiff];
				float denom = (sum_Wt > 0.2f) ? sum_Wt : 0.2f;
				DivideByNum(sum, denom, pDest);
			}



			for (int i = start + nBefDiff + 1; i <= nCenterEnd; i++)
			{
				int idx_Sub = (i - 1) - nBefDiff;
				Assign(&inp2, &a_inpAcc[idx_Sub]);
				MultiplyByNum(inp2, a_weightAcc[idx_Sub], &inp2);

				DecBy(sum, inp2);
				DecBy(sum_Wt, a_weightAcc[idx_Sub]);

				int idx_Add = i + nAftDiff;
				Assign(&inp2, &a_inpAcc[idx_Add]);
				MultiplyByNum(inp2, a_weightAcc[idx_Add], &inp2);

				IncBy(sum, inp2);
				IncBy(sum_Wt, a_weightAcc[idx_Add]);

				{
					pDest = (T *)&a_outAcc[i];
					float denom = (sum_Wt > 0.2f) ? sum_Wt : 0.2f;
					DivideByNum(sum, denom, pDest);
				}

				//AssertUndefinedOrValid(*pDest);
			}

			///////////////////////////////

			//	Fill bgn gap in output
			{
				for (int i = 0; i < start + nBefDiff; i++)
				{
					pDest = (T *)&a_outAcc[i];
					SetToUndefined(pDest);
				}
			}

			//	Fill end gap in output
			{
				const int nSrcIdx = (end)-nAftDiff;

				for (int i = nSrcIdx + 1; i < nSize_1D; i++)
				{
					pDest = (T *)&a_outAcc[i];
					SetToUndefined(pDest);
				}
			}


			AssertLineUndefinedOrValid(a_outAcc);
		}


		template<class T>
		void CalcSqrtLine(const VirtArrayAccessor_1D<T> & a_inpAcc, const VirtArrayAccessor_1D<float> & a_outAcc)
		{

			AssertLineUndefinedOrValid(a_inpAcc);

			Ncpp_ASSERT(a_inpAcc.GetSize() == a_outAcc.GetSize());

			PtrIterator2<T> ptrItr_Inp = a_inpAcc.GenPtrIterator();
			PtrIterator2<float> ptrItr_Out = a_outAcc.GenPtrIterator();


			// manage undefined from bgn.
			for (; ptrItr_Inp.CanMove(); ptrItr_Inp.MoveBgn(), ptrItr_Out.MoveBgn())
			{
				T * ptr_Inp = ptrItr_Inp.GetBgn();
				float * ptr_Out = ptrItr_Out.GetBgn();

				if (IsUndefined(*ptr_Inp))
				{
					SetToUndefined(ptr_Out);
				}
				else
				{
					break;
				}
			}

			// manage undefined from end.
			for (; ptrItr_Inp.CanMove(); ptrItr_Inp.MoveEnd(), ptrItr_Out.MoveEnd())
			{
				T * ptr_Inp = ptrItr_Inp.GetEnd();
				float * ptr_Out = ptrItr_Out.GetEnd();

				if (IsUndefined(*ptr_Inp))
				{
					SetToUndefined(ptr_Out);
				}
				else
				{
					break;
				}
			}


			// do actual stuff.
			for (; ptrItr_Inp.CanMove(); ptrItr_Inp.MoveBgn(), ptrItr_Out.MoveBgn())
			{
				T * ptr_Inp = ptrItr_Inp.GetBgn();
				float * ptr_Out = ptrItr_Out.GetBgn();

				//*ptr_Out = ElementOperations2::CalcMag<T>(*ptr_Inp);
				*ptr_Out = ElementOperations2::CalcSqrt<T>(*ptr_Inp);
			}

		}

		template<class T>
		void CalcStandevLine(const VirtArrayAccessor_1D<T> & a_avg_Acc, const VirtArrayAccessor_1D<float> & a_avg_MagSqr_Acc,
			const VirtArrayAccessor_1D<float> & a_outAcc)
		{
			AssertLineUndefinedOrValid(a_avg_Acc);
			AssertLineUndefinedOrValid(a_avg_MagSqr_Acc);

			Ncpp_ASSERT(a_avg_Acc.GetSize() == a_avg_MagSqr_Acc.GetSize());
			Ncpp_ASSERT(a_avg_Acc.GetSize() == a_outAcc.GetSize());

			PtrIterator2<T> ptrItr_Avg = a_avg_Acc.GenPtrIterator();
			PtrIterator2<float> ptrItr_Avg_MagSqr = a_avg_MagSqr_Acc.GenPtrIterator();
			PtrIterator2<float> ptrItr_Out = a_outAcc.GenPtrIterator();

			int cnt_undefined_Bgn = 0;

			// manage undefined from bgn.
			for (; ptrItr_Avg.CanMove(); ptrItr_Avg.MoveBgn(), ptrItr_Avg_MagSqr.MoveBgn(), ptrItr_Out.MoveBgn(), cnt_undefined_Bgn++)
			{   
				T * ptr_Avg = ptrItr_Avg.GetBgn();
				float * ptr_Avg_MagSqr = ptrItr_Avg_MagSqr.GetBgn();
				
				float * ptr_Out = ptrItr_Out.GetBgn();

				if (IsUndefined(*ptr_Avg) || IsUndefined(*ptr_Avg_MagSqr))
				{
					SetToUndefined(ptr_Out);
				}
				else
				{
					break;
				}
			}

			int cnt_undefined_End = 0;

			// manage undefined from end.
			for (; ptrItr_Avg.CanMove(); ptrItr_Avg.MoveEnd(), ptrItr_Avg_MagSqr.MoveEnd(), ptrItr_Out.MoveEnd(), cnt_undefined_End++)
			{
				T * ptr_Avg = ptrItr_Avg.GetEnd();
				float * ptr_Avg_MagSqr = ptrItr_Avg_MagSqr.GetEnd();
				float * ptr_Out = ptrItr_Out.GetEnd();

				if (IsUndefined(*ptr_Avg) || IsUndefined(*ptr_Avg_MagSqr))
				{
					SetToUndefined(ptr_Out);
				}
				else
				{
					break;
				}
			}

			int cnt = 0;
			//	do actual stuff.
			for (; ptrItr_Avg.CanMove();
				ptrItr_Avg.MoveBgn(), ptrItr_Avg_MagSqr.MoveBgn(), ptrItr_Out.MoveBgn(), cnt++)
			{
				T * ptr_Avg = ptrItr_Avg.GetBgn();
				float * ptr_Avg_MagSqr = ptrItr_Avg_MagSqr.GetBgn();
				float * ptr_Out = ptrItr_Out.GetBgn();

				*ptr_Out = ElementOperations2::CalcStandev<T>(*ptr_Avg, *ptr_Avg_MagSqr);
			}
	
			AssertLineUndefinedOrValid(a_outAcc);
		}

		template<class T>
		void CalcConflictLine(const VirtArrayAccessor_1D<T> & a_avg_Acc, const VirtArrayAccessor_1D<float> & a_avg_MagSqr_Acc,
			const VirtArrayAccessor_1D<ConflictInfo2> & a_outAcc, const Range<int> & a_range)
		{
			Ncpp_ASSERT(a_avg_Acc.GetSize() == a_avg_MagSqr_Acc.GetSize());
			Ncpp_ASSERT(a_avg_Acc.GetSize() == a_outAcc.GetSize());

			AssertLineUndefinedOrValid(a_avg_Acc);
			AssertLineUndefinedOrValid(a_avg_MagSqr_Acc);


			const int nSize_1D = a_outAcc.GetSize();

			const int nBefDiff = -a_range.GetBgn();
			const int nAftDiff = a_range.GetEnd();

			const int nRangeLen = nBefDiff + 1 + nAftDiff;


//--------------



			int start = 0;
			for (; start < nSize_1D; start++)
			{
				const T & avgVal = a_avg_Acc[start];
				const float & avgMagSqrVal = a_avg_MagSqr_Acc[start];

				if (IsUndefined(avgVal) || IsUndefined(avgMagSqrVal))
				{
					continue;
				}
				else
				{
					break;
				}
			}

			int end = nSize_1D - 1;
			for (; end >= start; end--)
			{
				const T & avgVal = a_avg_Acc[end];
				const float & avgMagSqrVal = a_avg_MagSqr_Acc[end];

				if (IsUndefined(avgVal) || IsUndefined(avgMagSqrVal))
				{
					continue;
				}
				else
				{
					break;
				}
			}


			//------

			if (end + 1 - start < nRangeLen)
			{
				SetLineToUndefined(a_outAcc);
				return;
			}

			//const int nCenterEnd = nSize_1D - 1 - nAftDiff;
			const int nCenterEnd = end - nAftDiff;


//--------------




			for (int i = start + nBefDiff; i <= nCenterEnd; i++)
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
					i = i;
				}

				//if (pOut->Exists)
				{
					// to be revised.
					//pOut->pSide_1 = &avg_1;

					pOut->Offset_Side_1 = &avg_1 - a_avg_Acc.GetData_FakeOrg();
					Ncpp_ASSERT(pOut->Offset_Side_1 >= 0);

					if (211 == pOut->Offset_Side_1)
					{
						i = i;
					}

					//pOut->pSide_2 = &avg_2;

					pOut->Offset_Side_2 = &avg_2 - a_avg_Acc.GetData_FakeOrg();
					Ncpp_ASSERT(pOut->Offset_Side_2 >= 0);
				}
				//else
				//{
				//	pOut->Offset_Side_1 = -700;
				//	
				//	//pOut->Offset_Side_1 = -7;
				//	//pOut->Offset_Side_2 = -7;
				//}
			}

			///////////////////////////////

			//	Fill bgn gap in output
			{
				for (int i = 0; i < start + nBefDiff; i++)
				{
					ConflictInfo2 * pDest = (ConflictInfo2 *)&a_outAcc[i];
					SetToUndefined(pDest);
				}
			}

			//	Fill end gap in output
			{
				for (int i = end - nAftDiff + 1; i < nSize_1D; i++)
				{
					ConflictInfo2 * pDest = (ConflictInfo2 *)&a_outAcc[i];
					SetToUndefined(pDest);
				}
			}


			AssertLineUndefinedOrValid(a_outAcc);

		}

		template<class T>
		void Calc_ConflictDiff_Line(const VirtArrayAccessor_1D<T> & a_avg_Acc, const VirtArrayAccessor_1D<float> & a_avg_MagSqr_Acc,
			const VirtArrayAccessor_1D<float> & a_outAcc, const Range<int> & a_range)
		{
			Ncpp_ASSERT(a_avg_Acc.GetSize() == a_avg_MagSqr_Acc.GetSize());
			Ncpp_ASSERT(a_avg_Acc.GetSize() == a_outAcc.GetSize());

			AssertLineUndefinedOrValid(a_avg_Acc);
			AssertLineUndefinedOrValid(a_avg_MagSqr_Acc);


			const int nSize_1D = a_outAcc.GetSize();

			const int nBefDiff = -a_range.GetBgn();
			const int nAftDiff = a_range.GetEnd();

			const int nRangeLen = nBefDiff + 1 + nAftDiff;


			//--------------



			int start = 0;
			for (; start < nSize_1D; start++)
			{
				const T & avgVal = a_avg_Acc[start];
				const float & avgMagSqrVal = a_avg_MagSqr_Acc[start];

				if (IsUndefined(avgVal) || IsUndefined(avgMagSqrVal))
				{
					continue;
				}
				else
				{
					break;
				}
			}

			int end = nSize_1D - 1;
			for (; end >= start; end--)
			{
				const T & avgVal = a_avg_Acc[end];
				const float & avgMagSqrVal = a_avg_MagSqr_Acc[end];

				if (IsUndefined(avgVal) || IsUndefined(avgMagSqrVal))
				{
					continue;
				}
				else
				{
					break;
				}
			}


			//------

			if (end + 1 - start < nRangeLen)
			{
				SetLineToUndefined(a_outAcc);
				return;
			}

			//const int nCenterEnd = nSize_1D - 1 - nAftDiff;
			const int nCenterEnd = end - nAftDiff;


			//--------------



			for (int i = start + nBefDiff; i <= nCenterEnd; i++)
			{
				//float * pOut = &a_outAcc[i];
				float * pOut = (float *)&a_outAcc[i];

				const T & avg_1 = a_avg_Acc[i - nBefDiff];
				float avg_MagSqr_1 = a_avg_MagSqr_Acc[i - nBefDiff];

				const T & avg_2 = a_avg_Acc[i + nAftDiff];
				float avg_MagSqr_2 = a_avg_MagSqr_Acc[i + nAftDiff];

				*pOut = ElementOperations2::CalcConflict(avg_1, avg_MagSqr_1, avg_2, avg_MagSqr_2);
			}

			///////////////////////////////

			//	Fill bgn gap in output
			{
				for (int i = 0; i < start + nBefDiff; i++)
				{
					ConflictInfo2 * pDest = (ConflictInfo2 *)&a_outAcc[i];
					SetToUndefined(pDest);
				}
			}

			//	Fill end gap in output
			{
				for (int i = end - nAftDiff + 1; i < nSize_1D; i++)
				{
					ConflictInfo2 * pDest = (ConflictInfo2 *)&a_outAcc[i];
					SetToUndefined(pDest);
				}
			}


			AssertLineUndefinedOrValid(a_outAcc);
		}

		template<class T>
		void CalcDiffLine(const VirtArrayAccessor_1D<T> & a_inp_Acc,
			const VirtArrayAccessor_1D<T> & a_outAcc, const Range<int> & a_range)
		{
			Ncpp_ASSERT(a_inp_Acc.GetSize() == a_outAcc.GetSize());

			AssertLineUndefinedOrValid(a_inp_Acc);

			const int nSize_1D = a_outAcc.GetSize();

			const int nBefDiff = -a_range.GetBgn();
			const int nAftDiff = a_range.GetEnd();

			const int nRangeLen = nBefDiff + 1 + nAftDiff;


			//--------------



			int start = 0;
			for (; start < nSize_1D; start++)
			{
				const T & inpVal = a_inp_Acc[start];

				if (IsUndefined(inpVal))
				{
					continue;
				}
				else
				{
					break;
				}
			}

			int end = nSize_1D - 1;
			for (; end >= start; end--)
			{
				const T & inpVal = a_inp_Acc[end];

				if (IsUndefined(inpVal))
				{
					continue;
				}
				else
				{
					break;
				}
			}


			//------

			if (end + 1 - start < nRangeLen)
			{
				SetLineToUndefined(a_outAcc);
				return;
			}

			//const int nCenterEnd = nSize_1D - 1 - nAftDiff;
			const int nCenterEnd = end - nAftDiff;


			//--------------



			for (int i = start + nBefDiff; i <= nCenterEnd; i++)
			{
				T * pOut = (T *)&a_outAcc[i];

				const T & inp_1 = a_inp_Acc[i - nBefDiff];

				const T & inp_2 = a_inp_Acc[i + nAftDiff];

				ElementOperations2::Subtract(inp_2, inp_1, pOut);
			}

			///////////////////////////////

			//	Fill bgn gap in output
			{
				for (int i = 0; i < start + nBefDiff; i++)
				{
					T * pDest = (T *)&a_outAcc[i];
					SetToUndefined(pDest);
				}
			}

			//	Fill end gap in output
			{
				for (int i = end - nAftDiff + 1; i < nSize_1D; i++)
				{
					T * pDest = (T *)&a_outAcc[i];
					SetToUndefined(pDest);
				}
			}


			AssertLineUndefinedOrValid(a_outAcc);
		}


		template<class T>
		void SetBidiffMagLineFromDiffLine(const VirtArrayAccessor_1D<T> & a_diff_Acc,
			const VirtArrayAccessor_1D<BidiffMag> & a_outAcc, const int a_posDiff)
		{
			Ncpp_ASSERT(a_diff_Acc.GetSize() == a_outAcc.GetSize());

			AssertLineUndefinedOrValid(a_diff_Acc);

			const int nSize_1D = a_outAcc.GetSize();


			VirtArrayAccessor_1D<float> outBkwdAcc;
			VirtArrayAccessor_1D<float> outFwdAcc;
			{
				const float * pOutData_Fwd = &a_outAcc.GetData()->FwdVal;
				const float * pOutData_Bkwd = &a_outAcc.GetData()->BkwdVal;

				const float * pOutActualData_Fwd = &a_outAcc.GetData_FakeOrg()->FwdVal;
				const float * pOutActualData_Bkwd = &a_outAcc.GetData_FakeOrg()->BkwdVal;

				outBkwdAcc.Init(pOutData_Bkwd, pOutActualData_Bkwd, a_outAcc.GetSize(), a_outAcc.GetStepSize() * 2);
				outFwdAcc.Init(pOutData_Fwd, pOutActualData_Fwd, a_outAcc.GetSize(), a_outAcc.GetStepSize() * 2);
			}


			//const int nBefDiff = -a_range.GetBgn();
			//const int nAftDiff = a_range.GetEnd();

			//const int nBefDiff = -a_posDiff;
			////const int nBefDiff = 0;
			//const int nAftDiff = a_posDiff;

			//const int nRangeLen = nBefDiff + 1 + nAftDiff;


			//--------------



			int start = 0;
			for (; start < nSize_1D; start++)
			{
				const T & inpVal = a_diff_Acc[start];

				if (IsUndefined(inpVal))
				{
					continue;
				}
				else
				{
					break;
				}
			}
			//if (start < nSize_1D)
			//{
			//	start -= a_posDiff;
			//}
			//Ncpp_ASSERT(start >= 0);
			Ncpp_ASSERT(start >= a_posDiff);


			int end = nSize_1D - 1;
			for (; end >= start; end--)
			{
				const T & inpVal = a_diff_Acc[end];

				if (IsUndefined(inpVal))
				{
					continue;
				}
				else
				{
					break;
				}
			}


			//------

			//if (end + 1 - start < nRangeLen)
			if (end + 1 - start < 0)
			{
				//for (int i = 0; i < nSize_1D; i++)
				//{
				//	BidiffMag & rOut = a_outAcc[i];
				//	SetLineToUndefined(&rOut.BkwdVal);
				//	SetLineToUndefined(&rOut.FwdVal);
				//}
				//SetLineToUndefined(a_outAcc);

				SetLineToUndefined(outFwdAcc);
				SetLineToUndefined(outBkwdAcc);
				
				return;
			}


			//const int nCenterEnd = end - nAftDiff;


			//--------------

			for (int i = start - 1; i >= start - a_posDiff; i--)
			{
				BidiffMag & rOut = a_outAcc[i];
				SetToUndefined(&rOut.BkwdVal);
			}

			for (int i = end; i > end - a_posDiff; i--)
			{
				BidiffMag & rOut = a_outAcc[i];
				SetToUndefined(&rOut.FwdVal);
			}


			//for (int i = start + nBefDiff; i <= nCenterEnd; i++)
			for (int i = start; i <= end; i++)
			{
				const T & diff = a_diff_Acc[i];
				const float diffMag = CalcMag(diff);

				BidiffMag & rOut_Fwd = a_outAcc[i];
				BidiffMag & rOut_Bkwd = a_outAcc[i - a_posDiff];

				rOut_Bkwd.FwdVal = rOut_Fwd.BkwdVal = diffMag;
			}

			///////////////////////////////

			//	Fill bgn gap in output
			{
				//for (int i = 0; i < start + nBefDiff; i++)
				for (int i = 0; i < start - a_posDiff; i++)
				{
					BidiffMag & rDest = a_outAcc[i];
					SetToUndefined(&rDest.BkwdVal);
					SetToUndefined(&rDest.FwdVal);

					//T * pDest = (T *)&a_outAcc[i];
					//SetToUndefined(pDest);
				}
			}

			//	Fill end gap in output
			{
				//for (int i = end - nAftDiff + 1; i < nSize_1D; i++)
				for (int i = end + 1; i < nSize_1D; i++)
				{
					BidiffMag & rDest = a_outAcc[i];
					SetToUndefined(&rDest.BkwdVal);
					SetToUndefined(&rDest.FwdVal);

					//SetToUndefined(pDest);
				}
			}

			//throw "func not complete";

			AssertLineUndefinedOrValid(outBkwdAcc);
			AssertLineUndefinedOrValid(outFwdAcc);
	
			//AssertLineUndefinedOrValid(a_outAcc);
		}


	};
}