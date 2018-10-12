#pragma once

#include <NovelCVLib\Ncpp\Common\commonLib_Misc.h>
#include <NovelCVLib\Ncpp\Math\mathLib.h>




//#define M_PI 3.14159265358979323846
#define M_PI 3.14159265358979323846f


namespace Ncv
{

	template<class T_IntScale>
	class AngleRotation : public Ncpp::Object
	{
		//typedef IntScale<int, float, 1000> T_IntScale;

	public:

		AngleRotation(float a_angDig)
		{
			// Ncpp_ASSERT(a_angDig >= 0);
			// Ncpp_ASSERT(a_angDig <= 90);


			m_angDig = a_angDig;
			m_angRad = (float)(a_angDig * M_PI / 180);

			m_nCos = T_IntScale::ScaleToI(cos(m_angRad));
			m_nSin = T_IntScale::ScaleToI(sin(m_angRad));

			m_nCos = T_IntScale::GoNearCeilByOne(m_nCos);
			m_nSin = T_IntScale::GoNearCeilByOne(m_nSin);

			const long long mag1 = Sqr(m_nCos) + Sqr(m_nSin);
			Ncpp_ASSERT(mag1 >= Sqr(T_IntScale::ScaleToI(1)));

		}


		float GetAngleByDigree() { return m_angDig; }
		float GetAngleByRad() { return m_angRad; }
		
		void RotateScaledPoint(const S64Point & a_inp, S64Point * a_pOut)
		{
			a_pOut->x = T_IntScale::IntDividByScale(a_inp.x * m_nCos - a_inp.y * m_nSin);
			a_pOut->y = T_IntScale::IntDividByScale(a_inp.x * m_nSin + a_inp.y * m_nCos);

			//a_pOut->x = T_IntScale::IntDividByScale((int)((long long)a_inp.x * m_nCos - (long long)a_inp.y * m_nSin));
			//a_pOut->y = T_IntScale::IntDividByScale((int)((long long)a_inp.x * m_nSin + (long long)a_inp.y * m_nCos));
		}

		S64Point  RotateScaledPoint(const S64Point & a_inp)
		{
			S64Point a_out;
			RotateScaledPoint(a_inp, &a_out);
			return a_out;
		}

		void ReverseRotateScaledPoint(const S64Point & a_inp, S64Point * a_pOut)
		{
			a_pOut->x = T_IntScale::IntDividByScale(a_inp.x * m_nCos + a_inp.y * m_nSin);
			a_pOut->y = T_IntScale::IntDividByScale(-a_inp.x * m_nSin + a_inp.y * m_nCos);

			//a_pOut->x = T_IntScale::IntDividByScale((int)((long long)a_inp.x * m_nCos + (long long)a_inp.y * m_nSin));
			//a_pOut->y = T_IntScale::IntDividByScale((int)((long long)-a_inp.x * m_nSin + (long long)a_inp.y * m_nCos));
		}

		S64Point  ReverseRotateScaledPoint(const S64Point & a_inp)
		{
			S64Point a_out;
			ReverseRotateScaledPoint(a_inp, &a_out);
			return a_out;
		}


	protected:


	protected:

		float m_angDig;
		float m_angRad;

		//int m_nCos;
		//int m_nSin;

		long long m_nCos;
		long long m_nSin;
	};


	//typedef Ncpp::ObjRef< AngleRotation > AngleRotationRef;

}