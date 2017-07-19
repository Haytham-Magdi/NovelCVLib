#pragma once

#include <NovelCVLib\Ncpp\Common\commonLib.h>
#include <NovelCVLib\Ncv\OpenCV\CvIncludes.h>
#include <NovelCVLib\Ncv\OpenCV\Types.h>
#include <NovelCVLib\Ncv\OpenCV\PixelTypes.h>
#include <NovelCVLib\Ncv\OpenCV\error.h>
#include <NovelCVLib\Ncv\OpenCV\Channel.h>

//#include "D:\HthmWork_D\OpenCV-2.3.1-win-superpack\opencv\build\include\opencv2\legacy\compat.hpp"



#define IMAGE_REF(T) Ncpp::ObjRef< Ncv::Image< T > >

namespace Ncv
{

	template<class T>
	class Image : FRM_Object(Image<T>)
	{
	public:
		Image(IplImage * a_src)
		{
			Ncv::InitLib();

			Init(a_src);
		}

		CHANNEL_REF(T) GetAt(int a_nChannel)
		{
			return m_channels[a_nChannel];
		}

		IplImage * GetIplImagePtr(void)
		{
			Ncpp_ASSERT( NULL != (IplImage *)m_orgImg );

			return (IplImage *)m_orgImg;
		}

		int GetNofChannels(void)
		{
			return m_orgImg->nChannels;
		}

		int GetWidth(void)
		{
			return m_channels[0]->GetWidth();
		}

		int GetHeight(void)
		{
			return m_channels[0]->GetHeight();
		}

		CvSize GetSize()
		{
			return cvGetSize (this->GetIplImagePtr());
		}

		int GetSize1D()
		{
			CvSize siz = GetSize();

			return siz.width * siz.height;
		}

		int GetSize1D_InBytes()
		{
			return GetNofChannels() * GetSize1D() * sizeof(T);
		}

		CvMat* GetMatPtr()
		{
			return cvGetMat(this->GetIplImagePtr(), &m_mat);
		}

		static Image * Create(CvSize a_siz, int a_nChannels)
		{
			return new Image(cvCreateImage(a_siz, 
				NCV_DEPTH_ID(T), a_nChannels)); 
		}

		void SetAll(T a_val)
		{
			for(unsigned int i=0; i<m_channels.size(); i++)
				m_channels[i]->SetAll(a_val);
		}

		T * GetPixAt(int a_nX, int a_nY)
		{
			return &m_pixs[a_nX * m_nofChannels + a_nY * m_nofLineUnits];
		}

		T * GetDataPtr()
		{
			return GetPixAt(0, 0);
		}

		IMAGE_REF(T) CloneNew()
		{
			IMAGE_REF(T) pRet = Image<T>::Create(this->GetSize(), this->GetNofChannels());

			return pRet;
		}

		Image< T > * CloneNew_WithChannels(int a_nNew_nofChnnels)
		{
			Image<T> * pRet = Image<T>::Create(this->GetSize(), a_nNew_nofChnnels);

			return pRet;
		}

		IMAGE_REF(T) Clone()
		{
			CvSize siz = this->GetSize();

			IMAGE_REF(T) pRet = this->CloneNew();
			this->CopyTo(pRet);

			return pRet;
		}

		void CopyTo(IMAGE_REF(T) destImg)
		{
			Ncpp_ASSERT(AreEqualCvSizes( GetSize(), destImg->GetSize()));
			Ncpp_ASSERT(GetNofChannels() == destImg->GetNofChannels());
			Ncpp_ASSERT(GetSize1D_InBytes() == destImg->GetSize1D_InBytes());

			memcpy(destImg->GetDataPtr(), this->GetDataPtr(), this->GetSize1D_InBytes());
		}

	protected:
		void Init(IplImage * a_src)
		{
			m_orgImg = a_src;

			int nofChns = m_nofChannels = a_src->nChannels;

			m_channels.resize(0);

			for(int i=0; i<nofChns; i++)
				m_channels.push_back(new Channel<T>(m_orgImg, i));

			{
				//m_nWidth = a_src->width;
				//m_nHeight = a_src->height;				

				m_nofLineUnits = a_src->widthStep / sizeof(T);

				//HCV_CALL( cvGetImageRawData ((IplImage *)a_src, (Ncpp::Uint8 **) &m_pixs, 
				HCV_CALL( cvGetRawData ((IplImage *)a_src, (Ncpp::Uint8 **) &m_pixs, 
					NULL, NULL));			

			//m_pixs = &srcData[m_nBgnX * m_nStepX + a_nChnl +
			//	m_nBgnY * m_nLineLen];

			}

		}



	protected:
		IplImageRef m_orgImg;
		ChannelRefColl<T> m_channels;
		CvMat m_mat;

		int m_nofChannels;

		// nofChannels * nofPixs
		int m_nofLineUnits;

		T * m_pixs;
	};


	typedef Ncv::Image< Ncpp::Uint8 > U8Image;
	typedef Ncpp::ObjRef< U8Image > U8ImageRef;

	typedef Ncv::Image< Ncpp::Int16 > S16Image;
	typedef Ncpp::ObjRef< S16Image > S16ImageRef;

	typedef Ncv::Image< Ncpp::Int32 > S32Image;
	typedef Ncpp::ObjRef< S32Image > S32ImageRef;

	typedef Ncv::Image< Ncpp::Float > F32Image;
	typedef Ncpp::ObjRef< F32Image > F32ImageRef;


/*	template<class T>
	class ImageRef : Ncpp::ObjRef< Image< T > >
	{
	};*/

}
