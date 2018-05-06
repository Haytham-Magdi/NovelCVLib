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


	template<class T_ImgElm, class T_AccElm, int const V_NofChannels>
	class ImageArrayHolder : public ArrayHolder_2D<T_AccElm>
	{
	public:

		ImageArrayHolder(ImageRef<T_ImgElm> a_srcImg)
		{
			Ncpp_ASSERT(a_srcImg->GetNofChannels() == V_NofChannels);

			m_srcImg = a_srcImg;

			////const Size_2D size11 = size_2D(a_srcImg->GetSize());
			//const Size_2D size11 = size_2D((const CvSize &)a_srcImg->GetSize());
			
			
			//const Size_2D size11 = Ncv::OpenCV_Util::size_2D(a_srcImg->GetSize());
			//const Size_2D size11 = size_2D(cvSize(400, 300));

			m_actualAccessor.Init((T_AccElm *)a_srcImg->GetDataPtr(), size_2D(a_srcImg->GetSize()));
			//m_actualAccessor.Init((T_AccElm *)a_srcImg->GetDataPtr(), size11);
			m_actualAccessor.AssignVirtAccessorTo(&m_virtAccessor);
		}

		ImageArrayHolder(const Size_2D & a_size)
		{
			m_srcImg = Image<T_ImgElm>::Create(toCvSize(a_size), V_NofChannels);

			m_actualAccessor.Init((T_AccElm *)m_srcImg->GetDataPtr(), size_2D(m_srcImg->GetSize()));
			//m_actualAccessor.Init((T_AccElm *)m_srcImg->GetDataPtr(), a_size);
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

		ImageArrayHolderRef<T_ImgElm, T_AccElm, V_NofChannels> CreateProxy()
		{
			ImageArrayHolderRef<T_ImgElm, T_AccElm, V_NofChannels> ret = 
				new ImageArrayHolder<T_ImgElm, T_AccElm, V_NofChannels>(m_srcImg);

			return ret;
		}

		ImageArrayHolderRef<T_ImgElm, T_AccElm, V_NofChannels> CreateTransposedProxy()
		{
			ImageArrayHolderRef<T_ImgElm, T_AccElm, V_NofChannels> ret = this->CreateProxy();
			ret->TransposeVirtAccessor();

			return ret;
		}

	protected:

		ImageRef<T_ImgElm> m_srcImg;
	};



}