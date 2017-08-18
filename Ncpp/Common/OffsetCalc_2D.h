#pragma once

#pragma inline_depth( 255 )

#include <stdlib.h>


#include <NovelCVLib\Common\Debug.h>
#include <NovelCVLib\Ncpp\Common\OffsetCalc_1D.h>


namespace Ncpp
{
	class OffsetCalc_2D;
	typedef Ncpp::ObjRef< OffsetCalc_2D > OffsetCalc_2D_Ref;

	class OffsetCalc_2D : public Ncpp::Object
	{
	public:

		OffsetCalc_2D(int a_nAbsoluteStepSize_X, int a_nOuterNofSteps_X, int a_nOuterNofSteps_Y)
		{
			m_isLocked = false;
			Init(a_nAbsoluteStepSize_X, a_nOuterNofSteps_X, a_nOuterNofSteps_Y);
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

		OffsetCalc_2D_Ref Clone()
		{
			OffsetCalc_2D_Ref pRet = new OffsetCalc_2D();

			pRet->m_offsetCalc_X = m_offsetCalc_X->Clone();
			pRet->m_offsetCalc_X->Lock();
			pRet->m_offsetCalc_X_Org = m_offsetCalc_X_Org;

			pRet->m_offsetCalc_Y = m_offsetCalc_Y->Clone();
			pRet->m_offsetCalc_Y->Lock();
			pRet->m_offsetCalc_Y_Org = m_offsetCalc_Y_Org;

			pRet->m_nOuterLimOffset = m_nOuterLimOffset;

			pRet->m_isLocked = false;
			return pRet;
		}

		int GetOffsetPart1()
		{
			return m_offsetCalc_X->GetOffsetPart1() + m_offsetCalc_Y->GetOffsetPart1();
		}

		int CalcPart2(int a_nStep_X, int a_nStep_Y)
		{
			return m_offsetCalc_X->CalcPart2(a_nStep_X) + m_offsetCalc_Y->CalcPart2(a_nStep_Y);
		}

		void SwitchXY()
		{
			if (m_isLocked)
				throw "m_isLocked";

			OffsetCalc_1D_Ref temp;

			temp = m_offsetCalc_X;
			m_offsetCalc_X = m_offsetCalc_Y;
			m_offsetCalc_Y = temp;
		}

		void SetRange_Relative_X(int a_nBgn_X, int a_nEnd_X)
		{
			if (m_isLocked)
				throw "m_isLocked";

			m_offsetCalc_X->Unlock();
			m_offsetCalc_X->SetRange_Relative(a_nBgn_X, a_nEnd_X);
			m_offsetCalc_X->Lock();
		}

		void SetRange_Relative_Y(int a_nBgn_Y, int a_nEnd_Y)
		{
			if (m_isLocked)
				throw "m_isLocked";

			m_offsetCalc_Y->Unlock();
			m_offsetCalc_Y->SetRange_Relative(a_nBgn_Y, a_nEnd_Y);
			m_offsetCalc_Y->Lock();
		}

		void SetRange_Relative(int a_nBgn_X, int a_nEnd_X, int a_nBgn_Y, int a_nEnd_Y)
		{
			if (m_isLocked)
				throw "m_isLocked";

			SetRange_Relative_X(a_nBgn_X, a_nEnd_X);
			SetRange_Relative_Y(a_nBgn_Y, a_nEnd_Y);
		}

		OffsetCalc_1D_Ref GetOffsetCalc_X()
		{
			return m_offsetCalc_X;
		}

		OffsetCalc_1D_Ref GetOffsetCalc_Y()
		{
			return m_offsetCalc_Y;
		}

		OffsetCalc_1D_Ref GetOffsetCalc_X_Org()
		{
			return m_offsetCalc_X_Org;
		}

		OffsetCalc_1D_Ref GetOffsetCalc_Y_Org()
		{
			return m_offsetCalc_Y_Org;
		}

	protected:

		OffsetCalc_2D()
		{
			m_isLocked = false;
		}

		void Init(int a_nAbsoluteStepSize_X, int a_nOuterNofSteps_X, int a_nOuterNofSteps_Y)
		{
			if (m_isLocked)
				throw "m_isLocked";

			m_offsetCalc_X = new OffsetCalc_1D(a_nOuterNofSteps_X, a_nAbsoluteStepSize_X);
			m_offsetCalc_X->Lock();
			m_offsetCalc_X_Org = m_offsetCalc_X;


			m_offsetCalc_Y = new OffsetCalc_1D(a_nOuterNofSteps_Y, m_offsetCalc_X->GetOuterLimOffset());
			m_offsetCalc_Y->Lock();
			m_offsetCalc_Y_Org = m_offsetCalc_Y;

			//m_offsetCalc_X->Init(a_nOuterNofSteps_X, a_nAbsoluteStepSize_X);
			//m_offsetCalc_Y->Init(a_nOuterNofSteps_Y, m_offsetCalc_X->GetOuterLimOffset());

			m_nOuterLimOffset = m_offsetCalc_Y->GetOuterLimOffset();
		}

	protected:

		OffsetCalc_1D_Ref m_offsetCalc_X;
		OffsetCalc_1D_Ref m_offsetCalc_Y;

		OffsetCalc_1D_Ref m_offsetCalc_X_Org;
		OffsetCalc_1D_Ref m_offsetCalc_Y_Org;

		int m_nOuterLimOffset;

		bool m_isLocked;
	};

}