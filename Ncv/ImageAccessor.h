#pragma once

#include <NovelCVLib\Ncpp\Common\commonLib_Misc.h>
#include <NovelCVLib\OpenCV\CvIncludes.h>
#include <NovelCVLib\OpenCV\Types.h>
#include <NovelCVLib\OpenCV\error.h>
#include <NovelCVLib\OpenCV\funcs1.h>
#include <vector>
#include <NovelCVLib\OpenCV\Image.h>



namespace Ncv
{
	using namespace Ncpp;

	//template<class T>
	//class MemAccessor_2D;

	template<class T_ImgElm, class T_AccElm, int const V_NofChannels>
	class ImageAccessor;


#define ImageAccessor_REF(T_ImgElm, T_AccElm, V_NofChannels) ObjRef< ImageAccessor< T_ImgElm, T_AccElm, V_NofChannels >>

	//typedef ImageAccessor< float, float, 3 > F32Image3C_FloatAcc;
	//typedef ObjRef< F32Image3C_FloatAcc > F32Image3C_FloatAcc_Ref;

	typedef ImageAccessor< Float, F32ColorVal, 3 > F32ImageAccessor3C;
	typedef ObjRef< F32ImageAccessor3C > F32ImageAccessor3C_Ref;

	//typedef ImageAccessor< Ncpp::Float, float, 1 > F32ImageAccessor1C;
	typedef ImageAccessor< Float, float, 1 > F32ImageAccessor1C;
	typedef ObjRef< F32ImageAccessor1C > F32ImageAccessor1C_Ref;

	typedef ImageAccessor< Int32, int, 1 > S32ImageAccessor1C;
	typedef ObjRef< S32ImageAccessor1C > S32ImageAccessor1C_Ref;




	template<class T_ImgElm, class T_AccElm, int const V_NofChannels>
	class ImageAccessor : public Ncpp::Object
	{
	public:

		//ImageAccessor(Ncpp::ObjRef<Image<T_ImgElm>> a_srcImg)
		//ImageAccessor(Ncpp::ObjRef<Ncv::Image<T_ImgElm>> a_srcImg)
		ImageAccessor(IMAGE_REF(T_ImgElm) a_srcImg)
		{
			m_isLocked = false;
			IplImage * p1 = ((Image<T_ImgElm>*)a_srcImg)->GetIplImagePtr();

			Init(a_srcImg);
		}

		ImageAccessor(OffsetCalc_2D_Ref a_offsetCalc)
		{
			m_isLocked = false;
			Init(a_offsetCalc);
		}

		OffsetCalc_2D_Ref GetOffsetCalc()
		{
			return GetMemAccessor()->GetOffsetCalc();
		}

		CvSize GetSize()
		{
			return cvSize(m_memAccessor->GetNofElms_X(), m_memAccessor->GetNofElms_Y());
		}

		CvSize GetSrcImgSize()
		{
			return m_srcImg->GetSize();
		}

		int GetSize_1D()
		{
			return m_memAccessor->GetNofElms_X() * m_memAccessor->GetNofElms_Y();
		}

		T_AccElm * GetDataPtr()
		{
			return m_memAccessor->GetDataPtr();
		}

		bool IsLocked()
		{
			return m_isLocked;
		}

		void Lock()
		{
			m_isLocked = true;
		}

		void Unlock()
		{
			m_isLocked = false;
		}

		//ImageAccessor_REF(T_ImgElm, T_AccElm, V_NofChannels) CloneNew()
		//{
		//	ImageAccessor_REF(T_ImgElm, T_AccElm, V_NofChannels) ret =
		//		new ImageAccessor<T_ImgElm, T_AccElm, V_NofChannels>();

		//	ret->m_srcImg = m_srcImg;
		//	ret->m_memAccessor = this->m_memAccessor;

		//	return ret;
		//}

		ImageAccessor_REF(T_ImgElm, T_AccElm, V_NofChannels) CloneAccAndImage()
		{
			return Clone(true);
		}

		ImageAccessor_REF(T_ImgElm, T_AccElm, V_NofChannels) CloneAccessorOnly()
		{
			return Clone(false);
		}

		MemAccessor_2D_REF(T_AccElm) GetMemAccessor()
		{
			return m_memAccessor;
		}

		IMAGE_REF(T_ImgElm) GetSrcImg()
		{
			return m_srcImg;
		}

		void SetSrcImg(IMAGE_REF(T_ImgElm) a_srcImg)
		{
			if (m_isLocked)
				throw "m_isLocked";

			m_srcImg = a_srcImg;
		}

		static MemAccessor_2D_REF(T_AccElm) CreateAccessorFromImage(
			IMAGE_REF(T_ImgElm) a_srcImg)
		{
			Ncpp_ASSERT(a_srcImg->GetNofChannels() == V_NofChannels);

			OffsetCalc_2D_Ref offsetCalc = new OffsetCalc_2D(1, a_srcImg->GetSize().width, a_srcImg->GetSize().height);
			offsetCalc->Lock();

			MemAccessor_2D_REF(T_AccElm) ret = new MemAccessor_2D<T_AccElm>((T_AccElm *)a_srcImg->GetDataPtr(), offsetCalc);
			//a_pAccessor->Init((T_AccElm *)a_srcImg->GetDataPtr(), offsetCalc);

			return ret;
		}

		void SwitchXY()
		{
			m_memAccessor->Unlock();
			m_memAccessor->SwitchXY();
			m_memAccessor->Lock();
		}

	protected:

		ImageAccessor()
		{

		}

