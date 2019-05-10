#pragma once

#pragma inline_depth( 255 )

#include <stdlib.h>


#include <NovelCVLib\Common\Debug.h>
#include <NovelCVLib\Common\Object.h>


namespace Ncv
{
	using namespace Ncpp;

#define NOF_ALL_PIXEL_LINK_TYPES 8
#define NOF_PRIMARY_PIXEL_LINK_TYPES 4

	typedef enum
	{
		RC = 0,
		RD = 1,
		CD = 2,
		LD = 3,

		LC = 4,
		LU = 5,
		CU = 6,
		RU = 7
	}PixelLinkIndex;


    class PixelLinkType
    {
	public:
		
		PixelLinkType(PixelLinkIndex a_index, int a_shiftX, int a_shiftY)
		{
			Index = a_index;
			ReverseIndex = (PixelLinkIndex)(((int)a_index + (NOF_PRIMARY_PIXEL_LINK_TYPES)) % NOF_ALL_PIXEL_LINK_TYPES);

			ShiftX = a_shiftX;
			ShiftY = a_shiftY;

			m_isDiagonal = (a_shiftX != 0 && a_shiftY != 0);
		}

        
	public:

		PixelLinkIndex const GetIndex() { return Index; }
		PixelLinkIndex const GetReverseIndex() { return ReverseIndex; }

		int GetShiftX() const { return ShiftX; }
		int GetShiftY() const { return ShiftY; }

		bool IsDiagonal() const { return m_isDiagonal; }

	private:

		PixelLinkIndex Index;
		PixelLinkIndex ReverseIndex;

		int ShiftX;
		int ShiftY;

		bool m_isDiagonal;
    };







}