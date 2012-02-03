/*
 * Copyright (c) 2003-2006, Bram Stein
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions 
 * are met:
 * 
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer. 
 *  2. Redistributions in binary form must reproduce the above copyright 
 *     notice, this list of conditions and the following disclaimer in the 
 *     documentation and/or other materials provided with the distribution. 
 *  3. The name of the author may not be used to endorse or promote products 
 *     derived from this software without specific prior written permission. 
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR "AS IS" AND ANY EXPRESS OR IMPLIED 
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO 
 * EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY 
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, 
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "./FocusManager.h"
#include "./Component.h"
#include "./event/FocusEvent.h"
#include "./component/Window.h"
#include "./event/WindowEvent.h"
#include "./event/KeyEvent.h"
#include "./component/Menu.h"
#include "./component/MenuItem.h"

namespace ui
{
	FocusManager::FocusManager()
		:	permanentFocusOwner(0),
			focusOwner(0),
			oppositeComponent(0)
	{
	}

	void FocusManager::setPermanentFocusOwner(Component* c)
	{
		if(c == permanentFocusOwner)
			return;

		// we assign early so that a call to get(Permanent)FocusOwner
		// in a focus listener returns the correct result.
		Component *tmp = permanentFocusOwner;
		permanentFocusOwner = c;

		if(tmp != 0)
		{
			
			
			event::FocusEvent focusLostEvent(tmp,event::FocusEvent::FOCUS_LOST,false,c);
			tmp->processFocusEvent(focusLostEvent);
		}
	
		if(c != 0)
		{
			event::FocusEvent focusGainedEvent(c,event::FocusEvent::FOCUS_GAINED,false,tmp);
			c->processFocusEvent(focusGainedEvent);

			/*
			// if this component is member of a window, we also need to set focus to the
			// window.
			for(Component* parent = c->getParent(); parent != 0;)
			{	
				if(parent->isRootContainer())
				{
					// set activated
					Window* window = static_cast<Window*>(parent);
					event::WindowEvent event(parent,event::WindowEvent::ACTIVATED);
					window->processWindowEvent(event);
				}
				parent = parent->getParent();
			}
			*/
		}
		setFocusOwner(0);
		focusOwner = permanentFocusOwner;
	}

	Component* FocusManager::getPermanentFocusOwner()
	{
		return permanentFocusOwner;
	}

	void FocusManager::setFocusOwner(Component* c)
	{	
		if(c == focusOwner)
			return;

		Component *tmp = focusOwner;
		focusOwner = c;

		if(tmp != 0 && tmp != permanentFocusOwner)
		{
			event::FocusEvent focusLostEvent(tmp,event::FocusEvent::FOCUS_LOST,true,c);
			tmp->processFocusEvent(focusLostEvent);
		}

		if(c != 0)
		{
			event::FocusEvent focusGainedEvent(c,event::FocusEvent::FOCUS_GAINED,true,tmp);
			c->processFocusEvent(focusGainedEvent);
		}
	}
	
	Component* FocusManager::getFocusOwner()
	{
		return focusOwner;
	}

	void FocusManager::buildStack(Component *node, bool backward)
	{
		ComponentList list = node->getChildren();
		ComponentList::iterator iter;

		if(!backward)
		{
			if(node->isVisible() && node->hasFocusListener())
			{
				stack.push_back(node);
			}
		}


		for(iter = list.begin(); iter != list.end(); ++iter)
		{
			buildStack((*iter),backward);
		}

		if(node->isRootContainer())
		{
			// Rather nasty hack, since windows are not part
			// of the normal component hierarchy. Luckely,
			// all root containers are derived from Window (Frame and Dialog).
			// Sigh.
			Window * tmp = static_cast<Window *>(node);
			if(tmp)
			{
				WindowList children = tmp->getOwnedWindows();
				WindowList::const_iterator iter;
				for(iter = children.begin(); iter != children.end(); ++iter)
				{
					if((*iter)->isVisible())
					{
						buildStack((*iter),backward);
					}
				}
			}
		}

		if(backward)
		{
			if(node->isVisible() && node->hasFocusListener())
			{
				stack.push_back(node);
			}
		}
	}

	void FocusManager::keyPressed(int keyCode, int modifier)
	{
		if(permanentFocusOwner != 0 && focusOwner != 0)
		{
			if(permanentFocusOwner != focusOwner)
			{
				event::KeyEvent keyEvent(focusOwner,event::KeyEvent::KEY_PRESSED,keyCode,modifier);
				focusOwner->processKeyEvent(keyEvent);
			}
			else
			{
				event::KeyEvent keyEvent(permanentFocusOwner,event::KeyEvent::KEY_PRESSED,keyCode,modifier);
				permanentFocusOwner->processKeyEvent(keyEvent);
			}
		}
	}

	void FocusManager::keyReleased(int keyCode, int modifier)
	{
		if(permanentFocusOwner != 0 && focusOwner != 0)
		{
			if(permanentFocusOwner != focusOwner)
			{
				event::KeyEvent keyReleasedEvent(focusOwner,event::KeyEvent::KEY_RELEASED,keyCode,modifier);
				focusOwner->processKeyEvent(keyReleasedEvent);

				event::KeyEvent keyTypedEvent(focusOwner,event::KeyEvent::KEY_TYPED,keyCode,modifier);
				focusOwner->processKeyEvent(keyTypedEvent);
			}
			else
			{
				event::KeyEvent keyReleasedEvent(permanentFocusOwner,event::KeyEvent::KEY_RELEASED,keyCode,modifier);
				permanentFocusOwner->processKeyEvent(keyReleasedEvent);

				event::KeyEvent keyTypedEvent(permanentFocusOwner,event::KeyEvent::KEY_TYPED,keyCode,modifier);
				permanentFocusOwner->processKeyEvent(keyTypedEvent);

			}
		}
	}

	void FocusManager::focusRightComponent()
	{
		//fprintf(stderr,"focus next called\n");
		Component * root(permanentFocusOwner);
		Component * goal(permanentFocusOwner);

		if(permanentFocusOwner != focusOwner)
		{
			goal = focusOwner;
		}
		

		if(permanentFocusOwner->getParent() != 0)
		{
			for(root = permanentFocusOwner->getParent(); root->getParent() != 0;)
			{
				root = root->getParent();
			}
		}

		buildStack(root,false);
/*
		std::deque<Component *>::iterator iter;

		for(iter = stack.begin(); iter != stack.end(); ++iter)
		{
				if((*iter)->getThemeName() == "Menu")
				{
					fprintf(stderr,"%s: %s",(*iter)->getThemeName().c_str(),static_cast<Menu *>((*iter))->getText().c_str());
				}
				else if((*iter)->getThemeName() == "MenuItem")
				{
					fprintf(stderr,"%s: %s",(*iter)->getThemeName().c_str(),static_cast<MenuItem *>((*iter))->getText().c_str());
				}

				if((*iter) == goal)
				{
					fprintf(stderr,"<---\n");
				}
				else
				{
					fprintf(stderr,"\n");
				}		
		}
*/
		std::deque<Component *> back(stack);

		while(!stack.empty())
		{
			if(stack.front() == goal)
			{
				if(stack.size() != 1)
				{
					stack.pop_front();

					/*
					if(stack.front()->getThemeName() == "Menu")
					{
						fprintf(stderr,"-->%s: %s",stack.front()->getThemeName().c_str(),static_cast<Menu *>(stack.front())->getText().c_str());
					}
					else if(stack.front()->getThemeName() == "MenuItem")
					{
						fprintf(stderr,"-->%s: %s",stack.front()->getThemeName().c_str(),static_cast<MenuItem *>(stack.front())->getText().c_str());
					}
					*/
					if(stack.front()->canHoldPermanentFocus())
					{
						setPermanentFocusOwner(stack.front());
					}
					else
					{
						setFocusOwner(stack.front());
					}
				}
				else
				{
					if(back.back()->canHoldPermanentFocus())
					{
						setPermanentFocusOwner(back.back());
					}
					else
					{
						setFocusOwner(back.back());
					}
				}
				break;
			}
			stack.pop_front();
			back.pop_back();
		}
		
		stack.clear();
	}

	void FocusManager::focusLeftComponent()
	{
		Component * root(permanentFocusOwner);
		Component * goal(permanentFocusOwner);

		if(permanentFocusOwner != focusOwner)
		{
			goal = focusOwner;
		}

		if(permanentFocusOwner->getParent() != 0)
		{
			for(root = permanentFocusOwner->getParent(); root->getParent() != 0;)
			{
				root = root->getParent();
			}
		}

		buildStack(root, true);

		std::deque<Component *> back(stack);

		while(!stack.empty())
		{
			if(stack.back() == goal)
			{
				if(stack.size() != 1)
				{
					stack.pop_back();

					if(stack.back()->canHoldPermanentFocus())
					{
						setPermanentFocusOwner(stack.back());
					}
					else
					{
						setFocusOwner(stack.back());
					}
				}
				else
				{
					if(back.front()->canHoldPermanentFocus())
					{
						setPermanentFocusOwner(back.front());
					}
					else
					{
						setFocusOwner(back.front());
					}
				}
				break;
			}
			stack.pop_back();
			back.pop_front();
		}
		stack.clear();
	}
}