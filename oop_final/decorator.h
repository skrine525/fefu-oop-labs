#pragma once
#include "city.h"

namespace Decorator
{
	class ProduceDecorator : public ProductionRoom
	{
	public:
		ProduceDecorator(ProductionRoom* room, std::size_t cycles) : room(room), cycles(cycles) {}

		void Produce() override;

	private:
		ProductionRoom* room;
		std::size_t cycles;
	};
}
