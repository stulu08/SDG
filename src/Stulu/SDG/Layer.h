#pragma once
#include "Core.h"

namespace SDG {
	class STULU_API Layer
	{
	public:
		virtual ~Layer() {};

		virtual void onAttach(){}
		virtual void onDetach(){}
		virtual void onRender() {}
	};
}

