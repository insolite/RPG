#include "./GridLayout.h"
#include "../Container.h"
#include "../util/Insets.h"
#include "../util/Rectangle.h"
#include "../util/Dimension.h"

namespace ui
{
	namespace layout
	{
		GridLayout::GridLayout(int r, int c)
			:	cols(c),
				rows(r)
		{
		}

		GridLayout::GridLayout(int r, int c, int vGap, int hGap)
			:	cols(c),
				rows(r)
		{
			setVgap(vGap);
			setHgap(hGap);
		}

		GridLayout::GridLayout(const GridLayout& rhs)
			:	LayoutManager(static_cast<LayoutManager>(rhs)),
				cols(rhs.cols),
				rows(rhs.rows)
		{
		}

		GridLayout& GridLayout::operator=(const GridLayout& rhs)
		{
			GridLayout temp(rhs);
			swap(temp);
			return *this;
		}

		void GridLayout::swap(GridLayout& rhs) throw()
		{
			std::swap(rows,rhs.rows);
			std::swap(cols,rhs.cols);
		}

		const util::Dimension GridLayout::preferredLayoutSize(const Container* parent) const
		{
			util::Insets insets = parent->getInsets();
			int numComponents = parent->getNumberOfChildren();

			int numRows = getRows();
			int numCols = getColumns();

			if(numRows > 0)
			{
				numCols = (numComponents + numRows - 1) / numRows;
			}
			else
			{
				numRows = (numComponents + numCols - 1) / numCols;
			}
			ComponentList childList = parent->getChildren();

			int width = 0;
			int height = 0;

			ComponentList::const_iterator iter;
			for(iter = childList.begin(); iter != childList.end(); ++iter)
			{
				width = std::max((*iter)->getPreferredSize().width,width);
				height = std::max((*iter)->getPreferredSize().height,height);
			}
			return util::Dimension(insets.left + insets.right + numCols * width + (numCols-1)*getHgap(),insets.top + insets.bottom + numRows * height + (numRows-1)*getVgap());
		}

		void GridLayout::layoutContainer(const Container* parent)
		{
			util::Insets insets = parent->getInsets();
			int numComponents = parent->getNumberOfChildren();

			int numRows = rows;
			int numCols = cols;


			if(numRows > 0)
			{
				numCols = (numComponents + numRows - 1) / numRows;
			}
			else
			{
				numRows = (numComponents + numCols - 1) / numCols;
			}
			
			int width = parent->getBounds().width - (insets.left + insets.right);
			int height = parent->getBounds().height - (insets.top + insets.bottom);
			width = (width - (numCols - 1) * getHgap()) / numCols;
			height = (height - (numRows - 1) * getVgap()) / numRows;

			ComponentList childList = parent->getChildren();
			ComponentList::const_iterator iter;

			int x = insets.left;
			int y = insets.top;

			int i = 1;

			// there is probably a more efficient and correct way to do this,
			// but after a wild night out, I'm happy that it works at all.
			for(iter = childList.begin(); iter != childList.end(); ++iter)
			{
				(*iter)->setBounds(x,y,width,height);

				if(numCols > numRows)
				{
					if(i >= numCols)
					{
						y += height + getVgap();
						x  = insets.left;
						i = 0;
					}
					else
					{
						x += width + getHgap();
					}
				}
				else
				{
					if(i >= numRows)
					{
						x += width + getHgap();
						y = insets.top;
						i = 0;
					}
					else
					{
						y += height + getVgap();
					}
				}
				i++;
			}
		}

		void GridLayout::setColumns(int cols)
		{
			this->cols = cols;
		}

		int GridLayout::getColumns() const
		{
			return cols;
		}

		void GridLayout::setRows(int rows)
		{
			this->rows = rows;
		}

		int GridLayout::getRows() const
		{
			return rows;
		}
	}
}