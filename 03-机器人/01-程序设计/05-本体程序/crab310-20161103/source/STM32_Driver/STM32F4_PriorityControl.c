#include "STM32F4_PriorityControl.h"
#include "misc.h"

void setSystemPriorityGroup()
{
		NVIC_PriorityGroupConfig(STM32_NVIC_PriorityGroup);
}
