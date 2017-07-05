#pragma once

#pragma inline_depth( 255 )

#include <stdlib.h>


#include <Novel-Lib\Ncpp\Common\Debug.h>


namespace Ncpp
{
	class IndexCalc2D : FRM_Object
	{
	public:

		IndexCalc2D()
		{
			m_bInitDone = false;

			m_nSizX = -1;
			m_nSizY = -1;
			m_nSizTot = -1;
		}

		IndexCalc2D(int a_nSizX, int a_nSizY)
		{
			m_bInitDone = false;

			Init(a_nSizX, a_nSizY);
		}

		void Init(int a_nSizX, int a_nSizY)
		{
			Ncpp_ASSERT(!m_bInitDone);

			m_nSizX = a_nSizX;
			m_nSizY = a_nSizY;
			m_nSizTot = a_nSizX * a_nSizY;

			m_bInitDone = true;
		}

		int Calc(int a_x, int a_y)
		{
			return a_x + a_y * m_nSizX;
		}

		int Calc_X(int a_nIdx)
		{
			return a_nIdx % m_nSizX;
		}

		int Calc_Y(int a_nIdx)
		{
			return a_nIdx / m_nSizX;
		}

		int GetSizeX()
		{
			return m_nSizX;
		}

		int GetSizeY()
		{
			return m_nSizY;
		}

		int GetTotalSize()
		{
			return m_nSizTot;
		}

	protected:

		int m_nSizX;
		int m_nSizY;
		int m_nSizTot;

		bool m_bInitDone;
	};

	class IndexCalc3D : FRM_Object
	{
	public:

		IndexCalc3D()
		{
			m_bInitDone = false;

			m_nSizX = -1;
			m_nSizY = -1;
			m_nSizZ = -1;
			m_nSizXY = -1;
			m_nSizTot = -1;
		}

		IndexCalc3D(int a_nSizX, int a_nSizY, int a_nSizZ)
		{
			m_bInitDone = false;

			Init(a_nSizX, a_nSizY, a_nSizZ);
		}

		void Init(int a_nSizX, int a_nSizY, int a_nSizZ)
		{
			Ncpp_ASSERT(!m_bInitDone);

			m_nSizX = a_nSizX;
			m_nSizY = a_nSizY;
			m_nSizZ = a_nSizZ;
			m_nSizXY = a_nSizX * a_nSizY;
			m_nSizTot = a_nSizX * a_nSizY * a_nSizZ;

			m_bInitDone = true;
		}

		int Calc(int a_x, int a_y, int a_z)
		{
			return a_x + a_y * m_nSizX +
				a_z * m_nSizXY;
		}

		int Calc_X(int a_nIdx)
		{
			int nIdxXY = a_nIdx % m_nSizXY;

			return nIdxXY % m_nSizX;
		}

		int Calc_Y(int a_nIdx)
		{
			int nIdxXY = a_nIdx % m_nSizXY;

			return nIdxXY / m_nSizX;
		}

		int Calc_Z(int a_nIdx)
		{
			return a_nIdx / m_nSizXY;
		}

		int GetSizeX()
		{
			return m_nSizX;
		}

		int GetSizeY()
		{
			return m_nSizY;
		}

		int GetSizeZ()
		{
			return m_nSizZ;
		}

		int GetTotalSize()
		{
			return m_nSizTot;
		}

	protected:

		int m_nSizX;
		int m_nSizY;
		int m_nSizXY;
		int m_nSizZ;
		int m_nSizTot;

		bool m_bInitDone;
	};

}