#include "StdAfx.h"
#include "SliderActionListener.h"


SliderActionListener::SliderActionListener(void)
{
}


SliderActionListener::~SliderActionListener(void)
{
}

void SliderActionListener::action(const gcn::ActionEvent& actionEvent)
	{
		if (actionEvent.getSource() == Universe::instance->brushMaskSlider)
		{
			gcn::Slider* slider = (gcn::Slider*)actionEvent.getSource();
			char str[5];

			slider->setValue((int)slider->getValue() + 0.5f);
			//printf("%.2f\n",slider->getValue() + 0.5f);
			Universe::instance->DeleteBrushMask();
			Universe::instance->CreateBrushMask((int)(slider->getValue() + 0.5 - 1.0f));
			//Universe::instance->PrintBrushMask();
			sprintf(str, "%.0fx", slider->getValue());
			Universe::instance->brushMaskSizeLabel->setCaption(str);
		}
	}