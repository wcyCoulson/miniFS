#include "Bitmap.h"


Bitmap::Bitmap(byte * content, int length)
{
	if (length % 8 != 0)
	{
		printf("bitmap's length must be div by 8");
		exit(-1);
	}
	bitmapSlots = (byte*)malloc(sizeof(byte)*(length / 8));
	memset(bitmapSlots, 0, sizeof(bitmapSlots));
	for (int i = 0; i < length / 8; i++)
	{
		bitmapSlots[i] |= content[i];
	}
	this->slotCount = length;
}

Bitmap::~Bitmap()
{
	free(bitmapSlots);
}

//这个keyValue指的是内容块的编号，第一号内容块的keyValue为0,其返回该块是否被占用
bool Bitmap::GetBlockState(int keyValue)
{
	if (keyValue > this->slotCount)
	{
		printf("your keyValue big than bitmap length");
		exit(-1);
	}
	//获得数组那个位
	int indexInArray = keyValue / 8;
	int indexInChar = keyValue % 8;
	byte b = this->bitmapSlots[indexInArray];
	b = b >> indexInChar;
	b = b & 1;
	if (b == 1)
		return true;
	else return false;
}


void Bitmap::SetBlockState(int keyValue, bool state)
{
	if (keyValue > this->slotCount)
	{
		printf("your keyValue big than bitmap length");
		exit(-1);
	}
	//获得数组那个位
	int indexInArray = keyValue / 8;
	int indexInChar = keyValue % 8;
	if (state)
	{
		bitmapSlots[indexInArray] |= (1 << indexInChar);
	}	
	else
	{
		bitmapSlots[indexInArray] &= ~(1 << indexInChar);
	}
	return;
}

void Bitmap::printout()
{
	int i = 0;
	for (i = 0; i < this->slotCount / 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			byte b = this->bitmapSlots[i];
			b = b >> j;
			b &= 1;
			printf("%d", b);
		}
		printf("  ");
	}
	printf("\n");
}
