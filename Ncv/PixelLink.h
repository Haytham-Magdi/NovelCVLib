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

			void Init(const PixelLinkType * a_pType, T_LinkOwner * a_pPeer, bool a_exists)
			{
				m_pType = a_pType;
				m_pPeer = a_pPeer;
				m_exists = a_exists;
			}

			const PixelLinkType & GetType() const { return *m_pType; }

			T_LinkOwner * GetPeerPtr() const { return m_pPeer; }

	private:

		PixelLinkType * m_pType;
		T_LinkOwner * m_pPeer;
		bool m_exists;



    };







}