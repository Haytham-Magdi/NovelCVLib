#pragma once

#include <NovelCVLib\Ncpp\Common\commonLib_Misc.h>
#include <NovelCVLib\Ncpp\Math\mathLib.h>

//#include <NovelCVLib\Ncpp\Common\ActualArrayAccessor_2D.h>



//#define M_PI 3.14159265358979323846
#define M_PI 3.14159265358979323846f


namespace Ncv
{


	class AngleRotation : public Ncpp::Object
	{
		//typedef IntScale<int, float, 1000> SizeRotIntScale;
		typedef IntScale<int, float, 1000> SRIntScale;

	public:

		AngleRotation(float a_angDig);

		float GetAngleByDigree() { return m_angDig; }
		float GetAngleByRad() { return m_angRad; }
		
		void RotateScaledPoint(const S32Point & a_inp, S32Point * a_pOut)
		{
			a_pOut->x = a_inp.x * m_nCos - a_inp.y * m_nSin;
			a_pOut->y = a_inp.x * m_nSin + a_inp.y * m_nCos;
		}

		void ReverseRotateScaledPoint(const S32Point & a_inp, S32Point * a_pOut)
		{
			a_pOut->x = a_inp.x * m_nCos + a_inp.y * m_nSin;
			a_pOut->y = -a_inp.x * m_nSin + a_inp.y * m_nCos;
		}


	protected:


	protected:

		float m_angDig;
		float m_angRad;

		int m_nCos;
		int m_nSin;
	};


	typedef Ncpp::ObjRef< AngleRotation > ImgSizeRotationRef;

}