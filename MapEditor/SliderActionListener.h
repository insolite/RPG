#pragma once
#include "Universe.h"

class SliderActionListener :
	public gcn::ActionListener
{
public:
	void action(const gcn::ActionEvent& actionEvent)
	{
		if (actionEvent.getSource() == Universe::instance->brushMaskSlider)
		{
			gcn::Slider* slider = (gcn::Slider*)actionEvent.getSource();
			char str[5];

			slider->setValue((int)slider->getValue() + 0.5f);
			sprintf(str, "%.0fx", slider->getValue());
			Universe::instance->brushMaskSizeLabel->setCaption(str);
			// The value of the Slider has changed.
		}
	}

	SliderActionListener(void);
	~SliderActionListener(void);
};
