


int Round( float a_num )
{
	int nRet;

	if( a_num > 0 )
		nRet = (int) ( a_num + 0.55555555555 );
	else
		nRet = (int) ( a_num - 0.55555555555 );

	return nRet;
}