		void Init(IMAGE_REF(T_ImgElm) a_srcImg)
		{
			if (m_isLocked)
				throw "m_isLocked";

			m_srcImg = a_srcImg;
			//m_memAccessor = new MemAccessor_2D<T_AccElm>();
			m_memAccessor = ImageAccessor::CreateAccessorFromImage(m_srcImg);
		}

		void Init(OffsetCalc_2D_Ref a_offsetCalc)
		{
			if (m_isLocked)
				throw "m_isLocked";

			m_srcImg = F32Image::Create(
				//cvSize(a_offsetCalc->GetOffsetCalc_X_Org()->GetNofElms(),
				//a_offsetCalc->GetOffsetCalc_Y_Org()->GetNofElms()),
				cvSize(a_offsetCalc->GetOffsetCalc_X_Org()->GetOuterNofElms(),
				a_offsetCalc->GetOffsetCalc_Y_Org()->GetOuterNofElms()),
				//cvSize(a_offsetCalc->GetOffsetCalc_Y()->GetNofElms(),
				//a_offsetCalc->GetOffsetCalc_X()->GetNofElms()),
				V_NofChannels);

			m_memAccessor = new MemAccessor_2D<T_AccElm>((T_AccElm *)m_srcImg->GetDataPtr(), a_offsetCalc);
			//ImageAccessor::CreateAccessorFromImage(m_srcImg, m_memAccessor);
		}

	protected:

		ImageAccessor_REF(T_ImgElm, T_AccElm, V_NofChannels) Clone(bool a_bCloneImage)
		{
			ImageAccessor_REF(T_ImgElm, T_AccElm, V_NofChannels) ret =
				new ImageAccessor<T_ImgElm, T_AccElm, V_NofChannels>();

			if (a_bCloneImage)
			{
				ret->m_srcImg = m_srcImg->Clone();
			}
			else
			{
				ret->m_srcImg = m_srcImg;
			}

			ret->m_memAccessor = m_memAccessor->Clone();
			ret->m_memAccessor->SetDataPtr((T_AccElm *)ret->m_srcImg->GetDataPtr());
			ret->m_memAccessor->Lock();

			return ret;
		}

	protected:

		MemAccessor_2D_REF(T_AccElm) m_memAccessor;
		IMAGE_REF(T_ImgElm) m_srcImg;

		bool m_isLocked;
	};

	//typedef VectorValImageAcc< Float, 4 > F32VectorValImageAcc_4C;


	//template <size_t N>
	//using Vector = Matrix<N, 1>;

	//template <size_t N>
	//using Vector = Matrix<N, 1>;

	template<class T, int const V_NofChannels>
	using VectorValImageAcc = ImageAccessor<T, VectorVal<T, V_NofChannels>, V_NofChannels>;

	template<class T, int const V_NofChannels>
	using VectorValImageAcc_Ref = ObjRef< VectorValImageAcc<T, V_NofChannels> >;

	//typedef VectorValImageAcc_Ref = ObjRef< VectorValImageAcc<T, V_NofChannels> >;


	//template<class T, int const V_NofChannels>
	//typedef ImageAccessor<T, VectorVal<T, V_NofChannels>, V_NofChannels> VectorValImageAcc<T, V_NofChannels>;



	////template<class T_ImgElm, class T_AccElm, int const V_NofChannels>
	//template<class T, int const V_NofChannels>
	//class VectorValImageAcc : public ImageAccessor<T, VectorVal<T, V_NofChannels>, V_NofChannels>
	//{
	//public:
	//	//VectorValImageAcc(IMAGE_REF(T) a_srcImg) : base(a_srcImg)
	//		VectorValImageAcc(IMAGE_REF(T) a_srcImg) : (a_srcImg)
	//	{
	//		//m_isLocked = false;
	//		//Init(a_srcImg);
	//	}

	//	VectorValImageAcc(OffsetCalc_2D_Ref a_offsetCalc) : (a_offsetCalc)
	//	{
	//		//m_isLocked = false;
	//		//Init(a_offsetCalc);
	//	}
	//};

	////template<class T_ImgElm, class T_AccElm, int const V_NofChannels>
	//template<class T, int const V_NofChannels>
	//class VectorValImageAcc_Ref : public ObjRef< VectorValImageAcc<T, V_NofChannels> >
	//{
	//public:
	//};

	typedef VectorValImageAcc< Float, 4 > F32VectorValImageAcc_4C;
	typedef ObjRef< F32VectorValImageAcc_4C > F32VectorValImageAcc_4C_Ref;

	typedef VectorValImageAcc< Float, 3 > F32VectorValImageAcc_3C;
	typedef ObjRef< F32VectorValImageAcc_3C > F32VectorValImageAcc_3C_Ref;

	typedef VectorValImageAcc< Float, 1 > F32VectorValImageAcc_1C;
	typedef ObjRef< F32VectorValImageAcc_1C > F32VectorValImageAcc_1C_Ref;

	typedef VectorValImageAcc< Int32, 1 > S32VectorValImageAcc_1C;
	typedef ObjRef< S32VectorValImageAcc_1C > S32VectorValImageAcc_1C_Ref;

	//#define VectorValImageAcc(T, N) ImageAccessor_REF(T, VectorVal<T, N>, N) ;  S32ImageAccessor1C;


	//#define VectorValImageAcc_REF(T, N) ImageAccessor_REF(T, VectorVal<T, N>, N) ;  S32ImageAccessor1C;




	//typedef ObjRef< S32ImageAccessor1C > S32ImageAccessor1C_Ref;






}