#pragma once

#include <NovelCVLib\Ncpp\Common\commonLib_Misc.h>
#include <NovelCVLib\Ncpp\Math\mathLib.h>




//#define M_PI 3.14159265358979323846
#define M_PI 3.14159265358979323846f


namespace Ncv
{


	class AngleRotation : public Ncpp::Object
	{
		typedef IntScale<int, float, 1000> ARIntScale;

	public:

		AngleRotation(float a_angDig);

		float GetAngleByDigree() { return m_angDig; }
		float GetAngleByRad() { return m_angRad; }
		
		void RotateScaledPoint(const S32Point & a_inp, S32Point * a_pOut)
		{
			a_pOut->x = ARIntScale::IntDividByScale(a_inp.x * m_nCos - a_inp.y * m_nSin);
			a_pOut->y = ARIntScale::IntDividByScale(a_inp.x * m_nSin + a_inp.y * m_nCos);
		}

		S32Point  RotateScaledPoint(const S32Point & a_inp)
		{
			S32Point a_out;
			RotateScaledPoint(a_inp, &a_out);
			return a_out;
		}

		void ReverseRotateScaledPoint(const S32Point & a_inp, S32Point * a_pOut)
		{
			a_pOut->x = ARIntScale::IntDividByScale(a_inp.x * m_nCos + a_inp.y * m_nSin);
			a_pOut->y = ARIntScale::IntDividByScale(-a_inp.x * m_nSin + a_inp.y * m_nCos);
		}

		S32Point  ReverseRotateScaledPoint(const S32Point & a_inp)
		{
			S32Point a_out;
			ReverseRotateScaledPoint(a_inp, &a_out);
			return a_out;
		}


	protected:


	protected:

		float m_angDig;
		float m_angRad;

		int m_nCos;
		int m_nSin;
	};


	typedef Ncpp::ObjRef< AngleRotation > AngleRotationRef;

}