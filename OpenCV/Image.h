#pragma once

#include <NovelCVLib\Ncpp\Common\commonLib_Misc.h>
#include <NovelCVLib\OpenCV\CvIncludes.h>
#include <NovelCVLib\OpenCV\Types.h>
#include <NovelCVLib\OpenCV\PixelTypes.h>
#include <NovelCVLib\OpenCV\error.h>
#include <NovelCVLib\OpenCV\Channel.h>

#include <NovelCVLib\OpenCV\OpenCVKillers.h>

//#include <NovelCVLib\OpenCV\funcs1.h>
////#include <NovelCVLib\Ncv\ConvKernel.h>
//#include <NovelCVLib\OpenCV\Hsv.h>


//#include "D:\HthmWork_D\OpenCV-2.3.1-win-superpack\opencv\build\include\opencv2\legacy\compat.hpp"



#define IMAGE_REF(T) Ncpp::ObjRef< Ncv::Image< T > >

namespace Ncv
{

#define IMAGE_REF(T) Ncpp::ObjRef< Ncv::Image< T > >

	template<class T>
	class Image;

	template<class T>
	using ImageRef = Ncpp::ObjRef<Ncv::Image<T>>;

	template<class T>
	class Image : public Ncpp::Object
	{
	public:
		Image(CvMatRef a_src)
		{
			//Ncpp:Ncpp_ASSERT(nullptr != a_src);

			Ncv::InitLib();

			Init(a_src);
		}

		CHANNEL_REF(T) GetAt(int a_nChannel)
		{
			return m_channels[a_nChannel];
		}

		int GetNofChannels(void)
		{
			return m_orgImg->channels();
		}

		int GetWidth(void)
		{
			return m_channels[0]->GetWidth();
		}

		int GetHeight(void)
		{
			return m_channels[0]->GetHeight();
		}

		cv::Size GetSize()
		{
			return this->GetMat().size();
		}

		int GetSize1D()
		{
			cv::Size siz = GetSize();

			return siz.width * siz.height;
		}

		int GetSize1D_InBytes()
		{
			return GetNofChannels() * GetSize1D() * sizeof(T);
		}

		cv::Mat& GetMat()
		{
			//return cvGetMat(this->GetMat(), &m_mat);
			return this->m_mat;
		}

		cv::Mat* GetMatPtr()
		{
			//return cvGetMat(this->GetMat(), &m_mat);
			return &this->m_mat;
		}

		static Image * Create(cv::Size a_size, int a_nChannels)
		{
			Ncv::CvMatRef matRef = new cv::Mat();

			//int type;

			T v1;

			if (std::is_same<T, float>::value)
			{
				(*matRef).create(a_size, CV_32FC(a_nChannels));
			}
			else if (std::is_same<T, double>::value)
			{
				(*matRef).create(a_size, CV_64FC(a_nChannels));
			}
			else if (std::is_same<T, int>::value)
			{
				(*matRef).create(a_size, CV_32SC(a_nChannels));
			}
			else if (std::is_same<T, short>::value)
			{
				(*matRef).create(a_size, CV_16SC(a_nChannels));
			}
			else if (std::is_same<T, unsigned short>::value)
			{
				(*matRef).create(a_size, CV_16UC(a_nChannels));
			}
			else if (std::is_same<T, char>::value)
			{
				(*matRef).create(a_size, CV_8SC(a_nChannels));
			}
			else if (std::is_same<T, uchar>::value)
			{
				(*matRef).create(a_size, CV_8UC(a_nChannels));
			}
			else
			{
				throw "Invalid type case!";
			}


			//return new Image(cvCreateImage(a_siz, 
			//	NCV_DEPTH_ID(T), a_nChannels)); 
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

		IMAGE_REF(T) CloneEmpty()
		{
			IMAGE_REF(T) pRet = Image<T>::Create(this->GetSize(), this->GetNofChannels());
			return pRet;
		}

		Image< T > * CreateWithSameSize(int a_nNew_nofChnnels)
		{
			Image<T> * pRet = Image<T>::Create(this->GetSize(), a_nNew_nofChnnels);
			return pRet;
		}

		IMAGE_REF(T) Clone()
		{
			cv::Size siz = this->GetSize();

			IMAGE_REF(T) pRet = this->CloneEmpty();
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
		void Init(CvMatRef a_src)
		//void Init(cv::Mat &  a_src)
		{
			m_orgImg = a_src;

			int nofChns = m_nofChannels = a_src->channels();

			m_channels.resize(0);

			for(int i=0; i<nofChns; i++)
				m_channels.push_back(new Channel<T>(m_orgImg, i));

			{
				//m_nWidth = a_src->width;
				//m_nHeight = a_src->height;				

				m_nofLineUnits = a_src->cols / sizeof(T);

				m_pixs = (T *)a_src->data;
			}

		}



	protected:
		CvMatRef m_orgImg;
		ChannelRefColl<T> m_channels;
		cv::Mat m_mat;

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
