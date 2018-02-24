# Laboratory work analysis
## Description 
I created a Windows application.

Based on idea of a Shopping List, I created 2 text inputs to the window, that have the same input box size but 
different style (one by default, other created by me). 

I did 2 buttons, one "Add" and other "Remove"(one by default, other changed by me). 
With button "Add" from the first input box, the shopping list through function SendMessage()will be copied to the second box.
The cursor will be alwasy from new line.
Pressing on button "Remove" both inputs will be cleaned. Is also possible to delete by one character, if box2 is changed to 1.

Also, texts that appear on the window, I did through 2 methods. 
First one, Title (Shopping List) made by function DrawText() with new style and a sentence (Add item to buy) made using defined label,
because it changes position to center of the window when the window is maximizing, and comes back to first position when minimizing.

I gaved limited size for window at maximizing and maximizing it.

When maximizing the window, first of all a new window will appear, a message (Unable to maximize) with OK choice. 
After closing the message window, the main window will maximize. 
Same with minimizing or roll down the window. It will minimize and after that will apper a message window (Unable to minimize).
In case of close buttom. First the main window will change its position, then a message window will appear (Do you want to close the window?)
with Yes or No option.

## Disadvantages
 1. Input from the first input box will be copied to the second, which is bad in case we have to add only one new item, it will copy all items.
 2. When maximize the screen and move it pulling the bar, it will restore first size. It doesn't save the maximized sized.
 


