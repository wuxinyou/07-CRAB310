#include "stm32f10x_conf.h"

#ifdef USE_FULL_ASSERT
void assert_failed()
{
/* User can add his own implementation to report the file name and line number,
ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */ /* Infinite loop */
// 	printf("Wrong parameters value: file %s on line %d\r\n", file, line);
	while (1)
	{
		
	}
}
#endif



