#pragma once

#include <NovelCVLib\Ncpp\Common\commonLib_Misc.h>
#include <NovelCVLib\OpenCV\CvIncludes.h>
#include <NovelCVLib\OpenCV\Image.h>
#include <NovelCVLib\OpenCV\OpenCV_Util.h>

#include <NovelCVLib\Ncpp\Common\ArrayHolder_2D.h>



namespace Ncv
{
	using namespace Ncpp;
	using namespace Ncv::OpenCV_Util;
	

	template<class T_ImgElm, class T_AccElm, int const V_NofChannels>
	class ImageArrayHolder;



	template<class T_ImgElm, class T_AccElm, int const V_NofChannels>
	using ImageArrayHolderRef = ObjRef<ImageArrayHolder<T_ImgElm, T_AccElm, V_NofChannels>>;


	template<class T_ImgElm, class T_AccElm, int const V_NofChannels>
	class ImageArrayHolder : public ArrayHolder_2D<T_AccElm>
	{
	public:

		ImageArrayHolder(ImageRef<T_ImgElm> a_srcImg)
		{
			Ncpp_ASSERT(a_srcImg->GetNofChannels() == V_NofChannels);

			m_srcImg = a_srcImg;

			m_actualAccessor.Init((T_AccElm *)a_srcImg->GetDataPtr(), size_2D(a_srcImg->GetSize()));
			m_actualAccessor.AssignVirtAccessorTo(&m_virtAccessor);
		}

		ImageArrayHolder(const Size_2D & a_size)
		{
			m_srcImg = Image<T_ImgElm>::Create(toCvSize(a_size), V_NofChannels);

			m_actualAccessor.Init((T_AccElm *)m_srcImg->GetDataPtr(), size_2D(m_srcImg->GetSize()));
			m_actualAccessor.AssignVirtAccessorTo(&m_virtAccessor);
		}

		template<class Y_ImgElm, class Y_AccElm, int const YV_NofChannels>
		static ImageArrayHolderRef<T_ImgElm, T_AccElm, V_NofChannels> CreateEmptyFrom(ImageArrayHolderRef<Y_ImgElm, Y_AccElm, YV_NofChannels> a_src)
		
		//static ImageArrayHolderRef<T_ImgElm, T_AccElm, V_NofChannels> CreateEmptyFrom()
		//static Ncpp::ObjRef< ImageArrayHolder_2D_Ref<T_ImgElm, T_AccElm, V_NofChannels> > CreateEmptyFrom()
		//static ObjRef< ImageArrayHolder<T_ImgElm, T_AccElm, V_NofChannels> > CreateEmptyFrom()
		{
			ImageArrayHolderRef<T_ImgElm, T_AccElm, V_NofChannels> ret = 
				new ImageArrayHolder<T_ImgElm, T_AccElm, V_NofChannels>(a_src->GetActualAccessor().GetSize());

			const ActualArrayAccessor_2D<Y_AccElm> & srcActualAcc = a_src->GetActualAccessor();
			const VirtArrayAccessor_2D<Y_AccElm> & srcVirtAcc = a_src->GetVirtAccessor();

			const int headerDif = srcVirtAcc.GetData() - srcActualAcc.GetData();

			const ActualArrayAccessor_2D<T_AccElm> & retActualAcc = ret->GetActualAccessor();
			VirtArrayAccessor_2D<T_AccElm> * pRetVirtAcc = (VirtArrayAccessor_2D<T_AccElm> *)&ret->GetVirtAccessor();

			pRetVirtAcc->Init(pRetVirtAcc->GetData() + headerDif,
				srcVirtAcc.GetSize_X(), srcVirtAcc.GetStepSize_X(),
				srcVirtAcc.GetSize_Y(), srcVirtAcc.GetStepSize_Y());

			return ret;
		}



		ImageRef<T_ImgElm> GetSrcImg()
		{
			return m_srcImg;
		}

		//ImageArrayHolderRef<T_ImgElm, T_AccElm, V_NofChannels> CloneWithData()
		//{
		//	ImageArrayHolderRef<T_ImgElm, T_AccElm, V_NofChannels> ret = new ImageArrayHolder<T_ImgElm, T_AccElm, V_NofChannels>(
		//		m_srcImg->Clone());
		//	return ret;
		//}

		//ImageArrayHolderRef<T_ImgElm, T_AccElm, V_NofChannels> CloneEmpty()
		//{
		//	ImageArrayHolderRef<T_ImgElm, T_AccElm, V_NofChannels> ret = new ImageArrayHolder<T_ImgElm, T_AccElm, V_NofChannels>(
		//		//m_srcImg->CloneEmpty());
		//		this->GetVirtAccessor().GetSize());
		//	return ret;
		//}

		ImageArrayHolderRef<T_ImgElm, T_AccElm, V_NofChannels> CreateProxy()
		{
			ImageArrayHolderRef<T_ImgElm, T_AccElm, V_NofChannels> ret = 
				new ImageArrayHolder<T_ImgElm, T_AccElm, V_NofChannels>(m_srcImg);

			VirtArrayAccessor_2D<T_AccElm> * pRetVirtAcc = (VirtArrayAccessor_2D<T_AccElm> *)&ret->GetVirtAccessor();
			m_virtAccessor.CopyTo(pRetVirtAcc);

			return ret;
		}

		ImageArrayHolderRef<T_ImgElm, T_AccElm, V_NofChannels> CreateTransposedProxy()
		{
			ImageArrayHolderRef<T_ImgElm, T_AccElm, V_NofChannels> ret =
				new ImageArrayHolder<T_ImgElm, T_AccElm, V_NofChannels>(m_srcImg);

			VirtArrayAccessor_2D<T_AccElm> * pRetVirtAcc = (VirtArrayAccessor_2D<T_AccElm> *)&ret->GetVirtAccessor();
			m_virtAccessor.AssignTransposeTo(pRetVirtAcc);

			return ret;
		}

	protected:

		ImageRef<T_ImgElm> m_srcImg;
	};



}