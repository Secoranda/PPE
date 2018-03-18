
# Laboratory work analysis
## Description 
I created a Windows application.

Main idea of the app is a List of a Crew's members, that entered per one person's name in first input box, can be add using Add button to the second input box as a list. Pressing on Clear button the whole list is deleted. If user need to change or delete information about one member is enough to press on right mouse click and a pop-up menu will appear (with 2 options: Rename or Delete). Choosing Delete, the selected member will be deleted and by choosing Rename, a dialog box will appear with a input box for new changes and a button Rename that will save the changes. A disadvantage is that: in case no name will be entered in the rename box than in the list will be a empty line.

Based on child window controls, were implemented 2 scrolls that change the window's weight and height. So is possible to change the size with one unit or using SB_THUMBTRACK() is possible to maximize and minimize as much as user needs.

On upper part of the window is a Menu that has 2 fields (File and Keyboard). Pressing on File, user has 2 options: About and Exit. On Exit the window will close and on About, a window will appear with a message: "Add members of a team in a simple List".

Second field: Keyboard will have 2 subfields: Change background color (CTRL+C) and Minimize the screen (CTRL+SPACE). So, or pressing on menu options or having the keyboard combinations from brackets, user will get the same result. Minize the screen, will have only one option of minimized size, however change color has a loop of choosing random color for the background. As a consequence, each time user will choose this option, the window's background will change.

Specific for this Win app is icon and cursor implementation. So, Icon will appear on task bar and on window's bar. About cursor: it is a yellish cursor that will appear not only on background but also on all window's objects because of WM_SETCURSOR() case.



## Was implemented
### Mandatory Objectives
1. Display a dialog box on some event (ex. on clicking some button)
2. Add a system menu to your application with at least 3 items (add actions to that items)
3. Add a scroll bar that will change any visible parameter of any other element (color of a text)
4. Hook keyboard input. Add 2 custom events for 2 different keyboard combinations (ex. change window background on ctrl+space)

### Objectives with points
1. Add a listbox and attach some events when any element is accessed (clicked) (2pt)
2. Add 2 scroll bars that will manage main window size or position (1pt)
3. Customize your application by adding an icon and using different cursor in application  (1pt)

