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


	//template<class T_LinkOwnerEx, class T_Elm, class T_PixelLinkEx>
	template<class T_Elm, class T_PixelLinkEx>
    class PixelLinkOwner
    {
        public:

			PixelLinkOwner()
			{
				//	This is a necessary workaround to avoid error C2440.
				m_linksHeadPtr = m_links;
			}

			void SetElm(T_Elm * a_pElm)
			{
				m_pElm = a_pElm;
			}

			

			//T_PixelLinkEx & GetLinkAt(int a_index) const
			T_PixelLinkEx & GetLinkAt(PixelLinkIndex a_index) const
			{ 
				Ncpp_ASSERT(a_index >= 0 && a_index < NOF_ALL_PIXEL_LINK_TYPES);

				//T_PixelLinkEx & rLink = *((T_PixelLinkEx *)&m_links[a_index]);
				//return rLink;

				return m_linksHeadPtr[a_index]; 
			}
			

			T_Elm * GetElmPtr() const { return m_pElm; }

			int GetNofLinks() const { return NOF_ALL_PIXEL_LINK_TYPES; }

	private:

		//PixelLink<T_LinkOwnerEx> m_links[NOF_ALL_PIXEL_LINK_TYPES];

		T_PixelLinkEx m_links[NOF_ALL_PIXEL_LINK_TYPES];
		//T_PixelLinkEx m_links[8];
		
		T_PixelLinkEx * m_linksHeadPtr;

		T_Elm * m_pElm;

    };







}