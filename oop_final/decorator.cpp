#include "decorator.h"

void Decorator::ProduceDecorator::Produce()
{
	for (size_t i = 0; i < cycles; i++)
	{
		room->Produce();
	}
}