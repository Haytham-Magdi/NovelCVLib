#pragma once

#include <NovelCVLib\Ncpp\Common\commonLib_Misc.h>
#include <NovelCVLib\OpenCV\CvIncludes.h>
//#include <NovelCVLib\OpenCV\Types.h>
//#include <NovelCVLib\OpenCV\error.h>
//#include <NovelCVLib\OpenCV\funcs1.h>
//#include <vector>
#include <NovelCVLib\OpenCV\Image.h>
#include <NovelCVLib\OpenCV\OpenCV_Util.h>

#include <NovelCVLib\Ncpp\Common\ArrayHolder_2D.h>



namespace Ncv
{
	using namespace Ncpp;
	using namespace Ncv::OpenCV_Util;
	

	template<class T_ImgElm, class T_AccElm, int const V_NofChannels>
	class ImageArrayHolder;


//#define ImageArrayHolder_REF(T_ImgElm, T_AccElm, V_NofChannels) ObjRef< ImageArrayHolder< T_ImgElm, T_AccElm, V_NofChannels >>

	template<class T_ImgElm, class T_AccElm, int const V_NofChannels>
	using ImageArrayHolderRef = ObjRef<ImageArrayHolder<T_ImgElm, T_AccElm, V_NofChannels>>;
	//using ImageArrayHolderRef = ObjRef<ImageArrayHolder<T, VectorVal<T, V_NofChannels>, V_NofChannels>>;


	//template<class T>
	template<class T_ImgElm, class T_AccElm, int const V_NofChannels>
	class ImageArrayHolder : public ArrayHolder_2D<T_AccElm>
	{
	public:

		ImageArrayHolder(ImageRef<T_ImgElm> a_srcImg)
		{
			Ncpp_ASSERT(a_srcImg->GetNofChannels() == V_NofChannels);

			//Size_2D size = size_2D(a_srcImg->GetSize());
			//CvSize imgSize = a_srcImg->GetSize();

			m_srcImg = a_srcImg;

			m_actualAccessor.Init((T_AccElm *)a_srcImg->GetDataPtr(), size_2D(a_srcImg->GetSize()));
			//m_actualAccessor.Init((T_AccElm *)a_srcImg->GetDataPtr(), imgSize.width, imgSize.height);
			m_actualAccessor.AssignVirtAccessorTo(&m_virtAccessor);
		}

		ImageRef<T_ImgElm> GetSrcImg()
		{
			return m_srcImg;
		}

		ImageArrayHolderRef<T_ImgElm, T_AccElm, V_NofChannels> CloneWithData()
		{
			ImageArrayHolderRef<T_ImgElm, T_AccElm, V_NofChannels> ret = new ImageArrayHolder<T_ImgElm, T_AccElm, V_NofChannels>(
				m_srcImg->Clone());
			return ret;
		}

		ImageArrayHolderRef<T_ImgElm, T_AccElm, V_NofChannels> CloneEmpty()
		{
			ImageArrayHolderRef<T_ImgElm, T_AccElm, V_NofChannels> ret = new ImageArrayHolder<T_ImgElm, T_AccElm, V_NofChannels>(
				m_srcImg->CloneEmpty());
			return ret;
		}


	protected:

		ImageRef<T_ImgElm> a_srcImg;
	};



	typedef ImageArrayHolder< Float, F32ColorVal, 3 > F32ImageArrayHolder3C;
	typedef ImageArrayHolderRef< Float, F32ColorVal, 3 > F32ImageArrayHolder3C_Ref;

	typedef ImageArrayHolder< Float, float, 1 > F32ImageArrayHolder1C;
	typedef ImageArrayHolderRef< Float, float, 1 > F32ImageArrayHolder1C_Ref;

	typedef ImageArrayHolder< Int32, int, 1 > S32ImageArrayHolder1C;
	typedef ImageArrayHolderRef< Int32, int, 1 > S32ImageArrayHolder1C_Ref;


	template<class T_ImgElm, int const V_NofChannels>
	using VectorValImageArrayHolder = ImageArrayHolder<T_ImgElm, VectorVal<T_ImgElm, V_NofChannels>, V_NofChannels>;

	template<class T_ImgElm, int const V_NofChannels>
	using VectorValImageArrayHolderRef = ObjRef<ImageArrayHolder<T_ImgElm, VectorVal<T_ImgElm, V_NofChannels>, V_NofChannels>>;




	//typedef VectorValImageArrayHolder_Ref = ObjRef< VectorValImageArrayHolder<T, V_NofChannels> >;



	///////////////////////////////////////////////
	///////////////////////////////////////////////

	typedef VectorValImageArrayHolder< Float, 4 > F32VectorValImageArrayHolder_4C;
	typedef ObjRef< F32VectorValImageArrayHolder_4C > F32VectorValImageArrayHolder_4C_Ref;

	typedef VectorValImageArrayHolder< Float, 3 > F32VectorValImageArrayHolder_3C;
	typedef ObjRef< F32VectorValImageArrayHolder_3C > F32VectorValImageArrayHolder_3C_Ref;

	typedef VectorValImageArrayHolder< Float, 1 > F32VectorValImageArrayHolder_1C;
	typedef ObjRef< F32VectorValImageArrayHolder_1C > F32VectorValImageArrayHolder_1C_Ref;

	typedef VectorValImageArrayHolder< Int32, 1 > S32VectorValImageArrayHolder_1C;
	typedef ObjRef< S32VectorValImageArrayHolder_1C > S32VectorValImageArrayHolder_1C_Ref;


}