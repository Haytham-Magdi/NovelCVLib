#pragma once

#pragma inline_depth( 255 )

#include <stdlib.h>


#include <NovelCVLib\Common\Debug.h>
#include <NovelCVLib\Common\Object.h>

#include <NovelCVLib\Ncv\PixelLinkTypes.h>

namespace Ncv
{
	using namespace Ncpp;

	template<class T_LinkOwner>
    class PixelLink
    {
        public:

			void Init(const PixelLinkType * a_pType, T_LinkOwner * a_pOwner, T_LinkOwner * a_pPeerOwner, bool a_exists)
			{
				m_pType = (PixelLinkType *)a_pType;
				m_pOwner = a_pOwner;
				m_pPeerOwner = a_pPeerOwner;
				m_exists = a_exists;
			}

			const PixelLinkType & GetType() const { return *m_pType; }

			T_LinkOwner * GetOwnerPtr() const { return m_pOwner; }
			T_LinkOwner * GetPeerOwnerPtr() const { return m_pPeerOwner; }

			bool Exists() const { return m_exists; }

	private:

		PixelLinkType * m_pType;
		T_LinkOwner * m_pOwner;
		T_LinkOwner * m_pPeerOwner;
		bool m_exists;



    };







}