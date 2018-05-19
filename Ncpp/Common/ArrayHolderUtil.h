#pragma once

#include <NovelCVLib\Ncpp\Common\VirtArrayAccessor_1D.h>
#include <NovelCVLib\Ncpp\Common\ActualArrayAccessor_1D.h>
#include <NovelCVLib\Ncpp\Common\ArrayHolder_1D.h>
#include <NovelCVLib\Ncpp\Common\SimpleArrayHolder_1D.h>
#include <NovelCVLib\Ncpp\Common\ArrayHolderProxy_1D.h>
#include <NovelCVLib\Ncpp\Common\VirtArrayAccessor_2D.h>
#include <NovelCVLib\Ncpp\Common\ActualArrayAccessor_2D.h>
#include <NovelCVLib\Ncpp\Common\ArrayHolder_2D.h>
#include <NovelCVLib\Ncpp\Common\SimpleArrayHolder_2D.h>
#include <NovelCVLib\Ncpp\Common\ArrayHolderProxy_2D.h>



namespace Ncv
{
	using namespace Ncpp;

	//template<class T>
	//class ArrayHolderUtil;


	//template<class T>
	//class ArrayHolderUtil : public Ncpp::Object
	//{
	//public:

	namespace ArrayHolderUtil
	{
		//using namespace Ncv;

		//static ArrayHolder_2D_Ref<T> CreateFrom(const Size_2D & a_size)
		template<class T>
		ArrayHolder_2D_Ref<T> CreateFrom(const Size_2D & a_size)
		{
			ArrayHolder_2D_Ref<T> ret = new SimpleArrayHolder_2D<T>(a_size);
			return ret;
		}

		template<class T, class Y>
		ArrayHolder_2D_Ref<T> CreateEmptyFrom(ArrayHolder_2D_Ref<Y> a_src)
		{
			const ActualArrayAccessor_2D<Y> & srcActualAcc = a_src->GetActualAccessor();
			const VirtArrayAccessor_2D<Y> & srcVirtAcc = a_src->GetVirtAccessor();

			const int headerDif = srcVirtAcc.GetData() - srcActualAcc.GetData();

			ArrayHolder_2D_Ref<T> ret = new SimpleArrayHolder_2D<T>(srcActualAcc.GetSize());
			//VirtArrayAccessor_2D<Y> * pRetVirtAcc = (VirtArrayAccessor_2D<Y> *)&ret->GetVirtAccessor();
			VirtArrayAccessor_2D<T> * pRetVirtAcc = (VirtArrayAccessor_2D<T> *)&ret->GetVirtAccessor();
			//VirtArrayAccessor_2D<Y> & pRetVirtAcc = ret->GetVirtAccessor();

			pRetVirtAcc->Init(pRetVirtAcc->GetData() + headerDif,
				//pRetVirtAcc.Init(pRetVirtAcc.GetData() + headerDif,
				srcVirtAcc.GetSize_X(), srcVirtAcc.GetStepSize_X(),
				srcVirtAcc.GetSize_Y(), srcVirtAcc.GetStepSize_Y());

			return ret;
		}

		////static ArrayHolder_2D_Ref<T> CreateWithoutDataFrom(ArrayHolder_2D_Ref<T> a_src)
		//template<class T>
		//ArrayHolder_2D_Ref<T> CreateWithoutDataFrom(ArrayHolder_2D_Ref<T> a_src)
		//{
		//	ArrayHolder_2D_Ref<T> ret = new SimpleArrayHolder_2D(a_src->GetActualAccessor().GetSize());
		//	VirtArrayAccessor_2D & retVirtAcc = ret->GetVirtAccessor();
		//	a_src->GetVirtAccessor().CopyTo(&retVirtAcc);

		//	retVirtAcc.SetData(ret->GetActualAccessor().GetData());

		//	return ret;
		//}

		////static ArrayHolder_2D_Ref<T> CreateCopyFrom(ArrayHolder_2D_Ref<T> a_src)
		//template<class T>
		//ArrayHolder_2D_Ref<T> CreateCopyFrom(ArrayHolder_2D_Ref<T> a_src)
		//{
		//	ArrayHolder_2D_Ref<T> ret = CreateWithoutDataFrom(a_src);

		//	const ActualArrayAccessor_2D & srcActAcc = a_src->GetActualAccessor();
		//	memcpy(ret->GetActualAccessor().GetData(), srcActAcc.GetData(), srcActAcc.CalcSize_1D() * sizeof(T));

		//	return ret;
		//}

		//static ArrayHolder_2D_Ref<T> CreateTransposedProxyFrom(ArrayHolder_2D_Ref<T> a_src)
		template<class T>
		ArrayHolder_2D_Ref<T> CreateTransposedProxyFrom(ArrayHolder_2D_Ref<T> a_src)
		{
			ArrayHolder_2D_Ref<T> ret = new ArrayHolderProxy_2D<T>(a_src);
			
			VirtArrayAccessor_2D<T> * pRetVirtAcc = (VirtArrayAccessor_2D<T> *)&ret->GetVirtAccessor();
			a_src->GetVirtAccessor().AssignTransposeTo(pRetVirtAcc);

			//ret->TransposeVirtAccessor();

			return ret;
		}

	//private:

	//	ArrayHolderUtil() {}

	//protected:

	//};
	}

}