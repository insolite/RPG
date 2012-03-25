#pragma once
#include "Universe.h"

class SliderActionListener :
	public gcn::ActionListener
{
public:
	void action(const gcn::ActionEvent& actionEvent);

	SliderActionListener(void);
	~SliderActionListener(void);
};
