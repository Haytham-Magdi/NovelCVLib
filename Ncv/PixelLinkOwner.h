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


	//template<class T_LinkOwnerEx, class T_Elm, class T_PixelLink>
	template<class T_Elm, class T_PixelLink, class T_CoreSharedPixelLink>
    class PixelLinkOwner
    {
        public:

			PixelLinkOwner()
			{
				//	This is a necessary workaround to avoid error C2440.
				m_linksHeadPtr = m_links;
				m_coreSharedLinksHeadPtr = m_coreSharedLinks;
			}

			void SetElm(T_Elm * a_pElm)
			{
				m_pElm = a_pElm;
			}

			

			//T_PixelLink & GetLinkAt(int a_index) const
			T_PixelLink & GetLinkAt(PixelLinkIndex a_index) const
			{ 
				Ncpp_ASSERT(a_index >= 0 && a_index < NOF_ALL_PIXEL_LINK_TYPES);

				//T_PixelLink & rLink = *((T_PixelLink *)&m_links[a_index]);
				//return rLink;

				return m_linksHeadPtr[a_index]; 
			}
			
			T_CoreSharedPixelLink & GetCoreSharedLinkAt(PixelLinkIndex a_index) const
			{
				Ncpp_ASSERT(a_index >= 0 && a_index < NOF_PRIMARY_PIXEL_LINK_TYPES);

				return m_coreSharedLinksHeadPtr[a_index];
			}


			T_Elm * GetElmPtr() const { return m_pElm; }

			int GetNofLinks() const { return NOF_ALL_PIXEL_LINK_TYPES; }

	private:

		//PixelLink<T_LinkOwnerEx> m_links[NOF_ALL_PIXEL_LINK_TYPES];

		T_PixelLink m_links[NOF_ALL_PIXEL_LINK_TYPES];
		T_PixelLink * m_linksHeadPtr;

		T_CoreSharedPixelLink m_coreSharedLinks[NOF_PRIMARY_PIXEL_LINK_TYPES];
		T_CoreSharedPixelLink * m_coreSharedLinksHeadPtr;

		T_Elm * m_pElm;

    };







}