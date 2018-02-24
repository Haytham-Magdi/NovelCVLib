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

	template<class T>
	class ArrayHolderUtil;


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
			ArrayHolder_2D_Ref<T> ret = new SimpleArrayHolder_2D(a_size);
			return ret;
		}

		//static ArrayHolder_2D_Ref<T> CreateWithoutDataFrom(ArrayHolder_2D_Ref<T> a_src)
		template<class T>
		ArrayHolder_2D_Ref<T> CreateWithoutDataFrom(ArrayHolder_2D_Ref<T> a_src)
		{
			ArrayHolder_2D_Ref<T> ret = new SimpleArrayHolder_2D(a_src->GetActualAccessor().GetSize());
			VirtArrayAccessor_2D & retVirtAcc = ret->GetVirtAccessor();
			a_src->GetVirtAccessor().CopyTo(&retVirtAcc);

			retVirtAcc.SetData(ret->GetActualAccessor());

			return ret;
		}

		//static ArrayHolder_2D_Ref<T> CreateCopyFrom(ArrayHolder_2D_Ref<T> a_src)
		template<class T>
		ArrayHolder_2D_Ref<T> CreateCopyFrom(ArrayHolder_2D_Ref<T> a_src)
		{
			ArrayHolder_2D_Ref<T> ret = CreateWithoutDataFrom(a_src);

			const ActualArrayAccessor_2D & srcActAcc = a_src->GetActualAccessor();
			memcpy(ret->GetActualAccessor().GetData(), srcActAcc.GetData(), srcActAcc.CalcSize_1D() * sizeof(T));

			return ret;
		}

		//static ArrayHolder_2D_Ref<T> CreateTransposedProxyFrom(ArrayHolder_2D_Ref<T> a_src)
		template<class T>
		ArrayHolder_2D_Ref<T> CreateTransposedProxyFrom(ArrayHolder_2D_Ref<T> a_src)
		{
			ArrayHolder_2D_Ref<T> ret = new ArrayHolderProxy_2D(a_src);
			ret->TransposeVirtAccessor();

			return ret;
		}

	//private:

	//	ArrayHolderUtil() {}

	//protected:

	//};
	}

}