/*
 * utils.c
 *
 *  Created on: Feb 17, 2018
 *      Author: mafish
 */

#include "utils.h"

int32_t ilimit(int32_t val, int32_t min, int32_t max)
{
	if(val > max) return max;
	if(val < min) return min;
	return val;
}
int32_t iabs(int32_t val)
{
	if(val >= 0) return val;
	else return -val;
}
