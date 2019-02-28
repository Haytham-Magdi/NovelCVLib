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
#include <NovelCVLib\Ncv\BidiffInfo.h>

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

			for (; ptrItr.HasValidPos(); ptrItr.MoveBgn())
			{
				T * ptr = ptrItr.GetBgn();
				ElementOperations2::Assign<T>(ptr, a_val);
			}
		}

		template<class T>
		void SetLineToUndefined(const VirtArrayAccessor_1D<T> & a_acc)
		{
			PtrIterator2<T> ptrItr = a_acc.GenPtrIterator();

			for (; ptrItr.HasValidPos(); ptrItr.MoveBgn())
			{
				T * ptr = ptrItr.GetBgn();
				ElementOperations2::SetToUndefined<T>(ptr);
			}
		}

		template<class T>
		void SetUndefinedInLineToValue(const VirtArrayAccessor_1D<T> & a_acc, const T & a_value)
		{
			PtrIterator2<T> ptrItr = a_acc.GenPtrIterator();

			for (; ptrItr.HasValidPos(); ptrItr.MoveBgn())
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

			for (; ptrItr.HasValidPos(); ptrItr.MoveBgn())
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

			//for (; ptrItr.HasValidPos(); ptrItr.MoveBgn(), cnt++)
			for (; ptrItr.HasValidPos(); ptrItr.MoveBgn())
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

			for (; ptrItr.HasValidPos(); ptrItr.MoveBgn(), cnt++)
			{
				ptr = ptrItr.GetBgn();
				ElementOperations2::AssertUndefinedOrValid<T>(*ptr);
			}
		}

		template<class T>
		void AddValueToLine(const VirtArrayAccessor_1D<T> & a_inpAcc, const VirtArrayAccessor_1D<T> & a_outAcc, const T & a_value)
		{
			AssertLineUndefinedOrValid(a_inpAcc);

			Ncpp_ASSERT(a_inpAcc.GetSize() == a_outAcc.GetSize());


			PtrIterator2<T> ptrItr_Inp = a_inpAcc.GenPtrIterator();
			PtrIterator2<T> ptrItr_Out = a_outAcc.GenPtrIterator();


			// manage undefined from bgn.
			for (; ptrItr_Inp.HasValidPos(); ptrItr_Inp.MoveBgn(), ptrItr_Out.MoveBgn())
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
			for (; ptrItr_Inp.HasValidPos(); ptrItr_Inp.MoveEnd(), ptrItr_Out.MoveEnd())
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
			for (; ptrItr_Inp.HasValidPos(); ptrItr_Inp.MoveBgn(), ptrItr_Out.MoveBgn(), cnt++)
			{
				T * ptr_Inp = ptrItr_Inp.GetBgn();
				T * ptr_Out = ptrItr_Out.GetBgn();

				ElementOperations2::Add<T>(*ptr_Inp, a_value, ptr_Out);
			}

			AssertLineUndefinedOrValid(a_outAcc);
		}
		
		template<class T>
		void CalcSqrVectorLine(const VirtArrayAccessor_1D<T> & a_inpAcc, const VirtArrayAccessor_1D<T> & a_outAcc)
		{
			AssertLineUndefinedOrValid(a_inpAcc);

			Ncpp_ASSERT(a_inpAcc.GetSize() == a_outAcc.GetSize());


			PtrIterator2<T> ptrItr_Inp = a_inpAcc.GenPtrIterator();
			PtrIterator2<T> ptrItr_Out = a_outAcc.GenPtrIterator();


			// manage undefined from bgn.
			for (; ptrItr_Inp.HasValidPos(); ptrItr_Inp.MoveBgn(), ptrItr_Out.MoveBgn())
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
			for (; ptrItr_Inp.HasValidPos(); ptrItr_Inp.MoveEnd(), ptrItr_Out.MoveEnd())
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
			for (; ptrItr_Inp.HasValidPos(); ptrItr_Inp.MoveBgn(), ptrItr_Out.MoveBgn(), cnt++)
			{
				T * ptr_Inp = ptrItr_Inp.GetBgn();
				T * ptr_Out = ptrItr_Out.GetBgn();

				ElementOperations2::CalcSqrVector<T>(*ptr_Inp, ptr_Out);
			}

			AssertLineUndefinedOrValid(a_outAcc);
		}
		

		template<class T>
		void AddLines(const VirtArrayAccessor_1D<T> & a_inp1_Acc, const VirtArrayAccessor_1D<T> & a_inp2_Acc, const VirtArrayAccessor_1D<T> & a_outAcc)
		{
			AssertLineUndefinedOrValid(a_inp1_Acc);
			AssertLineUndefinedOrValid(a_inp2_Acc);


			Ncpp_ASSERT(a_inp1_Acc.GetSize() == a_outAcc.GetSize());
			Ncpp_ASSERT(a_inp1_Acc.GetSize() == a_inp2_Acc.GetSize());


			PtrIterator2<T> ptrItr_Inp1 = a_inp1_Acc.GenPtrIterator();
			PtrIterator2<T> ptrItr_Inp2 = a_inp2_Acc.GenPtrIterator();
			PtrIterator2<T> ptrItr_Out = a_outAcc.GenPtrIterator();


			// manage undefined from bgn.
			for (; ptrItr_Inp1.HasValidPos(); ptrItr_Inp1.MoveBgn(), ptrItr_Inp2.MoveBgn(), ptrItr_Out.MoveBgn())
			{
				T * ptr_Inp1 = ptrItr_Inp1.GetBgn();
				T * ptr_Inp2 = ptrItr_Inp2.GetBgn();
				T * ptr_Out = ptrItr_Out.GetBgn();

				if (IsUndefined(*ptr_Inp1) || IsUndefined(*ptr_Inp2))
				{
					SetToUndefined(ptr_Out);
				}
				else
				{
					break;
				}
			}

			// manage undefined from end.
			for (; ptrItr_Inp1.HasValidPos(); ptrItr_Inp1.MoveEnd(), ptrItr_Inp2.MoveEnd(), ptrItr_Out.MoveEnd())
			{
				T * ptr_Inp1 = ptrItr_Inp1.GetEnd();
				T * ptr_Inp2 = ptrItr_Inp2.GetEnd();
				T * ptr_Out = ptrItr_Out.GetEnd();

				if (IsUndefined(*ptr_Inp1) || IsUndefined(*ptr_Inp2))
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
			for (; ptrItr_Inp1.HasValidPos(); ptrItr_Inp1.MoveBgn(), ptrItr_Inp2.MoveBgn(), ptrItr_Out.MoveBgn(), cnt++)
			{
				T * ptr_Inp1 = ptrItr_Inp1.GetBgn();
				T * ptr_Inp2 = ptrItr_Inp2.GetBgn();
				T * ptr_Out = ptrItr_Out.GetBgn();

				ElementOperations2::Add<T>(*ptr_Inp1, *ptr_Inp2, ptr_Out);
			}


			AssertLineUndefinedOrValid(a_outAcc);
		}

		template<class T>
		void SubtractLines(const VirtArrayAccessor_1D<T> & a_inp1_Acc, const VirtArrayAccessor_1D<T> & a_inp2_Acc, const VirtArrayAccessor_1D<T> & a_outAcc)
		{
			AssertLineUndefinedOrValid(a_inp1_Acc);
			AssertLineUndefinedOrValid(a_inp2_Acc);


			Ncpp_ASSERT(a_inp1_Acc.GetSize() == a_outAcc.GetSize());
			Ncpp_ASSERT(a_inp1_Acc.GetSize() == a_inp2_Acc.GetSize());


			PtrIterator2<T> ptrItr_Inp1 = a_inp1_Acc.GenPtrIterator();
			PtrIterator2<T> ptrItr_Inp2 = a_inp2_Acc.GenPtrIterator();
			PtrIterator2<T> ptrItr_Out = a_outAcc.GenPtrIterator();


			// manage undefined from bgn.
			for (; ptrItr_Inp1.HasValidPos(); ptrItr_Inp1.MoveBgn(), ptrItr_Inp2.MoveBgn(), ptrItr_Out.MoveBgn())
			{
				T * ptr_Inp1 = ptrItr_Inp1.GetBgn();
				T * ptr_Inp2 = ptrItr_Inp2.GetBgn();
				T * ptr_Out = ptrItr_Out.GetBgn();

				if (IsUndefined(*ptr_Inp1) || IsUndefined(*ptr_Inp2))
				{
					SetToUndefined(ptr_Out);
				}
				else
				{
					break;
				}
			}

			// manage undefined from end.
			for (; ptrItr_Inp1.HasValidPos(); ptrItr_Inp1.MoveEnd(), ptrItr_Inp2.MoveEnd(), ptrItr_Out.MoveEnd())
			{
				T * ptr_Inp1 = ptrItr_Inp1.GetEnd();
				T * ptr_Inp2 = ptrItr_Inp2.GetEnd();
				T * ptr_Out = ptrItr_Out.GetEnd();

				if (IsUndefined(*ptr_Inp1) || IsUndefined(*ptr_Inp2))
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
			for (; ptrItr_Inp1.HasValidPos(); ptrItr_Inp1.MoveBgn(), ptrItr_Inp2.MoveBgn(), ptrItr_Out.MoveBgn(), cnt++)
			{
				T * ptr_Inp1 = ptrItr_Inp1.GetBgn();
				T * ptr_Inp2 = ptrItr_Inp2.GetBgn();
				T * ptr_Out = ptrItr_Out.GetBgn();

				ElementOperations2::Subtract<T>(*ptr_Inp1, *ptr_Inp2, ptr_Out);
			}
		
			AssertLineUndefinedOrValid(a_outAcc);
		}

		template<class T>
		void DivideLineByNum(const VirtArrayAccessor_1D<T> & a_inpAcc, const VirtArrayAccessor_1D<T> & a_outAcc, const float a_num)
		{
			AssertLineUndefinedOrValid(a_inpAcc);


			Ncpp_ASSERT(a_inpAcc.GetSize() == a_outAcc.GetSize());


			PtrIterator2<T> ptrItr_Inp = a_inpAcc.GenPtrIterator();
			PtrIterator2<T> ptrItr_Out = a_outAcc.GenPtrIterator();


			// manage undefined from bgn.
			for (; ptrItr_Inp.HasValidPos(); ptrItr_Inp.MoveBgn(), ptrItr_Out.MoveBgn())
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
			for (; ptrItr_Inp.HasValidPos(); ptrItr_Inp.MoveEnd(), ptrItr_Out.MoveEnd())
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
			for (; ptrItr_Inp.HasValidPos(); ptrItr_Inp.MoveBgn(), ptrItr_Out.MoveBgn(), cnt++)
			{
				T * ptr_Inp = ptrItr_Inp.GetBgn();
				T * ptr_Out = ptrItr_Out.GetBgn();

				ElementOperations2::DivideByNum<T>(*ptr_Inp, a_num, ptr_Out);
			}

			AssertLineUndefinedOrValid(a_outAcc);
		}

		template<class T>
		void MultiplyLineByNum(const VirtArrayAccessor_1D<T> & a_inpAcc, const VirtArrayAccessor_1D<T> & a_outAcc, const float a_num)
		{
			AssertLineUndefinedOrValid(a_inpAcc);

			Ncpp_ASSERT(a_inpAcc.GetSize() == a_outAcc.GetSize());


			PtrIterator2<T> ptrItr_Inp = a_inpAcc.GenPtrIterator();
			PtrIterator2<T> ptrItr_Out = a_outAcc.GenPtrIterator();


			// manage undefined from bgn.
			for (; ptrItr_Inp.HasValidPos(); ptrItr_Inp.MoveBgn(), ptrItr_Out.MoveBgn())
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
			for (; ptrItr_Inp.HasValidPos(); ptrItr_Inp.MoveEnd(), ptrItr_Out.MoveEnd())
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
			for (; ptrItr_Inp.HasValidPos(); ptrItr_Inp.MoveBgn(), ptrItr_Out.MoveBgn())
			{
				T * ptr_Inp = ptrItr_Inp.GetBgn();
				T * ptr_Out = ptrItr_Out.GetBgn();

				ElementOperations2::MultiplyByNum<T>(*ptr_Inp, a_num, ptr_Out);
			}
		
			AssertLineUndefinedOrValid(a_outAcc);
		}


		template<class T>
		void CopyLine(const VirtArrayAccessor_1D<T> & a_destAcc, const VirtArrayAccessor_1D<T> & a_srcAcc)
		{
			AssertLineUndefinedOrValid(a_srcAcc);

			Ncpp_ASSERT(a_srcAcc.GetSize() == a_destAcc.GetSize());

			PtrIterator2<T> ptrItr_Src = a_srcAcc.GenPtrIterator();
			PtrIterator2<T> ptrItr_Dest = a_destAcc.GenPtrIterator();


			// manage undefined from bgn.
			for (; ptrItr_Src.HasValidPos(); ptrItr_Src.MoveBgn(), ptrItr_Dest.MoveBgn())
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
			for (; ptrItr_Src.HasValidPos(); ptrItr_Src.MoveEnd(), ptrItr_Dest.MoveEnd())
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
			for (; ptrItr_Src.HasValidPos(); ptrItr_Src.MoveBgn(), ptrItr_Dest.MoveBgn())
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


			if (a_shift > 0)
			{
				for (int i = 0; ptrItr_Dest.HasValidPos() && i < a_shift; 
					ptrItr_Src.MoveEnd(), ptrItr_Dest.MoveBgn(), i++)
				{
					T * ptr_Dest = ptrItr_Dest.GetBgn();
					SetToUndefined(ptr_Dest);
				}
			}
			else if (a_shift < 0)
			{
				for (int i = 0; ptrItr_Src.HasValidPos() && ptrItr_Dest.HasValidPos() && i > a_shift; 
					ptrItr_Src.MoveBgn(), ptrItr_Dest.MoveEnd(), i--)
				{
					T * ptr_Dest = ptrItr_Dest.GetEnd();
					SetToUndefined(ptr_Dest);
				}
			}

			/////////////////

			// manage undefined from bgn.
			for (; ptrItr_Src.HasValidPos(); ptrItr_Src.MoveBgn(), ptrItr_Dest.MoveBgn())
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
			for (; ptrItr_Src.HasValidPos(); ptrItr_Src.MoveEnd(), ptrItr_Dest.MoveEnd())
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
			for (; ptrItr_Src.HasValidPos(); ptrItr_Src.MoveBgn(), ptrItr_Dest.MoveBgn())
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
			for (; ptrItr_Inp.HasValidPos(); ptrItr_Inp.MoveBgn(), ptrItr_Out.MoveBgn())
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
			for (; ptrItr_Inp.HasValidPos(); ptrItr_Inp.MoveEnd(), ptrItr_Out.MoveEnd())
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
			for (; ptrItr_Inp.HasValidPos(); ptrItr_Inp.MoveBgn(), ptrItr_Out.MoveBgn())
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
			for (; ptrItr_Inp.HasValidPos(); ptrItr_Inp.MoveBgn(), ptrItr_Out.MoveBgn())
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
			for (; ptrItr_Inp.HasValidPos(); ptrItr_Inp.MoveEnd(), ptrItr_Out.MoveEnd())
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
			for (; ptrItr_Inp.HasValidPos(); ptrItr_Inp.MoveBgn(), ptrItr_Out.MoveBgn())
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
			for (; ptrItr_Inp.HasValidPos(); ptrItr_Inp.MoveBgn(), ptrItr_Out.MoveBgn())
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
			for (; ptrItr_Inp.HasValidPos(); ptrItr_Inp.MoveEnd(), ptrItr_Out.MoveEnd())
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
			for (; ptrItr_Inp.HasValidPos(); ptrItr_Inp.MoveBgn(), ptrItr_Out.MoveBgn())
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
			for (; ptrItr_Avg.HasValidPos(); ptrItr_Avg.MoveBgn(), ptrItr_Avg_MagSqr.MoveBgn(), ptrItr_Out.MoveBgn(), cnt_undefined_Bgn++)
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
			for (; ptrItr_Avg.HasValidPos(); ptrItr_Avg.MoveEnd(), ptrItr_Avg_MagSqr.MoveEnd(), ptrItr_Out.MoveEnd(), cnt_undefined_End++)
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
			for (; ptrItr_Avg.HasValidPos();
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
				pOut->IsConfirmed = false;

				////	for debug.
				//if (pOut->Exists)
				//{
				//	i = i;
				//}

				//if (pOut->Exists)
				{
					// to be revised.
					//pOut->pSide_1 = &avg_1;

					pOut->Offset_Side_1 = &avg_1 - a_avg_Acc.GetActualData();
					Ncpp_ASSERT(pOut->Offset_Side_1 >= 0);

					pOut->Offset_Side_2 = &avg_2 - a_avg_Acc.GetActualData();
					Ncpp_ASSERT(pOut->Offset_Side_2 >= 0);
				}
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
		void CalcConflictLine2(const VirtArrayAccessor_1D<T> & a_avg_Acc, const VirtArrayAccessor_1D<float> & a_avg_MagSqr_Acc,
			const VirtArrayAccessor_1D<float> & a_normStandev_Acc, const VirtArrayAccessor_1D<ConflictInfo2> & a_outAcc, const Range<int> & a_range)
		{
			Ncpp_ASSERT(a_avg_Acc.GetSize() == a_avg_MagSqr_Acc.GetSize());
			Ncpp_ASSERT(a_avg_Acc.GetSize() == a_normStandev_Acc.GetSize());
			Ncpp_ASSERT(a_avg_Acc.GetSize() == a_outAcc.GetSize());

			AssertLineUndefinedOrValid(a_avg_Acc);
			AssertLineUndefinedOrValid(a_avg_MagSqr_Acc);
			AssertLineUndefinedOrValid(a_normStandev_Acc);

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
				const float & normStandevVal = a_normStandev_Acc[start];

				if (IsUndefined(avgVal) || IsUndefined(avgMagSqrVal) || IsUndefined(normStandevVal))
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
				const float & normStandevVal = a_normStandev_Acc[end];

				if (IsUndefined(avgVal) || IsUndefined(avgMagSqrVal) || IsUndefined(normStandevVal))
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
				float normStandev_1 = a_normStandev_Acc[i - nBefDiff];

				const T & avg_2 = a_avg_Acc[i + nAftDiff];
				//float avg_MagSqr_2 = sac_Avg_MagSqr[i + nAftDiff];
				float avg_MagSqr_2 = a_avg_MagSqr_Acc[i + nAftDiff];
				float normStandev_2 = a_normStandev_Acc[i + nAftDiff];

				float normStandev_c = a_normStandev_Acc[i];


				pOut->Exists = ElementOperations2::CalcConflict2(avg_1, avg_MagSqr_1, normStandev_1,
					avg_2, avg_MagSqr_2, normStandev_2, normStandev_c);
				//pOut->IsConfirmed = false;
				pOut->IsConfirmed = pOut->Exists;

				////	for debug.
				//if (pOut->Exists)
				//{
				//	i = i;
				//}

				//if (pOut->Exists)
				{
					// to be revised.
					//pOut->pSide_1 = &avg_1;

					pOut->Offset_Side_1 = &avg_1 - a_avg_Acc.GetActualData();
					Ncpp_ASSERT(pOut->Offset_Side_1 >= 0);

					pOut->Offset_Side_2 = &avg_2 - a_avg_Acc.GetActualData();
					Ncpp_ASSERT(pOut->Offset_Side_2 >= 0);
				}
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
		//void CalcThinConflictLine(const VirtArrayAccessor_1D<T> & a_avg_Acc, const VirtArrayAccessor_1D<float> & a_avg_MagSqr_Acc,
		//	const VirtArrayAccessor_1D<float> & a_normStandev_Acc, const VirtArrayAccessor_1D<ConflictInfo2> & a_outAcc, const Range<int> & a_range)
		void CalcThinConflictLine(const VirtArrayAccessor_1D<T> & a_avg_Acc, const VirtArrayAccessor_1D<float> & a_avg_MagSqr_Acc,
			const VirtArrayAccessor_1D<T> & a_avg_Center_Acc, const VirtArrayAccessor_1D<float> & a_avg_MagSqr_Center_Acc,
			const VirtArrayAccessor_1D<float> & a_normStandev_Acc, const VirtArrayAccessor_1D<ConflictInfo2> & a_outAcc, const Range<int> & a_range)
		{
			Ncpp_ASSERT(a_avg_Acc.GetSize() == a_avg_MagSqr_Acc.GetSize());
			Ncpp_ASSERT(a_avg_Acc.GetSize() == a_normStandev_Acc.GetSize());
			Ncpp_ASSERT(a_avg_Acc.GetSize() == a_outAcc.GetSize());
			Ncpp_ASSERT(a_avg_Acc.GetSize() == a_avg_Center_Acc.GetSize());
			Ncpp_ASSERT(a_avg_Acc.GetSize() == a_avg_MagSqr_Center_Acc.GetSize());


			AssertLineUndefinedOrValid(a_avg_Acc);
			AssertLineUndefinedOrValid(a_avg_MagSqr_Acc);
			AssertLineUndefinedOrValid(a_avg_Center_Acc);
			AssertLineUndefinedOrValid(a_avg_MagSqr_Center_Acc);
			AssertLineUndefinedOrValid(a_normStandev_Acc);
			
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
				const T & avgCenterVal = a_avg_Center_Acc[start];
				const float & avgMagSqrCenterVal = a_avg_MagSqr_Center_Acc[start];
				const float & normStandevVal = a_normStandev_Acc[start];

				if (IsUndefined(avgVal) || IsUndefined(avgMagSqrVal) || 
					IsUndefined(avgCenterVal) || IsUndefined(avgMagSqrCenterVal) || IsUndefined(normStandevVal))
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
				const T & avgCenterVal = a_avg_Center_Acc[end];
				const float & avgMagSqrCenterVal = a_avg_MagSqr_Center_Acc[end];
				const float & normStandevVal = a_normStandev_Acc[end];
				
				if (IsUndefined(avgVal) || IsUndefined(avgMagSqrVal) || 
					IsUndefined(avgCenterVal) || IsUndefined(avgMagSqrCenterVal) || IsUndefined(normStandevVal))
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
				float avg_MagSqr_1 = a_avg_MagSqr_Acc[i - nBefDiff];
				float normStandev_1 = a_normStandev_Acc[i - nBefDiff];
				
				const T & avg_2 = a_avg_Acc[i + nAftDiff];
				float avg_MagSqr_2 = a_avg_MagSqr_Acc[i + nAftDiff];
				float normStandev_2 = a_normStandev_Acc[i + nAftDiff];
			
				const T & avg_c = a_avg_Center_Acc[i];
				float avg_MagSqr_c = a_avg_MagSqr_Center_Acc[i];
				float normStandev_c = a_normStandev_Acc[i];


				pOut->Exists = ElementOperations2::CalcThinConflict(avg_1, avg_MagSqr_1, normStandev_1, 
					avg_2, avg_MagSqr_2, normStandev_2,
					avg_c, avg_MagSqr_c, normStandev_c
					);
				//pOut->IsConfirmed = false;
				pOut->IsConfirmed = pOut->Exists;

				////	for debug.
				//if (pOut->Exists)
				//{
				//	i = i;
				//}

				//if (pOut->Exists)
				{
					// to be revised.
					//pOut->pSide_1 = &avg_1;

					pOut->Offset_Side_1 = &avg_1 - a_avg_Acc.GetActualData();
					Ncpp_ASSERT(pOut->Offset_Side_1 >= 0);

					pOut->Offset_Side_2 = &avg_2 - a_avg_Acc.GetActualData();
					Ncpp_ASSERT(pOut->Offset_Side_2 >= 0);
				}
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
		void CalcHighPassEdgeLine_Core(const VirtArrayAccessor_1D<T> & a_inpAcc,
			const VirtArrayAccessor_1D<T> & a_withAvgDiffAcc,
			const VirtArrayAccessor_1D<float> & a_standevBefAcc,
			const VirtArrayAccessor_1D<T> & a_outAcc)
		{
			Ncpp_ASSERT(a_inpAcc.GetSize() == a_withAvgDiffAcc.GetSize());
			Ncpp_ASSERT(a_inpAcc.GetSize() == a_standevBefAcc.GetSize());
			Ncpp_ASSERT(a_inpAcc.GetSize() == a_outAcc.GetSize());

			AssertLineUndefinedOrValid(a_inpAcc);
			AssertLineUndefinedOrValid(a_withAvgDiffAcc);
			AssertLineUndefinedOrValid(a_standevBefAcc);


			PtrIterator2<T> ptrItr_Inp = a_inpAcc.GenPtrIterator();
			PtrIterator2<T> ptrItr_WithAvgDiff = a_withAvgDiffAcc.GenPtrIterator();
			PtrIterator2<float> ptrItr_StandevBef = a_standevBefAcc.GenPtrIterator();
			PtrIterator2<T> ptrItr_Out = a_outAcc.GenPtrIterator();


			// manage undefined from bgn.
			for (; ptrItr_Inp.HasValidPos(); ptrItr_Inp.MoveBgn(), ptrItr_WithAvgDiff.MoveBgn(), ptrItr_StandevBef.MoveBgn(), ptrItr_Out.MoveBgn())
			{
				T * ptr_Inp = ptrItr_Inp.GetBgn();
				T * ptr_WithAvgDiff = ptrItr_WithAvgDiff.GetBgn();
				float * ptr_StandevBef = ptrItr_StandevBef.GetBgn();
				T * ptr_Out = ptrItr_Out.GetBgn();

				if (IsUndefined(*ptr_Inp) || IsUndefined(*ptr_WithAvgDiff) || IsUndefined(*ptr_StandevBef))
				{
					SetToUndefined(ptr_Out);
				}
				else
				{
					break;
				}
			}

			// manage undefined from end.
			for (; ptrItr_Inp.HasValidPos(); ptrItr_Inp.MoveEnd(), ptrItr_WithAvgDiff.MoveEnd(), ptrItr_StandevBef.MoveEnd(), ptrItr_Out.MoveEnd())
			{
				T * ptr_Inp = ptrItr_Inp.GetEnd();
				T * ptr_WithAvgDiff = ptrItr_WithAvgDiff.GetEnd();
				float * ptr_StandevBef = ptrItr_StandevBef.GetEnd();
				T * ptr_Out = ptrItr_Out.GetEnd();

				if (IsUndefined(*ptr_Inp) || IsUndefined(*ptr_WithAvgDiff) || IsUndefined(*ptr_StandevBef))
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
			for (; ptrItr_Inp.HasValidPos(); ptrItr_Inp.MoveBgn(), ptrItr_WithAvgDiff.MoveBgn(), ptrItr_StandevBef.MoveBgn(), ptrItr_Out.MoveBgn(), cnt++)
			//for (; ptrItr_Inp1.HasValidPos(); ptrItr_Inp1.MoveBgn(), ptrItr_Inp2.MoveBgn(), ptrItr_Out.MoveBgn(), cnt++)
			{
				//T * ptr_Inp = ptrItr_Inp.GetBgn();
				//T * ptr_WithAvgDiff = ptrItr_WithAvgDiff.GetBgn();
				//float * ptr_StandevBef = ptrItr_StandevBef.GetBgn();
				//T * ptr_Out = ptrItr_Out.GetBgn();

				T & rInp = *ptrItr_Inp.GetBgn();
				T & rWithAvgDiff = *ptrItr_WithAvgDiff.GetBgn();
				float & rStandevBef = *ptrItr_StandevBef.GetBgn();
				T & rOut = *ptrItr_Out.GetBgn();

				float withAvgDiffMag = CalcMag(rWithAvgDiff);

				//if (withAvgDiffMag * 2 > 0.8 * rStandevBef && rStandevBef > 20)
				if (fabs(withAvgDiffMag) * 2 > 0.8 * rStandevBef && rStandevBef > 20)
				{
					Assign(&rOut, rInp);
				}
				else
				{
					//SetToZero(&rOut);
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
		//void CalcHighPassEdgeLine_Core2(const VirtArrayAccessor_1D<T> & a_avg_Acc, const VirtArrayAccessor_1D<float> & a_avg_MagSqr_Acc,
			//const VirtArrayAccessor_1D<float> & a_outAcc, const Range<int> & a_range)
		void CalcHighPassEdgeLine_Core2(const VirtArrayAccessor_1D<T> & a_inpAcc,
			const VirtArrayAccessor_1D<float> & a_withAvgDiffMagAcc,
			const VirtArrayAccessor_1D<float> & a_shiftDiffMagAcc,
			const VirtArrayAccessor_1D<T> & a_outAcc, const int a_shift)
		{
			//const Range<int> a_range = Range<int>::New(-a_shift, 0);

			Ncpp_ASSERT(a_inpAcc.GetSize() == a_withAvgDiffMagAcc.GetSize());
			Ncpp_ASSERT(a_inpAcc.GetSize() == a_shiftDiffMagAcc.GetSize());
			Ncpp_ASSERT(a_inpAcc.GetSize() == a_outAcc.GetSize());

			AssertLineUndefinedOrValid(a_inpAcc);
			AssertLineUndefinedOrValid(a_withAvgDiffMagAcc);
			AssertLineUndefinedOrValid(a_shiftDiffMagAcc);


			const int nSize_1D = a_outAcc.GetSize();

			//const int nBefDiff = -a_range.GetBgn();
			//const int nAftDiff = a_range.GetEnd();

			//const int nRangeLen = nBefDiff + 1 + nAftDiff;
			//const int nRangeLen = a_shift + 1;


			//--------------



			int start = 0;
			for (; start < nSize_1D; start++)
			{
				const T & inpVal = a_inpAcc[start];
				const float & withAvgDiffMag = a_withAvgDiffMagAcc[start];
				const float & shiftDiffMag = a_shiftDiffMagAcc[start];

				if (IsUndefined(inpVal) || IsUndefined(withAvgDiffMag) || IsUndefined(shiftDiffMag))
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
				const float & withAvgDiffMag = a_withAvgDiffMagAcc[end];
				const float & shiftDiffMag = a_shiftDiffMagAcc[end];

				if (IsUndefined(inpVal) || IsUndefined(withAvgDiffMag) || IsUndefined(shiftDiffMag))
				{
					continue;
				}
				else
				{
					break;
				}
			}


			//------

			////if (end + 1 - start < nRangeLen)
			//if (end + 1 - start < a_shift + 1)
			//{
			//	SetLineToUndefined(a_outAcc);
			//	return;
			//}





			////const int nCenterEnd = nSize_1D - 1 - nAftDiff;
			//const int nCenterEnd = end - nAftDiff;


			//--------------


			//for (int i = start; i < start + a_shift; i++)
			for (int i = start - a_shift; i < start; i++)
			{
				//SetToZero(&a_outAcc[i]);
			}

			//for (int i = start + nBefDiff; i <= nCenterEnd; i++)
			for (int i = start; i <= end; i++)
			{
				//float * pOut = &a_outAcc[i];
				//float * pOut = (float *)&a_outAcc[i];

				T & rOutC = a_outAcc[i];
				T & rOutP = a_outAcc[i - a_shift];
				
				const T & rInpC = a_inpAcc[i];
				float withAvgDiffMagC = a_withAvgDiffMagAcc[i];
				
				float shiftDiffMag = a_shiftDiffMagAcc[i];

				const T & rInpP = a_inpAcc[i - a_shift];
				AssertValue(rInpP);
				
				float withAvgDiffMagP = a_withAvgDiffMagAcc[i - a_shift];
				AssertValue(withAvgDiffMagP);

				if (shiftDiffMag > withAvgDiffMagC && shiftDiffMag > withAvgDiffMagP)
				{
					Assign(&rOutC, rInpC);
					Assign(&rOutP, rInpP);
				}
				else
				{
					//SetToZero(&rOutC);
				}

			}

			///////////////////////////////

			//	Fill bgn gap in output
			{
				//for (int i = 0; i < start + nBefDiff; i++)
				for (int i = 0; i < start - a_shift; i++)
				{
					T * pDest = (T *)&a_outAcc[i];
					SetToUndefined(pDest);
				}
			}

			//	Fill end gap in output
			{
				//for (int i = end - nAftDiff + 1; i < nSize_1D; i++)
				for (int i = end + 1; i < nSize_1D; i++)
				{
					T * pDest = (T *)&a_outAcc[i];
					SetToUndefined(pDest);
				}
			}


			AssertLineUndefinedOrValid(a_outAcc);
		}


		template<class T>
		void CalcDiffLine(const VirtArrayAccessor_1D<T> & a_inpAcc,
			const VirtArrayAccessor_1D<T> & a_outAcc, const Range<int> & a_range)
		{
			Ncpp_ASSERT(a_inpAcc.GetSize() == a_outAcc.GetSize());

			AssertLineUndefinedOrValid(a_inpAcc);

			const int nSize_1D = a_outAcc.GetSize();

			const int nBefDiff = -a_range.GetBgn();
			const int nAftDiff = a_range.GetEnd();

			const int nRangeLen = nBefDiff + 1 + nAftDiff;


			//--------------



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

			//const int nCenterEnd = nSize_1D - 1 - nAftDiff;
			const int nCenterEnd = end - nAftDiff;


			//--------------



			for (int i = start + nBefDiff; i <= nCenterEnd; i++)
			{
				T * pOut = (T *)&a_outAcc[i];

				const T & inp_1 = a_inpAcc[i - nBefDiff];

				const T & inp_2 = a_inpAcc[i + nAftDiff];

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

		template<class T = void>
		void CalcConflictLine_FromDiffMagImages(const VirtArrayAccessor_1D<float> & a_diffMag1_1_Acc, 
			const VirtArrayAccessor_1D<float> & a_diffMag1_2_Acc, const VirtArrayAccessor_1D<float> & a_diffMag2_Acc,
			const VirtArrayAccessor_1D<ConflictInfo2> & a_outAcc, const int a_posDist1_1)
		{

			Ncpp_ASSERT(a_diffMag1_1_Acc.GetSize() == a_diffMag1_2_Acc.GetSize());
			Ncpp_ASSERT(a_diffMag1_1_Acc.GetSize() == a_diffMag2_Acc.GetSize());
			Ncpp_ASSERT(a_diffMag1_1_Acc.GetSize() == a_outAcc.GetSize());

			AssertLineUndefinedOrValid(a_diffMag1_1_Acc);
			AssertLineUndefinedOrValid(a_diffMag1_2_Acc);
			AssertLineUndefinedOrValid(a_diffMag2_Acc);


			const int nSize_1D = a_outAcc.GetSize();

			//--------------



			int start = 0;
			//for (; start < nSize_1D; start++)
			for (; start < nSize_1D - a_posDist1_1; start++)
			{
				//const float & diffMag1_1_Val = a_diffMag1_1_Acc[start];
				//const float & diffMag1_2_Val = a_diffMag1_2_Acc[start];
				const float & diffMag2_Val = a_diffMag2_Acc[start];

				//const float & diffMag1_2_Val = a_diffMag1_2_Acc[start + a_posDist1_1];

				if (IsUndefined(diffMag2_Val))
				{
					continue;
				}
				else
				{
					break;
				}
			}

			//const int aftStart = start + 4 * a_posDist1_1 - 1;
			//const int aftStart = start + a_posDist1_1;

			//int end = nSize_1D - 1;
			int end = nSize_1D - 1 - a_posDist1_1;
			Ncpp_ASSERT(end > 0);
			for (; end >= start; end--)
			{
				//const float & diffMag1_1_Val = a_diffMag1_1_Acc[end];
				//const float & diffMag1_2_Val = a_diffMag1_2_Acc[end];
				//const float & diffMag2_Val = a_diffMag2_Acc[end];

				//const float & diffMag1_2_Val = a_diffMag1_2_Acc[end + a_posDist1_1];
				const float & diffMag2_Val = a_diffMag2_Acc[end + a_posDist1_1];

				if (IsUndefined(diffMag2_Val))
				//if (IsUndefined(diffMag1_2_Val))
				{
					continue;
				}
				else
				{
					break;
				}
			}



			//for (int i = start + nBefDiff; i <= nCenterEnd; i++)
			//for (int i = start; i <= end; i++)
			for (int i = start; i <= end; i++)
			{
				const float & rDiffMag1_1_c = a_diffMag1_1_Acc[i];
				Ncpp_ASSERT(!IsUndefined(rDiffMag1_1_c));
					
				const float & rDiffMag1_1_b = a_diffMag1_1_Acc[i - a_posDist1_1];
				Ncpp_ASSERT(!IsUndefined(rDiffMag1_1_b));

				const float & rDiffMag1_2_d = a_diffMag1_2_Acc[i + a_posDist1_1];

				const float & rDiffMag2_c = a_diffMag2_Acc[i];
				const float & rDiffMag2_d = a_diffMag2_Acc[i + a_posDist1_1];

				Ncpp_ASSERT(!IsUndefined(rDiffMag1_2_d));
				Ncpp_ASSERT(!IsUndefined(rDiffMag2_c));
				Ncpp_ASSERT(!IsUndefined(rDiffMag2_d));


				ConflictInfo2 * pOut = (ConflictInfo2 *)&a_outAcc[i];

				const int minDiff = 20;
				//const int minDiff = 40;
				//const int minDiff = 50;
				pOut->Exists = (
					rDiffMag1_1_c > minDiff &&
					rDiffMag1_2_d > minDiff &&
					rDiffMag1_2_d > 0.75 * rDiffMag1_1_c &&
					rDiffMag2_c > 0.6 * rDiffMag1_1_c &&
					rDiffMag2_d > 0.6 * rDiffMag1_1_c
					);
				
				pOut->IsConfirmed = false;


				// //	for debug.
				// if (pOut->Exists)
				// {
				// 	i = i;
				// }

				//if (pOut->Exists)
				{
					// float & diffMag1_1_Val_Bef = a_diffMag1_1_Acc[i - 2 * a_posDist1_1];
					//Ncpp_ASSERT(diffMag1_1_Val_Bef >= 0);

					pOut->Offset_Side_1 = &a_outAcc[i - 2 * a_posDist1_1] - a_outAcc.GetActualData();
					//pOut->Offset_Side_1 = &diffMag1_1_Val_Bef - a_diffMag1_1_Acc.GetActualData();
					Ncpp_ASSERT(pOut->Offset_Side_1 >= 0);

					// float & diffMag1_1_Val_Aft = a_diffMag1_1_Acc[i + a_posDist1_1];
					// Ncpp_ASSERT(diffMag1_1_Val_Aft >= 0);

					pOut->Offset_Side_2 = &a_outAcc[i + a_posDist1_1] - a_outAcc.GetActualData();
					//pOut->Offset_Side_2 = &diffMag1_1_Val_Aft - a_diffMag1_1_Acc.GetActualData();
					Ncpp_ASSERT(pOut->Offset_Side_2 >= 0);
				}

			}

			///////////////////////////////

			//	Fill bgn gap in output
			{
				//for (int i = 0; i < start + nBefDiff; i++)
				for (int i = 0; i < start; i++)
				{
					ConflictInfo2 * pDest = (ConflictInfo2 *)&a_outAcc[i];
					SetToUndefined(pDest);
				}
			}

			//	Fill end gap in output
			{
				//for (int i = end - nAftDiff + 1; i < nSize_1D; i++)
				for (int i = end + 1; i < nSize_1D; i++)
				{
					ConflictInfo2 * pDest = (ConflictInfo2 *)&a_outAcc[i];
					SetToUndefined(pDest);
				}
			}


			AssertLineUndefinedOrValid(a_outAcc);

		}

		template<class T>
		void CalcConflictLine_FromDiffImages2(const VirtArrayAccessor_1D<T> & a_inp_Acc, 
			const VirtArrayAccessor_1D<T> & a_diff1_Acc, const VirtArrayAccessor_1D<T> & a_diff2_Acc,
			const VirtArrayAccessor_1D<ConflictInfo2> & a_outAcc, const int a_posDist1)
		{

			Ncpp_ASSERT(a_inp_Acc.GetSize() == a_diff1_Acc.GetSize());
			Ncpp_ASSERT(a_inp_Acc.GetSize() == a_diff2_Acc.GetSize());
			Ncpp_ASSERT(a_inp_Acc.GetSize() == a_outAcc.GetSize());

			AssertLineUndefinedOrValid(a_inp_Acc);
			AssertLineUndefinedOrValid(a_diff1_Acc);
			AssertLineUndefinedOrValid(a_diff2_Acc);


			const int nSize_1D = a_outAcc.GetSize();

			//--------------



			int start = 0;
			//for (; start < nSize_1D; start++)
			for (; start < nSize_1D - a_posDist1; start++)
			{
				//const T & diffMag1_Val = a_diff1_Acc[start];
				//const T & inp_Val = a_inp_Acc[start];
				const T & diffMag2_Val = a_diff2_Acc[start];

				//const T & inp_Val = a_inp_Acc[start + a_posDist1];

				if (IsUndefined(diffMag2_Val))
				{
					continue;
				}
				else
				{
					break;
				}
			}

			//const int aftStart = start + 4 * a_posDist1 - 1;
			//const int aftStart = start + a_posDist1;

			//int end = nSize_1D - 1;
			int end = nSize_1D - 1 - a_posDist1;
			Ncpp_ASSERT(end > 0);
			for (; end >= start; end--)
			{
				//const T & diffMag1_Val = a_diff1_Acc[end];
				//const T & inp_Val = a_inp_Acc[end];
				//const T & diffMag2_Val = a_diff2_Acc[end];

				//const T & inp_Val = a_inp_Acc[end + a_posDist1];
				const T & diffMag2_Val = a_diff2_Acc[end + a_posDist1];

				if (IsUndefined(diffMag2_Val))
					//if (IsUndefined(inp_Val))
				{
					continue;
				}
				else
				{
					break;
				}
			}



			//for (int i = start + nBefDiff; i <= nCenterEnd; i++)
			//for (int i = start; i <= end; i++)
			for (int i = start; i <= end; i++)
			{
				const T & rDiff1_c = a_diff1_Acc[i];
				Ncpp_ASSERT(!IsUndefined(rDiff1_c));
				const float diff1Mag_c = CalcMag(rDiff1_c);

				T diff1Uv_c;
				if (diff1Mag_c > 0.1)
				{
					DivideByNum(rDiff1_c, diff1Mag_c, &diff1Uv_c);
				}

				const T & rDiff1_b = a_diff1_Acc[i - a_posDist1];
				Ncpp_ASSERT(!IsUndefined(rDiff1_b));
				const float diff1Mag_b = CalcMag(rDiff1_b);

				const T & rDiff1_d = a_diff1_Acc[i + a_posDist1];
				Ncpp_ASSERT(!IsUndefined(rDiff1_d));
				const float diff1Mag_d = CalcMag(rDiff1_d);

				//--


				T diff1Uv_b;
				T uvDiff_bc;
				float uvDiffMag_bc;
				if (diff1Mag_b > 0.1 && diff1Mag_c > 0.1)
				{
					DivideByNum(rDiff1_b, diff1Mag_b, &diff1Uv_b);

					Subtract(diff1Uv_c, diff1Uv_b, &uvDiff_bc);
					uvDiffMag_bc = CalcMag(uvDiff_bc);
				}

				T diff1Uv_d;
				T uvDiff_cd;
				float uvDiffMag_cd;
				if (diff1Mag_d > 0.1 && diff1Mag_c > 0.1)
				{
					DivideByNum(rDiff1_d, diff1Mag_d, &diff1Uv_d);

					Subtract(diff1Uv_d, diff1Uv_c, &uvDiff_cd);
					uvDiffMag_cd = CalcMag(uvDiff_cd);
				}

				//T diff1_Sum_cb;
				//Add(rDiff1_c, rDiff1_b, &diff1_Sum_cb);
				//const float diff1_SumMag_cb = CalcMag(diff1_Sum_cb);

				//const T & rInp_d = a_inp_Acc[i + a_posDist1];

				//const T & rDiff2_c = a_diff2_Acc[i];
				//const T & rDiff2_d = a_diff2_Acc[i + a_posDist1];

				////Ncpp_ASSERT(!IsUndefined(rInp_d));
				//Ncpp_ASSERT(!IsUndefined(rDiff2_c));
				//Ncpp_ASSERT(!IsUndefined(rDiff2_d));

				//const float & diffMag2_c = CalcMag(rDiff2_c);
				//const float & diffMag2_d = CalcMag(rDiff2_d);

				ConflictInfo2 * pOut = (ConflictInfo2 *)&a_outAcc[i];

				if (288212 == pOut->Index)
				{
					i = i;
				}

				const int minDiff = 20;
				//const int minDiff = 30;
				//const int minDiff = 40;
				//const int minDiff = 50;
				pOut->Exists = (
					diff1Mag_c > minDiff &&
					
					(diff1Mag_b < diff1Mag_c * 0.3 ||
					uvDiffMag_bc > 0.5)
					//uvDiffMag_bc > 0.8)
					
					&&
					
					(diff1Mag_d < diff1Mag_c * 0.3 ||
					uvDiffMag_cd > 0.5)
					//uvDiffMag_cd > 0.8)
					
					//rInp_d > minDiff &&
					//rInp_d > 0.75 * diff1Mag_c &&
					
					//diffMag2_c > 0.6 * diff1Mag_c &&
					//diffMag2_d > 0.6 * diff1Mag_c
					);

				//pOut->IsConfirmed = false;
				pOut->IsConfirmed = pOut->Exists;


				// //	for debug.
				// if (pOut->Exists)
				// {
				// 	i = i;
				// }

				//if (pOut->Exists)
				{
					// T & diffMag1_Val_Bef = a_diff1_Acc[i - 2 * a_posDist1];
					//Ncpp_ASSERT(diffMag1_Val_Bef >= 0);

					pOut->Offset_Side_1 = &a_outAcc[i - 2 * a_posDist1] - a_outAcc.GetActualData();
					//pOut->Offset_Side_1 = &diffMag1_Val_Bef - a_diff1_Acc.GetActualData();
					Ncpp_ASSERT(pOut->Offset_Side_1 >= 0);

					// T & diffMag1_Val_Aft = a_diff1_Acc[i + a_posDist1];
					// Ncpp_ASSERT(diffMag1_Val_Aft >= 0);

					pOut->Offset_Side_2 = &a_outAcc[i + a_posDist1] - a_outAcc.GetActualData();
					//pOut->Offset_Side_2 = &diffMag1_Val_Aft - a_diff1_Acc.GetActualData();
					Ncpp_ASSERT(pOut->Offset_Side_2 >= 0);
				}

			}

			///////////////////////////////

			//	Fill bgn gap in output
			{
				//for (int i = 0; i < start + nBefDiff; i++)
				for (int i = 0; i < start; i++)
				{
					ConflictInfo2 * pDest = (ConflictInfo2 *)&a_outAcc[i];
					SetToUndefined(pDest);
				}
			}

			//	Fill end gap in output
			{
				//for (int i = end - nAftDiff + 1; i < nSize_1D; i++)
				for (int i = end + 1; i < nSize_1D; i++)
				{
					ConflictInfo2 * pDest = (ConflictInfo2 *)&a_outAcc[i];
					SetToUndefined(pDest);
				}
			}


			AssertLineUndefinedOrValid(a_outAcc);

		}


	};
}