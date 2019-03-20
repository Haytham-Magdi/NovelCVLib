#pragma once

#pragma inline_depth( 255 )

#include <stdlib.h>


#include <NovelCVLib\Common\Debug.h>
#include <NovelCVLib\Common\Object.h>

#include <NovelCVLib\Ncv\PixelLink.h>
#include <NovelCVLib\Ncv\PixelLinkTypes.h>

namespace Ncv
{
	using namespace Ncpp;


	template<class T_LinkOwnerEx, class T_Elm, class T_PixelLinkEx>
    class PixelLinkOwner
    {
        public:

			void SetElm(T_Elm * a_pElm)
			{
				m_pElm = a_pElm;
			}

			//PixelLink<T_LinkOwnerEx> & GetLinkAt(PixelLinkIndex a_index) const { return GetLinkAt((int)a_index); }
			T_PixelLinkEx & GetLinkAt(PixelLinkIndex a_index) const { return GetLinkAt((int)a_index); }
			

			//PixelLink<T_LinkOwnerEx> & GetLinkAt(int a_index) const { return m_links[a_index]; }
			T_PixelLinkEx & GetLinkAt(int a_index) const { return m_links[a_index]; }


			T_Elm * GetElmPtr() const { return m_pElm; }

			int GetNofLinks() const { return NOF_ALL_PIXEL_LINK_TYPES; }

	private:

		PixelLink<T_LinkOwnerEx> m_links[NOF_ALL_PIXEL_LINK_TYPES];
		T_Elm * m_pElm;

    };







}